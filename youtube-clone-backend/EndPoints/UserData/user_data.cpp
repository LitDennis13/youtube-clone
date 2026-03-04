#include "user_data.h"
#include "../../HttpImplementation/http_implementation.h"
#include <iostream>


void FetchUserData::main_function() {
    check_method_and_content_type(HTTPMethods::GET, HTTPContentType::None);
    
    JsonData user_data;
    JsonData user_status("userStatus", "-2", false); // -2: no login attempted -1: user does not exist, 0: password mismatch, 1: user exists and password matchs
    JsonData user_id("userID", "-1", false);
    JsonData username("username", "", true);
    JsonData user_logged_in("userLoggedIn", "false", false);
    user_data.add_entry(user_status);
    user_data.add_entry(username);
    user_data.add_entry(user_id);
    user_data.add_entry(user_logged_in);
    

    response.set_status_code(HTTPSatusCode::x200);
    response.add_header({HTTPHeader::ContentType, content_type_to_string(HTTPContentType::ApplicationJson)});
    response.set_content(user_data.get_json_as_string());
}

void FetchUserData::request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) {

}




void Authentication::main_function() {
    check_method_and_content_type(HTTPMethods::POST, HTTPContentType::ApplicationJson);
    
    std::cout << "Username: " << std::get<JsonData>(data)["username"] << std::endl;
    std::cout << "Password: " << std::get<JsonData>(data)["password"] << std::endl;
    std::cout << "Create User: " << std::get<JsonData>(data)["createUser"] << std::endl;

    JsonData tokenJson;
    JsonData token("token", "random ahh thing", true);
    tokenJson.add_entry(token);
    
    

    response.set_status_code(HTTPSatusCode::x200);
    response.add_header({HTTPHeader::ContentType, content_type_to_string(HTTPContentType::ApplicationJson)});
    response.set_content(tokenJson.get_json_as_string());
}

void Authentication::request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) {

}