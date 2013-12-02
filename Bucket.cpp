#include "Bucket.h"

#include <iostream>

using std::vector;

Bucket::Bucket(){
	for (int i = 0; i < BANDAS+1; i++){
		this->offsets[i] = 0;
	}
	this->banda0 = 0;
}

bool Bucket::vacio(){
	return this->docs.size() == 0;
}

// void Bucket::agregarDoc(unsigned doc,unsigned char band){
// 	unsigned pos = this->offsets[band];
// 	if (pos == 0 && band != banda0){
// 		pos = this->offsets[band] = this->docs.size();
// 		if (this->docs.size() == 0){
// 			this->banda0 = band;
// 		}
// 	}
// 	unsigned posSig = this->offsets[band+1];
// 	if (posSig == 0){
// 		this->docs.push_back(doc);
// 		this->offsets[band+1] = pos +1;
// 	} else {
// 		vector<unsigned>::iterator it = this->docs.begin();
// 		it+= pos;
// 		this->docs.insert(it,doc);
// 		this->offsets[band+1] += 1;
// 	}
// }

void Bucket::agregarDoc(unsigned doc,unsigned char band){
	this->docs.push_back(doc);
	for (unsigned i = band+1; i < BANDAS+1; i++){
		this->offsets[i]++;
	}
}

unsigned Bucket::size(unsigned char band){
	return (this->offsets[band+1] - this->offsets[band]);
}
bool Bucket::isDocument(unsigned doc,unsigned char band){
	unsigned pos = this->offsets[band];
	if (pos == 0 && band != this->banda0){
		return false;
	}
	vector<unsigned>::iterator end;
	end = this->docs.begin() + this->offsets[band+1];
	for (vector<unsigned>::iterator it = this->docs.begin()+pos;
	it != end; ++it){
		if (*it == doc){
			return true;
		}
	}
	return false;
}

bool Bucket::isDocument(vector<unsigned>& vDocs, unsigned char band){
	unsigned pos = this->offsets[band];
	if (band != this->banda0 && pos == 0){
		return false;
	}
	vector<unsigned>::iterator end;
	end = this->docs.begin() + this->offsets[band+1];
	for (vector<unsigned>::iterator it = this->docs.begin()+pos;
	it != end; ++it){
		for (vector<unsigned>::iterator i = vDocs.begin(); i != vDocs.end(); ++i){
			if (*it == *i){
				return true;
			}
		}
	}
	return false;
}

bool Bucket::areCandidatos(unsigned doc1, unsigned doc2){
	for (unsigned i = 0; i < BANDAS; i++){
		if (this->isDocument(doc1,i) && this->isDocument(doc2,i)){
			return true;
		}
	}
	return false;
}

bool Bucket::areCandidatos(unsigned doc1, vector<unsigned>& vDocs){
	for (unsigned i = 0; i < BANDAS; i++){
		if (this->isDocument(doc1,i) && this->isDocument(vDocs,i)){
			return true;
		}
	}
	return false;
}

Bucket::~Bucket(){}

void Bucket::mostrar(){
	for (unsigned char i = 0; i < BANDAS; i++){
		unsigned char offIni = this->offsets[i];
		if (offIni == 0 && i != banda0){
			continue;
		}
		std::cout<<"Banda "<<(int)i<<std::endl;
		unsigned* ptr = &this->docs[offIni];
		for (int j = offIni; j < this->offsets[i+1]; j++){
			std::cout<<"\t"<<*ptr<<std::endl;
			ptr++;
		}
	}
}
