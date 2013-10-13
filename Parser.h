#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <istream>

#ifndef PARSER_H_
#define PARSER_H_
#define TAMANIO_STOPWORDS 584
using namespace std;

class Parser{
private:
	static string stopwords[TAMANIO_STOPWORDS];
	ifstream archivo;
	string linea;
	//Convierte palabra a minúscula
	void toLowerCase(string& palabra);
	//Devuelve true si la palabra es una stopword
	bool esStopword(string palabra, string stopwords[]);

public:

	Parser(const string& path);
	~Parser();
	//Devuelve true si se llego al fin del archivo
	bool eofDocument();

	void quitarStopword(string& palabra);

	void procesarArchivo();

	void reemplazarStopword(string& palabra);
};

#endif /* PARSER_H_ */
