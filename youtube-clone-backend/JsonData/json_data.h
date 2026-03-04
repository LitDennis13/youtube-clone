#pragma once
#include <iostream>
#include <vector>
#include <variant>

class JsonData;
using JSONValueType = std::variant<std::string, std::vector<JsonData>>;

JsonData parse_json_data(std::string raw_json_data, bool start);

std::ostream &operator<<(std::ostream &out, const JsonData &obj);

class JsonData {
private:
    std::string field_name;
    JSONValueType field_value;
    bool multi_value;
    bool start;
    bool is_string;
    
public:
    JsonData();
    JsonData(std::string start_data); // get json data from string
    JsonData(std::string new_field_name, JSONValueType new_field_value, bool new_is_string); // single entry constructor

    void set_start(bool new_start_value);

    void reset_and_set_field_value();
    void reset_and_set_entries();

    std::string get_name() const;
    std::string get_value() const;

    void set_is_string(bool new_is_string);

    void set_field_name(std::string new_name);

    void set_field_value(std::string new_value);

    void add_entry(JsonData entry);

    void print() const;

    std::string get_json_as_string() const;
    
    JsonData operator[](std::string search_field_name) const;

    operator std::string() const;

    friend class JsonData;
};


class JSONImproperFormat: public std::exception {
private:
    std::string return_message;
public:
    JSONImproperFormat();

    const char* what();
};

class JSONFieldDoesNotExist: public std::exception {
private:
    std::string field_name;
    std::string non_exsistent_field;
    std::string return_message;
public:
    JSONFieldDoesNotExist(std::string new_non_exsistent_field);
    JSONFieldDoesNotExist(std::string new_field_name, std::string new_non_exsistent_field);

    const char* what();
};

class JSONCannotGetSingleValue: public std::exception {
private:
    std::string error_field_name;
    std::string return_message;

public:
    JSONCannotGetSingleValue(std::string new_error_field_name);

    const char* what();
};

class JSONCannotGetMultiValue: public std::exception {
private:
    std::string error_field_name;
    std::string return_message;

public:
    JSONCannotGetMultiValue(std::string new_error_field_name);

    const char* what();
};