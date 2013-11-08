#include "Hash.h"

using namespace std;

Hash::Hash() {

	for (int i = 0; i<TAMANIO; i++) {
		for (int j = 0; j < N; j++) {
			this->valoresGenerados[i][j] = this->generarValorRandom();
		}
	}

}

Hash::~Hash() { }

//Genera un numero entero grande sin signo random
uint64_t Hash::generarValorRandom() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	default_random_engine generator (seed);
	uniform_int_distribution<uint64_t> distribution(0,M-1);
	return distribution(generator);
}

//Separa la clave de 8 bytes en 8 numeros de 1 byte
void Hash::splitClave(uint64_t clave, unsigned char buffer[]) {
	char shift = 64;
	for (int i = 0; i<N; i++) {
		shift -= N;		
		buffer[i] = (unsigned char)((clave >> shift) & 0xFF);	
	}
}

//Calcula la funcion correspondiente al numero pasado por parametro y guarda los valores en el buffer
uint64_t Hash::calcularFuncion(int numeroDeFuncion, unsigned char buffer[]) {
	uint64_t resultado = 0;
	for (int i = 0; i<N; i++) {
		resultado += (this->valoresGenerados[numeroDeFuncion][i]*buffer[i]);
	}
	return resultado;
}

//Calcula la funcion correspondiente al numero pasado por parametro del valorAHashear
uint64_t Hash::aplicarHash(uint64_t valorAHashear, int numeroDeFuncion) {
	unsigned char buffer[N];
	this->splitClave(valorAHashear,buffer);
	return this->calcularFuncion(numeroDeFuncion,buffer);
}