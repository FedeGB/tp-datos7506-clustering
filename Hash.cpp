#include "Hash.h"
#include <chrono>
#include <random>
#include <cstdlib>
#include <fstream>

#define N 8

using std::vector;
using std::uint64_t;

Hash::Hash(unsigned cantFuncs) {
	for (unsigned i = 0; i<cantFuncs; i++){
		vector<uint64_t> nums;
		for (unsigned j = 0; j < N; j++){
			nums.push_back(this->generarValorRandom());
		}
		this->valoresGenerados.push_back(nums);
	}
}

Hash::~Hash() {}

//Genera un numero entero grande sin signo random
uint64_t Hash::generarValorRandom() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 generator(seed);
	std::uniform_int_distribution<uint64_t> distribution(0,M-1);
	return (distribution(generator) % M);
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
uint64_t Hash::calcularFuncion(unsigned numeroDeFuncion, unsigned char buffer[]) {
	uint64_t resultado = 0;
	vector<uint64_t>& vAux = this->valoresGenerados[numeroDeFuncion];
	for (unsigned i = 0; i<N; i++) {
		resultado += (vAux[i]*buffer[i]);
	}
	return (resultado % M);
}

//Calcula la funcion correspondiente al numero pasado por parametro del valorAHashear
uint64_t Hash::hashear(uint64_t valorAHashear, unsigned numeroDeFuncion) {
	unsigned char buffer[N];
	this->splitClave(valorAHashear,buffer);
	return this->calcularFuncion(numeroDeFuncion,buffer);
}

void Hash::levantarValores(std::vector<std::vector<uint64_t> > valoresPrevios) {
	this->valoresGenerados = valoresPrevios;
}

void Hash::guardarValores(){ 
	std::ofstream vHashing("saves/valores.hash", std::ios::out | std::ofstream::binary | std::ios::trunc);
	for(std::vector<std::vector<uint64_t> >::iterator it = this->valoresGenerados.begin(); it != this->valoresGenerados.end(); ++it) {
		for(int i = 0; i < N; ++i) {
			vHashing.write((char*)&((*it).at(i)),8);
		}
	}
	vHashing.close();
}
