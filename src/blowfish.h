#pragma once 

#include <cstdint>


namespace Halfooda::BCrypt {
    class Blowfish {
    public:
        Blowfish();
        void encrypt(uint32_t* left, uint32_t* right);
        uint64_t decrypt(uint64_t block);

    protected:
        uint32_t p[18];
        uint32_t s1[256];
        uint32_t s2[256];
        uint32_t s3[256];
        uint32_t s4[256];

    private:
        uint32_t f(uint32_t block);
        void swap(uint32_t* input1, uint32_t* input2);
    };
}
