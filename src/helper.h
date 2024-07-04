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

#pragma once
#include <cstdint>

namespace BCrypt {
    // Convert a 32 bit integer into an 4 byte char array
    // @param the 32 bit interger to split
    // @return pointer to the 4 byte char array
    char* uint32_to_char(uint32_t input);

    // Convert a 4 byte char array into one 32 bit ineger
    // The bytes are in reversed order in memory but are
    // interpreted right because of little endianess
    // @param pointer to the 4 byte char array
    // @return the 32 bit interger to split
    uint32_t char_to_uint32(char* input);

    // Print a warning to the standart output
    // @param the message as a c string
    void print_warning(const char* message);

    // Throw an error
    // @param the message
    void throw_error(const char* message);
}
