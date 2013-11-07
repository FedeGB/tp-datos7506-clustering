#ifndef CODIFICACION_H
#define CODIFICACION_H

#include <cstddef>

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
    CDelta(unsigned long int numero);

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
    static int decodificar(uchar* bytes, size_t nBytes, unsigned long int* numero);

    virtual ~DDelta();
};

/****************************
 * Funciones codificacion
 *****************************/

// Escribe un numero en unario
// recibe un buffer en donde depositara el codigo unario
int unary_code(unsigned long int number, uchar* unary);

// Escribe un numero en binario con la cantidad de bits pedida
// Recibe un buffer en donde depositara el codigo binario
// Pre: el numero debe poder representarse con la cantidad de bits indicada
// Post: El codigo binario devuelto se lee de izquierda a derecha
int binary_code(unsigned long int number, int bits, uchar* binary);

// Funcion que genera un codigo con una primera parte en codigo especificado (func)
// y la segunda parte en codigo binario
int base_code(unsigned long int number, int func(unsigned long int, uchar*), uchar* vec);

// Escribe un numero en codigo gamma
// Recibe un buffer en el cual se depositara el codigo gamma
int gamma_code(unsigned long int number, uchar* gamma);

/****************************
 * Funciones decodificacion
 *****************************/

// Decodifica un codigo unario
unsigned long int unary_decode(uchar* unary);

// Decodifica un codigo binario
unsigned long int binary_decode(uchar* binary, size_t len);

// Decodifica un codigo gamma, y se le pasa un puntero a un entero para saber
// cuantos uchar decodifico del array
unsigned long int gamma_decode(uchar* gamma, int* usados);

// Decodifica un codigo delta
unsigned long int delta_decode(uchar* delta, int* usados);

#endif
