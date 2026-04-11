#pragma once
#include <iostream>

const std::string MYSQL_PORT = "3306";

struct HandShakePacket {
    int payload_length;
    int sequence_id;
    int protocol_version;
    std::string server_version;
    int connection_id;
    std::string auth_plugin_data_part_1;
    int capability_flags_1;
    int character_set;
    int status_flags;
    int capability_flags_2;
    int auth_plugin_data_length;
    std::string auth_plugin_data_part_2;
    std::string auth_plugin_name;
};


class MySQLClient {
private:
    const int BUFFER_LEN = 8192;
    bool clientStarted;
    int sock_fd;

    HandShakePacket hand_shake_packet;

    void hand_shake_packet_parse(char buffer[], const int len);

public:
    MySQLClient();

    void start_client();
    void stop_client();

    std::string send_reqeust(std::string request);
};

class MySQLClientNotStarted: public std::exception {
public:
    MySQLClientNotStarted();

    const char* what();
};