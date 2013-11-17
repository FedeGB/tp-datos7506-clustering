#include "Cluster.h"

using std::set;

bool ncomp(Document* x, Document* y) { 
	
	return x->number < y->number;
}

Cluster::Cluster(Document* lider) {
	this->clusteroide = lider;
	this->documentos.insert(lider);
	lider->makeClusteroid();
	this->sumSim = 0;	
}

float Cluster::calidad() {
	unsigned int n = this->documentos.size();
	return (this->sumSim / ((n*(n-1))/2));
}


Document* getClusteroide() {
	return this->clusteroide;
}

void agregarDoc(Document* doc, LSH& lsh) {
	// Ahora estan ordenados por numero, habria q ver de ordenarlos por suma de distancia al cuadrado dentro del cluster
	for(std::set<Document*>::iterator it = this->documentos.begin(); it != this->documentos.end(); ++it) {
		// Calculo de similaridad  de doc con docs del cluster, LSH
		// sumSim += etc
		// sumamos distancia al cuadrada de la distancia actual a ambos documentos
	}
	this->documentos.insert(doc);
	// Si los tenemos ordenados por suma de sitancias al cuadrado el clusteroide lo podemos sacar tomando el primero del set o container que usemos
	// Sino habria q fijarse cual es el de menos suma de dist al cuadrado y ponerlo como clusteroide
	// De todas formas hay que marcar al documento correspondiente como lider y desmarcar al anterior si hubo cambio
		
}
