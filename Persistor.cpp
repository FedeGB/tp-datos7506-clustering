#include "Persistor.h"
#include <string>
#include <sstream>
#include <fstream>
#include <ostream>

Persistor::Persistor() {
}

Persistor::~Persistor() {
}

void Persistor::saveClusters(const std::vector<std::vector<uint64_t>* >& hashDocs, const std::vector<Cluster*>& clusters) {

	std::ofstream fClusteroids("saves/clusteroides.bin");
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
			CDelta codificador(*hashes);
			uchar* codigoAGuardar = codificador.codigo; 
			fClusteroids << codigoAGuardar;//write no me dejaba guardar otra cosa que no sea char (!)
			//fClusteroids.write(codigoAGuardar, sizeof(codigoAGuardar));
		}
		//Guardo los nombres de los documentos que pertenecen a un cluster
		while ((*it)->tieneDocumentos()) {
			std::string nombre = (*it)->obtenerDocumento()->name; 
			//fCluster.write(nombre.c_str(), sizeof(nombre)); esta linea hace que se guarde cualquier cosa
			fCluster << nombre.c_str() << std::endl;
		}
		fCluster.close();
	}	
	fClusteroids.close();
}