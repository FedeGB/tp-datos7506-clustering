#include "GeneradorCluster.h"
#include <iostream>
#include <cmath>

#define DIFDIST 0.1 // Parametro para diferencia de distancias entre documentos
#define DIFCAL 0.1 // Parametro para diferencia de calidad de clusters

using std::vector;

GeneradorCluster::GeneradorCluster() { }

GeneradorCluster::~GeneradorCluster() { }

double GeneradorCluster::calidad(std::vector<Cluster*>& conjuntoClusters) {
	vector<Cluster*>::iterator it = conjuntoClusters.begin();
	double calidad = 0;
	while(it != conjuntoClusters.end()) {
		//std::cout << "Calidad clus= " << (*it)->calidad() << std::endl;
		calidad += (*it)->calidad();
		++it;
	}
	return calidad/conjuntoClusters.size();
}

void GeneradorCluster::obtenerClusters(unsigned k, bool multiple, vector<Document*>& documentos, vector<Cluster*>& conjuntoClusters, LSH& lsh) {
	vector<unsigned> lideres;
	lsh.getKLeaders(k, lideres);
	Cluster* actual;
	unsigned l;
	// Creamos los k Clusters con sus respectivos lideres
	for(l = 0; l < k; ++l) {
		actual = new Cluster(documentos.at(lideres[l]));
		conjuntoClusters.push_back(actual);
	}
	unsigned i = 0;
	unsigned aux;
	unsigned num_clusteroide, num_actual, seleccion;
	seleccion = 0;
	vector<unsigned> selecciones;
	double dist_actual, dist_menor, dif;
	while(i < documentos.size()) {
		if((documentos.at(i))->isClusteroid()) {
			++i;
			continue;
		}
		selecciones.clear();
		num_actual = (documentos.at(i))->number;
		l = 0; // Posicion conjuntoClusters
		dist_menor = 1.2;
		// Seleccion cluster/s a donde agregar el documento
		while(l < k) {
			num_clusteroide = ((conjuntoClusters.at(l))->getClusteroide())->number;
			dist_actual = lsh.distancia(num_actual, num_clusteroide);
			if(dist_actual < dist_menor) {
				dist_menor = dist_actual;
				seleccion = l;
				// Al for no entra en caso de no haber multiples pues selecciones siempre tendria 0 elementos
				for(unsigned t = 0; t < selecciones.size(); ++t) {
					dist_actual = lsh.distancia(num_actual, ((conjuntoClusters.at(selecciones[t]))->getClusteroide())->number);
					dif = dist_actual - dist_menor;
					if(dif > DIFDIST) {
						aux = selecciones[selecciones.size()-1];
						selecciones[t] = aux;
						selecciones.pop_back();
					}
				}
			}
			else if(multiple) {
				dif = dist_actual - dist_menor;
				if(dif <= DIFDIST)	
					selecciones.push_back(l);
			}
			++l;
		}
		// Agrego documento a cluster/s
		//std::cout << "AGREGO DOC: " << documentos.at(i)->number << std::endl;
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
	unsigned posIni = (unsigned)floor(sqrt((double)N));
	vector<Cluster*> conjuntoAux;
	double calidadAct, calidadSig, calidadAnt, difpre, difpost;
		
	while(posIni > 0) {
		//std::cout << "POS INI: " << posIni << std::endl;
		//std::cout << "k" << std::endl;
		this->obtenerClusters(posIni, multiple, documentos, conjuntoClusters, lsh);
		//std::cout << "k+1" << std::endl;
		this->obtenerClusters(posIni+1, multiple, documentos, conjuntoAux, lsh);
		calidadSig = this->calidad(conjuntoAux);
		for(vector<Cluster*>::iterator ite = conjuntoAux.begin(); ite != conjuntoAux.end(); ++ite) {
			delete (*ite);
		}
		conjuntoAux.clear();
		//std::cout << "k-1" << std::endl;
		this->obtenerClusters(posIni-1, multiple, documentos, conjuntoAux, lsh);
		calidadAnt = this->calidad(conjuntoAux);
		calidadAct = this->calidad(conjuntoClusters);
		//std::cout << "CALSIG: " << calidadSig << std::endl;
		//std::cout << "CALANT: " << calidadAnt << std::endl;
		difpre = calidadAct - calidadAnt;
		difpost = calidadSig - calidadAct;
		//std::cout << "DIFPRE: " << difpre << std::endl;
		//std::cout << "DIFPOST: " << difpost << std::endl;
		//std::cout << "DIFCAL: " << difpost - difpre << std::endl;
		if(difpost - difpre > DIFCAL) { // Este tema hay que ver bien los valores y demas...
			posIni = (unsigned)floor(sqrt((double)(N-posIni))) + posIni;
		}
		else {
			for(vector<Cluster*>::iterator ite = conjuntoAux.begin(); ite != conjuntoAux.end(); ++ite) {
				delete (*ite);
			}
			break;
		}
		for(vector<Cluster*>::iterator ite = conjuntoAux.begin(); ite != conjuntoAux.end(); ++ite) {
			delete (*ite);
		}
		for(vector<Cluster*>::iterator ite = conjuntoClusters.begin(); ite != conjuntoClusters.end(); ++ite) {
				delete (*ite);
		}
		conjuntoAux.clear();
		conjuntoClusters.clear();
	}	
}
