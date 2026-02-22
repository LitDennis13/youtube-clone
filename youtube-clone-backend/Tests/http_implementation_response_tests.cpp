#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "../HttpImplementation/http_implementation.h"

class HttpResponseTest: public testing::Test {
protected:
    HttpResponse r_1;
    HttpResponse r_2;

    HttpResponseTest() {
        r_1 = HttpResponse();
        r_1.set_status_code(HTTPSatusCode::x200);
        r_1.set_headers({
            {HTTPHeader::ContentType, "application/json"},
            {HTTPHeader::ContentLength, "27"},
            {HTTPHeader::Connection, "close"}
        });
        r_1.set_content("{\"status\":\"success\",\"id\":1}");

        r_2 = HttpResponse();
        r_2.set_status_code(HTTPSatusCode::x404);
        r_2.set_headers({
            {HTTPHeader::ContentType, "text/plain"},
            {HTTPHeader::ContentLength, "9"},
            {HTTPHeader::Connection, "close"}
        });
        r_2.set_content("Not Found");
    }
};

TEST_F(HttpResponseTest, CorrectResponse1) {
    EXPECT_STREQ(r_1.get_response().c_str(), "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 27\r\nConnection: close\r\n\r\n{\"status\":\"success\",\"id\":1}");
}

TEST_F(HttpResponseTest, CorrectResponse2) {
    EXPECT_STREQ(r_2.get_response().c_str(), "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 9\r\nConnection: close\r\n\r\nNot Found");
}

TEST_F(HttpResponseTest, ChangeInHeadersCausesFail) {
    r_2.set_headers({
        {HTTPHeader::ContentType, "text"},
        {HTTPHeader::ContentLength, "9"},
        {HTTPHeader::Connection, "open"}
    });
    EXPECT_STRNE(r_2.get_response().c_str(), "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 9\r\nConnection: close\r\n\r\nNot Found");
}

TEST_F(HttpResponseTest, WrongContentLengthDoesNotCauseFail) {
    r_2.set_headers({
        {HTTPHeader::ContentType, "text/plain"},
        {HTTPHeader::ContentLength, "1212129"},
        {HTTPHeader::Connection, "close"}
    });
    EXPECT_STREQ(r_2.get_response().c_str(), "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 9\r\nConnection: close\r\n\r\nNot Found");
}

