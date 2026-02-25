#include "server.h"
#include "../EndPointHandler/end_point_handler.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>


void display_errno_and_exit();

void sigchld_handler(int sig);

void run_server() {
    int yes = 1;

    int addr_info_status;
    int set_sock_opt_status;
    int bind_status;
    int listen_status;
    int send_status;
    int sig_action_status;
    int sock_fd;
    int new_sock_fd;

    addrinfo hints;
    addrinfo* results = nullptr;

    sockaddr_storage connected_Address;
    socklen_t connected_address_len = (socklen_t)sizeof(sockaddr_storage);

    char buffer[BUFFER_LEN];
    int bytes_in_buffer = 0;

    struct sigaction sa;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    
    addr_info_status = getaddrinfo(nullptr, PORT.c_str(), &hints, &results);

    if (addr_info_status != 0) {
        std::cout << "Get Address Info Error: " << gai_strerror(addr_info_status) << std::endl;
    }

    addrinfo* p = nullptr;
    for (p = results; p != nullptr; p = p->ai_next) {
        sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sock_fd == -1) {
            std::cout << "Error: could not get socket file descriptor" << std::endl;
            continue;
        }

        set_sock_opt_status = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
        if (set_sock_opt_status == -1) {
            std::cout << "Error: could not set socket option" << std::endl;
            display_errno_and_exit();
        }

        bind_status = bind(sock_fd, p->ai_addr, p->ai_addrlen);
        if (bind_status == -1) {
            close(sock_fd);
            std::cout << "Error: could not bind socket" << std::endl;
            continue;
        }
        break;
    }

    freeaddrinfo(results);

    if (p == nullptr) {
        std::cout << "Error: server could not bind" << std::endl;
        display_errno_and_exit();
    }

    listen_status = listen(sock_fd, BACK_LOG);
    if (listen_status == -1) {
        std::cout << "Error: could not listen" << std::endl;
        display_errno_and_exit();
    }
    
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART;
    sig_action_status = sigaction(SIGCHLD, &sa, nullptr);

    if (sig_action_status == -1) {
        std::cout << "Error: Sigaction" << std::endl;
        display_errno_and_exit();
    }

    while (true) {
        connected_address_len = (socklen_t)sizeof(sockaddr_storage);
        new_sock_fd = accept(sock_fd, (sockaddr*)&connected_Address, &connected_address_len);
        if (new_sock_fd == -1) {
            std::cout << "Error: could not accept" << std::endl;
        }

        if (!fork()) {
            close(sock_fd);
            memset(buffer, 0, BUFFER_LEN);
            bytes_in_buffer = recv(new_sock_fd, &buffer, BUFFER_LEN, 0);
            if (bytes_in_buffer == 0) std::cout << "Empty Message Recieved" << std::endl;

            std::string http_request = std::string(buffer, bytes_in_buffer);
            
            std::string http_response = end_point_handler(http_request);
            
            send_status = send(new_sock_fd, http_response.c_str(), http_response.size(), 0);
            std::cout << "SENT " << send_status << " Bytes" << std::endl;
            if (send_status == -1) {
                std::cout << "Error: could not send data" << std::endl;
                display_errno_and_exit();
            }

            close(new_sock_fd);
            exit(0);
        }
        close(new_sock_fd);
    }    
}


void display_errno_and_exit() {
    std::cout << "Errno Code: " << errno << std::endl;
    exit(1);
}

void sigchld_handler(int sig) {
    int oldErrno = errno;
    while (waitpid(-1, nullptr, WNOHANG) > 0);
    errno = oldErrno;
}