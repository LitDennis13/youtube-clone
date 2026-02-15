#include "endPointHandler.h"
#include "../HttpImplementation/httpImplementation.h"
#include "../server/server.h"
#include "../JsonData/jsonData.h"
#include <iostream>
#include <vector>

#include "../EndPoints/Root/root.h"
#include "../EndPoints/SignIn/signIn.h"
#include "../EndPoints/SignUp/signUp.h"

#include "../EndPoints/NotFound/notFound.h"


EndPointType::EndPointType(HttpRequest newRequest, std::string newEndPointName): request(newRequest), endPointName(newEndPointName), response() {
    switch (newRequest.getContentType()) {
        case HTTPContentType::TextPlain: {
            data = newRequest.getContent();
            break;
        }
        case HTTPContentType::ApplicationJson: {
            data = JsonData(newRequest.getContent());
            break;
        }
        default: {
            break;
        }
    }
}

void EndPointType::checkMethodAndContentType(HTTPMethods correctMethod, HTTPContentType correctContentType) {
    try {
        if (correctMethod != HTTPMethods::NONE && correctMethod != request.getMethod()) {
            throw WrongHTTPMethod(endPointName, request.getMethod(), correctMethod);
        }
        else if (correctContentType != HTTPContentType::None && correctContentType != request.getContentType()) {
            throw WrongHTTPContentType(endPointName, request.getContentType(), correctContentType);
        }
    } catch (WrongHTTPMethod err) {
        std::cout << err.what() << std::endl;
        exit(1);
    } catch (WrongHTTPContentType err) {
        std::cout << err.what() << std::endl;
        exit(1);
    }
}

void EndPointType::httpOptionsHandler() {
    response.setStatusCode(HTTPSatusCode::x204);
    for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
        if (header.first == HTTPHeader::AccessControlRequestMethod) {
            response.addHeader({HTTPHeader::AccessControlAllowMethods, header.second});
        }
        else if (header.first == HTTPHeader::AccessControlRequestHeaders) {
            response.addHeader({HTTPHeader::AccessControlAllowHeaders, header.second});
        }
    }
}

std::string EndPointType::getResponse() {
    for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
        if (header.first == HTTPHeader::Origin) {
            response.addHeader({HTTPHeader::AccessControlAllowOrigin, header.second});
        }
        else {
            requestHeadersToCheck(header);
        }
    }
    return response.getResponse();
}

std::string endPointHandler(std::string rawRequest) {
    std::cout << "\n\n\n\n\n\n----------------------------------------------------------Request Start" << std::endl;
    std::cout << rawRequest << std::endl;
    std::cout << "----------------------------------------------------------Request End\n\n" << std::endl;
    HttpRequest request;
    HttpResponse response;

    try {
        request = HttpRequest(rawRequest);
    } catch (HTTPInvalidMethod invldMthd) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldMthd.what() << std::endl;
        return response.getResponse();
    } catch (HTTPInvalidHeader invldHdr) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldHdr.what() << std::endl;
        return response.getResponse();
    } catch (HTTPImproperFormat invldFrmt) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldFrmt.what() << std::endl;
        return response.getResponse();
    } catch (HTTPContentTypeNotRecognized invldContType) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldContType.what() << std::endl;
        return response.getResponse();
    }
    
    std::string requestTarget = request.getRequestTarget();
    EndPointType* EndPoint = new NotFound(request, "Not Found");
    if (requestTarget == "/") {
        EndPoint = new Root(request, "Root");
    }
    else if (requestTarget == "/signin") {
        EndPoint = new SignIn(request, "Sign in");
    }
    else if (requestTarget == "/signup") {
        EndPoint = new SignUp(request, "Sign up");
    }

    switch (request.getMethod()) {
        case HTTPMethods::GET:
        case HTTPMethods::HEAD:
        case HTTPMethods::POST:
        case HTTPMethods::PUT:
        case HTTPMethods::DELETE: {
            EndPoint->mainFunction();
        }
        case HTTPMethods::CONNECT: {
            break;
        }
        case HTTPMethods::OPTIONS: {
            EndPoint->httpOptionsHandler();
            break;
        }
        case HTTPMethods::TRACE: {
            break;
        }
        default: {
            break;
        }

    }

    std::string realResponse = EndPoint->getResponse();

    free(EndPoint);

    std::cout << "----------------------------------------------------------Response Start" << std::endl;
    std::cout << realResponse << std::endl;
    std::cout << "Reponse Length: " << realResponse.size() << std::endl;
    std::cout << "----------------------------------------------------------Response End" << std::endl;

    
    return realResponse;
}

WrongHTTPMethod::WrongHTTPMethod(std::string newErrorEndPoint, HTTPMethods newIncorrectMethod, HTTPMethods newCorrectMethod): errorEndPoint(newErrorEndPoint), incorrectMethod(newIncorrectMethod), correctMethod(newCorrectMethod) {
}

const char* WrongHTTPMethod::what() {
    returnMessage = "The end point \"" + errorEndPoint + "\" requires http method \"" + methodToString(correctMethod) + "\" but got method \"" + methodToString(incorrectMethod) + "\".";

    return returnMessage.c_str();
}

WrongHTTPContentType::WrongHTTPContentType(std::string newErrorEndPoint, HTTPContentType newIncorrectContentType, HTTPContentType newCorrectContentType): errorEndPoint(newErrorEndPoint), incorrectContentType(newIncorrectContentType), correctContentType(newCorrectContentType) {
}

const char* WrongHTTPContentType::what() {
    returnMessage = "The end point \"" + errorEndPoint + "\" requires content type \"" + contentTypeToString(correctContentType) + "\" but got content type \"" + contentTypeToString(incorrectContentType) + "\".";

    return returnMessage.c_str();
}