#include<stdio.h>
#include<openssl/sha.h>
#include<string.h>
#include<stdlib.h>

void printHash(unsigned char* hash){

	printf("[%d] [%d]\n", strlen(hash), SHA256_DIGEST_LENGTH);
  for(int i = 0;i<SHA256_DIGEST_LENGTH;i++){
    printf("%02x",hash[i]);
  } printf("\n");
}

char* generateHash(char* filename){
  FILE* fp = fopen(filename, "r");
  if(fp==NULL){
    printf("Error opening the file\n");
    return NULL;
  }
  char buffer[257];
  int ch;
  int itr = 0;
  while((ch == fgetc(fp))!=EOF && itr<256){
    buffer[itr++] = (char) ch;
  }
  buffer[256] = '\0';
  fclose(fp);
  SHA256_CTX sha256_context;
  SHA256_Init(&sha256_context);        
  SHA256_Update(&sha256_context, buffer , strlen(buffer));
  unsigned char* hash = (char*) malloc(SHA256_DIGEST_LENGTH*sizeof(char));
  SHA256_Final(hash, &sha256_context);
  printHash(hash);
  return hash;
}


int main() {
  unsigned char* filename = generateHash("test1.txt");
  printHash(filename);
  return 0;
}
