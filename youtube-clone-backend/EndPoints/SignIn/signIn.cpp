#include "signIn.h"
#include "../../HttpImplementation/httpImplementation.h"
#include <iostream>

void SignIn::mainFunction() {
    checkMethodAndContentType(HTTPMethods::POST, HTTPContentType::ApplicationJson);
    
    std::cout << contentTypeToString(request.getContentType()) << std::endl;

    std::cout << std::get<JsonData>(data).getJsonAsString() << std::endl;
    std::cout << std::get<JsonData>(data)["username"] << std::endl;
    

    response.setStatusCode(HTTPSatusCode::x200);
    response.addHeader({HTTPHeader::ContentType, contentTypeToString(HTTPContentType::TextPlain)});
    response.setContent("Sign in");
}

void SignIn::requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) {

}