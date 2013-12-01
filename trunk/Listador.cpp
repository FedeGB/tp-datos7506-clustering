#include "Listador.h"
#include "Indexador.h"
#include "Document.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <iterator>

using std::set;
using std::vector;
using std::string;

bool ncomp(DuplaDoc* x, DuplaDoc* y) { 
	return x->nameDoc < y->nameDoc;
}

DuplaDoc::DuplaDoc(string nameDod) {
	this->nameDoc = nameDoc;
	this->numbersClusters = new vector<unsigned int>;
}

DuplaDoc::~DuplaDoc() {}

Listador::Listador() {}

void Listador::listarPorDocumentos() {
	set<DuplaDoc*, bool(*)(DuplaDoc*, DuplaDoc*)> documentsToList;
	Document* doc_actual;
	char nombreDoc[100];
	string path = string("saves/clusters");
	Indexador indexar(path);
	unsigned int contadorCluster = 1;
	while (indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		path.clear();
		path = string("saves/clusters/");
		path += doc_actual->name;
		std::ifstream cluster(path, std::ios::in);
		while (!cluster.eof()) {
			cluster >> nombreDoc;
			DuplaDoc* dupla_insert = new DuplaDoc(nombreDoc);  
			std::pair<std::set<DuplaDoc*, bool(*)(DuplaDoc*, DuplaDoc*)>::iterator,bool> status = documentsToList.insert(dupla_insert);
			if (!status.second) {
				set<DuplaDoc*, bool (*)(DuplaDoc*, DuplaDoc*)>::iterator dupla_modificar = documentsToList.find(dupla_insert);
				(*dupla_modificar)->numbersClusters->push_back(contadorCluster);
			}
		}
		cluster.close();
		contadorCluster++;
	}
	for(set<DuplaDoc*>::iterator it = documentsToList.begin(); it != documentsToList.end(); ++it) {
		std::cout << "El documento " << (*it)->nameDoc << " esta en el/los cluster/s: " << std::endl;
		for(vector<unsigned int>::iterator numCluster = (*it)->numbersClusters->begin(); numCluster != (*it)->numbersClusters->end(); ++numCluster) {
			std::cout << (*numCluster) << std::endl; 
		} 
	}
	for(set<DuplaDoc*>::iterator it = documentsToList.begin(); it != documentsToList.end(); ++it) {
		delete (*it)->numbersClusters;
		delete (*it);
	}



}