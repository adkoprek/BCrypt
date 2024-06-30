#include "base64.h"
#include <cstdint>
#include <string>

#define WHITESPACE 64
#define EQUALS     65


namespace Halfooda::BCrypt {
    uint8_t* Base64::encrypt_64(uint8_t* input, char lenght) {
        static std::string output;
        output = "";
        char pad = lenght % 3;

        for (char i = 0; i < lenght ; i += 3) {

            uint32_t n = ((uint32_t)input[i]) << 16;
            if ((i + 2) < lenght) 
                n += ((uint32_t)input[i + 1]) << 8;
            if ((i + 3) < lenght) 
                n += input[i + 2];
            
            uint8_t n0 = (uint8_t)(n >> 18) & 0x3F;
            uint8_t n1 = (uint8_t)(n >> 12) & 0x3F;
            uint8_t n2 = (uint8_t)(n >> 6)  & 0x3F;
            uint8_t n3 = (uint8_t)n         & 0x3F;

            output += m_table[n0];
            output += m_table[n1];

            if ((i + 2) >= lenght) {
                output += m_table[n2];
                break;
            }
            output += m_table[n2];

            if ((i + 3) >= lenght) 
                output += m_table[n3];
            
            output += m_table[n3];
        }

        return (uint8_t*)output.data();
    }

    char* Base64::decrypt_64(char* input, char lenght) {
        static std::string output;
        output = "";
        char pad = 0;
        if (input[lenght - 1] == '=') {
            pad = 1;
            input[lenght - 1] = 'A';
            if (input[lenght - 2] == '=') {
                pad = 2;
                input[lenght - 2] = 'A';
            }
        }

        for (char i = 0; i < lenght; i += 4)  {
            uint32_t n = (m_decode_table[input[i]]  << 18) + (m_decode_table[input[i + 1]] << 12) +
                (m_decode_table[input[i + 2]] << 6) + m_decode_table[input[i + 3]];

            output += ((n >> 16) & 255);
            output += ((n >> 8) & 255);
            output += (n & 255);  
        }

        return (char*)output.data();
    }
}
