#include <iostream>

#include "message.h"

void print_warning(const char *message) {
    std::cout << "[BCrypt] Warning: " << message << std::endl;
}

void throw_error(const char *message) {
    throw "[BCrypt] Exception: message";
}
