#include "jsonData.h"
#include <iostream>
#include <vector>
#include <variant>

JsonData parseJsonData(std::string rawJsonData, bool start=false) {
    JsonData returnData;
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
                    JsonData newEntry = parseJsonData(subJson);
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

            JsonData newEntry = JsonData();
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

std::ostream &operator<<(std::ostream &out, const JsonData &obj) {
    out << obj.getValue();
    return out;
}

JsonData::JsonData(): fieldName(""), multiValue(false), start(false) {
}

JsonData::JsonData(std::string startData): fieldName(""), multiValue(false), start(false) {
    *this = parseJsonData(startData, true);
}

void JsonData::setStart(bool newStartValue) {
    start = newStartValue;
}

void JsonData::resetAndSetFieldValue() {
    fieldValue = "";
}
void JsonData::resetAndSetEntries() {
    fieldValue = std::vector<JsonData>{};
    std::get<std::vector<JsonData>>(fieldValue).clear();
}

std::string JsonData::getName() const {
    return fieldName;
}

std::string JsonData::getValue() const {
    if (multiValue == true) {
        throw JSONCannotGetSingleValue(fieldName);
    }
    return std::get<std::string>(fieldValue);
}

void JsonData::setFieldName(std::string newName) {
    fieldName = newName;
}

void JsonData::setFieldValue(std::string newValue) {
    resetAndSetFieldValue();
    multiValue = false;
    fieldValue = newValue;
}

void JsonData::addEntry(JsonData entry) {
    if (multiValue == false) resetAndSetEntries(); 
    multiValue = true;
    
    std::get<std::vector<JsonData>>(fieldValue).push_back(entry);
}

void JsonData::print() const {
    if (multiValue) {
        for (const JsonData &entry: std::get<std::vector<JsonData>>(fieldValue)) {
            entry.print();
        }
    }
    else {
        std::cout << fieldName << ": " << std::get<std::string>(fieldValue) << std::endl;
    }
}

std::string JsonData::getJsonAsString() const {
    std::string returnString = "";
    if (multiValue) {
        if (!start) {
            returnString += '\"' + fieldName + "\":";
        }
        returnString += "{";

        for (const JsonData &entry : std::get<std::vector<JsonData>>(fieldValue)) {
            returnString += entry.getJsonAsString() + ',';
        }
        returnString.pop_back();

        returnString += "}";
    }
    else {
        std::string localFieldValue = std::get<std::string>(fieldValue);
        returnString = '\"' + fieldName + "\":";
        try {
            stoi(localFieldValue);
            returnString += localFieldValue;
        } catch (std::invalid_argument err) {
            returnString += '\"' + localFieldValue + '\"';
        }
    }
    return returnString;
}

JsonData JsonData::operator[](std::string searchFieldName) const {
    if (multiValue == false) {
        throw JSONCannotGetMultiValue(fieldName);
    }

    for (const JsonData &entry : std::get<std::vector<JsonData>>(fieldValue)) {
        if (entry.getName() == searchFieldName) {
            return entry;
        }
    }
    if (start) throw JSONFieldDoesNotExist(searchFieldName);
    else throw JSONFieldDoesNotExist(fieldName, searchFieldName);
}

JsonData::operator std::string() const {
    return getValue();
}




JSONFieldDoesNotExist::JSONFieldDoesNotExist(std::string newNonExsistentField): fieldName(""), nonExsistentField(newNonExsistentField), returnMessage("") {
}

JSONFieldDoesNotExist::JSONFieldDoesNotExist(std::string newFieldName, std::string newNonExsistentField): fieldName(newFieldName), nonExsistentField(newNonExsistentField), returnMessage("") {
}

const char* JSONFieldDoesNotExist::what() {
    if (fieldName == "") returnMessage = "The field \"" + nonExsistentField + "\" does not exist.";
    else returnMessage = "The field \"" + nonExsistentField + "\" does not exist in the field \"" + fieldName + "\".";
    return returnMessage.c_str();
}

JSONCannotGetSingleValue::JSONCannotGetSingleValue(std::string newErrorFieldName): errorFieldName(newErrorFieldName), returnMessage("") {
}

const char* JSONCannotGetSingleValue::what() {
    returnMessage = "The field \"" + errorFieldName + "\" contains a sub json value and cannot return a single value.";
    return returnMessage.c_str();
}

JSONCannotGetMultiValue::JSONCannotGetMultiValue(std::string newErrorFieldName): errorFieldName(newErrorFieldName), returnMessage("") {
}

const char* JSONCannotGetMultiValue::what() {
    returnMessage = "The field \"" + errorFieldName + "\" is a single value field. Meaning it cannot be used with [].";
    return returnMessage.c_str();
}



