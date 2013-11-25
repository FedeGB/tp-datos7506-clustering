#ifndef CLUSTER_H
#define CLUSTER_H

#include <set>
#include "Document.h"
#include "LSH.h"

class Dupla {
	public:
		Document* documento;
		double sqdistance;
		Dupla(Document *doc, double dist);
		void sumarDistancia(double dist);
		~Dupla();
		
};

bool ncomp(Dupla* x, Dupla* y);



class Cluster {
	private:
		std::set<Dupla*, bool(*)(Dupla*, Dupla*)>* documentos; // documentos pertenecientes al cluster ordenados por numero
		double sumSim; // suma de las similaridades entre documentos
		
	public:
		Cluster(Document* lider);
		void agregarDoc(Document* doc, LSH& lsh); // Recibe la referencia del LSH para pedirle similaridades
		double calidad();
		Document* getClusteroide();
		~Cluster();
		
};


#endif
