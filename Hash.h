#ifndef __HASH_H__
#define __HASH_H__

#include <stdint.h>
#include <vector>

#define M 2305843009213693951
#define TAMANIO 240


class Hash {

private:
	std::vector<std::vector<uint64_t> > valoresGenerados;
public:
	explicit Hash(unsigned= TAMANIO);
	~Hash();
	uint64_t hashear(uint64_t, unsigned);
	void levantarValores(std::vector<std::vector<uint64_t> > valoresPrevios);
	void guardarValores();
private:
	void splitClave(uint64_t, unsigned char[]);

	uint64_t calcularFuncion(unsigned, unsigned char []);

	uint64_t generarValorRandom();
};

#endif /* HASH_H_ */
