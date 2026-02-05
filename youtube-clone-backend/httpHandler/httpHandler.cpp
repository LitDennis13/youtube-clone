#include "httpHandler.h"
#include "../HttpImplementation/httpImplementation.h"
#include "../server/server.h"
#include <iostream>
#include <vector>
#include <variant>

/*class JsonData;

class JsonDataEntry {
public:
    virtual void printEntry() = 0;

    friend class JsonData;
};

class SingleJsonDataEntry : public JsonDataEntry {
public:
    std::string fieldName;
    std::string fieldValue;

    SingleJsonDataEntry(std::string newFieldName, std::string newFieldValue): fieldName(newFieldName), fieldValue(newFieldValue) {}

    void printEntry() {
        std::cout << fieldName << ": " << fieldValue << std::endl;
    }


    friend class JsonData;
};

class MultipleJsonDataEntry : public JsonDataEntry {
private:
    std::string fieldName;

    std::vector<SingleJsonDataEntry> subEntrys;

    MultipleJsonDataEntry() = default;

    void addEntry(SingleJsonDataEntry entry) {
        subEntrys.push_back(entry);
    }



public:
    friend class JsonData;
};
// {"username":"Random User Name","password":"Totally Real Password","more data":{"one":1,"five":5},"more data after the more data":"data again"}
class JsonData {
private:

    std::vector<JsonDataEntry*> data;

public:

    JsonData(std::string rawJsonData) {
        bool gettingEntryName = true; // if true it signals we are getting entry name, if false it signals we are getting entry value
        std::string entryName = "";
        std::string entryValue = "";

        int characterPointer = 2; // start at the first character in a json string
        while (characterPointer < rawJsonData.size()) {
            char beforeCharacter = rawJsonData[characterPointer - 1];
            char character = rawJsonData[characterPointer];

            if (character == '\"' && beforeCharacter != '\\') {
                if (gettingEntryName) { // getting here means we are at the end of an entry name
                    gettingEntryName = false;
                    characterPointer += 3;
                }
                else { // getting here means we are at the end of an entry value and are ready to move onto a new entry entirely
                    gettingEntryName = true;

                    SingleJsonDataEntry* newEntry = new SingleJsonDataEntry(entryName, entryValue);
                    data.push_back(newEntry);

                    entryName = "";
                    entryValue = "";

                    characterPointer += 3;
                }
            }
            else if (gettingEntryName) {
                entryName += character;
                characterPointer++;
            }
            else {
                entryValue += character;
                characterPointer++;
            }
        }

        for (int i = 0; i < data.size(); i++) {
            data[i]->printEntry();
        }

    }

};*/


class JsonDataEntry {
private:
    std::string fieldName;
    std::variant<std::string, std::vector<JsonDataEntry>> fieldValue;
    bool multiValue;
    
    bool start;

    void resetAndSetFieldValue() {
        fieldValue = "";
    }
    void resetAndSetEntries() {
        fieldValue = std::vector<JsonDataEntry>{};
        std::get<std::vector<JsonDataEntry>>(fieldValue).clear();
    }

public:
    JsonDataEntry(): start(true) {}
    JsonDataEntry(std::string newFieldName): fieldName(newFieldName), multiValue(false), start(false) {
    }

    void setFieldName(std::string newName) {
        fieldName = newName;
    }

    void setFieldValue(std::string newValue) {
        resetAndSetFieldValue();
        multiValue = false;
        fieldValue = newValue;
    }

    void addEntry(JsonDataEntry entry) {
        if (multiValue == false) resetAndSetEntries(); 
        multiValue = true;
        
        std::get<std::vector<JsonDataEntry>>(fieldValue).push_back(entry);
    }

    void print() const {
        if (multiValue) {
            std::cout << fieldName << " -"<< std::endl;
            for (const JsonDataEntry &entry: std::get<std::vector<JsonDataEntry>>(fieldValue)) {
                entry.print();
            }
        }
        else {
            std::cout << fieldName << ": " << std::get<std::string>(fieldValue) << std::endl;
        }
    }
};

class JsonData {
private:
    JsonDataEntry data;

    JsonDataEntry parseJsonData(std::string rawJsonData) {
        JsonDataEntry returnData;
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
            else if (rawJsonData[characterPointer] == '\"' && rawJsonData[characterPointer - 1] != '\\') {
                if (gettingEntryName) { // getting here means we are at the end of an entry name
                    if (rawJsonData[characterPointer+1] == ':' && rawJsonData[characterPointer+2] == '{') {
                        gettingSubJson = true;
                        characterPointer += 2;
                    }
                    else {
                        gettingEntryName = false;
                        characterPointer += 3;
                    }
                }
                else { // getting here means we are at the end of an entry value and are ready to move onto a new entry entirely
                    gettingEntryName = true;

                    JsonDataEntry newEntry = JsonDataEntry(entryName);
                    newEntry.setFieldValue(entryValue);

                    returnData.addEntry(newEntry);

                    entryName = "";
                    entryValue = "";

                    characterPointer += 3;
                }
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

public:

    JsonData(std::string rawJsonData) {
        data = parseJsonData(rawJsonData);
        data.print();
    }


};


std::string httpRequestHandler(std::string rawRequest) {
    std::cout << "\n\n\n\n\n\n----------------------------------------------------------Request Start" << std::endl;
    std::cout << rawRequest << std::endl;
    std::cout << "----------------------------------------------------------Request End\n\n" << std::endl;
    HttpRequest request;
    HttpResponse response;

    try {
        request = HttpRequest(rawRequest);
    } catch (HTTPInvalidMethod invldMthd) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldMthd.what() << std::endl;
        return response.getResponse();
    } catch (HTTPInvalidHeader invldHdr) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldHdr.what() << std::endl;
        return response.getResponse();
    } catch (HTTPImproperFormat invldFrmt) {
        response.setStatusCode(HTTPSatusCode::x400);
        std::cout << invldFrmt.what() << std::endl;
        return response.getResponse();
    }
    
    
    switch (request.getMethod()) {
        case HTTPMethods::GET:
        case HTTPMethods::HEAD: {
            response.setStatusCode(HTTPSatusCode::x200);
            response.setContent("Hello, World!");
            response.addHeader({HTTPHeader::ContentType, "text/html;charset=utf-8"});
            
            for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
                if (header.first == HTTPHeader::Origin) {
                    response.addHeader({HTTPHeader::AccessControlAllowOrigin, header.second});
                }
                
            }

            break;
        }
        case HTTPMethods::POST: {
            response.setStatusCode(HTTPSatusCode::x204);

            JsonData jsonData(request.getContent());


            for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
                if (header.first == HTTPHeader::Origin) {
                    response.addHeader({HTTPHeader::AccessControlAllowOrigin, header.second});
                }
                else if (header.first == HTTPHeader::ContentType) {
                    if (header.second == "application/json") {
                        
                    }
                }
            }            

            break;
        }
        case HTTPMethods::PUT: {
            break;
        }
        case HTTPMethods::DELETE: {
            break;
        }
        case HTTPMethods::CONNECT: {
            break;
        }
        case HTTPMethods::OPTIONS: {
            response.setStatusCode(HTTPSatusCode::x204);
            for (const std::pair<HTTPHeader, std::string> &header: request.getHeaders()) {
                if (header.first == HTTPHeader::Origin) {
                    response.addHeader({HTTPHeader::AccessControlAllowOrigin, header.second});
                }
                else if (header.first == HTTPHeader::AccessControlRequestMethod) {
                    response.addHeader({HTTPHeader::AccessControlAllowMethods, header.second});
                }
                else if (header.first == HTTPHeader::AccessControlRequestHeaders) {
                    response.addHeader({HTTPHeader::AccessControlAllowHeaders, header.second});
                }
            }
            break;
        }
        case HTTPMethods::TRACE: {
            break;
        }

    }




    

    std::cout << "----------------------------------------------------------Response Start" << std::endl;
    std::cout << response.getResponse() << std::endl;
    std::cout << "Reponse Length: " << response.getResponse().size() << std::endl;
    std::cout << "----------------------------------------------------------Response End" << std::endl;

    
    return response.getResponse();
}