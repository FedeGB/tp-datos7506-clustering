#include "GeneradorCluster.h"
#include <iostream>

#define DIFDIST 0.1 // Parametro para diferencia de distancias entre documentos
#define DIFCAL 0.1 // Parametro para diferencia de calidad de clusters

using std::vector;

GeneradorCluster::GeneradorCluster() { }

GeneradorCluster::~GeneradorCluster() { }

double GeneradorCluster::calidad(std::vector<Cluster*>& conjuntoClusters) {
	
}

void GeneradorCluster::obtenerClusters(unsigned k, bool multiple, vector<Document*>& documentos, vector<Cluster*>& conjuntoClusters, LSH& lsh) {
	vector<unsigned> lideres;
	lsh.getKLeaders(k, lideres);
	Cluster* actual;
	unsigned l;
	// Creamos los k Clusters con sus respectivos lideres
	for(l = 0; l < k; ++l) {
		actual = new Cluster(documentos.at(lideres[l]));
		conjuntoClusters[l] = actual;
	}
	unsigned i = 0;
	unsigned num_clusteroide, num_actual, seleccion;
	vector<unsigned> selecciones;
	double dist_actual, dist_menor, dif;
	while(i < documentos.size()) {
		if((documentos.at(i))->isClusteroid()) {
			++i;
			continue;
		}
		selecciones.clear();
		num_actual = (documentos.at(i))->number;
		l = 0;
		dist_menor = 1;
		// Seleccion cluster/s a donde agregar el documento
		while(l < k) {
			num_clusteroide = ((conjuntoClusters.at(l))->getClusteroide())->number;
			dist_actual = lsh.distancia(num_actual, num_clusteroide);
			if(dist_actual < dist_menor) {
				dist_menor = dist_actual;
				seleccion = l;
			}
			else if(multiple) {
				dif = dist_actual - dist_menor;
				if(dif <= DIFDIST)	
					selecciones.push_back(l);
			}
			++l;
		}
		// Agrego documento a cluster/s
		(conjuntoClusters.at(seleccion))->agregarDoc(documentos.at(i), lsh);
		if(multiple) {
			for(unsigned s = 0; s < selecciones.size(); ++s) {
				(conjuntoClusters.at(selecciones[s]))->agregarDoc(documentos.at(i), lsh);
			}
		}
		++i;
	}
}

void GeneradorCluster::KMeans(unsigned N, bool multiple, vector<Document*>& documentos, vector<Cluster*>& conjuntoClusters, LSH& lsh) {
	
}
