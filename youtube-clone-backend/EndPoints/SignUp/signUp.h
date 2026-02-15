#pragma once
#include "../../EndPointHandler/endPointHandler.h"
#include "../../HttpImplementation/httpImplementation.h"


class SignUp: public EndPointType {
private:
    using EndPointType::EndPointType;
    void requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) override;

public:
    void mainFunction() override;
};