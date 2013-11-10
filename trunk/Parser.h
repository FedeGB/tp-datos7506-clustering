#ifndef PARSER_H_
#define PARSER_H_

#include <fstream>
#include <string>

#define TAMANIO_STOPWORDS 584

class Parser{
private:
	static std::string stopwords[TAMANIO_STOPWORDS];
	std::ifstream archivo;
	unsigned k;
	std::string lineaActual;
	//Convierte palabra a minúscula
	void toLowerCase(std::string& palabra);
	//Devuelve true si la palabra es una stopword
	bool esStopword(const std::string& palabra,std::string stopwords[]);

public:

	Parser(const std::string& path, unsigned largoDeShingle);
	~Parser();
	//Devuelve true si se llego al fin del archivo
	bool eofDocument();

	void quitarStopword(const std::string& stpWord, std::string& line);
	
	bool esAlfaNum(int number);
	
	void quitarNotAlfaNum(std::string& line, bool bordes);
	
	void limpiarEspaciosMultiples(std::string& line);

	void procesarLinea(std::string& line);

	std::string obtenerShingle();

	bool tieneShingle();

	std::string eliminarStopwords(std::string& line);
};

#endif /* PARSER_H_ */
