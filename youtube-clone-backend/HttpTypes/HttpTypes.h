#pragma once
#include <iostream>
#include <vector>

enum HTTPMethods {
    GET,
    HEAD,
    POST,
    PUT,
    Delete,
    CONNECT,
    OPTIONS,
    TRACE,
};

enum HTTPSatusCode {
    x200,
    x201,
    x204,
    x404,
    x500,
    x501,
};

enum HTTPHeader {
    ContentType,
    ContentLength,
    AccessControlAllowOrigin,
    AccessControlRequestMethod,
    Vary,
};

std::string HttpHeaderToString(HTTPHeader header);

class HttpResponse {
private:
    HTTPSatusCode statusCode;

    std::vector<std::pair<HTTPHeader, std::string>> headers;

    std::string content;


    std::string CRLF() const;

    std::string getStatusLine() const;

    std::string getContentLength() const;

public:
    HttpResponse();

    void setStatusCode(HTTPSatusCode newCode);

    void setHeaders(std::vector<std::pair<HTTPHeader, std::string>> newHeaders);

    void setContent(std::string newContent);

    std::string getResponse() const;

};

class HttpRequest {
private:
    HTTPMethods method;
    std::string requestTarget;

    std::vector<std::pair<HTTPHeader, std::string>> headers;

    std::string content;
public:
    HttpRequest(std::string request);
    
    std::vector<std::pair<HTTPHeader, std::string>> getHeaders() const;

    std::string getContent() const;
};
