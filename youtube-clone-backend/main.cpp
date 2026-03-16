#include "Server/server.h"
#include "Base64Encode/base_64_encode.h"

int main() {
    // run_server();
    std::string binary = std::string("\x00\x01\x02", 3);
    std::cout << binary << std::endl;

    std::cout << base_64_encode("e") << std::endl;
    std::cout << (9 & 0x3) << std::endl;
    return 0;
}