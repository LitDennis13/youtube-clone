#pragma once
#include "JsonHandler/jsonHandler.h"
#include <iostream>




class EndPointType {
protected:
    std::string textData;
    JsonData jsonData;

};



std::string endPointerHandler(std::string rawRequest);