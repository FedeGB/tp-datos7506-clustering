#ifndef __LSH_H__
#define __LSH_H__

#include <vector>
#include <cstdint>
#include "Bucket.h"

class LSH{
private:
    Bucket* buckets;
    std::vector<std::vector<uint64_t>* >& hashmins;
    unsigned n; //cantidad de documentos
public:
	LSH(unsigned,std::vector<std::vector<uint64_t>*>&);
	void doLsh();
	~LSH();
};

#endif // __LSH_H__
