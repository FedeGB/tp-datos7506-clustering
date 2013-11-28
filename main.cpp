#include "Parser.h"
#include "Hash.h"
#include "Indexador.h"
#include "minHash.h"
#include "Document.h"
#include "Cluster.h"
#include "LSH.h"
#include "GeneradorCluster.h"
#include "Persistor.h"
#include <iostream>

using namespace std;

int main() {
	
	Indexador indexar("./docs/");
	Document* doc_actual;
	Parser* parser;
	minHash hashmin(7);
	vector<vector<uint64_t>* > hashDocs;
	vector<vector<uint64_t>* > hashDocs2;
	vector<Document*> docs;
	Cluster* cluster;
	unsigned cantDocs = 0;
	while(indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		parser = new Parser(indexar.Path+doc_actual->name,7);
		vector<uint64_t>* hashings = new vector<uint64_t>(240,18446744073709551615U);
		while (parser->tieneShingle()) {
			hashmin.doMinHash(parser->obtenerShingle(),*hashings);
		}
		hashDocs.push_back(hashings);
		docs.push_back(doc_actual);
		delete parser;
		//delete doc_actual;
		cantDocs++;
	}

	LSH lsHashing(cantDocs,hashDocs);
	lsHashing.doLsh();
	
	vector<Cluster*> conjunto;
	
	GeneradorCluster generador;
	//generador.obtenerClusters(3, true, docs, conjunto, lsHashing);
	generador.KMeans(cantDocs, false, docs, conjunto, lsHashing);
	// for (int i = 0; i < cantDocs; i++){
	// 	for (int j = 0; j < cantDocs; j++){
	// 		cout<<"Distancia "<<i<<" "<<j<<": "<<lsHashing.distancia(i,j)<<endl;
			
	// 	}
	// }

	Persistor persistor;
	persistor.saveClusters(hashDocs,conjunto);
	Persistor otroPersistor;
	otroPersistor.cargarClusteroides(hashDocs2);
	/*for (vector<vector<uint64_t>* >::iterator it1 = hashDocs2.begin(); it1 != hashDocs2.end(); ++it1){
		for (vector<uint64_t>::iterator it2 = (*it1)->begin(); it2 != (*it1)->end(); ++it2){
			std::cout << *it2 << std::endl;
		}
	}*/


	for (vector<vector<uint64_t>*>::iterator it = hashDocs2.begin(); it != hashDocs2.end(); ++it){
		delete (*it);
	}
	int i = 0;
	for (vector<vector<uint64_t>*>::iterator it = hashDocs.begin(); it != hashDocs.end(); ++it){
		delete docs[i];
		delete (*it);
		i++;
	}
	for(vector<Cluster*>::iterator ite = conjunto.begin(); ite != conjunto.end(); ++ite) {
		delete (*ite);
	}
	return 0;
}
