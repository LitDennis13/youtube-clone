#pragma once
#include "../HttpImplementation/httpImplementation.h"
#include "JsonHandler/jsonHandler.h"
#include <iostream>
#include <variant>

using Data = std::variant<std::string, JsonData>;

class EndPointType {
protected:
    HttpRequest request;
    HttpResponse response;
    Data data;

public:
    EndPointType(HttpRequest newRequest);

    void httpOptionsHandler();

    virtual void mainFunction() = 0;

    virtual void requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) = 0;

    std::string getResponse();
};



std::string endPointerHandler(std::string rawRequest);