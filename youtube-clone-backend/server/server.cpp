#include "server.h"
#include "../EndPointHandler/endPointHandler.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>


void displayErrnoAndExit();

void sigchldHandler(int sig);

void runServer() {
    int yes = 1;

    int addrInfoStatus;
    int setSockOptStatus;
    int bindStatus;
    int listenStatus;
    int sendStatus;
    int sigActionStatus;
    int sockFD;
    int newSockFD;

    addrinfo hints;
    addrinfo* results = nullptr;

    sockaddr_storage connectedAddress;
    socklen_t connectedAddressLen = (socklen_t)sizeof(sockaddr_storage);

    char buffer[BUFFER_LEN];
    int bytesInBuffer = 0;

    struct sigaction sa;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    
    addrInfoStatus = getaddrinfo(nullptr, PORT.c_str(), &hints, &results);

    if (addrInfoStatus != 0) {
        std::cout << "Get Address Info Error: " << gai_strerror(addrInfoStatus) << std::endl;
    }

    addrinfo* p = nullptr;
    for (p = results; p != nullptr; p = p->ai_next) {
        sockFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockFD == -1) {
            std::cout << "Error: could not get socket file descriptor" << std::endl;
            continue;
        }

        setSockOptStatus = setsockopt(sockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
        if (setSockOptStatus == -1) {
            std::cout << "Error: could not set socket option" << std::endl;
            displayErrnoAndExit();
        }

        bindStatus = bind(sockFD, p->ai_addr, p->ai_addrlen);
        if (bindStatus == -1) {
            close(sockFD);
            std::cout << "Error: could not bind socket" << std::endl;
            continue;
        }
        break;
    }

    freeaddrinfo(results);

    if (p == nullptr) {
        std::cout << "Error: server could not bind" << std::endl;
        displayErrnoAndExit();
    }

    listenStatus = listen(sockFD, BACK_LOG);
    if (listenStatus == -1) {
        std::cout << "Error: could not listen" << std::endl;
        displayErrnoAndExit();
    }
    
    sa.sa_handler = sigchldHandler;
    sa.sa_flags = SA_RESTART;
    sigActionStatus = sigaction(SIGCHLD, &sa, nullptr);

    if (sigActionStatus == -1) {
        std::cout << "Error: Sigaction" << std::endl;
        displayErrnoAndExit();
    }

    while (true) {
        connectedAddressLen = (socklen_t)sizeof(sockaddr_storage);
        newSockFD = accept(sockFD, (sockaddr*)&connectedAddress, &connectedAddressLen);
        if (newSockFD == -1) {
            std::cout << "Error: could not accept" << std::endl;
        }

        if (!fork()) {
            close(sockFD);
            memset(buffer, 0, BUFFER_LEN);
            bytesInBuffer = recv(newSockFD, &buffer, BUFFER_LEN, 0);
            if (bytesInBuffer == 0) std::cout << "Empty Message Recieved" << std::endl;

            std::string httpRequest = std::string(buffer, bytesInBuffer);
            
            std::string httpResponse = endPointerHandler(httpRequest);
            sendStatus = send(newSockFD, httpResponse.c_str(), httpResponse.size(), 0);
            std::cout << "SENT " << sendStatus << " Bytes" << std::endl;
            if (sendStatus == -1) {
                std::cout << "Error: could not send data" << std::endl;
                displayErrnoAndExit();
            }

            close(newSockFD);
            exit(0);
        }
        close(newSockFD);
    }    
}


void displayErrnoAndExit() {
    std::cout << "Errno Code: " << errno << std::endl;
    exit(1);
}

void sigchldHandler(int sig) {
    int oldErrno = errno;
    while (waitpid(-1, nullptr, WNOHANG) > 0);
    errno = oldErrno;
}