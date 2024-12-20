//this file defines the creation of a basic blockchain as i understand it.
#include<stdio.h>
#include<stdlib.h>
#include<openssl/sha.h>
#include<string.h>
#include<limits.h>
#include<stdbool.h>


typedef struct SingleBlock* Block;
typedef struct LedgerNode* Node;

#define err_st "IT'S NOT YOU IT'S US\nSORRY FOR THE INCONVENIENCE\n";
int MAX_SIZE = 1000;

struct SingleBlock{
  char* prevHash;
  char* datafile;
  char* Hash;
};

struct LedgerNode{
  Block transaction;
  Node prev;
  Node next;
};

char* generateHash(char* transaction){
  unsigned char* hash = (unsigned char*)malloc(SHA256_DIGEST_LENGTH*sizeof(unsigned char));
  char* temp = (char*)malloc(MAX_SIZE*sizeof(char));
  FILE* data = fopen(transaction, "r");
  int i = 0;
  while(fgetc(data)!=EOF && i<INT_MAX-1){
    i++;
  }
  free(temp);
  char* content = (char*) malloc((i+1)*sizeof(char));
  i = 0;
  while((content[i] == fgetc(data))!=EOF){
    i++;
  }
  SHA256_CTX sha256_ctx;
  SHA256_Init(&sha256_ctx);
  SHA256_Update(&sha256_ctx, content, strlen(content));
  SHA256_Final(hash, &sha256_ctx);
  fclose(data);
  return hash;
}

Node getNode(int index, Node genesis){
  int i = 0;
  Node temp = genesis;
  while(temp!=NULL){
    if(index == i++){
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

Block createBlock(int index, Node genesis){
  bool isGenesis = (index==0)?true:false;
  Block block = (Block) malloc(sizeof(struct SingleBlock));
  
  if(isGenesis){ 
    block->Hash = (unsigned char*) calloc(SHA256_DIGEST_LENGTH,sizeof(unsigned char));
    block->datafile = "genesis.txt";
    block->prevHash = NULL;
  } else {
    
    block->prevHash = getNode(index, genesis)->transaction->Hash;
    char* filename = (char*) calloc(100, sizeof(char));
    printf("Enter the filename to add to the blockchain ledger: (with extension)\n");
    scanf("%s", filename);
    block->Hash = generateHash(filename);
    block->datafile = filename;
  }
  return block;
}

Node createNode(int index, Node genesis){

  Node node = (Node) malloc(sizeof(struct LedgerNode));
  node->transaction = createBlock(index, genesis);
  node->prev = NULL;
  node->next = NULL;
  return node;
}

void cout(char* str){
  printf("%s\n", str);
}

void displayLedger(Node genesis){
  Node temp = genesis;
  int srl = 0;
  printf("No.\tFILENAME\tFILE-HASH\tPREVIOUS-FILE-HASH\n");
  while(temp!=NULL){
    printf("%d\t%s\t%s\t%s\n", srl++, temp->transaction->datafile, temp->transaction->Hash, temp->transaction->prevHash);
    temp = temp->next;
  }
}
int main() {
  int index = 0;
  Node genesis;
  genesis = createNode(index++, genesis);
  genesis->transaction->datafile = "genesis.txt";
  int option = 0;
  while(true) {
    cout("Enter `0` to exit");
    cout("Enter `1` to add to blockchain ledger");
    cout("Enter `2` to display the blockchain");
    cout("");
    printf("Enter choice: ");
    scanf("%d", option);
    switch(option){
    case 0:
      return 1;
    case 1:
      {
	Node temp = createNode(index++, genesis);
	genesis->next = temp;
	temp->prev = genesis;
      }
    case 2:
      {
	displayLedger(genesis);
      }  
    }
  }
  return 0;
}
