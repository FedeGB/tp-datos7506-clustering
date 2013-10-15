#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <istream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <cstdlib>

#ifndef PARSER_H_
#define PARSER_H_
#define TAMANIO_STOPWORDS 584
using namespace std;

class Parser{
private:
	static string stopwords[TAMANIO_STOPWORDS];
	ifstream archivo;
	unsigned k;
	//Convierte palabra a minúscula
	void toLowerCase(string& palabra);
	//Devuelve true si la palabra es una stopword
	bool esStopword(const string& palabra,string stopwords[]);

public:

	Parser(const string& path, unsigned largoDeShingle);
	~Parser();
	//Devuelve true si se llego al fin del archivo
	bool eofDocument();

	void quitarStopword(const string& stpWord, string& line);
	
	void quitarNotAlfaNum(string& line);

	void procesarArchivo();

	string obtenerShingle();
};

#endif /* PARSER_H_ */
