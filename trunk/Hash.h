#include <iostream>
#include <random>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <stdint.h>

#ifndef HASH_H_
#define HASH_H_
#define M 2305843009213693951
#define TAMANIO 240
#define N 8
using namespace std;

class Hash {

private:
	unsigned long long int valoresGenerados[TAMANIO][N];

	void splitClave(uint64_t clave, unsigned char buffer[]);

	uint64_t calcularFuncion(int numeroDeFuncion, unsigned char buffer[]);

	uint64_t generarValorRandom();
	
public:
	Hash();
	
	~Hash();

	uint64_t aplicarHash(uint64_t valorAHashear, int numeroDeFuncion);

};

#endif /* HASH_H_ */