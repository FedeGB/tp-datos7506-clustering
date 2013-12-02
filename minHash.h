#ifndef __MIN_HASH_H__
#define __MIN_HASH_H__

#include <vector>
#include <string>
#include "Hash.h"

class minHash{
private:
    Hash hashing;
    char sizeShingle;
public:
	explicit minHash(char = 7);
	~minHash();
	void doMinHash(const std::string&, std::vector<uint64_t>&);
	unsigned masCercano(std::vector<std::vector<uint64_t>*>& vHashMin, std::vector<uint64_t>& vHashNew);
	void persistirHash();
	void levantarHash();

private:
	uint64_t calcFila(const std::string&);
	unsigned char card(char);
};

#endif // __MIN_HASH_H__
