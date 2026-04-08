#include "Server/server.h"
// #include "Base64Encode/base_64_encode.h"
#include "MySQLClient/mysql_client.h"
#include <sstream>
int main() {
    // run_server();

    MySQLClient mysql_client;
    mysql_client.startClient();

    // std::string test_request = "GET / HTTP/1.1\r\nAccept: */*\r\nHost: localhost:3490\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\n\r\n";
    std::string test_request = "140000000353454C454354202A2046524F4D207573657273";
    std::cout << test_request << std::endl;
    
    
    // std::cout << mysql_client.sendReqeust(test_request) << std::endl;

    
    return 0;
}