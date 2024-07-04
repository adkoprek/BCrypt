#include <iostream>
#include <sys/types.h>

#include "bcrypt.h"


void print_with_lenght(char* message, char lenght);

int main() {
    BCrypt::BCrypt bcrypt(3);
    const char* hash = bcrypt.encrypt("Test");
    print_with_lenght((char*)hash, 60);
    bool corectness_false = bcrypt.verify("asdg", hash);
    bool corectness_true = bcrypt.verify("Test", hash);
    std::cout << "The first try was: " << std::boolalpha << corectness_false << std::endl;
    std::cout << "The second try was: " << std::boolalpha << corectness_true << std::endl;
}

void print_with_lenght(char* message, char lenght) {
    std::cout << "Message: ";
    for (char i = 0; i < lenght; i++) {
        std::cout << std::hex << message[i];
    }
    std::cout << std::endl;
}
