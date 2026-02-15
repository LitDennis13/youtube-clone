#pragma once
#include <iostream>
#include <vector>
#include <variant>

class JsonData;
using JSONValueType = std::variant<std::string, std::vector<JsonData>>;

JsonData parseJsonData(std::string rawJsonData, bool start);

std::ostream &operator<<(std::ostream &out, const JsonData &obj);

class JsonData {
private:
    std::string fieldName;
    JSONValueType fieldValue;
    bool multiValue;
    bool start;
    
public:
    JsonData();
    JsonData(std::string startData);

    void setStart(bool newStartValue);

    void resetAndSetFieldValue();
    void resetAndSetEntries();

    std::string getName() const;
    std::string getValue() const; 

    void setFieldName(std::string newName);

    void setFieldValue(std::string newValue);

    void addEntry(JsonData entry);

    void print() const;

    std::string getJsonAsString() const;
    
    JsonData operator[](std::string searchFieldName) const;

    operator std::string() const;

    friend class JsonData;
};


class JSONFieldDoesNotExist: public std::exception {
private:
    std::string fieldName;
    std::string nonExsistentField;
    std::string returnMessage;
public:
    JSONFieldDoesNotExist(std::string newNonExsistentField);
    JSONFieldDoesNotExist(std::string newFieldName, std::string newNonExsistentField);

    const char* what();
};

class JSONCannotGetSingleValue: public std::exception {
private:
    std::string errorFieldName;
    std::string returnMessage;

public:
    JSONCannotGetSingleValue(std::string newErrorFieldName);

    const char* what();
};

class JSONCannotGetMultiValue: public std::exception {
private:
    std::string errorFieldName;
    std::string returnMessage;

public:
    JSONCannotGetMultiValue(std::string newErrorFieldName);

    const char* what();
};
