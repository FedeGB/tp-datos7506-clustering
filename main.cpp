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
	
	int opt, dflag, oflag, aflag, gflag, lflag, k;
	aflag = gflag = lflag = dflag = oflag = k = 0;
	bool multiple = false;
	std::string path(" ");
	Document* doc_actual = NULL;
	
	while( (opt = getopt(argc, argv, "a:c::d:glo:")) != -1 ) {
		
		switch(opt) {
			case 'a':
				if(argc > 3) {
					fprintf(stderr, "Hay parametros de más\n");
					return ARGERROR;
				}
				aflag = 1;
				path = std::string(optarg);
				
				break;
			
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
				gflag = 1;
				
				break;
			
			case 'l':
				if(argc > 2) {
					fprintf(stderr, "Hay parametros de más\n");
					return ARGERROR;
				}
				
				lflag = 1;
				
				break;
			
			case 'o':
				if(strcmp(optarg, "Y") == 0) {
					multiple = true;
				}
				if(strcmp(optarg, "N") == 0) {
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
	
	
	if(gflag) {
		path = std::string("saves/clusters");
		Indexador indexar(path);
		char nombreDoc[100];
		doc_actual = NULL;
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
			cout << "Categoria: " << nombreDoc << endl;
			cout << nombreDoc << endl;
			clus >> nombreDoc;
			while(!clus.eof()) {
				cout << nombreDoc << endl;
				memset(nombreDoc, ' ', 100);
				clus >> nombreDoc;
				
			}
			clus.close();
			delete doc_actual;
		}
				
		return 0;
	}
	if(lflag) {
		return 0;
	}
	if(aflag) {
		return 0;
	}
	
	
	
	if(!dflag && !oflag) {
		fprintf(stderr, "Falto algun parametro\n");
		return ARGERROR;
	}
	
	Indexador indexar(path);
	Parser* parser;
	minHash hashmin(7);
	vector<vector<uint64_t>* > hashDocs;
	vector<Document*> docs;
	Cluster* cluster;
	unsigned cantDocs = 0;
	
	cout << "Indexando arhchivos..." << endl;
	while(indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		cout << "Indexando: " << doc_actual->name << endl;
		parser = new Parser(indexar.Path+doc_actual->name,7);
		vector<uint64_t>* hashings = new vector<uint64_t>(240,18446744073709551615U);
		while (parser->tieneShingle()) {
			hashmin.doMinHash(parser->obtenerShingle(),*hashings);
		}
		hashDocs.push_back(hashings);
		docs.push_back(doc_actual);
		delete parser;
		cantDocs++;
	}

	cout << "Construyendo LSH..." << endl;
	LSH lsHashing(cantDocs,hashDocs);
	lsHashing.doLsh();
	
	cout << "Generando clusters..." << endl;
	vector<Cluster*> conjunto;
	GeneradorCluster generador;
	
	if(k != 0 ) {
		cout << "Usted ha decidido generar "<<k<<" clusters..."<< endl;
		generador.obtenerClusters(k, multiple, docs, conjunto, lsHashing);
	}
	else {
		cout << "Realizando K-Means..." << endl;
		generador.KMeans(cantDocs, multiple, docs, conjunto, lsHashing);
	}

	cout << "Persistiendo clusters..." << endl;
	Persistor persistor;
	persistor.saveClusters(hashDocs,conjunto);

	cout << "Finalizando..." << endl;	
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
