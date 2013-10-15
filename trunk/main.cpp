#include "Parser.h"

int main() {

	Parser *parser = new Parser("prueba.txt",7);
	parser->procesarArchivo();
	delete parser;
	return 0;
}

