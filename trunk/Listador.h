#ifndef LISTADOR_H
#define LISTADOR_H

#include <set>
#include "Document.h"
#include "Cluster.h"
#include <vector>
#include <string>

class DuplaDoc {
	public:
		std::string nameDoc;
		std::vector<unsigned int>* numbersClusters; 
		DuplaDoc(std::string);
		~DuplaDoc();
		
};

bool ncomp(Dupla* x, Dupla* y);

class Listador {
		
	public:
		Listador();
		void listarPorDocumentos();
		void listarPorCluster();
		~Listador();
		
};
#endif
