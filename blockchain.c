#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<openssl/sha.h>

typedef struct SingleBlock* Block;

struct SingleBlock{
  char* filename;
  Block next;
  Block prev;
  unsigned char* prevHash;
  unsigned char* Hash;
};

void printHash(unsigned char* hash){
  for(int i = 0;i<SHA256_DIGEST_LENGTH;i++){
    printf("%02x", hash[i]);
  }
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
  while((ch = fgetc(fp))!=EOF && itr<256){
    buffer[itr++] = (char) ch;
  }
  buffer[256] = '\0';
  fclose(fp);
  SHA256_CTX sha256_context;
  SHA256_Init(&sha256_context);        
  SHA256_Update(&sha256_context, buffer , strlen(buffer));
  char* hash = (char*) malloc(SHA256_DIGEST_LENGTH*sizeof(char));
  SHA256_Final(hash, &sha256_context);
  return hash;
}

Block createBlock(Block genesis){
  Block block =  (Block) malloc(sizeof(struct SingleBlock));
  if(genesis == NULL) {
    block->filename = "genesis.txt";
    block->prevHash = (unsigned char*) calloc(SHA256_DIGEST_LENGTH,sizeof(char));
    
    block->Hash = generateHash(block->filename);
    block->prev = NULL;
    block->next = NULL;
    return block;
  }
  char* filename = (char*) malloc(15*sizeof(char));
  printf("\nEnter filename with extension: ");
  scanf("%s", filename);
  block->filename = filename;
  Block temp = genesis;
  while(temp->next!=NULL){
    temp = temp->next;
  }
  temp->next = block;
  block->prev = temp;
  block->Hash = generateHash(block->filename);
  block->prevHash = (unsigned char*) malloc(sizeof(char)*SHA256_DIGEST_LENGTH);
  for(int i = 0;i<SHA256_DIGEST_LENGTH;i++){
    block->prevHash[i] = temp->Hash[i];
  }
  block->next = NULL;
  printf("Block created\n");
  return genesis;
}
void printLedger(Block genesis){
  Block temp = genesis;
  while(temp!=NULL){
    printf("%s\t", temp->filename);
    printHash(temp->prevHash); printf("\t");
    printHash(temp->Hash); printf("\n");
    temp = temp->next;
  }
  
}
int testCreateBlock(){

  Block genesis = NULL;
  genesis = createBlock(genesis);
  //  printLedger(genesis);
  genesis = createBlock(genesis);
  //  printLedger(genesis);
  genesis = createBlock(genesis);
  printLedger(genesis);
  return 1;
}

int main(){

  //tests
  // printf("%d", testHash()); => passed
  printf("%d\n", testCreateBlock());
  //tests end
  
  return 0;
}
