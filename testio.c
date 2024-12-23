#include <stdio.h>

int main() {
    FILE *fp = fopen("genesis.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp));
        printf("%s", buffer);
    

    fclose(fp);
    return 0;
}

