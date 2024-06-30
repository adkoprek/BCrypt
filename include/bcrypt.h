#pragma once

#include <cstdint>
#include <string>
#include "../src/blowfish.h"
    

namespace Halfooda::BCrypt {
    class BCrypt {
    public:
        BCrypt(char cost);
        char* encrypt(char* password);
        bool verify(char* password, char* hash);

    public:
        char m_cost;
        char* extract_salt(char* hash);
        uint32_t* cycle_password(char* password);
        char* extract_password(char* hash);
    };
}
