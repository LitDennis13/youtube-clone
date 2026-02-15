#include "root.h"
#include "../../HttpImplementation/httpImplementation.h"


void Root::mainFunction() {
    response.setStatusCode(HTTPSatusCode::x200);
    response.addHeader({HTTPHeader::ContentType, "text/plain"});
    response.setContent("Hello, World!");
}

void Root::requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) {

}