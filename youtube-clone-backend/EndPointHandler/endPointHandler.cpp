#include "endPointHandler.h"
#include "../HttpImplementation/httpImplementation.h"
#include "../server/server.h"
#include "JsonHandler/jsonHandler.h"
#include <iostream>
#include <vector>

#include "../EndPoints/RootEndPoint/rootEndPoint.h"

#include "../EndPoints/NotFound/notFound.h"


EndPointType::EndPointType(HttpRequest newRequest): request(newRequest), response() {
    switch (newRequest.getContentType()) {
        case HTTPRequestContentType::TextPlain: {
            data = newRequest.getContent();
            break;
        }
        case HTTPRequestContentType::ApplicationJson: {
            data = JsonData(newRequest.getContent());
            break;
        }
        default: {
            break;
        }
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

std::string endPointerHandler(std::string rawRequest) {
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
    
    EndPointType* EndPoint = new NotFound(request);
    if (request.getRequestTarget() == "/") {
        EndPoint = new RootEndPoint(request);
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

    }

    std::string realResponse = EndPoint->getResponse();

    free(EndPoint);
    

    std::cout << "----------------------------------------------------------Response Start" << std::endl;
    std::cout << realResponse << std::endl;
    std::cout << "Reponse Length: " << realResponse.size() << std::endl;
    std::cout << "----------------------------------------------------------Response End" << std::endl;

    
    return realResponse;
}