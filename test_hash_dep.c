#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>

void hash_print(unsigned char* hash) {
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    const char* input = "Hello, World!";
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_context;
    
    SHA256_Init(&sha256_context);        
    SHA256_Update(&sha256_context, input, strlen(input));
    SHA256_Final(hash, &sha256_context);
    
    hash_print(hash);
    return 0;
}

