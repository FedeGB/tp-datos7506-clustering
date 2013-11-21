#include "Parser.h"
#include "Hash.h"
#include "Indexador.h"
#include "minHash.h"
#include "Document.h"
#include "LSH.h"
#include <iostream>

using namespace std;

int main() {
	
	Indexador indexar("./docs/");
	Document* doc_actual;
	Parser* parser;
	minHash hashmin(7);
	vector<vector<uint64_t>* > hashDocs;
	unsigned cantDocs = 0;
	while(indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		parser = new Parser(indexar.Path+doc_actual->name,7);
		vector<uint64_t>* hashings = new vector<uint64_t>(240);
		while (parser->tieneShingle()) {
			hashmin.doMinHash(parser->obtenerShingle(),*hashings);
		}
		hashDocs.push_back(hashings);
		delete parser;
		delete doc_actual;
		cantDocs++;
	}

	LSH lsHashing(cantDocs,hashDocs);
	lsHashing.doLsh();

	for (vector<vector<uint64_t>*>::iterator it = hashDocs.begin(); it != hashDocs.end(); ++it){
		delete (*it);
	}
	return 0;
}
