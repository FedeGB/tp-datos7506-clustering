#include "Document.h"

using std::string;

// Clase contenedroa de un documento
Document::Document(const string nombre, unsigned int numero) {
	this->name = nombre;
	this->number = numero;	
	this->clusteroid = false;
}

bool Document::isCluteroid() {
	return this->clusteroide;
}

void Document::makeCluseroid() {
	this->clusteroide = true;
}

void Document::notClusteroid() {
	this->clusteroide = false;
}

Document::~Document() {
}
