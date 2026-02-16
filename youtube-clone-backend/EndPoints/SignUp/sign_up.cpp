#include "sign_up.h"
#include "../../HttpImplementation/http_implementation.h"


void SignUp::main_function() {
    response.set_status_code(HTTPSatusCode::x200);
    response.add_header({HTTPHeader::ContentType, "text/plain"});
    response.set_content("Sign Up");
}

void SignUp::request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) {

}