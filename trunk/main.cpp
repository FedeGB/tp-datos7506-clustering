#include "Parser.h"

int main() {

	Parser *parser = new Parser("prueba.txt",7);
	while (parser->tieneShingle()) {
		cout << parser->obtenerShingle() << endl;
	}
	delete parser;
	return 0;
}

