#include "http_implementation.h"
#include <iostream>
#include <vector>

std::string to_lower(std::string input) {
    std::string result = "";
    for (char &c : input) {
        if ((int)c >= 65 && (int)c <= 90) {
            result += (char)((int)c + 32);
        }
        else {
            result += c;
        }
    }

    return result;
}

std::string http_header_to_string(HTTPHeader header) {
    switch (header) {
        case HTTPHeader::Accept: {
            return "Accept";
            break;
        }
        case HTTPHeader::AcceptEncoding: {
            return "Accept-Encoding";
            break;
        }
        case HTTPHeader::AcceptLanguage: {
            return "Accept-Language";
            break;
        }
        case HTTPHeader::AccessControlAllowHeaders: {
            return "Access-Control-Allow-Headers";
            break;
        }
        case HTTPHeader::AccessControlRequestHeaders: {
            return "Access-Control-Request-Headers";
            break;
        }
        case HTTPHeader::AccessControlAllowMethods: {
            return "Access-Control-Allow-Methods";
            break;
        }
        case HTTPHeader::AccessControlRequestMethod: {
            return "Access-Control-Request-Method";
            break;
        }
        case HTTPHeader::AccessControlAllowOrigin: {
            return "Access-Control-Allow-Origin";
            break;
        }
        case HTTPHeader::CacheControl: {
            return "Cache-Control";
            break;
        }
        case HTTPHeader::Connection: {
            return "Connection";
            break;
        }
        case HTTPHeader::ContentType: {
            return "Content-Type";
            break;
        }
        case HTTPHeader::ContentLength: {
            return "Content-Length";
            break;
        }
        case HTTPHeader::Host: {
            return "Host";
            break;
        }
        case HTTPHeader::Referer: {
            return "Referer";
            break;
        }
        case HTTPHeader::Origin: {
            return "Origin";
            break;
        }
        case HTTPHeader::PostmanToken: {
            return "Postman-Token";
            break;
        }
        case HTTPHeader::SecChUa: {
            return "sec-ch-ua";
            break;
        }
        case HTTPHeader::SecChUaPlatform: {
            return "sec-ch-ua-platform";
            break;
        }
        case HTTPHeader::SecChUaMobile: {
            return "sec-ch-ua-mobile";
            break;
        }
        case HTTPHeader::SecFetchMode: {
            return "Sec-Fetch-Mode";
            break;
        }
        case HTTPHeader::SecFetchSite: {
            return "Sec-Fetch-Site";
            break;
        }
        case HTTPHeader::SecFetchDest: {
            return "Sec-Fetch-Dest";
            break;
        }
        case HTTPHeader::SecFetchUser: {
            return "sec-fetch-user";
            break;
        }
        case HTTPHeader::UpgradeInsecureRequests: {
            return "Upgrade-Insecure-Requests";
            break;
        }
        case HTTPHeader::UserAgent: {
            return "User-Agent";
            break;
        }
        case HTTPHeader::Vary: {
            return "Vary";
            break;
        }
        default: {
            throw HTTPInvalidHeader();
            break;
        }
    }
}

HTTPHeader string_to_http_header(std::string header_str) {
    std::string l_header = to_lower(header_str);
    
    if (l_header == to_lower(http_header_to_string(HTTPHeader::Accept))) {
        return HTTPHeader::Accept;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::AcceptEncoding))) {
        return HTTPHeader::AcceptEncoding;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::AcceptLanguage))) {
        return HTTPHeader::AcceptLanguage;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::AccessControlRequestHeaders))) {
        return HTTPHeader::AccessControlRequestHeaders;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::AccessControlRequestMethod))) {
        return HTTPHeader::AccessControlRequestMethod;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::AccessControlAllowOrigin))) {
        return HTTPHeader::AccessControlAllowOrigin;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::CacheControl))) {
        return HTTPHeader::CacheControl;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::Connection))) {
        return HTTPHeader::Connection;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::ContentType))) {
        return HTTPHeader::ContentType;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::ContentLength))) {
        return HTTPHeader::ContentLength;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::Host))) {
        return HTTPHeader::Host;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::Referer))) {
        return HTTPHeader::Referer;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::Origin))) {
        return HTTPHeader::Origin;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::PostmanToken))) {
        return HTTPHeader::PostmanToken;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecChUa))) {
        return HTTPHeader::SecChUa;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecChUaPlatform))) {
        return HTTPHeader::SecChUaPlatform;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecChUaMobile))) {
        return HTTPHeader::SecChUaMobile;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecFetchMode))) {
        return HTTPHeader::SecFetchMode;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecFetchSite))) {
        return HTTPHeader::SecFetchSite;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecFetchDest))) {
        return HTTPHeader::SecFetchDest;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::SecFetchUser))) {
        return HTTPHeader::SecFetchUser;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::UpgradeInsecureRequests))) {
        return HTTPHeader::UpgradeInsecureRequests;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::UserAgent))) {
        return HTTPHeader::UserAgent;
    }
    else if (l_header == to_lower(http_header_to_string(HTTPHeader::Vary))) {
        return HTTPHeader::Vary;
    }
    else {
        throw HTTPInvalidHeader(l_header);
    }
}

std::string method_to_string(HTTPMethods method) {
    switch (method) {
        case HTTPMethods::GET: {
            return "GET";
        }
        case HTTPMethods::HEAD: {
            return "HEAD";
        }
        case HTTPMethods::POST: {
            return "POST";
        }
        case HTTPMethods::PUT: {
            return "PUT";
        }
        case HTTPMethods::DELETE: {
            return "DELETE";
        }
        case HTTPMethods::CONNECT: {
            return "CONNECT";
        }
        case HTTPMethods::OPTIONS: {
            return "OPTIONS";
        }
        case HTTPMethods::TRACE: {
            return "TRACE";
        }
        case HTTPMethods::NONE: {
            return "NONE?";
        }
    }
}

HTTPMethods string_to_method(std::string method_str) {
    if (method_str == method_to_string(HTTPMethods::GET)) {
        return HTTPMethods::GET;
    }
    else if (method_str == method_to_string(HTTPMethods::HEAD)) {
        return HTTPMethods::HEAD;
    }
    else if (method_str == method_to_string(HTTPMethods::POST)) {
        return HTTPMethods::POST;
    }
    else if (method_str == method_to_string(HTTPMethods::PUT)) {
        return HTTPMethods::PUT;
    }
    else if (method_str == method_to_string(HTTPMethods::DELETE)) {
        return HTTPMethods::DELETE;
    }
    else if (method_str == method_to_string(HTTPMethods::CONNECT)) {
        return HTTPMethods::CONNECT;
    }
    else if (method_str == method_to_string(HTTPMethods::OPTIONS)) {
        return HTTPMethods::OPTIONS;
    }
    else if (method_str == method_to_string(HTTPMethods::TRACE)) {
        return HTTPMethods::TRACE;
    }
    else {
        throw HTTPInvalidMethod(method_str);
    }
}

std::string content_type_to_string(HTTPContentType content_type) {
    switch (content_type) {
        case HTTPContentType::TextPlain: {
            return "text/plain";
            break;
        }
        case HTTPContentType::ApplicationJson: {
            return "application/json";
            break;
        }
        case HTTPContentType::None: {
            return "NONE";
            break;
        }
    };
}

HTTPContentType string_to_content_type(std::string content_type_str) {
    if (content_type_str == content_type_to_string(HTTPContentType::TextPlain)) {
        return HTTPContentType::TextPlain;
    }
    else if (content_type_str == content_type_to_string(HTTPContentType::ApplicationJson)) {
        return HTTPContentType::ApplicationJson;
    }
    else {
        throw HTTPContentTypeNotRecognized(content_type_str);
    }
}



/* ================================== HttpReponse Implementation ================================== */

HttpResponse::HttpResponse(): status_code(HTTPSatusCode::x200), headers({}), content("") {
}

void HttpResponse::set_status_code(HTTPSatusCode new_status_code) {
    status_code = new_status_code;
}

std::string HttpResponse::CRLF() const {
    return "\r\n";
}

std::string HttpResponse::get_status_line() const {
    std::string line = "HTTP/1.1 ";

    switch (status_code) {
        case HTTPSatusCode::x200: {
            line += "200 OK";
            break;
        }
        case HTTPSatusCode::x201: {
            line += "201 Created";
            break;
        }
        case HTTPSatusCode::x204: {
            line += "204 No Content";
            break;
        }
        case HTTPSatusCode::x400: {
            line += "400 Bad Request";
            break;
        }
        case HTTPSatusCode::x404: {
            line += "404 Not Found";
            break;
        }
        case HTTPSatusCode::x500: {
            line += "500 Internal Server Error";
            break;
        }
        case HTTPSatusCode::x501: {
            line += "501 Not Implemented";
        }
    }
    return line;
}

std::string HttpResponse::get_content_length() const {
    return std::to_string(content.size());
}

void HttpResponse::set_headers(std::vector<std::pair<HTTPHeader, std::string>> new_headers) {
    headers.clear();
    headers = new_headers;
}

void HttpResponse::add_header(std::pair<HTTPHeader, std::string> new_header) {
    headers.push_back(new_header);
}

void HttpResponse::set_content(std::string new_content) {
    content = new_content;
}

std::string HttpResponse::get_response() const { 
    std::string response = get_status_line() + CRLF();
    
    for (const std::pair<HTTPHeader, std::string> header : headers) {
        if (header.first == HTTPHeader::ContentLength) {
            response += http_header_to_string(HTTPHeader::ContentLength) + ": " + get_content_length() + CRLF();
        }
        else {
            response += http_header_to_string(header.first) + ": " + header.second + CRLF();
        }
    }
    response += CRLF() + content;

    return response;
}


/* ================================== HttpRequest Implementation ================================== */

HttpRequest::HttpRequest() = default;

HttpRequest::HttpRequest(std::string request): method(HTTPMethods::GET), request_target(""), headers({}), content(""), content_type(HTTPContentType::None) {
    bool got_method = false;
    bool got_request_target = false;
    std::string method_as_string = "";

    bool found_colon = false;
    bool found_CRLF = false;
    std::string header_field = "";
    std::string header_value = "";

    bool found_headers_end = false;

    int i = 0;
    for (; i < request.size(); i++) {
        if (request[i] == ' ') {
            if (!got_method) got_method = true;
            else if (!got_request_target) got_request_target = true;
        }
        else if (request[i] == '\r' && request[i+1] == '\n') {
            i += 2;
            break;
        }
        else if (!got_method) {
            method_as_string += request[i];
        }
        else if (!got_request_target) {
            request_target += request[i];
        }
    }

    method = string_to_method(method_as_string);

    for (; i < request.size(); i++) {
        if (i+1 < request.size() && request[i] == '\r' && request[i+1] == '\n') {            
            if (header_value[0] == ' ') header_value.erase(header_value.begin());
            if (header_value[header_value.size() - 1] == ' ') header_value.erase(header_value.end());
            
            headers.push_back({string_to_http_header(header_field), header_value});

            i++;
            if (i+2 < request.size() && request[i+1] == '\r' && request[i+2] == '\n') {
                i += 3;
                found_headers_end = true;
                break;
            }
            
            header_field = "";
            header_value = "";
            found_colon = false;
        }
        else if (request[i] == ':' && found_colon != true) {
            found_colon = true;
        }
        else if (!found_colon) {
            header_field += request[i];
        }
        else {
            header_value += request[i];
        }
    }

    if (!found_headers_end) {
        throw HTTPImproperFormat();
    }

    for (; i < request.size(); i++) {
        content += request[i];
    }

    for (const std::pair<HTTPHeader, std::string> &header : headers) {
        if (header.first == HTTPHeader::ContentType) {
            content_type = string_to_content_type(header.second);
        }
    }
}

HTTPMethods HttpRequest::get_method() const {
    return method;
}
std::string HttpRequest::get_request_target() const {
    return request_target;
}
HTTPContentType HttpRequest::get_content_type() const {
    return content_type;
}

std::vector<std::pair<HTTPHeader, std::string>> HttpRequest::get_headers() const {
    return headers;
}

std::string HttpRequest::get_content() const {
    return content;
}

/* ================================== HTTPInvalidHeader Exception Class Implementation ================================== */

HTTPInvalidHeader::HTTPInvalidHeader() {
    general = "Inputted HTTP header is not implemented or is invalid";
    specific = "";
}

HTTPInvalidHeader::HTTPInvalidHeader(std::string inputted_header): HTTPInvalidHeader()  {
    specific = "HTTP header \"" + inputted_header + "\" is not implemented or is invalid";
}

const char* HTTPInvalidHeader::what() {
    if (specific != "") return (specific).c_str();
    else return (general).c_str();
}

/* ================================== HTTPInvalidHeader Exception Class Implementation ================================== */

HTTPInvalidMethod::HTTPInvalidMethod(std::string inputted_method) {
    specific = "HTTP method \"" + inputted_method + "\" is not implemented or is invalid";
}

const char* HTTPInvalidMethod::what() {
    return specific.c_str();
}

/* ================================== HTTPImproperFormat Exception Class Implementation ================================== */

HTTPImproperFormat::HTTPImproperFormat() = default;

const char* HTTPImproperFormat::what() {
    return "Improper Request Format";
}

/* ================================== HTTPContentTypeNotRecognized Exception Class Implementation ================================== */

HTTPContentTypeNotRecognized::HTTPContentTypeNotRecognized(std::string new_error_content_type): error_content_type(new_error_content_type), return_message("") {
}

const char* HTTPContentTypeNotRecognized::what() {
    return_message = "The content type \"" + error_content_type + "\" is not a supported content type.";
    return return_message.c_str();
}
