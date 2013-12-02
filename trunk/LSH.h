#ifndef __LSH_H__
#define __LSH_H__

#include <vector>
#include <cstdint>
#include "Bucket.h"

class LSH{
private:
	Bucket* buckets;
	std::vector<std::vector<uint64_t>* >& hashmins;
	std::vector<short>* vCantCand;
	unsigned n; //cantidad de documentos
public:
	LSH(unsigned,std::vector<std::vector<uint64_t>*>&);
	void doLsh();
	void initKLeaders();
	void getKLeaders(unsigned, std::vector<unsigned>&);
	double distancia(unsigned,unsigned);
	unsigned masCercano(unsigned);
	~LSH();
};

#endif // __LSH_H__
