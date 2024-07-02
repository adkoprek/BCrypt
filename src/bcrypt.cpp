#include <cstdint>
#include <cstring>
#include <iomanip>
#include <ios>
#include <iostream>

#include "bcrypt.h"
#include "eks_blowfish.h"
#include "message.h"


namespace BCrypt {
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

    char* BCrypt::encrypt(const char* passowrd) {
        uint32_t* key = cycle_password(passowrd);
        auto eks_blowfish = new EksBlowfish(m_cost, key);
        eks_blowfish->setup();
        unsigned char* hash = eks_blowfish->hash();
        char* encrypted_password = eks_blowfish->concatenate((char*)hash);
        return encrypted_password;
    }

    bool BCrypt::verify(const char* password, const char* hash) {
        uint32_t* key = cycle_password(password);
        char* salt = extract_salt(hash);
        auto eks_blowfish = new EksBlowfish(m_cost, key, salt);
        eks_blowfish->setup();
        unsigned char* predicted_hash = eks_blowfish->hash();
        char* correct_hash = extract_password(hash);

        for (char i = 0; i < 31; i++) {
            if (predicted_hash[i] != correct_hash[i]) return false;
        }

        delete eks_blowfish;
        return true;
    }

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

    uint32_t* BCrypt::cycle_password(const char* password) {
        static char passowrd_72[72];
        char index = 0;

        if (std::strlen(password) > 72) {
            throw_error("Password is to long, the maximum is 72 bytes");
        }
        
        while (true) {
            for (char i = 0; i < std::strlen(password) + 1; i++)
            {
                passowrd_72[index] = password[i];
                index++;
                if (index == 72) {
                    std::cout << "Data: " << std::setfill('0') << std::setw(2);
                    for (int i = 0; i < 72; i++)
                        std::cout << std::hex << +passowrd_72[i];
                    std::cout << std::endl;
                    return (uint32_t*)passowrd_72;
                }
            }
        }
    }

    char* BCrypt::extract_password(const char* hash) {
        char offset = 0;
        char delimiter_encountered = 0;
        static char passowrd[31];
        
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

        memcpy(passowrd, hash + offset + 22, 31);
        return passowrd;
    }
}
