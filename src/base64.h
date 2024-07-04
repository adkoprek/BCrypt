//  ____   _____ _______     _______ _______ 
// |  _ \ / ____|  __ \ \   / /  __ \__   __|
// | |_) | |    | |__) \ \_/ /| |__) | | |   
// |  _ <| |    |  _  / \   / |  ___/  | |   
// | |_) | |____| | \ \  | |  | |      | |   
// |____/ \_____|_|  \_\ |_|  |_|      |_|   
//   https://github.com/adkoprek/bcrypt
//
// A class for bcrypt base64 encodeing
//
// This class provides to very simple functions
// to encrypt and decrypt a base64 encoded string
// but this algorithem uses an different hashing
// table as the common base64 encoding.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#pragma once
#include <cstdint>


namespace BCrypt {
    class Base64 {
    public:
        /************************************************************
        *                       functions
        ************************************************************/

        // Base64 encrypt a string
        // @param c styled input string
        // @param lenght of the portion to encode
        // @return encoded string
        uint8_t* encrypt_64(uint8_t* input, char lenght);
        
        // Base64 decrypt a string
        // @param c styled input string
        // @param lenght of the portion to encode
        // @return decoded string
        char* decrypt_64(char* input, char lenght);
    };
}
