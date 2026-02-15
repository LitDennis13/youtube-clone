#pragma once
#include "../HttpImplementation/httpImplementation.h"
#include "../JsonData/jsonData.h"
#include <iostream>
#include <variant>

using Data = std::variant<std::string, JsonData>;

class EndPointType {
protected:
    std::string endPointName;
    HttpRequest request;
    HttpResponse response;
    Data data;
    
    void checkMethodAndContentType(HTTPMethods correctMethod, HTTPContentType correctContentType);
    virtual void requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) = 0;

public:
    EndPointType(HttpRequest newRequest, std::string newEndPointName);

    void httpOptionsHandler();

    virtual void mainFunction() = 0;

    std::string getResponse();
};

class WrongHTTPMethod: public std::exception {
private:
    std::string errorEndPoint;
    HTTPMethods incorrectMethod;
    HTTPMethods correctMethod;
    std::string returnMessage;
public:
    WrongHTTPMethod(std::string newErrorEndPoint, HTTPMethods newIncorrectMethod, HTTPMethods newCorrectMethod);

    const char* what();
};

class WrongHTTPContentType: public std::exception {
private:
    std::string errorEndPoint;
    HTTPContentType incorrectContentType;
    HTTPContentType correctContentType;
    std::string returnMessage;

public:
    WrongHTTPContentType(std::string newErrorEndPoint, HTTPContentType newIncorrectContentType, HTTPContentType newCorrectContentType);

    const char* what();
};


std::string endPointHandler(std::string rawRequest);