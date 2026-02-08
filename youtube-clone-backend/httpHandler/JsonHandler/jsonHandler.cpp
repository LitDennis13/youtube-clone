#include "jsonHandler.h"
#include <iostream>
#include <vector>
#include <variant>

JsonDataEntry::JsonDataEntry(): fieldName(""), multiValue(false), start(false) {}

void JsonDataEntry::setStart(bool newStartValue) {
    start = newStartValue;
}

void JsonDataEntry::resetAndSetFieldValue() {
    fieldValue = "";
}
void JsonDataEntry::resetAndSetEntries() {
    fieldValue = std::vector<JsonDataEntry>{};
    std::get<std::vector<JsonDataEntry>>(fieldValue).clear();
}

std::string JsonDataEntry::getName() const {
    return fieldName;
}

std::string JsonDataEntry::getValue() const {
    if (multiValue == true) {
        throw JSONCannotGetSingleValue(fieldName);
    }
    return std::get<std::string>(fieldValue);
}

void JsonDataEntry::setFieldName(std::string newName) {
    fieldName = newName;
}

void JsonDataEntry::setFieldValue(std::string newValue) {
    resetAndSetFieldValue();
    multiValue = false;
    fieldValue = newValue;
}

void JsonDataEntry::addEntry(JsonDataEntry entry) {
    if (multiValue == false) resetAndSetEntries(); 
    multiValue = true;
    
    std::get<std::vector<JsonDataEntry>>(fieldValue).push_back(entry);
}

void JsonDataEntry::print() const {
    if (multiValue) {
        for (const JsonDataEntry &entry: std::get<std::vector<JsonDataEntry>>(fieldValue)) {
            entry.print();
        }
    }
    else {
        std::cout << fieldName << ": " << std::get<std::string>(fieldValue) << std::endl;
    }
}

JsonDataEntry JsonDataEntry::operator[](std::string searchFieldName) const {
    if (multiValue == false) {
        throw JSONCannotGetMultiValue(fieldName);
    }

    for (const JsonDataEntry &entry : std::get<std::vector<JsonDataEntry>>(fieldValue)) {
        if (entry.getName() == searchFieldName) {
            return entry;
        }
    }
    if (start) throw JSONFieldDoesNotExist(searchFieldName);
    else throw JSONFieldDoesNotExist(fieldName, searchFieldName);
}

JsonDataEntry::operator std::string() const {
    return getValue();
}

JsonData::JsonData(std::string rawJsonData) {
    data = parseJsonData(rawJsonData, true);
    data.print();
}

JsonDataEntry JsonData::parseJsonData(std::string rawJsonData, bool start=false) {
    JsonDataEntry returnData;
    if (start) returnData.setStart(true);
    bool gettingEntryName = true; // if true it signals we are getting entry name, if false it signals we are getting entry value
    std::string entryName = "";

    std::string entryValue = "";
    bool gettingSubJson = false;
    std::string subJson = "";
    int jsonLevelsDeep = -1;

    int characterPointer = 2; // start at the first character in a json string
    while (characterPointer < rawJsonData.size()) {
        if (gettingSubJson) {
            subJson += rawJsonData[characterPointer];

            if (rawJsonData[characterPointer] == '{') {
                jsonLevelsDeep++;
            }
            else if (rawJsonData[characterPointer] == '}') {
                if (jsonLevelsDeep == 0) {
                    gettingSubJson = false;
                    std::cout << subJson << std::endl;
                    JsonDataEntry newEntry = parseJsonData(subJson);
                    newEntry.setFieldName(entryName);
                    returnData.addEntry(newEntry);

                    entryName = "";
                    subJson = "";
                    characterPointer += 3;                

                    continue;
                }
                else {
                    jsonLevelsDeep--;
                }
            }

            characterPointer++;                
        }
        else if (gettingEntryName && rawJsonData[characterPointer] == '\"' && rawJsonData[characterPointer - 1] != '\\') { // getting here means we are at the end of an entry name
            if (gettingEntryName) { 
                if (rawJsonData[characterPointer+1] == ':' && rawJsonData[characterPointer+2] == '{') {
                    gettingSubJson = true;
                    characterPointer += 2;
                }
                else {
                    gettingEntryName = false;
                    characterPointer += 2;
                }
            }
        }
        else if (!gettingEntryName && (rawJsonData[characterPointer] == ',' || rawJsonData[characterPointer] == '}')
            && (rawJsonData[characterPointer - 1] != '\"' || (rawJsonData[characterPointer - 1] == '\"' && rawJsonData[characterPointer - 2] != '\\'))) { // getting here means we are at the end of an entry value and are ready to move onto a new entry entirely
            gettingEntryName = true;

            if (entryValue[0] == '\"' && entryValue[entryValue.size() - 1] == '\"') {
                entryValue.erase(entryValue.begin());
                entryValue.pop_back();
            }

            JsonDataEntry newEntry = JsonDataEntry();
            newEntry.setFieldName(entryName);
            newEntry.setFieldValue(entryValue);

            returnData.addEntry(newEntry);

            entryName = "";
            entryValue = "";

            characterPointer += 2;
        }
        else if (gettingEntryName) {
            entryName += rawJsonData[characterPointer];
            characterPointer++;
        }
        else {
            entryValue += rawJsonData[characterPointer];
            characterPointer++;
        }
    }

    return returnData;
}

JsonDataEntry JsonData::operator[](std::string searchFieldName) const {
    return data[searchFieldName];
}


JSONFieldDoesNotExist::JSONFieldDoesNotExist(std::string newNonExsistentField): fieldName(""), nonExsistentField(newNonExsistentField) {
}

JSONFieldDoesNotExist::JSONFieldDoesNotExist(std::string newFieldName, std::string newNonExsistentField): fieldName(newFieldName), nonExsistentField(newNonExsistentField) {
}

const char* JSONFieldDoesNotExist::what() {
    if (fieldName == "") returnMessage = "The field " + nonExsistentField + " does not exist.";
    else returnMessage = "The field " + nonExsistentField + " does not exist in the field " + fieldName + ".";
    return returnMessage.c_str();
}

JSONCannotGetSingleValue::JSONCannotGetSingleValue(std::string newErrorFieldName): errorFieldName(newErrorFieldName) {
}

const char* JSONCannotGetSingleValue::what() {
    returnMessage = "The field " + errorFieldName + " contains a sub json value and cannot return a single value.";
    return returnMessage.c_str();
}

JSONCannotGetMultiValue::JSONCannotGetMultiValue(std::string newErrorFieldName): errorFieldName(newErrorFieldName) {

}

const char* JSONCannotGetMultiValue::what() {
    returnMessage = "The field " + errorFieldName + " is a single value field. Meaning it cannot be used with [].";
    return returnMessage.c_str();
}



