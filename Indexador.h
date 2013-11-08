#include <iostream>
#include <string>
#include <dirent.h>
#include <cstring>
#include <stdlib.h>

#ifndef INDEXADOR_H
#define INDEXADOR_H
using namespace std;

class Document {
	public:
		string name;
		int number;
		
		Document(const string nombre, int numero);
		~Document();
	
};

class Indexador {
	private:
		DIR *directorio;
		struct dirent *actual;
		int contador;
		int filtro(const struct dirent *unDirent);
		
	public:
		string Path;

		Indexador(const string dirPath);
		~Indexador();
		
		bool quedanArchivos();
		Document* obtenerDocumento();
		
};



#endif
