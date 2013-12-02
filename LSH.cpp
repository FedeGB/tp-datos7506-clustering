#include "LSH.h"

#include <iostream>
#include <random>
#include <set>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include "qsort.h"

#ifndef BANDAS
#define BANDAS 40
#endif // BANDAS
#ifndef FILAS
#define FILAS 6
#endif // FILAS

using std::vector;
using std::set;

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
	this->vLideres = NULL;
}
void LSH::doLsh(){
	for (int i = 0; i < BANDAS; i++){
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
	// for (unsigned i = 0; i < 2*this->n; i++){
	// 	std::cout<<"Bucket: "<<i<<std::endl;
	// 	this->buckets[i].mostrar();
	// }

}

void LSH::initKLeaders(){
	this->vLideres = new vector<unsigned>();
	vector<short>* vCantCand = new vector<short>(this->n,0);
	Bucket* it = this->buckets;
	for (unsigned i = 0; i < 2*this->n; i++){
		if (it->vacio()){
			it++;
			continue;
		}
		for (unsigned char band = 0; band < BANDAS; band++){
			for (unsigned k = 0; k < this->n; k++){
				if (it->isDocument(k,band)){
					vCantCand->at(k) += it->size(band);
				}
			}
		}
		it++;
	}
	for (unsigned i = 0; i < this->n; i++){
		this->vLideres->push_back(i);
	}
	qsort<vector<short>::iterator>(vCantCand->begin(),vCantCand->end(), this->vLideres->begin(),this->vLideres->end());

	delete vCantCand;
}

void LSH::getKLeaders(unsigned k, vector<unsigned>& lideres){
	if (this->vLideres == NULL){
		this->initKLeaders();
	}
	while (lideres.size() > k){
		lideres.pop_back();
	}
	unsigned pos = lideres.size();
	while (lideres.size() < k){
		std::cout<<"Pos: "<<pos<<" : "<<(this->vLideres->at(pos))<<std::endl;
		lideres.push_back(this->vLideres->at(pos));
		pos++;
	}
}

// void LSH::getKLeaders(unsigned k, vector<unsigned>& lideres){
// 	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
// 	std::mt19937_64 generator(seed);
// 	std::uniform_int_distribution<uint64_t> distribution(0,this->n);
// 	set<unsigned> docsUsados;
// 	unsigned bigK = sqrt(this->n)/4;
// 	if (bigK * k >= this->n){
// 		bigK = 2;
// 	}
// 	while (docsUsados.size()<bigK*k){
// 		unsigned lider = distribution(generator) % this->n;
// 		docsUsados.insert(lider);
// 	}
// 	unsigned lider = *docsUsados.begin();
// 	lideres.push_back(lider);
// 	docsUsados.erase(lider);
// 	while (lideres.size()<k){
// 		double distMax = -1;
// 		unsigned sigLider;
// 		for (vector<unsigned>::iterator i = lideres.begin(); i != lideres.end(); ++i){
// 			for (set<unsigned>::iterator j = docsUsados.begin(); j != docsUsados.end(); ++j){
// 				if (*i == *j){
// 					continue;
// 				}
// 				double distAux = this->distancia(*i,*j);
// 				if (distAux > distMax){
// 					distMax = distAux;
// 					sigLider = *j;
// 				}
// 			}
// 		}
// 		lideres.push_back(sigLider);
// 		docsUsados.erase(sigLider);	
// 	}
// }

double LSH::distancia(unsigned doc1,unsigned doc2){
	double similitud = 0.0;
	unsigned char cantIguales = 0;
	vector<uint64_t>::iterator itDoc1 = this->hashmins[doc1]->begin();
	vector<uint64_t>::iterator itDoc2 = this->hashmins[doc2]->begin();
	for (int i = 0; i < BANDAS*FILAS; i++){
		if (*itDoc1 == *itDoc2){
			cantIguales++;
		}
		itDoc1++;
		itDoc2++;
	}
	similitud = (double)cantIguales/(double)(BANDAS*FILAS);
	return 1.0-similitud;
}

unsigned LSH::masCercano(unsigned docNew){
	double distance = 2; //la distancia está entre 0 y 1
	unsigned doc = 0;
	for (unsigned i = 0; i < this->hashmins.size(); i++){
		if (i == docNew){continue;}
		double distAux = this->distancia(i,docNew);
		if (distAux <= distance){
			distance = distAux;
			doc = i;
		}
	}
	return doc;
}


LSH::~LSH(){
	delete[] this->buckets;
	delete this->vLideres;
}
