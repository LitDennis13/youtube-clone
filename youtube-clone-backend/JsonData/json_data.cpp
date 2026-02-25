#include "json_data.h"
#include <iostream>
#include <vector>
#include <variant>

JsonData parse_json_data(std::string raw_json_data, bool start=false) {
    JsonData return_data;
    return_data.set_start(start);
    bool getting_entry_name = true; // if true it signals we are getting entry name, if false it signals we are getting entry value
    std::string entry_name = "";

    std::string entry_value = "";
    bool getting_sub_json = false;
    std::string sub_json = "";
    int json_levels_deep = -1;

    auto contains_quote = [](std::string str) {
        for (int i = 0; i < str.size(); i++) {
            if (str[i-1] != '\\' && str[i] == '\"') return true;
        }
        return false;
    };

    int character_pointer = 2; // start at the first character in a json string
    while (character_pointer < raw_json_data.size()) {
        if (getting_sub_json) {
            sub_json += raw_json_data[character_pointer];

            if (raw_json_data[character_pointer] == '{') {
                json_levels_deep++;
            }
            else if (raw_json_data[character_pointer] == '}') {
                if (json_levels_deep == 0) {
                    getting_sub_json = false;
                    JsonData new_entry = parse_json_data(sub_json);
                    new_entry.set_field_name(entry_name);
                    return_data.add_entry(new_entry);

                    entry_name = "";
                    sub_json = "";
                    character_pointer += 3;                

                    continue;
                }
                else {
                    json_levels_deep--;
                }
            }

            character_pointer++;                
        }
        else if (getting_entry_name && raw_json_data[character_pointer] == '\"' && raw_json_data[character_pointer - 1] != '\\') { // getting here means we are at the end of an entry name
            if (raw_json_data[character_pointer+1] != ':') {
                throw JSONImproperFormat();
            }

            if (raw_json_data[character_pointer+2] == '{') {
                    getting_sub_json = true;
                    character_pointer += 2;
                }
            else {
                getting_entry_name = false;
                character_pointer += 2;
            }
        }
        else if (!getting_entry_name && (raw_json_data[character_pointer] == ',' || raw_json_data[character_pointer] == '}')
            && (raw_json_data[character_pointer - 1] != '\"' || (raw_json_data[character_pointer - 1] == '\"' && raw_json_data[character_pointer - 2] != '\\'))) { // getting here means we are at the end of an entry value and are ready to move onto a new entry entirely
            getting_entry_name = true;

            if (entry_value[0] == '\"' && entry_value[entry_value.size() - 1] == '\"') {
                entry_value.erase(entry_value.begin());
                entry_value.pop_back();
            }

            JsonData new_entry = JsonData(entry_name, entry_value);
            return_data.add_entry(new_entry);

            character_pointer += 2;
            if (contains_quote(entry_name) || contains_quote(entry_value) ||
            (raw_json_data[character_pointer - 2] == ',' && raw_json_data[character_pointer - 1] != '\"') || 
            ((character_pointer - 2 == raw_json_data.size() - 1) && raw_json_data[character_pointer - 2] != '}')) {
                throw JSONImproperFormat();
            }

            entry_name = "";
            entry_value = "";
        }
        else if (getting_entry_name) {
            entry_name += raw_json_data[character_pointer];
            character_pointer++;
        }
        else {
            entry_value += raw_json_data[character_pointer];
            character_pointer++;
        }
    }

    if (raw_json_data[0] != '{' ||
        raw_json_data[1] != '\"' ||
        raw_json_data[raw_json_data.size() - 1] != '}' ||
        raw_json_data[character_pointer - 2] != '}' ||
        getting_entry_name != true
        ) {
        throw JSONImproperFormat();
    }

    return return_data;
}

std::ostream &operator<<(std::ostream &out, const JsonData &obj) {
    out << obj.get_value();
    return out;
}

JsonData::JsonData(): field_name(""), multi_value(false), start(true) {
}

JsonData::JsonData(std::string start_data): field_name(""), multi_value(false), start(true) {
    *this = parse_json_data(start_data, true);
}

JsonData::JsonData(std::string new_field_name, JSONValueType new_field_value): field_name(new_field_name), field_value(new_field_value), multi_value(false), start(true) {
    if (std::holds_alternative<std::vector<JsonData>>(field_value)) {
        multi_value = true;
    }
}

void JsonData::set_start(bool new_start_value) {
    start = new_start_value;
}

void JsonData::reset_and_set_field_value() {
    field_value = "";
}
void JsonData::reset_and_set_entries() {
    field_value = std::vector<JsonData>{};
    std::get<std::vector<JsonData>>(field_value).clear();
}

std::string JsonData::get_name() const {
    return field_name;
}

std::string JsonData::get_value() const {
    if (multi_value == true) {
        throw JSONCannotGetSingleValue(field_name);
    }
    return std::get<std::string>(field_value);
}

void JsonData::set_field_name(std::string new_name) {
    field_name = new_name;
}

void JsonData::set_field_value(std::string new_value) {
    reset_and_set_field_value();
    multi_value = false;
    field_value = new_value;
}

void JsonData::add_entry(JsonData entry) {
    if (multi_value == false) reset_and_set_entries(); 
    multi_value = true;
    
    std::get<std::vector<JsonData>>(field_value).push_back(entry);
}

void JsonData::print() const {
    if (multi_value) {
        for (const JsonData &entry: std::get<std::vector<JsonData>>(field_value)) {
            entry.print();
        }
    }
    else {
        std::cout << field_name << ": " << std::get<std::string>(field_value) << std::endl;
    }
}

std::string JsonData::get_json_as_string() const {
    std::string return_string = "";
    if (multi_value) {
        if (!start) {
            return_string += '\"' + field_name + "\":";
        }
        return_string += "{";

        for (const JsonData &entry : std::get<std::vector<JsonData>>(field_value)) {
            return_string += entry.get_json_as_string() + ',';
        }
        return_string.pop_back();

        return_string += "}";
    }
    else {
        std::string local_field_value = std::get<std::string>(field_value);
        return_string = '\"' + field_name + "\":";
        try {
            stoi(local_field_value);
            return_string += local_field_value;
        } catch (std::invalid_argument err) {
            return_string += '\"' + local_field_value + '\"';
        }
    }
    return return_string;
}

JsonData JsonData::operator[](std::string search_field_name) const {
    if (multi_value == false) {
        throw JSONCannotGetMultiValue(field_name);
    }

    for (const JsonData &entry : std::get<std::vector<JsonData>>(field_value)) {
        if (entry.get_name() == search_field_name) {
            return entry;
        }
    }
    if (start) throw JSONFieldDoesNotExist(search_field_name);
    else throw JSONFieldDoesNotExist(field_name, search_field_name);
}

JsonData::operator std::string() const {
    return get_value();
}

JSONImproperFormat::JSONImproperFormat() {
}

const char* JSONImproperFormat::what() {
    return_message = "Inputted JSON string had improper JSON format and could not be parsed.";
    return return_message.c_str();
}


JSONFieldDoesNotExist::JSONFieldDoesNotExist(std::string new_non_exsistent_field): field_name(""), non_exsistent_field(new_non_exsistent_field), return_message("") {
}

JSONFieldDoesNotExist::JSONFieldDoesNotExist(std::string new_field_name, std::string new_non_exsistent_field): field_name(new_field_name), non_exsistent_field(new_non_exsistent_field), return_message("") {
}

const char* JSONFieldDoesNotExist::what() {
    if (field_name == "") return_message = "The field \"" + non_exsistent_field + "\" does not exist.";
    else return_message = "The field \"" + non_exsistent_field + "\" does not exist in the field \"" + field_name + "\".";
    return return_message.c_str();
}

JSONCannotGetSingleValue::JSONCannotGetSingleValue(std::string new_errorField_name): error_field_name(new_errorField_name), return_message("") {
}

const char* JSONCannotGetSingleValue::what() {
    return_message = "The field \"" + error_field_name + "\" contains a sub json value and cannot return a single value.";
    return return_message.c_str();
}

JSONCannotGetMultiValue::JSONCannotGetMultiValue(std::string new_errorField_name): error_field_name(new_errorField_name), return_message("") {
}

const char* JSONCannotGetMultiValue::what() {
    return_message = "The field \"" + error_field_name + "\" is a single value field. Meaning it cannot be used with [].";
    return return_message.c_str();
}



