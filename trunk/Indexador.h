#ifndef INDEXADOR_H
#define INDEXADOR_H

#include "Document.h"
#include <dirent.h>

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
