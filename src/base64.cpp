//  ____   _____ _______     _______ _______ 
// |  _ \ / ____|  __ \ \   / /  __ \__   __|
// | |_) | |    | |__) \ \_/ /| |__) | | |   
// |  _ <| |    |  _  / \   / |  ___/  | |   
// | |_) | |____| | \ \  | |  | |      | |   
// |____/ \_____|_|  \_\ |_|  |_|      |_|   
//   https://github.com/adkoprek/bcrypt
//
// The main class interface for the BCrypt algorithem
//
// This class has just to be intialized once with the cast
// and then can be used to encrypt with that cost but for
// decryption the cost is fetched from the hash.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include <cstdint>
#include <string>

#include "base64.h"
#include "base64_table.h"

#define WHITESPACE 64
#define EQUALS     65


namespace BCrypt {
    uint8_t* Base64::encrypt_64(uint8_t* input, char lenght) {
        static std::string output;
        output = "";
        char pad = lenght % 3;

        for (char i = 0; i < lenght ; i += 3) {

            uint32_t n = ((uint32_t)input[i]) << 16;
            if ((i + 2) < lenght) 
                n += ((uint32_t)input[i + 1]) << 8;
            if ((i + 3) < lenght) 
                n += input[i + 2];
            
            uint8_t n0 = (uint8_t)(n >> 18) & 0x3F;
            uint8_t n1 = (uint8_t)(n >> 12) & 0x3F;
            uint8_t n2 = (uint8_t)(n >> 6)  & 0x3F;
            uint8_t n3 = (uint8_t)n         & 0x3F;

            output += TABLE[n0];
            output += TABLE[n1];

            if ((i + 2) >= lenght) {
                output += TABLE[n2];
                break;
            }
            output += TABLE[n2];

            if ((i + 3) >= lenght) 
                output += TABLE[n3];
            
            output += TABLE[n3];
        }

        return (uint8_t*)output.data();
    }

    char* Base64::decrypt_64(char* input, char lenght) {
        static std::string output;
        output = "";
        char pad = 0;
        if (input[lenght - 1] == '=') {
            pad = 1;
            input[lenght - 1] = 'A';
            if (input[lenght - 2] == '=') {
                pad = 2;
                input[lenght - 2] = 'A';
            }
        }

        for (char i = 0; i < lenght; i += 4)  {
            uint32_t n = (DECODE_TABLE[input[i]]  << 18) + (DECODE_TABLE[input[i + 1]] << 12) +
                (DECODE_TABLE[input[i + 2]] << 6) + DECODE_TABLE[input[i + 3]];

            output += ((n >> 16) & 255);
            output += ((n >> 8) & 255);
            output += (n & 255);  
        }

        return (char*)output.data();
    }
}
