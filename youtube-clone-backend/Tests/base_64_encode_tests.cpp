#include <iostream>
#include <gtest/gtest.h>
#include "../Base64Encode/base_64_encode.h"

TEST(Base64CharTest, ReturnCorrectChar1) {
    EXPECT_EQ(base_64_char(34), 'i');
}
TEST(Base64CharTest, ReturnCorrectChar2) {
    EXPECT_EQ(base_64_char(14), 'O');
}
TEST(Base64CharTest, ReturnCorrectChar3) {
    EXPECT_EQ(base_64_char(57), '5');
}
TEST(Base64CharTest, ReturnCorrectChar4) {
    EXPECT_EQ(base_64_char(62), '+');
}
TEST(Base64CharTest, ReturnCorrectChar5) {
    EXPECT_EQ(base_64_char(16), 'Q');
}
TEST(Base64CharTest, ReturnCorrectChar6) {
    EXPECT_EQ(base_64_char(63), '/');
}
TEST(Base64CharTest, ReturnCorrectChar7) {
    EXPECT_EQ(base_64_char(0), 'A');
}

TEST(Base64CharTest, CorrectOutputWhenXisTooLarge1) {
    EXPECT_EQ(base_64_char(64), '\0');
}
TEST(Base64CharTest, CorrectOutputWhenXisTooLarge2) {
    EXPECT_EQ(base_64_char(160), '\0');
}

TEST(Base64CharTest, CorrectOutputWhenXisTooSmall1) {
    EXPECT_EQ(base_64_char(-1), '\0');
}
TEST(Base64CharTest, CorrectOutputWhenXisTooSmall2) {
    EXPECT_EQ(base_64_char(-15), '\0');
}

TEST(Base64EncodeTest, CorrectEncoding1) {
    EXPECT_STREQ(base_64_encode("hello").c_str(), "aGVsbG8=");
}
TEST(Base64EncodeTest, CorrectEncoding2) {
    EXPECT_STREQ(base_64_encode("epic games").c_str(), "ZXBpYyBnYW1lcw==");
}
TEST(Base64EncodeTest, CorrectEncoding3) {
    EXPECT_STREQ(base_64_encode("").c_str(), "");
}

TEST(Base64EncodeTest, CorrectEncoding4) {
    EXPECT_STREQ(base_64_encode("f").c_str(), "Zg==");
}

TEST(Base64EncodeTest, CorrectEncoding5) {
    EXPECT_STREQ(base_64_encode("fo").c_str(), "Zm8=");
}

TEST(Base64EncodeTest, CorrectEncoding6) {
    EXPECT_STREQ(base_64_encode("foo").c_str(), "Zm9v");
}

TEST(Base64EncodeTest, CorrectEncoding7) {
    EXPECT_STREQ(base_64_encode("foob").c_str(), "Zm9vYg==");
}

TEST(Base64EncodeTest, CorrectEncoding8) {
    EXPECT_STREQ(base_64_encode("fooba").c_str(), "Zm9vYmE=");
}

TEST(Base64EncodeTest, CorrectEncoding9) {
    EXPECT_STREQ(base_64_encode("foobar").c_str(), "Zm9vYmFy");
}

TEST(Base64EncodeTest, CorrectEncoding10) {
    EXPECT_STREQ(base_64_encode("hello world").c_str(), "aGVsbG8gd29ybGQ=");
}

TEST(Base64EncodeTest, CorrectEncoding11) {
    EXPECT_STREQ(base_64_encode("Base64!").c_str(), "QmFzZTY0IQ==");
}
TEST(Base64EncodeTest, CorrectEncoding12) {
    EXPECT_STREQ(base_64_encode(" ").c_str(), "IA==");
}

TEST(Base64EncodeTest, CorrectEncoding13) {
    EXPECT_STREQ(base_64_encode("   ").c_str(), "ICAg");
}

TEST(Base64EncodeTest, CorrectEncoding18) {
    EXPECT_STREQ(base_64_encode("!@#$%^&*()_+").c_str(), "IUAjJCVeJiooKV8r");
}
TEST(Base64EncodeTest, CorrectEncoding20) {
    EXPECT_STREQ(base_64_encode("pad!").c_str(), "cGFkIQ==");
}
TEST(Base64EncodeTest, CorrectEncoding21) {
    EXPECT_STREQ(base_64_encode("pads!!").c_str(), "cGFkcyEh");
}
TEST(Base64EncodeTest, CorrectEncoding22) {
    EXPECT_STREQ(base_64_encode("{\"username\":\"a name\"}").c_str(), "eyJ1c2VybmFtZSI6ImEgbmFtZSJ9");
}


