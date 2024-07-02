#pragma once
#include <cstdint>

#include "base64.h"
#include "blowfish.h"


namespace BCrypt {
    class EksBlowfish : private Blowfish, private Base64 {
    public:
        EksBlowfish(char cost, uint32_t* key);
        EksBlowfish(char cost, uint32_t* key, char* salt);
        void setup();
        uint8_t* hash();
        char* concatenate(char* hash);

    public:
        uint32_t m_salt[4];
        uint32_t* m_key;
        char m_cost;
        void generate_salt();
        void expand_key(uint32_t* salt, uint32_t* key, char key_lenght);
        void apply_s_box(uint32_t* s, uint32_t* l, uint32_t* r, uint32_t* salt);
        uint32_t char_to_int(char* str);
    };
}
