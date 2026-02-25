#include "authentication.h"
#include "../../HttpImplementation/http_implementation.h"
#include <iostream>

void Authentication::main_function() {
    check_method_and_content_type(HTTPMethods::POST, HTTPContentType::ApplicationJson);
    
    std::cout << "Username: " << std::get<JsonData>(data)["username"] << std::endl;
    std::cout << "Password: " << std::get<JsonData>(data)["password"] << std::endl;
    std::cout << "Create User: " << std::get<JsonData>(data)["createUser"] << std::endl;

    JsonData user_data;
    JsonData userid("userID", "100");
    JsonData username("username", "test username demxge");
    user_data.add_entry(username);
    user_data.add_entry(userid);
    

    response.set_status_code(HTTPSatusCode::x200);
    response.add_header({HTTPHeader::ContentType, content_type_to_string(HTTPContentType::ApplicationJson)});
    response.set_content(user_data.get_json_as_string());
}

void Authentication::request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) {

}