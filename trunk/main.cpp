#include "Parser.h"
#include "Hash.h"
#include "Indexador.h"

int main() {
	
	Indexador* indexar = new Indexador("./docs/");
	Document* doc_actual;
	Parser* parser;
	Hash *hash = new Hash();
	while(indexar->quedanArchivos()) {
		doc_actual = indexar->obtenerDocumento();
		parser = new Parser(indexar->Path+doc_actual->name,7);
		while (parser->tieneShingle()) {
			cout << parser->obtenerShingle() << endl;
		}
		delete parser;
		delete doc_actual;
	}
	cout << hash->aplicarHash(235641235412245461,4) << endl;
	delete indexar;
	delete hash;
	return 0;
}
