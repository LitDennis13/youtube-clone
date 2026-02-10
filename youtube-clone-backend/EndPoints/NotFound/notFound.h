#pragma once
#include "../../EndPointHandler/endPointHandler.h"
#include "../../HttpImplementation/httpImplementation.h"


class NotFound: public EndPointType {
    using EndPointType::EndPointType;
    
    void mainFunction() override;

    void requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) override;
};