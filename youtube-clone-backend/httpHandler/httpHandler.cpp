#include "httpHandler.h"
#include "../HttpTypes/HttpTypes.h"
#include "../server/server.h"
#include <iostream>
#include <vector>



std::string httpRequestHandler(std::string request) {
    std::cout << "\n\n\n\n\n\n----------------------------------------------------------Request Start" << std::endl;
    std::cout << request << std::endl;
    std::cout << "----------------------------------------------------------Request End\n\n" << std::endl;
    HttpRequest r = HttpRequest(request);
    /*
    Example Response
    HTTP/1.1 200 OK
    Vary: Origin
    Vary: Access-Control-Request-Method
    Vary: Access-Control-Request-Headers
    Content-Type: text/plain;charset=UTF-8
    Content-Length: 13
    Date: Fri, 16 Jan 2026 05:53:52 GMT
    Keep-Alive: timeout=60
    Connection: keep-alive
    
    Hello, World!
    */

    HttpResponse response;
    response.setHeaders({
        {HTTPHeader::ContentType, "text/html;charset=utf-8"},
        {HTTPHeader::ContentLength, ""},
        {HTTPHeader::AccessControlAllowOrigin, "http://localhost:3000"},
        {HTTPHeader::Vary, "Origin"},
    });
    response.setContent("Hello, HTTP!");

    std::cout << "----------------------------------------------------------Response Start" << std::endl;
    std::cout << response.getResponse() << std::endl;
    std::cout << "Reponse Length: " << response.getResponse().size() << std::endl;
    std::cout << "----------------------------------------------------------Response End" << std::endl;

    
    return response.getResponse();
}