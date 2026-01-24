#include "HttpTypes.h"
#include <iostream>
#include <vector>

std::string toLower(std::string &input) {
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

std::string HttpHeaderToString(HTTPHeader header) {
    switch (header) {
        case HTTPHeader::ContentType: {
            return "Content-Type";
            break;
        }
        case HTTPHeader::ContentLength: {
            return "Content-Length";
            break;
        }
        case HTTPHeader::AccessControlAllowOrigin: {
            return "Access-Control-Allow-Origin";
            break;
        }
        case HTTPHeader::AccessControlRequestMethod: {
            return "Access-Control-Request-Method";
            break;
        }
        case HTTPHeader::Vary: {
            return "Vary";
            break;
        }
    }
}

/* ================================== HttpReponse Implementation ================================== */

HttpResponse::HttpResponse(): statusCode(HTTPSatusCode::x200), headers({}),content("") {
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
            break;
        }
        default: {
            // implement error classes!!!
            break;
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

void HttpResponse::setContent(std::string newContent) {
    content = newContent;
}

std::string HttpResponse::getResponse() const {
    // "Vary: Access-Control-Request-Method" + CRLF() + "Vary: Access-Control-Request-Headers" + CRLF() + 
    std::string response = getStatusLine() + CRLF();
    
    for (const std::pair<HTTPHeader, std::string> header : headers) {
        if (header.first == HTTPHeader::ContentLength) {
            response += HttpHeaderToString(header.first) + ": " + getContentLength() + CRLF();
        }
        else {
            response += HttpHeaderToString(header.first) + ": " + header.second + CRLF();
        }
    }
    response += CRLF() + content;

    return response;
}

/* ================================== HttpRequest Implementation ================================== */

HttpRequest::HttpRequest(std::string request) {

}

std::vector<std::pair<HTTPHeader, std::string>> HttpRequest::getHeaders() const {
    return headers;
}

std::string HttpRequest::getContent() const {
    return content;
}
