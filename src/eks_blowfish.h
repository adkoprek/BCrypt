//  ____   _____ _______     _______ _______ 
// |  _ \ / ____|  __ \ \   / /  __ \__   __|
// | |_) | |    | |__) \ \_/ /| |__) | | |   
// |  _ <| |    |  _  / \   / |  ___/  | |   
// | |_) | |____| | \ \  | |  | |      | |   
// |____/ \_____|_|  \_\ |_|  |_|      |_|   
//   https://github.com/adkoprek/bcrypt
//
// A class implementation for the ekspensive blowfish
//
// This is class implements the setup of the Blowfish
// state with the user password and the encryption of
// 'OrpheanBeholderScryDoubt'
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#pragma once
#include <cstdint>

#include "base64.h"
#include "blowfish.h"


namespace BCrypt {
    class EksBlowfish : private Blowfish, private Base64 {
    public:
        /************************************************************
        *                       functions
        ************************************************************/

        // Constructor (no salt)
        // @param hash te be between 4 and 32
        // @param 72 byte key from the user
        EksBlowfish(char cost, uint32_t* key);

        // Constructor (with salt)
        // @param hash te be between 4 and 32
        // @param 72 byte key from the user
        // @param force to use this salt
        EksBlowfish(char cost, uint32_t* key, char* salt);

        // Setup the blowfish state, this can take a while
        void setup();

        // Hash the string 'OrpheanBeholderScryDoubt'
        uint8_t* hash();

        // Combine the cost, salt and hash
        char* concatenate(char* hash);

    private:
        /************************************************************
        *                       functions
        ************************************************************/

        // Generate random salt and store it internaly
        void generate_salt();

        // Expand the blowfish state
        // @param the salt in 32 bit packages
        // @param the user password in 32 bit packages
        // @the lenght of the key, can be 72 or 16
        void expand_key(uint32_t* salt, uint32_t* key, char key_lenght);

        // Apply the key to a specific S-Box
        // @param potiner to the according S-Box
        // @param lower 32 bits of current state (block)
        // @param upper 32 bits of current block
        // @param what salt to use of this round in 32 bit packages
        void apply_s_box(uint32_t* s, uint32_t* l, uint32_t* r, uint32_t* salt);

        /************************************************************
        *                       fields
        ************************************************************/

        uint32_t m_salt[4];             // Copy of salt in 32 bit packages
        uint32_t* m_key;                // Pointer toe the password of the user
        char m_cost;                    // The cost to use for this instance
    };
}
