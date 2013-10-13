/*
 * Parser.h
 *
 *  Created on: 12/10/2013
 *      Author: eze
 */
#include <fstream>
#include <string>

#ifndef PARSER_H_
#define PARSER_H_

using namespace std;

class Parser{
private:
	static string stopwords[584];
	ifstream* archivo;
	string linea;
	//Convierte palabra a minúscula
	void toLowerCase(string& palabra);
	//Devuelve true si la palabra es una stopword
	bool esStopword(string palabra, string stopwords[]);

public:

	Parser(const string path);
	~Parser();
	//Devuelve true si se llego al fin del archivo
	bool eofDocument();

	void quitarStopword(string& palabra);

	void procesarArchivo();

	void reemplazarStopword(string& palabra);
};

#endif /* PARSER_H_ */
