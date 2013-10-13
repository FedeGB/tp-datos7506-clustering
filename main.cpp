#include "Parser.h"

int main() {

	Parser *parser = new Parser("prueba.txt");
	parser->procesarArchivo();
	delete parser;
	return 0;
}

