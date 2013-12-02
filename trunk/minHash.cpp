#include "minHash.h"
#include <cmath>
#include <fstream>

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

void minHash::persistirHash() {
	this->hashing.guardarValores();
}

void minHash::levantarHash() {
	std::ifstream vHash("saves/valores.hash", std::ios::in | std::ifstream::binary);
	std::vector<std::vector<uint64_t> > valoresCargados;
	while (vHash.good()) {
		std::vector<uint64_t> numeros;
		unsigned int i=0;
		while (vHash.good() && i<8) {
			uint64_t num;
			vHash.read((char*)&num,8);
			vHash.peek();
			numeros.push_back(num);
			i++;
		}
		valoresCargados.push_back(numeros);
	}
	vHash.close();
	this->hashing.levantarValores(valoresCargados);
}
