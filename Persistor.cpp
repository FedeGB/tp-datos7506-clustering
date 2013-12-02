#include "Persistor.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <string>

using std::string;

Persistor::Persistor() {
}

Persistor::~Persistor() {
}
void cleanDirectory(const string& path){
	struct dirent* nextFile;
	DIR *theFolder;
	string filepath;
	theFolder = opendir(path.c_str());
	while (nextFile = readdir(theFolder)){
		filepath = path;
		filepath += nextFile->d_name;
		remove(filepath.c_str());
	}
}

void Persistor::saveClusters(const std::vector<std::vector<uint64_t>* >& hashDocs, const std::vector<Cluster*>& clusters) {
	cleanDirectory("saves/clusters/");
	std::ofstream fClusteroids("saves/clusteroides.clus", std::ios::out | std::ofstream::binary | std::ios::trunc);
	int count = 1;
	for (std::vector<Cluster*>::const_iterator it = clusters.begin(); it != clusters.end(); ++it) {
		std::stringstream nombre;
		nombre << "saves/clusters/cluster";
		nombre << count; 
		nombre << ".txt";	
		std::ofstream fCluster(nombre.str().c_str(),std::ios::out | std::ios::trunc);
		count++;
		//Persisto el clusteroide que pertenece a un cluster con todos sus valores de minhash
		unsigned int nroClusteroide = ((*it)->getClusteroide())->number;
		std::vector<uint64_t>* hashClusteroide = hashDocs[nroClusteroide];
		for (std::vector<uint64_t>::iterator hashes = hashClusteroide->begin(); hashes != hashClusteroide->end(); ++hashes){
			//std::cout << (*hashes) << std::endl;
			//fClusteroids << (*hashes);
			fClusteroids.write((char*)&(*hashes),8);
		}
		//Guardo los nombres de los documentos que pertenecen a un cluster
		std::string name = (*it)->getClusteroide()->name;
		fCluster << name.c_str() << std::endl;
		(*it)->iniciarDocumentos();
		while ((*it)->tieneDocumentos()) {
			name = (*it)->obtenerDocumento()->name; 
			fCluster << name.c_str() << std::endl;
		}
		fCluster.close();
	}	
	fClusteroids.close();
}

void Persistor::cargarClusteroides(std::vector<std::vector<uint64_t>* >& hashDocs){
	std::ifstream fClusteroids("saves/clusteroides.clus", std::ios::in | std::ifstream::binary);
	unsigned int clusteroide=1;
	while (fClusteroids.good()) {
		std::vector<uint64_t>* hashes = new std::vector<uint64_t>;
		unsigned int i=0;
		while (fClusteroids.good() && i<240) {
			uint64_t hash;
			fClusteroids.read((char*)&hash,8);
			//fClusteroids >> hash;
			std::cout << "se guardo " << "clusteroide "<< clusteroide <<" hash: " << i << " " << hash << std::endl;
			hashes->push_back(hash);
			i++;
		}
		clusteroide++;
		hashDocs.push_back(hashes);
	}
	fClusteroids.close();
}
