#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "../HttpImplementation/http_implementation.h"

class HttpRequestTest: public testing::Test {
protected:
    HttpRequest r_1;
    HttpRequest r_2;

    HttpRequestTest() {
        r_1 = HttpRequest("PUT /index.html HTTP/1.1\r\nHost: example.com\r\nUser-Agent: MyClient/1.0\r\nAccept: */*\r\nConnection: close\r\n\r\n");
        r_2 = HttpRequest("POST /submit HTTP/1.1\r\nHost: example.com\r\nUser-Agent: MyClient/1.0\r\nContent-Type: application/json\r\nContent-Length: 38\r\nConnection: close\r\n\r\n{\"username\":\"dennis\",\"score\":12345}");
    }
};

TEST_F(HttpRequestTest, ParseMethodCorrectly1) {
    EXPECT_EQ(r_1.get_method(), HTTPMethods::PUT);
}

TEST_F(HttpRequestTest, ParseMethodCorrectly2) {
    EXPECT_EQ(r_2.get_method(), HTTPMethods::POST);
}



TEST_F(HttpRequestTest, ParseRequestTargetCorrectly1) {
    EXPECT_STREQ(r_1.get_request_target().c_str(), "/index.html");
}

TEST_F(HttpRequestTest, ParseRequestTargetCorrectly2) {
    EXPECT_STREQ(r_2.get_request_target().c_str(), "/submit");
}



TEST_F(HttpRequestTest, ParseContentTypeCorrectly1) {
    EXPECT_EQ(r_1.get_content_type(), HTTPContentType::None);
}

TEST_F(HttpRequestTest, ParseContentTypeCorrectly2) {
    EXPECT_EQ(r_2.get_content_type(), HTTPContentType::ApplicationJson);
}



TEST_F(HttpRequestTest, ParseHeadersCorrectly1) {
    EXPECT_EQ(r_1.get_headers().size(), 4);

    bool found_host = false;
    bool found_user_agent = false;
    bool found_accept = false;
    bool found_connection = false;

    for (const std::pair<HTTPHeader, std::string> &header : r_1.get_headers()) {
        if (header.first == HTTPHeader::Host) {
            found_host = true;
            EXPECT_STREQ(header.second.c_str(), "example.com");
        }
        else if (header.first == HTTPHeader::UserAgent) {
            found_user_agent = true;
            EXPECT_STREQ(header.second.c_str(), "MyClient/1.0");
        }
        else if (header.first == HTTPHeader::Accept) {
            found_accept = true;
            EXPECT_STREQ(header.second.c_str(), "*/*");
        }
        else if (header.first == HTTPHeader::Connection) {
            found_connection = true;
            EXPECT_STREQ(header.second.c_str(), "close");
        }
    }

    if (!found_host ||
    !found_user_agent ||
    !found_accept ||
    !found_connection) {
        FAIL();
    }
}

TEST_F(HttpRequestTest, ParseHeadersCorrectly2) {
    EXPECT_EQ(r_2.get_headers().size(), 5);

    bool found_host = false;
    bool found_user_agent = false;
    bool found_content_type = false;
    bool found_content_length = false;
    bool found_connection = false;

    for (const std::pair<HTTPHeader, std::string> &header : r_2.get_headers()) {
        if (header.first == HTTPHeader::Host) {
            found_host = true;
            EXPECT_STREQ(header.second.c_str(), "example.com");
        }
        else if (header.first == HTTPHeader::UserAgent) {
            found_user_agent = true;
            EXPECT_STREQ(header.second.c_str(), "MyClient/1.0");
        }
        else if (header.first == HTTPHeader::ContentType) {
            found_content_type = true;
            EXPECT_STREQ(header.second.c_str(), "application/json");
        }
        else if (header.first == HTTPHeader::ContentLength) {
            found_content_length = true;
            EXPECT_STREQ(header.second.c_str(), "38");
        }
        else if (header.first == HTTPHeader::Connection) {
            found_connection = true;
            EXPECT_STREQ(header.second.c_str(), "close");
        }
    }

    if (!found_host ||
    !found_user_agent ||
    !found_content_type ||
    !found_content_length ||
    !found_connection) {
        FAIL();
    }
}



TEST_F(HttpRequestTest, ParseContentCorrectly1) {
    EXPECT_STREQ(r_1.get_content().c_str(), "");
}

TEST_F(HttpRequestTest, ParseContentCorrectly2) {
    EXPECT_STREQ(r_2.get_content().c_str(), "{\"username\":\"dennis\",\"score\":12345}");
}