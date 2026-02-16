#pragma once
#include "../../EndPointHandler/end_point_handler.h"
#include "../../HttpImplementation/http_implementation.h"


class SignUp: public EndPointType {
private:
    using EndPointType::EndPointType;
    void request_headers_to_check(const std::pair<HTTPHeader, std::string> &header) override;

public:
    void main_function() override;
};