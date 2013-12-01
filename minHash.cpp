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
		uint64_t hashResult = this->hashing.hashear(numFila,i);
		if (hashResult < vHash[i]){
			vHash[i] = hashResult;
		}
	}
}

unsigned char minHash::card(const char caracter){
	if (caracter >= 97){
		return (caracter % 97) + 1;
	} else {
		return 27; //espacio
	}
}

uint64_t minHash::calcFila(const string& shingle){
	uint64_t sum = 0;
	char potencia = this->sizeShingle;
	char i = 1;
	for (string::const_iterator it= shingle.begin(); it!=shingle.end(); it++){
		sum += (this->card(*it) - 1)*pow(27,potencia-i);
		i++;
	}
	sum+= 1;
	return sum;
}

unsigned minHash::masCercano(vector<vector<uint64_t>*>& vHashMin, vector<uint64_t>& vHashNew) {
	unsigned seleccion = 0;
	unsigned char iguales = 0;
	unsigned char max_sim = 0;
	vector<uint64_t>::iterator itNew;
	vector<uint64_t>::iterator itOlds;
	for(int doc = 0; doc < vHashMin.size(); ++doc) {
		itNew = vHashNew.begin();
		itOlds = vHashMin[doc]->begin();
		while(itNew != vHashNew.end()) {
			if(*itOlds == *itNew) {
				iguales++;
			}
			itOlds++;
			itNew++;
		}
		if(iguales > max_sim) {
			seleccion = doc;
			max_sim = iguales;
		}
		iguales = 0;
	}
	
	return seleccion;
}
