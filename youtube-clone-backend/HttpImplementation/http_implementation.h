#pragma once
#include <iostream>
#include <vector>
#include <exception>

enum HTTPMethods {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    NONE,
};

enum HTTPSatusCode {
    x200,
    x201,
    x204,
    x400,
    x404,
    x500,
    x501,
};

enum HTTPHeader {
    Accept,
    AcceptEncoding,
    AcceptLanguage,
    AccessControlAllowHeaders,
    AccessControlRequestHeaders,
    AccessControlAllowMethods,
    AccessControlRequestMethod,
    AccessControlAllowOrigin,
    CacheControl,
    Connection,
    ContentType,
    ContentLength,
    Host,
    Referer,
    Origin,
    PostmanToken,
    SecChUa,
    SecChUaPlatform,
    SecChUaMobile,
    SecFetchMode,
    SecFetchSite,
    SecFetchDest,
    SecFetchUser,
    UpgradeInsecureRequests,
    UserAgent,
    Vary,
};

enum HTTPContentType {
    TextPlain,
    ApplicationJson,
    None,
};

std::string http_header_to_string(HTTPHeader header);
HTTPHeader string_to_http_header(std::string header_str);

std::string method_to_string(HTTPMethods method);
HTTPMethods string_to_method(std:: string method_str);

std::string content_type_to_string(HTTPContentType content_type);
HTTPContentType string_to_content_type(std::string content_type_str);


class HttpResponse {
private:
    HTTPSatusCode status_code;

    std::vector<std::pair<HTTPHeader, std::string>> headers;

    std::string content;

    std::string CRLF() const;

    std::string get_status_line() const;

    std::string get_content_length() const;

public:
    HttpResponse();

    void set_status_code(HTTPSatusCode new_code);

    void set_headers(std::vector<std::pair<HTTPHeader, std::string>> new_headers);
    void add_header(std::pair<HTTPHeader, std::string> new_header);

    void set_content(std::string newContent);

    std::string get_response() const;

};

class HttpRequest {
private:
    HTTPMethods method;
    std::string request_target;
    std::vector<std::pair<HTTPHeader, std::string>> headers;
    std::string content;
    HTTPContentType content_type;

public:
    HttpRequest();
    HttpRequest(std::string request);

    HTTPMethods get_method() const;
    std::string get_request_target() const;
    HTTPContentType get_content_type() const;
    
    std::vector<std::pair<HTTPHeader, std::string>> get_headers() const;

    std::string get_content() const;
};


// Exception Classes

class HTTPInvalidHeader: public std::exception {
private:
    std::string general;
    std::string specific;

public:
    HTTPInvalidHeader();
    HTTPInvalidHeader(std::string inputted_header);

    const char* what();
};

class HTTPInvalidMethod: public std::exception {
private:
    std::string specific;

public:
    HTTPInvalidMethod(std::string inputted_method);

    const char* what();
};

class HTTPImproperFormat: public std::exception {
public:
    HTTPImproperFormat();

    const char* what();
};

class HTTPContentTypeNotRecognized: public std::exception {
private:
    std::string error_content_type;
    std::string return_message;

public:
    HTTPContentTypeNotRecognized(std::string new_error_content_type);

    const char* what();
};