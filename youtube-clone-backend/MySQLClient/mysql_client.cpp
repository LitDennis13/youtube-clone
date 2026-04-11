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

void MySQLClient::hand_shake_packet_parse(char buffer[], const int len) {
    int bf = 0; // buffer position
    
    hand_shake_packet.payload_length = ((int)buffer[bf + 2] << 16) + ((int)buffer[bf + 1] << 8) + ((int)buffer[bf]);
    bf += 3;

    hand_shake_packet.sequence_id = (int)buffer[bf];
    bf++;
    
    hand_shake_packet.protocol_version = (int)buffer[bf];
    bf++;

    hand_shake_packet.server_version = "";
    while (buffer[bf] != 0) {
        hand_shake_packet.server_version += buffer[bf];
        bf++;
    }
    bf++;


    hand_shake_packet.connection_id = ((int)buffer[bf + 3] << 24) + ((int)buffer[bf + 2] << 16) + ((int)buffer[bf + 1] << 8) + ((int)buffer[bf]);
    bf += 4;

    hand_shake_packet.auth_plugin_data_part_1 = "";
    while (buffer[bf] != 0) {
        hand_shake_packet.auth_plugin_data_part_1 += buffer[bf];
        bf++;
    }
    bf++;


    hand_shake_packet.capability_flags_1 = ((int)buffer[bf + 1] << 8) + ((int)buffer[bf]);
    bf += 2;

    hand_shake_packet.character_set = ((int)buffer[bf]);
    bf++;

    hand_shake_packet.status_flags = ((int)buffer[bf + 1] << 8) + ((int)buffer[bf]);
    bf += 2;

    hand_shake_packet.capability_flags_2 = ((int)buffer[bf + 1] << 8) + ((int)buffer[bf]);
    bf += 2;

    hand_shake_packet.auth_plugin_data_length = ((int)buffer[bf]);
    bf++;

    bf += 10;
    hand_shake_packet.auth_plugin_data_part_2 = "";
    
    int x = bf + hand_shake_packet.auth_plugin_data_length - hand_shake_packet.auth_plugin_data_part_1.length();
    for (; bf < x; bf++) {
        hand_shake_packet.auth_plugin_data_part_2 += buffer[bf];
    }

    hand_shake_packet.auth_plugin_name = "";
    while (buffer[bf] != 0) {
        hand_shake_packet.auth_plugin_name += buffer[bf];
        bf++;
    }
    bf++;

    std::cout << hand_shake_packet.auth_plugin_data_part_1.length() + hand_shake_packet.auth_plugin_data_part_2.length() << std::endl;
    std::cout << "Payload Length: " << hand_shake_packet.payload_length << std::endl;
    std::cout << "Sequence ID: " << hand_shake_packet.sequence_id << std::endl;
    std::cout << "Protocol Version: " << hand_shake_packet.protocol_version << std::endl;
    std::cout << "Server Version: " << hand_shake_packet.server_version << std::endl;
    std::cout << "Connection ID: " << hand_shake_packet.connection_id << std::endl;
    std::cout << "Auth Plugin Data Part 1: " << hand_shake_packet.auth_plugin_data_part_1 << std::endl;
    std::cout << "Cabability Flags 1: " << hand_shake_packet.capability_flags_1 << std::endl;
    std::cout << "Character Set: " << hand_shake_packet.character_set << std::endl;
    std::cout << "Status Flags: " << hand_shake_packet.status_flags << std::endl;
    std::cout << "Cabability Flags 2: " << hand_shake_packet.capability_flags_2 << std::endl;
    std::cout << "Auth Plugin Data Length: " << hand_shake_packet.auth_plugin_data_length << std::endl;
    std::cout << "Auth Plugin Data Part 2: " << hand_shake_packet.auth_plugin_data_part_2 << std::endl;
    std::cout << "Auth Plugin Name: " << hand_shake_packet.auth_plugin_name << std::endl;
    std::cout << "Payload Length: " << len << std::endl;

}

void MySQLClient::start_client() {
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

    hand_shake_packet_parse(buffer, bytes_in_buffer);

    freeaddrinfo(results);
}

void MySQLClient::stop_client() {
    close(sock_fd);
    clientStarted = false;
}

std::string MySQLClient::send_reqeust(std::string request) {
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
