#include "Bucket.h"

#include <iostream>

using std::vector;

Bucket::Bucket(){
	for (int i = 0; i < BANDAS+1; i++){
		this->offsets[i] = 0;
	}
	this->banda0 = -1;
}

void Bucket::agregarDoc(unsigned doc,unsigned char band){
	unsigned pos = this->offsets[band];
	if (pos == 0 && band != banda0){
		pos = this->offsets[band] = this->docs.size();
		if (this->docs.size() == 0){
			this->banda0 = band;
		}
	}
	unsigned posSig = this->offsets[band+1];
	if (posSig == 0){
		this->docs.push_back(doc);
		this->offsets[band+1] = pos +1;
	} else {
		vector<unsigned>::iterator it = this->docs.begin();
		it+= pos;
		this->docs.insert(it,doc);
		this->offsets[band+1] += 1;
	}
}

unsigned Bucket::size(unsigned char band){
	return (this->offsets[band+1] - this->offsets[band]);
}
bool Bucket::isDocument(unsigned doc,unsigned char band){
	unsigned pos = this->offsets[band];
	if (band != this->banda0 && pos == 0){
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
