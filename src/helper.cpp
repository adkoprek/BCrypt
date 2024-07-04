//  ____   _____ _______     _______ _______ 
// |  _ \ / ____|  __ \ \   / /  __ \__   __|
// | |_) | |    | |__) \ \_/ /| |__) | | |   
// |  _ <| |    |  _  / \   / |  ___/  | |   
// | |_) | |____| | \ \  | |  | |      | |   
// |____/ \_____|_|  \_\ |_|  |_|      |_|   
//   https://github.com/adkoprek/bcrypt
//
// Some needed helper functions
//
// The conversion from char array to 32 bit integer
// is very improtant because of the little endinaness
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include <iostream>

#include "helper.h"


// Convert a 32 bit integer into an 4 byte char array
char* BCrypt::uint32_to_char(uint32_t input) {
    static char output[4]; 

    output[0] = (input >> 24) & 0xff;
    output[1] = (input >> 16) & 0xff;
    output[2] = (input >> 8)  & 0xff;
    output[3] = (input >> 0)  & 0xff;

    return output;
}

// Convert a 4 byte char array into one 32 bit ineger
// The bytes are in reversed order in memory but are
// interpreted right because of little endianess
uint32_t BCrypt::char_to_uint32(char* input) {
    return  (input[0] << 24) & 0xff000000 |
            (input[1] << 16) & 0x00ff0000 |
            (input[2] << 8 ) & 0x0000ff00 |
            (input[3]      ) & 0x000000ff;
}

// Print a warning to the standart output
void BCrypt::print_warning(const char *message) {
    std::cout << "[BCrypt] Warning: " << message << std::endl;
}

// Throw an error
void BCrypt::throw_error(const char *message) {
    throw "[BCrypt] Exception: message";
}
