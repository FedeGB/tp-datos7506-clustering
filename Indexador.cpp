#include "Indexador.h"

Document::Document(const string nombre, int numero) {
	this->name = nombre;
	this->number = numero;	
}

Document::~Document() {
}

Indexador::Indexador(const string dirPath) {
	this->contador = 0;
	this->Path = dirPath;
	// http://manpages.courier-mta.org/htmlman3/scandir.3.html
	this->cantidad = ::scandir(dirParh.c_str(), &ent_vector, &filtro, ::alphasort);

}

// Al indexar un directorio nos encontramos con '.' y '..'
// Este metodo es para filtrar los mismos en el scandir
int Indexador::filtro(const struct dirent *unDirent) {
  return (strcmp(unDirent->d_name, ".") && strcmp(unDirent->d_name, ".."));
}

bool Indexador::quedanArchivos() {
	if(contador < cantidad)
		return true;
	return false;
}

Document Indexador::obtenerDocumento() {
	string nombreDoc(ent_vector[contador]->d_name);
	// cout << "  Archivo indexado: " << nombreDoc;
	::free(ent_vector[contador]);
	Document doc = Document(nombreDoc, contador);
	this->contador++;
	return doc;
}

Indexador::~Indexador() {
	::free(ent_vector);
}
