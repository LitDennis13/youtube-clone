#include "httpHandler.h"
#include "../HttpImplementation/httpImplementation.h"
#include "../server/server.h"
#include <iostream>
#include <vector>



std::string httpRequestHandler(std::string rawRequest) {
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
    }
    
    
    switch (request.getMethod()) {
        case HTTPMethods::GET:
        case HTTPMethods::HEAD: {
            response.setStatusCode(HTTPSatusCode::x200);
            response.setContent("Hello, World!");
            response.addHeader({HTTPHeader::ContentType, "text/html;charset=utf-8"});

            for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
                if (header.first == HTTPHeader::Origin) {
                    response.addHeader({HTTPHeader::AccessControlAllowOrigin, header.second});
                }
            }

            break;
        }
        case HTTPMethods::POST: {            
            break;
        }
        case HTTPMethods::PUT: {
            break;
        }
        case HTTPMethods::DELETE: {
            break;
        }
        case HTTPMethods::CONNECT: {
            break;
        }
        case HTTPMethods::OPTIONS: {
            response.setStatusCode(HTTPSatusCode::x204);
            for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
                if (header.first == HTTPHeader::Origin) {
                    response.addHeader({HTTPHeader::AccessControlAllowOrigin, header.second});
                }
                else if (header.first == HTTPHeader::AccessControlRequestMethod) {
                    response.addHeader({HTTPHeader::AccessControlAllowMethods, header.second});
                }
                else if (header.first == HTTPHeader::AccessControlRequestHeaders) {
                    response.addHeader({HTTPHeader::AccessControlAllowHeaders, header.second});
                }
            }
            break;
        }
        case HTTPMethods::TRACE: {
            break;
        }

    }




    

    std::cout << "----------------------------------------------------------Response Start" << std::endl;
    std::cout << response.getResponse() << std::endl;
    std::cout << "Reponse Length: " << response.getResponse().size() << std::endl;
    std::cout << "----------------------------------------------------------Response End" << std::endl;

    
    return response.getResponse();
}