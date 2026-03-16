#include "base_64_encode.h"

char base_64_char(int x) {
    if (x < 0 || x > 63) {
        std::cout << "x is too large" << std::endl;
        return '\0';
    }

    if (x <= 25) {
        return (char)('A' + x);
    }
    else if (x <= 51) {
        return (char)('a' + x - 26);
    }
    else if (x <= 61) {
        return (char)('0' + x - 52);
    }
    else if (x == 62) {
        return '+';
    }
    else {
        return '/';
    }
}
/*
   h        e        l         l      o
01101000 01100101 01101100 01101100 01101111
0110100001100101011011000110110001101111
011010 000110 010101 101100 011011 000110 111100
   a      G      V      s      b      G      8=   

   e
01100101

011001 010000
*/
std::string base_64_encode(std::string str) {
    std::string return_string = "";
    int stage = 0;
    int new_char_number = 0;
    int i = 0;
    while (i < str.size()) {
        if (stage == 0) {
            new_char_number = int(str[i]) >> 2;
            i++;
        }
        else if (stage == 1) {
            int last_two_bits_of_prev_char = (int(str[i - 1]) & 0x3) << 4;
            int first_four_bits_of_current_char = (int(str[i]) & 0xF0) >> 4;
            new_char_number = last_two_bits_of_prev_char + first_four_bits_of_current_char;
        }
        else if (stage == 2) {
            int last_four_bits_of_current_char = (int(str[i]) & 0xF) << 2;
            int first_two_bits_of_next_char = (int(str[i + 1]) & 0xF0) >> 6;
            new_char_number = last_four_bits_of_current_char + first_two_bits_of_next_char;
            i++;
        }
        else if (stage == 3) {
            int last_six_bits_of_current_char = int(str[i]) & 0x3F;
            new_char_number = last_six_bits_of_current_char;
            stage = -1;
            i++;
        }

        return_string += base_64_char(new_char_number);
        stage++;
    }
    
    if (str.size() % 3 == 1) {
        int new_char_number = (int(str[i - 1]) & 0x3) << 4;
        return_string += base_64_char(new_char_number);
        return_string += "==";
    }
    else if (str.size() % 3 == 2) {
        return_string += '=';
    }

    return return_string;
}