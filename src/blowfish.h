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

#pragma once 
#include <cstdint>


namespace BCrypt {
    class Blowfish {
    public:
        /************************************************************
        *                       functions
        ************************************************************/

        // Constructor
        Blowfish();

        // Deconstructor
        ~Blowfish();

        // Encrypt 64 bits with the current state
        // @paranm first 32 bits of the block to encrypt
        // @paranm last 32 bits of the block to encrypt
        void encrypt(uint32_t* left, uint32_t* right);

    protected:
        /************************************************************
        *                       fields
        ************************************************************/

        // Hold the state of blowish and are used to encrypt
        uint32_t p[18];                 
        uint32_t s1[256];               
        uint32_t s2[256];               
        uint32_t s3[256];               
        uint32_t s4[256];               

    private:
        /************************************************************
        *                       functions
        ************************************************************/

        // Apply the Feistel network on 32 bits
        // @param the 32 block input
        // @return the 32 block output
        uint32_t f(uint32_t block);

        // Swap two 32 bit integers
        // @param the first integer
        // @param the second integer
        void swap(uint32_t* input1, uint32_t* input2);
    };
}
