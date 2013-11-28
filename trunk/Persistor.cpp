#include "Persistor.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

Persistor::Persistor() {
}

Persistor::~Persistor() {
}

void Persistor::saveClusters(const std::vector<std::vector<uint64_t>* >& hashDocs, const std::vector<Cluster*>& clusters) {

	std::ofstream fClusteroids("saves/clusteroides.txt", std::ofstream::binary);
	int count = 1;
	for (std::vector<Cluster*>::const_iterator it = clusters.begin(); it != clusters.end(); ++it) {
		std::stringstream nombre;
		nombre << "saves/clusters/cluster";
		nombre << count; 
		nombre << ".txt";	
		std::ofstream fCluster(nombre.str().c_str());
		count++;
		//Persisto el clusteroide que pertenece a un cluster con todos sus valores de minhash
		unsigned int nroClusteroide = ((*it)->getClusteroide())->number;
		std::vector<uint64_t>* hashClusteroide = hashDocs[nroClusteroide];
		for (std::vector<uint64_t>::iterator hashes = hashClusteroide->begin(); hashes != hashClusteroide->end(); ++hashes){
			//std::cout << (*hashes) << std::endl;
			fClusteroids << (*hashes);
		}
		//Guardo los nombres de los documentos que pertenecen a un cluster
		(*it)->iniciarDocumentos();
		while ((*it)->tieneDocumentos()) {
			std::string nombre = (*it)->obtenerDocumento()->name; 
			fCluster << nombre.c_str() << std::endl;
		}
		fCluster.close();
	}	
	fClusteroids.close();
}

void Persistor::cargarClusteroides(std::vector<std::vector<uint64_t>* >& hashDocs){
	std::ifstream fClusteroids("saves/clusteroides.txt", std::ifstream::binary);
	unsigned int clusteroide=1;
	while (fClusteroids.good()) {
		std::vector<uint64_t>* hashes = new std::vector<uint64_t>(240);
		unsigned int i=0;
		while (fClusteroids.good() && i<240) {
			uint64_t hash;
			fClusteroids >> hash;
			std::cout << "se guardo " << "clusteroide "<< clusteroide <<" hash: " << i << " " << hash << std::endl;
			hashes->push_back(hash);
			i++;
		}
		clusteroide++;
		hashDocs.push_back(hashes);
	}
	fClusteroids.close();
}
