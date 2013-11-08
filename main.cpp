#include "Parser.h"
#include "Hash.h"

int main() {

	Parser *parser = new Parser("prueba.txt",7);
	Hash *hash = new Hash();
	/*while (parser->tieneShingle()) {
		cout << parser->obtenerShingle() << endl;
	}*/
	cout << hash->aplicarHash(235641235412245461,4) << endl;
	delete parser;
	delete hash;
	return 0;
}