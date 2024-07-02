#include <cstdint>
#include <cstring>

#include "blowfish.h"
#include "pi.h"


namespace BCrypt {
    Blowfish::Blowfish() {
        memcpy(p, P, 72);
        memcpy(s1, S1, 1024);
        memcpy(s2, S2, 1024);
        memcpy(s3, S3, 1024);
        memcpy(s4, S4, 1024);
    }

    void Blowfish::encrypt(uint32_t* left, uint32_t* right) {
        *left ^= p[0];
        for (char i = 1; i < 17; i++) {
            *right ^= f(*left) ^ p[i];
            swap(left, right);
        }
        *right ^= p[17];
        swap(left, right);
    }

    uint32_t Blowfish::f(uint32_t block) {
        uint32_t h = s1[block >> 24] + s2[(uint8_t)(block >> 16)];
        return (h xor s3[(uint8_t)(block >> 8)]) + s4[(uint8_t)block];
    }

    void Blowfish::swap(uint32_t* input1, uint32_t* input2) {
        uint32_t t;
        t = *input1;
        *input1 = *input2;
        *input2 = t;
    }
}
