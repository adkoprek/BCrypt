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
// @Author: Adam Koprek
// @Email: adkoprek@gmail.com

#pragma once
#include <cstdint>
    

namespace BCrypt {
    class BCrypt {
    public:
        /************************************************************
        *                       functions
        ************************************************************/

        // Constructor
        // @param the cost between 4 and 32
        BCrypt(char cost);

        // Genreate the hash from a password
        // @param the password
        // @return the hash
        char* encrypt(const char* password);

        // Verify if a string generates a given hash
        // @param the plain password 
        // @param the correct hash
        // @return true if correct
        bool verify(const char* password, const char* hash);

    private:
        /************************************************************
        *                       functions
        ************************************************************/

        // Extract the base64 encoded salt part of the hash
        // @param the hash
        // @return the base64 encoded salt
        char* extract_salt(const char* hash);

        // Extract the base64 encoded salt part of the hash
        // @param the hash
        // @return the base64 encoded password
        char* extract_password(const char* hash);

        // If the input password is shorter then 72 bytes repeat it until 72 bytes
        // @param the base64 encoded salt
        // @return the plain salt
        uint32_t* cycle_password(const char* password);

        /************************************************************
        *                       fields
        ************************************************************/
        char m_cost;
    };
}
