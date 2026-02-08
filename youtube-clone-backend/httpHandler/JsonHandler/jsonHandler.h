#pragma once
#include <iostream>
#include <vector>
#include <variant>

class JsonData;
class JsonDataEntry;
using JSONValueType = std::variant<std::string, std::vector<JsonDataEntry>>;

class JsonDataEntry {
private:
    std::string fieldName;
    JSONValueType fieldValue;
    bool multiValue;
    bool start;

    JsonDataEntry();

    void setStart(bool newStartValue);

    void resetAndSetFieldValue();
    void resetAndSetEntries();

    std::string getName() const;
    std::string getValue() const; 

    void setFieldName(std::string newName);

    void setFieldValue(std::string newValue);

    void addEntry(JsonDataEntry entry);

    void print() const;
    
public:
    JsonDataEntry operator[](std::string searchFieldName) const;

    operator std::string() const;

    friend class JsonData;
};

class JsonData {
private:
    JsonDataEntry data;
    JsonDataEntry parseJsonData(std::string rawJsonData, bool start);
    
public:
    JsonData(std::string rawJsonData);

    JsonDataEntry operator[](std::string searchFieldName) const;
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
