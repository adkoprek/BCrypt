//  ____   _____ _______     _______ _______ 
// |  _ \ / ____|  __ \ \   / /  __ \__   __|
// | |_) | |    | |__) \ \_/ /| |__) | | |   
// |  _ <| |    |  _  / \   / |  ___/  | |   
// | |_) | |____| | \ \  | |  | |      | |   
// |____/ \_____|_|  \_\ |_|  |_|      |_|   
//   https://github.com/adkoprek/bcrypt
//
// A class for blowfish calculations
//
// This class doesn't contain a full implementation
// of the Blowfish algorithem but just the parts 
// needed by the BCrypt algorithem.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include <cstdint>
#include <cstring>

#include "blowfish.h"
#include "pi.h"


namespace BCrypt {
    /************************************************************
    *                       public
    ************************************************************/

    // Constructor
    Blowfish::Blowfish() {
        // Copy the digits of pi into the boxes
        memcpy(p, P, 72);
        memcpy(s1, S1, 1024);
        memcpy(s2, S2, 1024);
        memcpy(s3, S3, 1024);
        memcpy(s4, S4, 1024);
    }

    // Deconstructor
    Blowfish::~Blowfish() {}

    // Encrypt 64 bits with the current state
    void Blowfish::encrypt(uint32_t* left, uint32_t* right) {
        *left ^= p[0];
        for (char i = 1; i < 17; i++) {
            *right ^= f(*left) ^ p[i];
            swap(left, right);
        }
        *right ^= p[17];
        swap(left, right);
    }

    /************************************************************
    *                       private
    ************************************************************/

    // Apply the Feistel network on 32 bits
    uint32_t Blowfish::f(uint32_t block) {
        uint32_t h = s1[block >> 24] + s2[(uint8_t)(block >> 16)];
        return (h xor s3[(uint8_t)(block >> 8)]) + s4[(uint8_t)block];
    }

    // Swap two 32 bit integers
    void Blowfish::swap(uint32_t* input1, uint32_t* input2) {
        uint32_t t;
        t = *input1;
        *input1 = *input2;
        *input2 = t;
    }
}
