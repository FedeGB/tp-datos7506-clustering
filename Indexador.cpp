#include "Indexador.h"
#include <cstring>
#include <stdlib.h>

using std::string;

// Clase contenedroa de un documento
Document::Document(const string nombre, int numero) {
	this->name = nombre;
	this->number = numero;	
}

Document::~Document() {
}

// Constructor del indexador
Indexador::Indexador(const string dirPath) {
	this->contador = 0;
	this->Path = dirPath;
	this->directorio = opendir(dirPath.c_str());
}

// Al indexar un directorio nos encontramos con '.' y '..'
// Este metodo es para filtrar los mismos
// Tambien si unDirent es NULL pasaria el filtro
// solo hay que fijarse despues que hacer con el
int Indexador::filtro(const struct dirent *unDirent) {
	if(!unDirent) {
		return 1;
	}
	return (strcmp(unDirent->d_name, ".") && strcmp(unDirent->d_name, ".."));
}

// Se fija si quedan archivos para indexar
// Coloca el puntero en el siguiente archivo valido,
// en caso de no haber mas retorna false
// Pre: No toma en cuenta subdirectorios!
bool Indexador::quedanArchivos() {
	this->actual = readdir(this->directorio);
	while(!this->filtro(this->actual)) {
		this->actual = readdir(this->directorio);
	}

	if(this->actual)
		return true;
	return false;
}

// Devuelve un puntero a un objeto contenedor documento
// Pre: Siempre hay que preguntar si quedan archivos antes de querer obtener uno nuevo
// con el metodo 'quedanArchivos'
Document* Indexador::obtenerDocumento() {
	string nombreDoc(this->actual->d_name);
	Document* doc = new Document(nombreDoc, contador);
	this->contador++;
	return doc;
}

Indexador::~Indexador() {
	closedir(directorio);
}
