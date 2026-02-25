#include <iostream>
#include <gtest/gtest.h>
#include "../JsonData/json_data.h"

class JsonDataTest: public testing::Test {
protected:
    JsonData test_1;
    JsonData test_2;
    JsonData test_3;
    JsonData test_4;
    JsonData test_5;

    JsonDataTest() {
        test_1 = JsonData("{\"username\":\"Username Example\",\"password\":\"Example Password\"}");
        test_2 = JsonData("{\"username\":\"Username Example\",\"password\":\"Example Password\",\"epic\":{\"one\":\"games\",\"two\":\"epic\",\"three\":{\"foo\":\"bar\",\"baz\":{\"foo\":\"bar\"}}}}");
        test_3 = JsonData("Test Entry", "example value");
        test_4 = JsonData("Test Entry 2", (std::vector<JsonData>){test_3});
        test_5 = JsonData();
    }

};

TEST_F(JsonDataTest, SingleEntryConstructorWorks1) {
    EXPECT_STREQ(test_3.get_json_as_string().c_str(), "\"Test Entry\":\"example value\"");
}

TEST_F(JsonDataTest, SingleEntryConstructorWorks2) {
    EXPECT_STREQ(test_4.get_json_as_string().c_str(), "{\"Test Entry\":\"example value\"}");
}

TEST_F(JsonDataTest, ProperJsonFormat1) {
    try {
        test_2 = JsonData("{\"hello\":\"939393\",\"x\":{\"one\":\"two\"},\"g\":\"t\"}");
    } catch (JSONImproperFormat err) { 
        FAIL();
    }
}

TEST_F(JsonDataTest, ProperJsonReturnFormat1) {
    EXPECT_STREQ(test_1.get_json_as_string().c_str(), "{\"username\":\"Username Example\",\"password\":\"Example Password\"}");
}
TEST_F(JsonDataTest, ProperJsonReturnFormat2) {
    EXPECT_STREQ(test_2.get_json_as_string().c_str(), "{\"username\":\"Username Example\",\"password\":\"Example Password\",\"epic\":{\"one\":\"games\",\"two\":\"epic\",\"three\":{\"foo\":\"bar\",\"baz\":{\"foo\":\"bar\"}}}}");
}

TEST_F(JsonDataTest, AccessWorks1) {
    EXPECT_STREQ(test_1["username"].get_value().c_str(), "Username Example");
}
TEST_F(JsonDataTest, AccessWorks2) {
    EXPECT_STREQ(test_2["epic"]["three"]["baz"]["foo"].get_value().c_str(), "bar");
}

TEST_F(JsonDataTest, AddingEntry1) {
    JsonData example = JsonData();
    example.set_field_name("Testing Field");
    example.set_field_value("example for testing purpose");
    test_1.add_entry(example);
    EXPECT_STREQ(test_1["Testing Field"].get_value().c_str(), "example for testing purpose");
}

TEST_F(JsonDataTest, AddingEntry2) {
    JsonData ex = JsonData();
    ex.set_field_name("Testing Field");

    JsonData example1 = JsonData();
    example1.set_field_name("Testing Field");
    example1.set_field_value("example for testing purpose");
    ex.add_entry(example1);

    JsonData example2 = JsonData();
    example2.set_field_name("Testing Field Two");
    example2.set_field_value("example for testing purpose Two");
    ex.add_entry(example2);

    JsonData example3 = JsonData();
    example3.set_field_name("Testing Field Three");
    example3.set_field_value("example for testing purpose Three");
    ex.add_entry(example3);

    test_1.add_entry(ex);


    EXPECT_STREQ(test_1["Testing Field"]["Testing Field Three"].get_value().c_str(), "example for testing purpose Three");
}

TEST_F(JsonDataTest, AddingEntry3) {
    JsonData ex = JsonData();
    ex.set_field_name("Testing Field");

    JsonData example1 = JsonData();
    example1.set_field_name("Testing Field");
    example1.set_field_value("example for testing purpose");
    ex.add_entry(example1);

    JsonData example2 = JsonData();
    example2.set_field_name("Testing Field Two");
    example2.set_field_value("example for testing purpose Two");
    ex.add_entry(example2);

    JsonData example3 = JsonData();
    example3.set_field_name("Testing Field Three");

    JsonData one = JsonData();
    one.set_field_name("One");
    one.set_field_value("Number One");
    example3.add_entry(one);

    JsonData two = JsonData();
    two.set_field_name("Two");
    two.set_field_value("Number Two");
    example3.add_entry(two);
    
    
    ex.add_entry(example3);

    test_1.add_entry(ex);

    try {
        EXPECT_STREQ(test_1["Testing Field"]["Testing Field Three"]["Two"].get_value().c_str(), "Number Two");
    } catch (JSONFieldDoesNotExist err) {
        std::cout << err.what() << std::endl;
        FAIL();
    }
}


TEST_F(JsonDataTest, ImproperJsonFormat1) {
    try {
        test_2 = JsonData("939393");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat2) {
    try {
        test_2 = JsonData("\"hello\":\"939393\"");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat3) {
    try {
        test_2 = JsonData("{\"hello\":\"939393}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat4) {
    try {
        test_2 = JsonData("{2232323}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat5) {
    try {
        test_2 = JsonData("{\"hello\":\"939393\",{\"one\":\"two\"},\"g\":\"t\"}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat6) {
    try {
        test_2 = JsonData("{\"hello\":\"939393\",\"x\":\"one\":\"two\",\"g\":\"t\"}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat7) {
    try {
        test_2 = JsonData("{\"hello\":\"939393\",\"x\"{\"one\":\"two\"},\"g\":\"t\"}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}


TEST_F(JsonDataTest, ImproperJsonFormat8) {
    try {
        test_2 = JsonData("{\"hello\": \"939393\",\"x\":{\"one\":\"two\"},\"g\":\"t\"}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat9) {
    try {
        test_2 = JsonData("{\"a\":1,}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat10) {
    try {
        test_2 = JsonData("{a: \"value\"}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat11) {
    try {
        test_2 = JsonData("{'hello': 'world'}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat12) {
    try {
        test_2 = JsonData("{\"text\": \"hello\\qworld\"}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, ImproperJsonFormat13) {
    try {
        test_2 = JsonData("{\"a\": 1 \"b\": 2}");
        FAIL();
    } catch (JSONImproperFormat err) { 
    }
}

TEST_F(JsonDataTest, SupportBooleans) {
    try {
        test_5 = JsonData("{\"username\":\"name\",\"password\":\"password\",\"createUser\":false}");
    } catch (JSONImproperFormat err) {
        FAIL();
    }
}

TEST_F(JsonDataTest, SupportNumbers) {
    try {
        test_5 = JsonData("{\"username\":\"name\",\"password\":\"password\",\"test\":32432}");
    } catch (JSONImproperFormat err) {
        FAIL();
    }
}





