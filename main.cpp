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
#include <string.h>
#include <string>
#include <unistd.h>
// http://www.gnu.org/software/libc/manual/html_node/Getopt.html unistd.h 'man'

#define ARGERROR -1

using namespace std;

int main(int argc, char** argv) {
	
	if( argc < 2 ) {
		fprintf(stderr, "La cantidad de argumentos es insuficiente\n");
		return ARGERROR;
	}
	
	int opt, dflag, oflag, k;
	dflag = oflag = k = 0;
	std::string path;
	bool multiple = false;
	
	while( (opt = getopt(argc, argv, "a:c::d:glo:")) != -1 ) {
		
		switch(opt) {
			case 'a':
				if(argc > 3) {
					fprintf(stderr, "Hay parametros de más\n");
					return ARGERROR;
				}
				
				return 0;
			
			case 'c':
				k = (unsigned)atoi(argv[optind]);
				break;
			
			case 'd':
				path = std::string(optarg);
				dflag = 1;
				break;
			
			case 'g':
				if(argc > 2) {
					fprintf(stderr, "Hay parametros de más\n");
					return ARGERROR;
				}
				
				return 0;
			
			case 'l':
				if(argc > 2) {
					fprintf(stderr, "Hay parametros de más\n");
					return ARGERROR;
				}
				
				return 0;
			
			case 'o':
				if(strcmp(argv[optind], "Y") == 0) {
					multiple = true;
				}
				if(strcmp(argv[optind], "N") == 0) {
					multiple = false;
				}
				else {
					fprintf(stderr, "El argumento del parametro -o es incorrecto\n");
					return ARGERROR;
				}
				oflag = 1;
				break;
				
			case '?':
				if( optopt == 'd' ) {
					fprintf(stderr, "Falto el path a los documentos\n");
				}
				if( optopt == 'o' ) {
					fprintf(stderr, "Falto indicar el argumento de -o\n");
				}
				if( optopt == 'a' ) {
					fprintf(stderr, "Falto el path al documento a agregar\n");
				}
				else {
					fprintf(stderr, "Parametro no reconocido\n");
				}
				return ARGERROR;
			default:
				return ARGERROR;
			
		}
	}
	
	// Llegamos aca si es un repositorio nuevo y hacemos el cluster de 0
	// En los demas casos se resuelve dentro del case correspondiente
	if(!dflag && !oflag) {
		fprintf(stderr, "Falto algun parametro\n");
		return ARGERROR;
	}
	
	Indexador indexar(path);
	Document* doc_actual;
	Parser* parser;
	minHash hashmin(7);
	vector<vector<uint64_t>* > hashDocs;
	vector<Document*> docs;
	Cluster* cluster;
	unsigned cantDocs = 0;
	
	cout << "Indexando arhchivos..." << endl;
	while(indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		parser = new Parser(indexar.Path+doc_actual->name,7);
		vector<uint64_t>* hashings = new vector<uint64_t>(240);
		while (parser->tieneShingle()) {
			hashmin.doMinHash(parser->obtenerShingle(),*hashings);
		}
		hashDocs.push_back(hashings);
		docs.push_back(doc_actual);
		delete parser;
		cantDocs++;
	}

	LSH lsHashing(cantDocs,hashDocs);
	lsHashing.doLsh();
	
	vector<Cluster*> conjunto;
	GeneradorCluster generador;
	
	if(k != 0 ) {
		generador.obtenerClusters(k, multiple, docs, conjunto, lsHashing);
	}
	else {
		generador.KMeans(cantDocs, multiple, docs, conjunto, lsHashing);
	}

	Persistor persistor;
	persistor.saveClusters(hashDocs,conjunto);
	
	// Liberamos memoria
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
