int testHash(){
	if(generateHash("genesis.txt") == NULL){
		return -1;
	}
	else return 1;
}
