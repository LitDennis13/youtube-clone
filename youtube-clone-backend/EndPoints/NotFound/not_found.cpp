#include "not_found.h"
#include "../../HttpImplementation/http_implementation.h"
#include <iostream>


void NotFound::main_function() {
    response.set_status_code(HTTPSatusCode::x404);
}

void NotFound::request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) {

}