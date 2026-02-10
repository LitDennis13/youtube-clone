#include "rootEndPoint.h"
#include "../../HttpImplementation/httpImplementation.h"


void RootEndPoint::mainFunction() {
    response.setStatusCode(HTTPSatusCode::x200);
    response.addHeader({HTTPHeader::ContentType, "text/plain"});
    response.setContent("Hello, World!");
}

void RootEndPoint::requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) {

}