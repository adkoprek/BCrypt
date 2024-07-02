#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "../src/eks_blowfish.h"
#include <sys/types.h>


void print_with_lenght(char* message, char lenght) {
    std::cout << "";
    for (char i = 0; i < lenght; i++) {
        std::cout << std::hex << message[i];
    }
    std::cout << std::endl;
}
    

int main()
{
    const char* salt_str = "QvbJ8B.7w77j9OlMyrieJu";
    const char* key_str = "correct battery horse staple\0correct battery horse staple\0correct batter";
    char salt[22];
    uint32_t key[18];
    memcpy(salt, salt_str, 22);
    memcpy(key, key_str, 72);
    strncpy((char*)key, key_str, 72);

    for (size_t i = 0; i < 18; i++)
        key[i] = (uint32_t)key_str[4 * i + 0] << 24 |
                 (uint32_t)key_str[4 * i + 1] << 16 |
                 (uint32_t)key_str[4 * i + 2] << 8  |
                 (uint32_t)key_str[4 * i + 3];
    
    Halfooda::BCrypt::EksBlowfish eks_blowifsh(5, key, salt);
    eks_blowifsh.setup();
    unsigned char* hash = eks_blowifsh.hash();
    char* end_msg = eks_blowifsh.concatenate((char*)hash);
    print_with_lenght(end_msg, 60);
}
