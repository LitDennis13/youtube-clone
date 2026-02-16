#pragma once
#include "../HttpImplementation/http_implementation.h"
#include "../JsonData/json_data.h"
#include <iostream>
#include <variant>

using Data = std::variant<std::string, JsonData>;

class EndPointType {
protected:
    std::string end_point_name;
    HttpRequest request;
    HttpResponse response;
    Data data;
    
    void check_method_and_content_type(HTTPMethods correct_method, HTTPContentType correct_content_type);
    virtual void request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) = 0;

public:
    EndPointType(HttpRequest new_request, std::string new_end_point_name);

    void http_options_handler();

    virtual void main_function() = 0;

    std::string get_response();
};

class WrongHTTPMethod: public std::exception {
private:
    std::string error_end_point;
    HTTPMethods incorrect_method;
    HTTPMethods correct_method;
    std::string return_message;
public:
    WrongHTTPMethod(std::string new_error_end_point, HTTPMethods new_incorrect_method, HTTPMethods new_correct_method);

    const char* what();
};

class WrongHTTPContentType: public std::exception {
private:
    std::string error_end_point;
    HTTPContentType incorrect_content_type;
    HTTPContentType correct_content_type;
    std::string return_message;

public:
    WrongHTTPContentType(std::string new_error_end_point, HTTPContentType new_incorrect_content_type, HTTPContentType new_correct_content_type);

    const char* what();
};


std::string end_point_handler(std::string raw_request);