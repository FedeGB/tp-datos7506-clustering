#ifndef INDEXADOR_H
#define INDEXADOR_H
#include <string>
#include <dirent.h>
#include <cstring>

class Document {
	public:
		string name;
		int number;
		
		Document(const string nombre, int numero);
		~Document();
	
};

class Indexador {
	private:
		struct dirent **ent_vector;
		int contador;
		const int cantidad;
		int filtro(const struct dirent *unDirent);
		
	public:
		string Path;

		Indexador(const string dirPath);
		~Indexador();
		
		bool quedanArchivos();
		Document obtenerDocumento();
		
};



#endif
