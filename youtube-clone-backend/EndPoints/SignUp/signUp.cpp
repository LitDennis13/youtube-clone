#include "signUp.h"
#include "../../HttpImplementation/httpImplementation.h"


void SignUp::mainFunction() {
    response.setStatusCode(HTTPSatusCode::x200);
    response.addHeader({HTTPHeader::ContentType, "text/plain"});
    response.setContent("Sign Up");
}

void SignUp::requestHeadersToCheck(const std::pair<HTTPHeader, std::string> &header) {

}