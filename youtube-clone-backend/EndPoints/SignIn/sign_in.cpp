#include "sign_in.h"
#include "../../HttpImplementation/http_implementation.h"
#include <iostream>

void SignIn::main_function() {
    check_method_and_content_type(HTTPMethods::POST, HTTPContentType::ApplicationJson);
    
    std::cout << content_type_to_string(request.get_content_type()) << std::endl;

    std::cout << std::get<JsonData>(data).get_json_as_string() << std::endl;
    std::cout << std::get<JsonData>(data)["username"] << std::endl;
    

    response.set_status_code(HTTPSatusCode::x200);
    response.add_header({HTTPHeader::ContentType, content_type_to_string(HTTPContentType::TextPlain)});
    response.set_content("Sign in");
}

void SignIn::request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) {

}