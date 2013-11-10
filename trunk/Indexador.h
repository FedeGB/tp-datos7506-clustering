#ifndef INDEXADOR_H
#define INDEXADOR_H

#include <string>
#include <dirent.h>

class Document {
	public:
		std::string name;
		int number;
		
		Document(const std::string nombre, int numero);
		~Document();
	
};

class Indexador {
	private:
		DIR *directorio;
		struct dirent *actual;
		int contador;
		int filtro(const struct dirent *unDirent);
		
	public:
		std::string Path;

		Indexador(const std::string dirPath);
		~Indexador();
		
		bool quedanArchivos();
		Document* obtenerDocumento();
		
};

#endif
