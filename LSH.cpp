#include "LSH.h"

#include <iostream>
#include <random>
#include <chrono>

#ifndef BANDAS
#define BANDAS 40
#endif // BANDAS
#ifndef FILAS
#define FILAS 6
#endif // FILAS

using std::vector;

unsigned FNV(vector<uint64_t>& v, unsigned m = 4294967295){
	uint64_t hash = 14695981039346656037U;
	for (vector<uint64_t>::iterator i = v.begin(); i != v.end(); ++i){
		for (int j = 0; j < 8; j++){
			unsigned char c = (*i >> (8*j)) & 0xff;
			hash = hash xor c;
			hash = hash * 1099511628211U;
		}
	}
	return hash % m;
}

LSH::LSH(unsigned cantDocs,vector<vector<uint64_t>*>& vHashMin):
hashmins(vHashMin){
	this->buckets = new Bucket[cantDocs*2];
	this->n = cantDocs;
}
void LSH::doLsh(){
	for (int i = 0; i < 40; i++){
		unsigned numDoc = 0;
		for (vector<vector<uint64_t>*>::iterator it = this->hashmins.begin();
		it != this->hashmins.end(); ++it){
			vector<uint64_t>::iterator ini = (*it)->begin()+i*FILAS;
			vector<uint64_t> v(ini,ini+FILAS);
			unsigned hash = FNV(v,2*this->n);
			this->buckets[hash].agregarDoc(numDoc,i);
			numDoc++;
		}
	}

	for (unsigned i = 0; i < 2*this->n; i++){
		std::cout<<"Bucket: "<<i<<std::endl;
		this->buckets[i].mostrar();
	}

}

void LSH::getKLeaders(unsigned k, vector<unsigned>& lideres){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 generator(seed);
	std::uniform_int_distribution<uint64_t> distribution(0,this->n-1);
	for (int i = 0; i < k; i++){
		lideres.push_back(distribution(generator) % this->n);
	}
}

double LSH::distancia(unsigned doc1,unsigned doc2){
	double similitud = 0.0;
	unsigned char cantIguales = 0;
	vector<uint64_t>::iterator itDoc1 = this->hashmins[doc1]->begin();
	vector<uint64_t>::iterator itDoc2 = this->hashmins[doc2]->begin();
	for (int i = 0; i < BANDAS*FILAS; i++){
		if (*itDoc1 == *itDoc2){
			cantIguales++;
		}
	}
	similitud = cantIguales/(BANDAS*FILAS);
	return 1-similitud;
}

LSH::~LSH(){
	delete[] this->buckets;
}
