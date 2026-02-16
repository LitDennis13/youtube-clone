#include "end_point_handler.h"
#include "../HttpImplementation/http_implementation.h"
#include "../JsonData/json_data.h"
#include "../Server/server.h"
#include <iostream>
#include <vector>

#include "../EndPoints/Root/root.h"
#include "../EndPoints/SignIn/sign_in.h"
#include "../EndPoints/SignUp/sign_up.h"

#include "../EndPoints/NotFound/not_found.h"


EndPointType::EndPointType(HttpRequest new_request, std::string new_end_point_name): request(new_request), end_point_name(new_end_point_name), response() {
    switch (new_request.get_content_type()) {
        case HTTPContentType::TextPlain: {
            data = new_request.get_content();
            break;
        }
        case HTTPContentType::ApplicationJson: {
            data = JsonData(new_request.get_content());
            break;
        }
        default: {
            break;
        }
    }
}

void EndPointType::check_method_and_content_type(HTTPMethods correct_method, HTTPContentType correct_content_type) {
    try {
        if (correct_method != HTTPMethods::NONE && correct_method != request.get_method()) {
            throw WrongHTTPMethod(end_point_name, request.get_method(), correct_method);
        }
        else if (correct_content_type != HTTPContentType::None && correct_content_type != request.get_content_type()) {
            throw WrongHTTPContentType(end_point_name, request.get_content_type(), correct_content_type);
        }
    } catch (WrongHTTPMethod err) {
        std::cout << err.what() << std::endl;
        exit(1);
    } catch (WrongHTTPContentType err) {
        std::cout << err.what() << std::endl;
        exit(1);
    }
}

void EndPointType::http_options_handler() {
    response.set_status_code(HTTPSatusCode::x204);
    for (const std::pair<HTTPHeader, std::string> &header: request.get_headers()) {
        if (header.first == HTTPHeader::AccessControlRequestMethod) {
            response.add_header({HTTPHeader::AccessControlAllowMethods, header.second});
        }
        else if (header.first == HTTPHeader::AccessControlRequestHeaders) {
            response.add_header({HTTPHeader::AccessControlAllowHeaders, header.second});
        }
    }
}

std::string EndPointType::get_response() {
    for (const std::pair<HTTPHeader, std::string> &header: request.get_headers()) {
        if (header.first == HTTPHeader::Origin) {
            response.add_header({HTTPHeader::AccessControlAllowOrigin, header.second});
        }
        else {
            request_headers_to_check(header);
        }
    }
    return response.get_response();
}

std::string end_point_handler(std::string raw_request) {
    std::cout << "\n\n\n\n\n\n----------------------------------------------------------Request Start" << std::endl;
    std::cout << raw_request << std::endl;
    std::cout << "----------------------------------------------------------Request End\n\n" << std::endl;
    HttpRequest request;
    HttpResponse response;

    try {
        request = HttpRequest(raw_request);
    } catch (HTTPInvalidMethod invld_mthd) {
        response.set_status_code(HTTPSatusCode::x400);
        std::cout << invld_mthd.what() << std::endl;
        return response.get_response();
    } catch (HTTPInvalidHeader invld_hdr) {
        response.set_status_code(HTTPSatusCode::x400);
        std::cout << invld_hdr.what() << std::endl;
        return response.get_response();
    } catch (HTTPImproperFormat invld_frmt) {
        response.set_status_code(HTTPSatusCode::x400);
        std::cout << invld_frmt.what() << std::endl;
        return response.get_response();
    } catch (HTTPContentTypeNotRecognized invld_cont_type) {
        response.set_status_code(HTTPSatusCode::x400);
        std::cout << invld_cont_type.what() << std::endl;
        return response.get_response();
    }
    
    std::string request_target = request.get_request_target();
    EndPointType* end_point = new NotFound(request, "Not Found");
    if (request_target == "/") {
        end_point = new Root(request, "Root");
    }
    else if (request_target == "/signin") {
        end_point = new SignIn(request, "Sign in");
    }
    else if (request_target == "/signup") {
        end_point = new SignUp(request, "Sign up");
    }

    switch (request.get_method()) {
        case HTTPMethods::GET:
        case HTTPMethods::HEAD:
        case HTTPMethods::POST:
        case HTTPMethods::PUT:
        case HTTPMethods::DELETE: {
            end_point->main_function();
        }
        case HTTPMethods::CONNECT: {
            break;
        }
        case HTTPMethods::OPTIONS: {
            end_point->http_options_handler();
            break;
        }
        case HTTPMethods::TRACE: {
            break;
        }
        default: {
            break;
        }

    }

    std::string real_response = end_point->get_response();

    free(end_point);

    std::cout << "----------------------------------------------------------Response Start" << std::endl;
    std::cout << real_response << std::endl;
    std::cout << "Reponse Length: " << real_response.size() << std::endl;
    std::cout << "----------------------------------------------------------Response End" << std::endl;

    
    return real_response;
}

WrongHTTPMethod::WrongHTTPMethod(std::string new_error_end_point, HTTPMethods new_incorrect_method, HTTPMethods new_correct_method): error_end_point(new_error_end_point), incorrect_method(new_incorrect_method), correct_method(new_correct_method) {
}

const char* WrongHTTPMethod::what() {
    return_message = "The end point \"" + error_end_point + "\" requires http method \"" + method_to_string(correct_method) + "\" but got method \"" + method_to_string(incorrect_method) + "\".";

    return return_message.c_str();
}

WrongHTTPContentType::WrongHTTPContentType(std::string new_error_end_point, HTTPContentType new_incorrect_content_type, HTTPContentType new_correct_content_type): error_end_point(new_error_end_point), incorrect_content_type(new_incorrect_content_type), correct_content_type(new_correct_content_type) {
}

const char* WrongHTTPContentType::what() {
    return_message = "The end point \"" + error_end_point + "\" requires content type \"" + content_type_to_string(correct_content_type) + "\" but got content type \"" + content_type_to_string(incorrect_content_type) + "\".";

    return return_message.c_str();
}