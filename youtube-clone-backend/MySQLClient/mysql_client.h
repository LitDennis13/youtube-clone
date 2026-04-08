#pragma once
#include <iostream>


const std::string MYSQL_PORT = "3306";

class MySQLClient {
private:
    const int BUFFER_LEN = 8192;
    bool clientStarted;
    int sock_fd;

public:
    MySQLClient();

    void startClient();
    void stopClient();

    std::string sendReqeust(std::string request);
};

class MySQLClientNotStarted: public std::exception {
public:
    MySQLClientNotStarted();

    const char* what();
};