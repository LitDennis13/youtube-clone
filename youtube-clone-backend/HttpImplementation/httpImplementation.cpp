#include "httpImplementation.h"
#include <iostream>
#include <vector>

std::string toLower(std::string input) {
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

std::string httpHeaderToString(HTTPHeader header) {
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

HTTPHeader stringToHTTPHeader(std::string header) {
    std::string lHeader = toLower(header);
    
    if (lHeader == toLower(httpHeaderToString(HTTPHeader::Accept))) {
        return HTTPHeader::Accept;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::AcceptEncoding))) {
        return HTTPHeader::AcceptEncoding;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::AcceptLanguage))) {
        return HTTPHeader::AcceptLanguage;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::AccessControlRequestHeaders))) {
        return HTTPHeader::AccessControlRequestHeaders;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::AccessControlRequestMethod))) {
        return HTTPHeader::AccessControlRequestMethod;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::AccessControlAllowOrigin))) {
        return HTTPHeader::AccessControlAllowOrigin;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::CacheControl))) {
        return HTTPHeader::CacheControl;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::Connection))) {
        return HTTPHeader::Connection;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::ContentType))) {
        return HTTPHeader::ContentType;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::ContentLength))) {
        return HTTPHeader::ContentLength;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::Host))) {
        return HTTPHeader::Host;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::Referer))) {
        return HTTPHeader::Referer;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::Origin))) {
        return HTTPHeader::Origin;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::PostmanToken))) {
        return HTTPHeader::PostmanToken;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecChUa))) {
        return HTTPHeader::SecChUa;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecChUaPlatform))) {
        return HTTPHeader::SecChUaPlatform;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecChUaMobile))) {
        return HTTPHeader::SecChUaMobile;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecFetchMode))) {
        return HTTPHeader::SecFetchMode;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecFetchSite))) {
        return HTTPHeader::SecFetchSite;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecFetchDest))) {
        return HTTPHeader::SecFetchDest;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::SecFetchUser))) {
        return HTTPHeader::SecFetchUser;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::UpgradeInsecureRequests))) {
        return HTTPHeader::UpgradeInsecureRequests;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::UserAgent))) {
        return HTTPHeader::UserAgent;
    }
    else if (lHeader == toLower(httpHeaderToString(HTTPHeader::Vary))) {
        return HTTPHeader::Vary;
    }
    else {
        throw HTTPInvalidHeader(lHeader);
    }
}

// function will convert the method as a string to a method in the enum type, however if the method is invalid the function throws an error
HTTPMethods stringToMethod(std::string methodSTR) {
    if (methodSTR == "GET") {
        return HTTPMethods::GET;
    }
    else if (methodSTR == "HEAD") {
        return HTTPMethods::HEAD;
    }
    else if (methodSTR == "POST") {
        return HTTPMethods::POST;
    }
    else if (methodSTR == "PUT") {
        return HTTPMethods::PUT;
    }
    else if (methodSTR == "DELETE") {
        return HTTPMethods::DELETE;
    }
    else if (methodSTR == "CONNECT") {
        return HTTPMethods::CONNECT;
    }
    else if (methodSTR == "OPTIONS") {
        return HTTPMethods::OPTIONS;
    }
    else if (methodSTR == "TRACE") {
        return HTTPMethods::TRACE;
    }
    else {
        throw HTTPInvalidMethod(methodSTR);
    }
}

HTTPRequestContentType stringToRequestContentType(std::string contentTypeSTR) {
    if (contentTypeSTR == "text/plain") {
        return HTTPRequestContentType::TextPlain;
    }
    else if (contentTypeSTR == "application/json") {
        return HTTPRequestContentType::ApplicationJson;
    }
    else {
        throw HTTPContentTypeNotRecognized(contentTypeSTR);
    }
}

/* ================================== HttpReponse Implementation ================================== */

HttpResponse::HttpResponse(): statusCode(HTTPSatusCode::x200), headers({}), content("") {
}

void HttpResponse::setStatusCode(HTTPSatusCode newStatusCode) {
    statusCode = newStatusCode;
}

std::string HttpResponse::CRLF() const {
    return "\r\n";
}

std::string HttpResponse::getStatusLine() const {
    std::string line = "HTTP/1.1 ";

    switch (statusCode) {
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

std::string HttpResponse::getContentLength() const {
    return std::to_string(content.size());
}

void HttpResponse::setHeaders(std::vector<std::pair<HTTPHeader, std::string>> newHeaders) {
    headers = newHeaders;
}

void HttpResponse::addHeader(std::pair<HTTPHeader, std::string> newHeader) {
    headers.push_back(newHeader);
}

void HttpResponse::setContent(std::string newContent) {
    content = newContent;
}

std::string HttpResponse::getResponse() const { 
    std::string response = getStatusLine() + CRLF();
    
    for (const std::pair<HTTPHeader, std::string> header : headers) {
        if (header.first == HTTPHeader::ContentType) {
            response += httpHeaderToString(HTTPHeader::ContentLength) + ": " + getContentLength() + CRLF();
        }
        response += httpHeaderToString(header.first) + ": " + header.second + CRLF();
    }
    response += CRLF() + content;

    return response;
}


/* ================================== HttpRequest Implementation ================================== */

HttpRequest::HttpRequest() = default;

HttpRequest::HttpRequest(std::string request): method(HTTPMethods::GET), requestTarget(""), headers({}), content(""), contentType(HTTPRequestContentType::None) {
    bool gotMethod = false;
    bool gotRequestTarget = false;
    std::string methodAsString = "";

    bool foundColon = false;
    bool foundCRLF = false;
    std::string headerField = "";
    std::string headerValue = "";

    bool foundHeadersEnd = false;

    int i = 0;
    for (; i < request.size(); i++) {
        if (request[i] == ' ') {
            if (!gotMethod) gotMethod = true;
            else if (!gotRequestTarget) gotRequestTarget = true;
        }
        else if (request[i] == '\r' && request[i+1] == '\n') {
            i += 2;
            break;
        }
        else if (!gotMethod) {
            methodAsString += request[i];
        }
        else if (!gotRequestTarget) {
            requestTarget += request[i];
        }
    }

    method = stringToMethod(methodAsString);

    for (; i < request.size(); i++) {
        if (i+1 < request.size() && request[i] == '\r' && request[i+1] == '\n') {            
            if (headerValue[0] == ' ') headerValue.erase(headerValue.begin());
            if (headerValue[headerValue.size() - 1] == ' ') headerValue.erase(headerValue.end());
            
            headers.push_back({stringToHTTPHeader(headerField), headerValue});

            i++;
            if (i+2 < request.size() && request[i+1] == '\r' && request[i+2] == '\n') {
                i += 3;
                foundHeadersEnd = true;
                break;
            }
            
            headerField = "";
            headerValue = "";
            foundColon = false;
        }
        else if (request[i] == ':' && foundColon != true) {
            foundColon = true;
        }
        else if (!foundColon) {
            headerField += request[i];
        }
        else {
            headerValue += request[i];
        }
    }

    if (!foundHeadersEnd) {
        throw HTTPImproperFormat();
    }

    for (; i < request.size(); i++) {
        content += request[i];
    }

    for (const std::pair<HTTPHeader, std::string> &header : headers) {
        if (header.first == HTTPHeader::ContentType) {
            contentType = stringToRequestContentType(header.second);
        }
    }
}

HTTPMethods HttpRequest::getMethod() const {
    return method;
}
std::string HttpRequest::getRequestTarget() const {
    return requestTarget;
}
HTTPRequestContentType HttpRequest::getContentType() const {
    return contentType;
}

std::vector<std::pair<HTTPHeader, std::string>> HttpRequest::getHeaders() const {
    return headers;
}

std::string HttpRequest::getContent() const {
    return content;
}

/* ================================== HTTPInvalidHeader Exception Class Implementation ================================== */

HTTPInvalidHeader::HTTPInvalidHeader() {
    general = "Inputted HTTP header is not implemented or is invalid";
    specific = "";
}

HTTPInvalidHeader::HTTPInvalidHeader(std::string inputtedHeader): HTTPInvalidHeader()  {
    specific = "HTTP header \"" + inputtedHeader + "\" is not implemented or is invalid";
}

const char* HTTPInvalidHeader::what() {
    if (specific != "") return (specific).c_str();
    else return (general).c_str();
}

/* ================================== HTTPInvalidHeader Exception Class Implementation ================================== */

HTTPInvalidMethod::HTTPInvalidMethod(std::string inputtedMethod) {
    specific = "HTTP method \"" + inputtedMethod + "\" is not implemented or is invalid";
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

HTTPContentTypeNotRecognized::HTTPContentTypeNotRecognized(std::string newErrorContentType): errorContentType(newErrorContentType), returnMessage("") {
}

const char* HTTPContentTypeNotRecognized::what() {
    returnMessage = "The content type \"" + errorContentType + "\" is not a supported content type.";
    return returnMessage.c_str();
}
