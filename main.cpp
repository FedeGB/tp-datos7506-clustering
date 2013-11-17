#include "Parser.h"
#include "Hash.h"
#include "Indexador.h"
#include "minHash.h"
#include "Document.h"
#include <iostream>

using namespace std;

int main() {
	
	Indexador indexar("./docs/");
	Document* doc_actual;
	Parser* parser;
	minHash hashmin(7);
	while(indexar.quedanArchivos()) {
		doc_actual = indexar.obtenerDocumento();
		parser = new Parser(indexar.Path+doc_actual->name,7);
		while (parser->tieneShingle()) {
			//cout << parser->obtenerShingle() << endl;
			parser->obtenerShingle();
		}
		delete parser;
		delete doc_actual;
	}
	vector<uint64_t> v;
	hashmin.doMinHash("aaaaaaa",v);
	for (vector<uint64_t>::iterator i = v.begin(); i != v.end(); ++i){
		cout<<*i<<endl;
	}

	return 0;
}
