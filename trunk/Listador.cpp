#include "Listador.h"
#include "Indexador.h"
#include "Document.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <iterator>
#include <string.h>

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

Listador::~Listador() {}

void Listador::listarPorDocumentos() {
	set<DuplaDoc*, bool(*)(DuplaDoc*, DuplaDoc*)> documentsToList;
	Document* doc_actual = NULL;
	char nombreDoc[100];
	string path = string("saves/clusters");
	Indexador indexar(path);
	unsigned int contadorCluster = 1;
	DuplaDoc* dupla_insert = NULL;
	std::pair<std::set<DuplaDoc*, bool(*)(DuplaDoc*, DuplaDoc*)>::iterator,bool> status;
	while (indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		path.clear();
		path = string("saves/clusters/");
		path += doc_actual->name;
		std::ifstream cluster(path, std::ios::in);
		while (!cluster.eof()) {
			memset(nombreDoc, ' ', 100);
			cluster >> nombreDoc;
			dupla_insert = new DuplaDoc(string(nombreDoc));  
			status = documentsToList.insert(dupla_insert);
			if (!status.second) {
				set<DuplaDoc*, bool (*)(DuplaDoc*, DuplaDoc*)>::iterator dupla_modificar = documentsToList.find(dupla_insert);
				(*dupla_modificar)->numbersClusters->push_back(contadorCluster);
			}
		}
		cluster.close();
		contadorCluster++;
		delete doc_actual;
	}
	for(set<DuplaDoc*>::iterator it = documentsToList.begin(); it != documentsToList.end(); ++it) {
		std::cout << "El documento " << (*it)->nameDoc << " esta en el/los cluster/s: " << std::endl;
		for(vector<unsigned int>::iterator numCluster = (*it)->numbersClusters->begin(); numCluster != (*it)->numbersClusters->end(); ++numCluster) {
			std::cout << (*numCluster) << std::endl; 
		} 
	}
	for(set<DuplaDoc*>::iterator it = documentsToList.begin(); it != documentsToList.end(); ++it) {
		delete ((*it)->numbersClusters);
		delete (*it);
	}



}

void Listador::listarPorCluster() {
	std::string path("saves/clusters");
	Indexador indexar(path);
	char nombreDoc[100];
	Document* doc_actual = NULL;
	while(indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		if(doc_actual->name == ".svn") {
			delete doc_actual;
			continue;
		}
		path.clear();
		path = std::string("saves/clusters/");
		path += doc_actual->name;
		std::ifstream clus(path, std::ios::in);
		memset(nombreDoc, ' ', 100);
		clus >> nombreDoc;
		std::cout << "Categoria: " << nombreDoc << std::endl;
		std::cout << nombreDoc << std::endl;
		clus >> nombreDoc;
		while(!clus.eof()) {
			std::cout << nombreDoc << std::endl;
			memset(nombreDoc, ' ', 100);
			clus >> nombreDoc;
			
		}
		clus.close();
		delete doc_actual;
	}
}
