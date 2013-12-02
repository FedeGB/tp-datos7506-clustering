#ifndef __BUCKET_H__
#define __BUCKET_H__

#include <vector>

#ifndef BANDAS
#define BANDAS 40
#endif // BANDAS
#ifndef FILAS
#define FILAS 6
#endif // FILAS

class Bucket{
private:
	std::vector<unsigned> docs;
	unsigned char offsets[BANDAS+1];
	unsigned char banda0;
public:
	Bucket();
	void agregarDoc(unsigned,unsigned char);
	unsigned size(unsigned char);
	bool isDocument(unsigned,unsigned char);
	bool areCandidatos(unsigned, unsigned);
	bool isDocument(std::vector<unsigned>&,unsigned char);
	bool areCandidatos(unsigned, std::vector<unsigned>&);
	bool vacio();
	~Bucket();

	void mostrar();

};


#endif // __BUCKET_H__
