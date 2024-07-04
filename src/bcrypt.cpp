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

#include <cstring>

#include "bcrypt.h"
#include "eks_blowfish.h"
#include "helper.h"


namespace BCrypt {
    /************************************************************
    *                       public
    ************************************************************/

    // Constructor
    BCrypt::BCrypt(char cost) {
        if (cost < 4) {
            print_warning("Cost forced to 4");
            m_cost = 4;
        }

        else if (cost > 32) {
            print_warning("Cost forced to 32");
            m_cost = 32;
        }

        else
            m_cost = cost;
    }

    // Genreate the hash from a password
    const char* BCrypt::encrypt(const char* passowrd) {
        uint32_t* key = cycle_password(passowrd);
        auto eks_blowfish = new EksBlowfish(m_cost, key);
        eks_blowfish->setup();
        unsigned char* hash = eks_blowfish->hash();
        char* encrypted_password = eks_blowfish->concatenate((char*)hash);

        delete eks_blowfish;
        eks_blowfish = nullptr;
        return encrypted_password;
    }

    // Verify if a string generates a given hash
    bool BCrypt::verify(const char* password, const char* hash) {
        char cost = extract_cost(hash);
        if (cost == -1) return -1;
        uint32_t* key = cycle_password(password);
        char* salt = extract_salt(hash);

        auto eks_blowfish = new EksBlowfish(cost, key, salt);
        eks_blowfish->setup();
        unsigned char* predicted_hash = eks_blowfish->hash();
        char* correct_hash = extract_password(hash);

        for (char i = 0; i < 31; i++) {
            if (predicted_hash[i] != correct_hash[i]) return false;
        }

        delete eks_blowfish;
        eks_blowfish = nullptr;
        return true;
    }

    /************************************************************
    *                       private
    ************************************************************/

    // Extract the cost with witch the hash was encoded
    char BCrypt::extract_cost(const char* hash) {
        char cost_num_1 = hash[4] - '0';
        char cost_num_2 = hash[5] - '0';
        char cost;

        if (strlen(hash) != 60)
            throw_error("The lenght of the hash is incorrect");

        else if (hash[0] != '$')
            throw_error("The structure of the hash is incorrect");

        else if (hash[1] != '2')
            throw_error("The encryption method used on this hash is not BCrypt");

        else if (hash[3] != '$')
            throw_error("The structure if the hash is incorrect");

        else if (cost_num_1 < 0 || cost_num_1 > 9)
            throw_error("The first digit is not a number");

        else if (cost_num_2 < 0 || cost_num_2 > 9)
            throw_error("The second digit is not a number");

        else if (hash[6] != '$')
            throw_error("The structure of the hash is incorrectz");

        else
            return cost_num_1 * 10 + cost_num_2;

        return -1;
    }

    // Extract the base64 encoded salt part of the hash
    char* BCrypt::extract_salt(const char* hash) {
        char offset = 0;
        char delimiter_encountered = 0;
        static char salt[22];
        
        while (offset < 59) {
            char character = hash[offset];
            offset++;

            if (character == '$') {
                delimiter_encountered += 1;
                if (delimiter_encountered == 3) break;
            }
        }

        if (offset == 59) {
            throw_error("Hash doesn't match the correct structure");
        }

        memcpy(salt, hash + offset, 22);
        return salt;
    }

    // If the input password is shorter then 72 bytes repeat it until 72 bytes
    char* BCrypt::extract_password(const char* hash) {
        char delimiter_encountered = 0;
        static char passowrd[31];
        memcpy(passowrd, hash + 29, 31);
        return passowrd;
    }

    // Extract the base64 encoded salt part of the hash
    uint32_t* BCrypt::cycle_password(const char* password) {
        char password_length = strlen(password) + 1;
        static char buffer[72];
        static uint32_t password_72[18];
        char index = 0;

        while (index < 72) {
            buffer[index] = password[index % password_length];
            index++;
        }

        for (int i = 0; i < 18; i++)
            password_72[i] = char_to_uint32(buffer + 4 * i);

        return password_72;
    }
}
