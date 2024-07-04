#pragma once
#include <cstdint>

namespace BCrypt {
    char* uint32_to_char(uint32_t input);

    uint32_t char_to_uint32(char* input);

    void print_warning(const char* message);

    void throw_error(const char* message);
}
