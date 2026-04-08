#include "mysql_client.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

void display_errno_and_exit_client();


MySQLClient::MySQLClient() {

}

void MySQLClient::startClient() {
    int yes = 1;

    int addr_info_status;
    int connect_status;

    addrinfo hints;
    addrinfo* results = nullptr;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    
    addr_info_status = getaddrinfo(nullptr, MYSQL_PORT.c_str(), &hints, &results);

    if (addr_info_status != 0) {
        std::cout << "MySQL Client - Get Address Info Error: " << gai_strerror(addr_info_status) << std::endl;
    }
    
    addrinfo* p = nullptr;
    for (p = results; p != nullptr; p = p->ai_next) {
        sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sock_fd == -1) {
            std::cout << "MySQL Client - Error: could not get socket file descriptor" << std::endl;
            continue;
        }

        connect_status = connect(sock_fd, p->ai_addr, p->ai_addrlen);
        if (connect_status == -1) {
            std::cout << "MySQL Client - Error: could not connect" << std::endl;
            close(sock_fd);
            display_errno_and_exit_client();
            continue;
        }

        break;
    }

    if (p == nullptr) {
        std::cout << "MySQL Client - Error: failed to connect" << std::endl;
        exit(1);
    
    }
    clientStarted = true;

    char buffer[BUFFER_LEN];
    int bytes_in_buffer = 0;

    
    memset(buffer, 0, BUFFER_LEN);
    bytes_in_buffer = recv(sock_fd, &buffer, BUFFER_LEN, 0);
    if (bytes_in_buffer == 0) std::cout << "MySQL Client - Empty Message Recieved" << std::endl;

    std::cout << std::string(buffer, bytes_in_buffer) << std::endl;

    freeaddrinfo(results);
 
}

void MySQLClient::stopClient() {
    close(sock_fd);
    clientStarted = false;
}

std::string MySQLClient::sendReqeust(std::string request) {
    if (!clientStarted) {
        throw MySQLClientNotStarted();
    }

    char buffer[BUFFER_LEN];
    int bytes_in_buffer = 0;

    send(sock_fd, request.c_str(), request.length(), 0);
    
    memset(buffer, 0, BUFFER_LEN);
    bytes_in_buffer = recv(sock_fd, &buffer, BUFFER_LEN, 0);
    if (bytes_in_buffer == 0) std::cout << "MySQL Client - Empty Message Recieved" << std::endl;

    std::string response = std::string(buffer, bytes_in_buffer);
    
    return response;
}

MySQLClientNotStarted::MySQLClientNotStarted() = default;

const char* MySQLClientNotStarted::what() {
    return "Tried to make MySQL Request while MySQL client is not started!";
}


void display_errno_and_exit_client() {
    std::cout << "Client - Errno Code: " << errno << std::endl;
    exit(1);
}
