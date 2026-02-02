#include "httpHandler.h"
#include "../HttpImplementation/httpImplementation.h"
#include "../server/server.h"
#include <iostream>
#include <vector>

class JsonData;

class JsonDataEntry {
public:
    virtual void printEntry() = 0;

    friend class JsonData;
};

class SingleJsonDataEntry : public JsonDataEntry {
public:
    std::pair<std::string, std::string> entry;

    SingleJsonDataEntry(std::pair<std::string, std::string> newEntry): entry(newEntry) {}

    void printEntry() {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }


    friend class JsonData;
};

// class MultipleJsonDataEntry : public JsonDataEntry {
// private:
//     std::vector<SingleJsonDataEntry> entrys;

//     MultipleJsonDataEntry() = default;

//     void addEntry(SingleJsonDataEntry entry) {
//         entrys.push_back(entry);
//     }

// public:
//     friend class JsonData;
// };
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

                    SingleJsonDataEntry* newEntry = new SingleJsonDataEntry({entryName, entryValue});
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