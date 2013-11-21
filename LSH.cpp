#include "LSH.h"

#include <iostream>

#ifndef BANDAS
#define BANDAS 40
#endif // BANDAS
#ifndef FILAS
#define FILAS 6
#endif // FILAS

using std::vector;

unsigned FNV(vector<uint64_t>& v, unsigned m = 4294967295){
	unsigned __int128 hash = 144066263297769815596495629667062367629UL;
	for (vector<uint64_t>::iterator i = v.begin(); i != v.end(); ++i){
		hash = hash * 309485009821345068724781371UL;
		hash = hash xor *i;
	}
	return hash % m;
}

LSH::LSH(unsigned cantDocs,vector<vector<uint64_t>*>& vHashMin):
hashmins(vHashMin){
	this->buckets = new Bucket[cantDocs];
	this->n = cantDocs;
}
void LSH::doLsh(){
	for (int i = 0; i < 20; i++){
		unsigned numDoc = 0;
		for (vector<vector<uint64_t>*>::iterator it = this->hashmins.begin();
		it != this->hashmins.end(); ++it){
			vector<uint64_t>::iterator ini = (*it)->begin()+i*FILAS;
			vector<uint64_t> v(ini,ini+FILAS);
			unsigned hash = FNV(v,this->n);
			this->buckets[hash].agregarDoc(numDoc,i);
			numDoc++;
		}
	}

	for (unsigned i = 0; i < this->n; i++){
		std::cout<<"Bucket: "<<i<<std::endl;
		this->buckets[i].mostrar();
	}

}
LSH::~LSH(){
	delete[] this->buckets;
}
