#include "eks_blowfish.h"
#include <cmath>
#include <cstdint>
#include <cstring>
#include <pthread.h>
#include <random>
#include <string>
#include <iostream> 

#define version "$2b$"
#define CAST static_cast<uint32_t>


namespace Halfooda::BCrypt {
    EksBlowfish::EksBlowfish(char cost, uint32_t* key) {
        Blowfish();
        m_cost = cost; 
        m_key = key;
        generate_salt();
    }

    EksBlowfish::EksBlowfish(char cost, uint32_t* key, char* salt) {
        Blowfish();
        m_cost = cost;
        m_key = key;
        std::cout << "Data: " ;
        for (int i = 0; i < 18; i++) 
            std::cout << std::hex << key[i];
        std::cout << std::endl;
        char* decrypted_salt = decrypt_64(salt, 22);
        for (int i = 0; i < 4; i++) 
             m_salt[i] = char_to_int(decrypted_salt + 4 * i);
    }

    uint32_t EksBlowfish::char_to_int(char* str) {
        return  (CAST(str[0]) << 24) & 0xff000000 |
                (CAST(str[1]) << 16) & 0x00ff0000 |
                (CAST(str[2]) << 8 ) & 0x0000ff00 |
                (CAST(str[3])      ) & 0x000000ff;
    }

    void EksBlowfish::setup() {
        static uint32_t null_salt[4] = { 0 };
        uint32_t computed_cost = pow(2, m_cost);

        expand_key(m_salt, m_key, 18);
        for (uint32_t i = 0; i < computed_cost; i++) {
            expand_key(null_salt, m_key, 18);
            expand_key(null_salt, m_salt, 4);
        }
    }

    uint8_t* EksBlowfish::hash() {
        uint32_t data[6] = {
            0x4F727068,
            0x65616E42,
            0x65686F6C,
            0x64657253,
            0x63727944,
            0x6F756274
        };

        for (char i = 0; i < 64; i++) {
            encrypt(&data[0], &data[1]);
            encrypt(&data[2], &data[3]);
            encrypt(&data[4], &data[5]);
        }

        unsigned char hash[24];
        for (int i = 0; i < 6; i++) {
            hash[4 * i + 0] = (data[i] >> 24) & 0xff;
            hash[4 * i + 1] = (data[i] >> 16) & 0xff;
            hash[4 * i + 2] = (data[i] >> 8)  & 0xff;
            hash[4 * i + 3] = (data[i] >> 0)  & 0xff;
        } 

        static unsigned char output[31];
        memcpy(output, encrypt_64(hash, 24), 31);

        return output;
    }

    char* EksBlowfish::concatenate(char* hash) {
        static std::string output = version;
        output = version;
        if (m_cost < 10) output += "0";
        output += std::to_string(m_cost);
        output += '$';


        unsigned char char_salt[24];
        for (int i = 0; i < 4; i++) {
            char_salt[4 * i + 0] = (m_salt[i] >> 24) & 0xff;
            char_salt[4 * i + 1] = (m_salt[i] >> 16) & 0xff;
            char_salt[4 * i + 2] = (m_salt[i] >> 8)  & 0xff;
            char_salt[4 * i + 3] = (m_salt[i] >> 0)  & 0xff;
        } 

        char salt[22];
        memcpy(salt, encrypt_64(char_salt, 16), 22);
        output.append(salt, 22);
        
        output.append(hash, 31);


        return (char*)output.data();
    }

    void EksBlowfish::generate_salt() {
        std::random_device seed;
        std::mt19937 engine(seed());
        std::uniform_int_distribution<char> span(33, 126);
        char buffer[4];

        for (char i = 0; i < 4; i++) {
            for (char n = 0; n < 4; n++) {
                char c = span(engine);
                buffer[n] = c;
            }
            memcpy(m_salt + i, buffer, 4);
        }
    }

    void EksBlowfish::expand_key(uint32_t* salt, uint32_t* key, char key_lenght) {
        for (char i = 0; i < 18; i++) 
            p[i] = p[i] xor key[i % key_lenght];

        uint32_t l = 0;
        uint32_t r = 0;
        int k = 0;
        for (char i = 0; i < 18; i += 2) {
            l ^= salt[k++];
            r ^= salt[k++];
            if (k > 3) k = 0;
            encrypt(&l, &r);
            p[i] = l;
            p[i + 1] = r;
        }

        apply_s_box(s1, &l, &r, salt);
        apply_s_box(s2, &l, &r, salt);
        apply_s_box(s3, &l, &r, salt);
        apply_s_box(s4, &l, &r, salt);
    }

    void EksBlowfish::apply_s_box(uint32_t* s, uint32_t* l, uint32_t* r, uint32_t* salt) {
        int k = 2;

        for (short i = 0; i < 256; i+=2) {
            *l ^= salt[k++];
            *r ^= salt[k++];
            if (k > 3) k = 0;
            encrypt(l, r);
            s[i] = *l;
            s[i + 1] = *r;
        }
    }
}
