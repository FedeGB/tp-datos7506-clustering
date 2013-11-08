#include "Parser.h"
#include "Indexador.h"

int main() {
	
	Indexador* indexar = new Indexador("./docs/");
	Document* doc_actual;
	Parser* parser;
	while(indexar->quedanArchivos()) {
		doc_actual = indexar->obtenerDocumento();
		parser = new Parser(indexar->Path+doc_actual->name,7);
		while (parser->tieneShingle()) {
			cout << parser->obtenerShingle() << endl;
		}
		delete parser;
		delete doc_actual;
	}
	delete indexar;
	return 0;
}

