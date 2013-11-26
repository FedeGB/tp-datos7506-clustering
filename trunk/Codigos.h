#ifndef CODIFICACION_H
#define CODIFICACION_H

/*
 * Codigos.h
 *
 *  Created on: 27 Jun 2013
 *      Author: GRUPO 19
 */

#include <cstddef>
#include <cstdint>

typedef unsigned char uchar;

class CDelta {
  private:
    // Escribe un codigo a una tira de bytes
    void escribirBinario(uchar* binario, uchar* code, size_t bits);

  public:
    uchar *codigo;
    int bits;
    int bytes;

    // Constructor de la clase
    CDelta(uint64_t numero);

    // Destructor de la clase
    virtual ~CDelta();
};

class DDelta {
  private:
    static void leerBinario(uchar* bytes, size_t nBytes, uchar* buffer);
    DDelta();

  public:
    // Decodifica los bits de un array de bytes
    // Post: Devuelve la cantidad de bits utilizados
    static int decodificar(uchar* bytes, size_t nBytes, uint64_t* numero);

    virtual ~DDelta();
};

/****************************
 * Funciones codificacion
 *****************************/

// Escribe un numero en unario
// recibe un buffer en donde depositara el codigo unario
int unary_code(uint64_t number, uchar* unary);

// Escribe un numero en binario con la cantidad de bits pedida
// Recibe un buffer en donde depositara el codigo binario
// Pre: el numero debe poder representarse con la cantidad de bits indicada
// Post: El codigo binario devuelto se lee de izquierda a derecha
int binary_code(uint64_t number, int bits, uchar* binary);

// Funcion que genera un codigo con una primera parte en codigo especificado (func)
// y la segunda parte en codigo binario
int base_code(uint64_t number, int func(unsigned long int, uchar*), uchar* vec);

// Escribe un numero en codigo gamma
// Recibe un buffer en el cual se depositara el codigo gamma
int gamma_code(uint64_t number, uchar* gamma);

/****************************
 * Funciones decodificacion
 *****************************/

// Decodifica un codigo unario
uint64_t unary_decode(uchar* unary);

// Decodifica un codigo binario
uint64_t binary_decode(uchar* binary, size_t len);

// Decodifica un codigo gamma, y se le pasa un puntero a un entero para saber
// cuantos uchar decodifico del array
uint64_t gamma_decode(uchar* gamma, int* usados);

// Decodifica un codigo delta
uint64_t delta_decode(uchar* delta, int* usados);

#endif
