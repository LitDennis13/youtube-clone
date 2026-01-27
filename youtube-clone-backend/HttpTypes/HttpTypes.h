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
    Accept,
    AcceptEncoding,
    AcceptLanguage,
    AccessControlRequestHeaders,
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
    UserAgent,
    Vary,
};

std::string httpHeaderToString(HTTPHeader header);
HTTPHeader stringToHTTPHeader(std::string header);

HTTPMethods stringToMethod(std:: string methodSTR);


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


// Exception Classes

class HTTPInvalidHeader: public std::exception {
private:
    std::string general;
    std::string specific;

public:
    HTTPInvalidHeader();
    HTTPInvalidHeader(std::string inputtedHeader);

    const char* what();
};

class HTTPInvalidMethod: public std::exception {
private:
    std::string specific;

public:
    HTTPInvalidMethod(std::string inputtedMethod);

    const char* what();
};