#include "notFound.h"
#include "../../HttpImplementation/httpImplementation.h"
#include <iostream>


void NotFound::mainFunction() {
    response.setStatusCode(HTTPSatusCode::x404);
}

void NotFound::requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) {

}