#include "minHash.h"
#include <cmath>

#define BANDAS 40
#define	FILAS 6
#define MAXHASH BANDAS*FILAS

using std::string;
using std::vector;

minHash::minHash(char shSize){
	this->sizeShingle = shSize;
}
minHash::~minHash(){}

void minHash::doMinHash(const string& shingle, vector<uint64_t>& vHash){
	uint64_t numFila = this->calcFila(shingle);
	for (unsigned i = 0; i < MAXHASH; i++){
		vHash[i] = (this->hashing.hashear(numFila,i));
	}
}

unsigned char minHash::card(const char caracter){
	if (caracter >= 97){
		return (caracter % 97) + 1;
	} else if (caracter >= 48){
		return 28 + (caracter % 48);
	} else {
		return 27;
	}
}

uint64_t minHash::calcFila(const string& shingle){
	uint64_t sum = 0;
	char potencia = this->sizeShingle;
	char i = 1;
	for (string::const_iterator it= shingle.begin(); it!=shingle.end(); it++){
		sum += (this->card(*it) - 1)*pow(37,potencia-i);
		i++;
	}
	sum+= 1;
	return sum;
}
