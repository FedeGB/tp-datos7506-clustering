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
	~Bucket();

	void mostrar();

};


#endif // __BUCKET_H__
