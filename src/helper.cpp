#include <iostream>

#include "helper.h"

char* BCrypt::uint32_to_char(uint32_t input) {
    static char output[4]; 

    output[0] = (input >> 24) & 0xff;
    output[1] = (input >> 16) & 0xff;
    output[2] = (input >> 8)  & 0xff;
    output[3] = (input >> 0)  & 0xff;

    return output;
}

uint32_t BCrypt::char_to_uint32(char* input) {
    return  (input[0] << 24) & 0xff000000 |
            (input[1] << 16) & 0x00ff0000 |
            (input[2] << 8 ) & 0x0000ff00 |
            (input[3]      ) & 0x000000ff;
}

void BCrypt::print_warning(const char *message) {
    std::cout << "[BCrypt] Warning: " << message << std::endl;
}

void BCrypt::throw_error(const char *message) {
    throw "[BCrypt] Exception: message";
}
