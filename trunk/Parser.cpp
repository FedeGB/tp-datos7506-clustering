#include "Parser.h"
#include <cctype>
#include <sstream>
#include <iterator>


using namespace std;

string Parser::stopwords[TAMANIO_STOPWORDS] = {"a", "able", "about", "above", "accordance", "according", "accordingly", "across", "act", "actually", "added",
		"affected", "affecting", "affects", "after", "afterwards", "again", "against", "ah", "all", "almost", "alone",
		"along", "already", "also", "although", "always", "am", "among", "amongst", "an", "and", "announce", "another",
		"any", "anybody", "anyhow", "anymore", "anyone", "anything", "anyway", "anyways", "anywhere", "apparently",
		"approximately", "are", "arise", "around", "as", "aside", "ask", "asking", "at", "available", "away", "awfully",
		"back", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "begin", "beginning",
		"beginnings", "begins", "behind", "being", "believe", "below", "beside", "besides", "between", "beyond", "both", "brief",
		"briefly", "but", "by", "came", "can", "can't", "cannot", "cause", "causes", "certain", "certainly", "come", "comes",
		"contain", "containing", "contains", "could", "couldnt", "date", "did", "didn't", "different", "do", "does", "doesn't",
		"doing", "don't", "done", "down", "downwards", "due", "during", "each", "effect", "eg", "eight", "eighty", "either",
		"else", "elsewhere", "end", "ending", "enough", "especially", "even", "ever", "every", "everybody", "everyone",
		"everything", "everywhere", "ex", "except", "far", "few", "fifth", "first", "five", "fix", "followed", "following",
		"follows", "for", "former", "formerly", "forth", "found", "four", "from", "further", "furthermore", "gave", "get", "gets",
		"getting", "give", "given", "gives", "giving", "go", "goes", "gone", "got", "gotten", "had", "happens", "hardly", "has",
		"hasn't", "have", "haven't", "having", "he", "hed", "hence", "her", "here", "hereafter", "hereby", "herein", "hers",
		"herself", "hi", "hid", "him", "himself", "his", "hither", "home", "how", "howbeit", "however", "hundred", "i", "i'll",
		"i've","id", "ie", "if", "immediate", "immediately", "importance", "important", "in", "inc", "indeed", "index", "information", "instead",
		"into", "invention", "inward", "is", "isn't", "it", "it'll", "its", "itself", "just", "keep", "keeps", "kept", "kg",
		"km", "know", "known", "knows", "largely", "last", "lately", "later", "latter", "latterly", "least", "less", "lest", "let",
		"lets", "like", "liked", "likely", "line", "little", "look", "looking", "looks", "made", "mainly", "make", "makes", "many",
		"may", "maybe", "me", "mean", "means", "meantime", "meanwhile", "merely", "mg", "might", "million", "miss", "ml", "more",
		"moreover", "most", "mostly", "much", "must", "my", "myself", "name", "namely", "nay", "near", "nearly", "necessarily",
		"necessary", "need", "needs", "neither", "never", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non",
		"none", "nonetheless", "noone", "nor", "normally", "not", "noted", "nothing", "now", "nowhere", "obtain", "obtained",
		"obviously", "off", "often", "oh", "ok", "okay", "old", "omitted", "on", "once", "one", "ones", "only", "onto", "or",
		"other", "others", "otherwise", "ought", "our", "ours", "ourselves", "out", "outside", "over", "overall", "owing", "own",
		"page", "pages", "part", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus", "poorly", "possible",
		"possibly", "potentially", "predominantly", "present", "previously", "primarily", "probably", "promptly", "proud", "provides",
		"put", "quickly", "quite", "ran", "rather", "readily", "really", "recent", "recently", "regarding", "regardless", "regards",
		"related", "relatively", "research", "respectively", "resulted", "resulting", "results", "right", "run", "said", "same", "saw",
		"say", "saying", "says", "sec", "section", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sent",
		"seven", "several", "shall", "she", "she'll", "shed", "shes", "should", "shouldn't", "show", "showed", "shown", "showns", "shows",
		"significant", "significantly", "similar", "similarly", "since", "six", "slightly", "so", "some", "somebody", "somehow", "someone",
		"something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specifically", "specified", "specify", "specifying",
		"still", "stop", "strongly", "sub", "substantially", "successfully", "such", "sufficiently", "suggest", "sure", "take", "taken",
		"taking", "tell", "tends", "th", "than", "thank", "thanks", "that", "that'll", "thats", "the", "their", "theirs", "them", "themselves",
		"then", "thence", "there", "there'll", "there've", "thereafter", "thereby", "therefore", "therein", "thereof", "thereto", "thereupon",
		"these", "they", "they'll", "they've", "theyre", "think", "this", "those", "thou", "though", "thousand", "through", "throughout",
		"thus", "tip", "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "trying", "twice", "two", "under",
		"unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon", "ups", "us", "use", "used", "useful", "usefully",
		"usefulness", "uses", "using", "usually", "value", "various", "very", "viz", "want", "wants", "was",
		"wasn't", "way", "we", "we'll", "we've", "wed", "welcome", "went", "were", "weren't", "what", "what'll", "whatever", "whats", "when",
		"whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "wheres", "whereupon", "wherever", "whether", "which",
		"while", "whim", "whither", "who", "who'll", "whod", "whoever", "whole", "whom", "whomever", "whose", "why", "widely", "willing", "wish",
		"with", "within", "without", "won't", "words", "world", "would", "wouldn't", "yes", "yet", "you", "you'll", "you've", "youd", "your", "youre",
		"yours", "yourself", "yourselves"};

Parser::Parser(const string& path, unsigned largoDeShingle) {
	this->archivo.open(path.c_str());
	if (!this->archivo.good()){
		this->archivo.close();
	}
	this->k=largoDeShingle;
	this->lineaActual = "";
}

Parser::~Parser(){
	if (this->archivo != NULL) {
		this->archivo.close();
	}
}

//Devuelve true si se llego al fin del archivo
bool Parser::eofDocument() {
	return this->archivo.eof();
}

//Convierte palabra a minúscula
void Parser::toLowerCase(string& palabra) {
	int i=0;
	for(string::iterator it = palabra.begin(); it!=palabra.end(); ++it) {
    	palabra.at(i) = tolower(palabra.at(i));
		i++;
   	}
}

//Devuelve true si el caracter es una stopword
bool Parser::esStopword(const string& palabra,string stopwords[]) {
	int Iarriba = (TAMANIO_STOPWORDS - 1);
	int Iabajo = 0;
	int Icentro;
	while (Iabajo <= Iarriba) {
   		Icentro = (Iarriba + Iabajo)/2;
   		if (stopwords[Icentro] == palabra)
			return true;
   		else
			if (palabra < stopwords[Icentro])
				Iarriba=Icentro-1;
			else
				Iabajo=Icentro+1;
   	}
	return false;
}

// Elimina las stopswords de la linea pasada como argumento
string Parser::eliminarStopwords(string& line) {
	stringstream stream(line);
	string aux;
	while (getline(stream,aux, ' ')){
		quitarNotAlfaNum(aux,true);
		if (this->esStopword(aux,this->stopwords)) {
			this->quitarStopword(aux,line);
		}
	}
	return line;
}

// Quita una stopword a una linea. Ambos pasados por parametro
// Pre: stpWord debe ser una stopword (no se verifica en el metodo)
void Parser::quitarStopword(const string& stpWord, string& line) {
	string actual = line;
	unsigned posIni = line.find(stpWord);
	unsigned i = posIni;
	int idx;
	while(i != actual.npos) {
		if(i != 0) {
			if((int)actual[i-1] != 32) {
				actual = actual.substr(i);
				i = actual.find(stpWord);
				posIni += (i);
				continue;
			}
		}
		idx = 0;
		while(stpWord[idx] == actual[i]) {
			idx++;
			i++;
		}
		if(esAlfaNum((int)actual[i])) { // Si es una letra o numero, no es stpWord
			posIni += idx;
			actual = actual.substr(i);
			i = actual.find(stpWord);
			posIni += i ;
			continue;
		} else { // Si paso todo, es nuestra stpWord
			break;
		}
	}
	if (posIni != line.npos) {
		line.erase(posIni,stpWord.length()+1);
	}
}

// Verifica si el numero ascii pasado por parametro es un numero
// o una letra minuscula
// Post: devuelve true en caso de serlo
bool Parser::esAlfaNum(int number) {
	if( !( ( (96 < number) && (number < 123) )
			|| ( (47 < number) && (number < 58) ) ) ) {
		return false;
	}
	return true;
}

// Quita los caracteres que no sean letras o numeros de la linea
// pasada por argumento. Tambien recibe un booleano para indicar si
// solo se quiere eliminar los caracteres no alfanumericos de los bordes
// de la linea (este caso es mas util para cuando la linea es solo una palabra)
// Por default el booleano de 'bordes' esta puesto en false
void Parser::quitarNotAlfaNum(string& line, bool bordes = false) {
	unsigned i;
	i = 0;
	while(i < line.length()) {
		if(bordes) {
			if( i != 0 && i != line.length()-1) {
				i++;
				continue;
			}
		}
		int num_ascii = (int) line[i];
		// Si no es una letra en minuscula, numero o espacio
		if( !( esAlfaNum(num_ascii) || (num_ascii == 32)
				|| (num_ascii == 45)
				|| (num_ascii == 95) ) ) {
				line.erase(i, 1);
				i--;
		} else {
				// Si es algun guion (medio o bajo)
				if ((num_ascii == 45) || (num_ascii == 95)) {
					if(i != 0 && i != line.length()-1 ) {	
						if(esAlfaNum((int)line[i-1]) && esAlfaNum((int)line[i+1])) {
							line[i] = ' ';
							i++;
							continue;
						}
					}
					line.erase(i, 1);
				}
		}
		i++;
	}                       
}

// Limpia los espacios multiples contiguos de una linea pasada por
// argumento. Espacios multiples son considerados 2 o mas espacios contiguos
void Parser::limpiarEspaciosMultiples(string& line) {
	unsigned i, posIni;
	i = 0;
	int ascii;
	int count = 0;
	while( i < line.length() ) {
		ascii = (int)line[i];
		if( ascii == 32 ) {
			if( count == 0 ) {
				posIni = i;
			}
			count++;
		} else {
			if( count > 1 ) {
				line.erase(posIni, count-1);
			}
			count = 0;
		}
		i++;
	}
}

// Procesa la linea pasada por argumento
// Post: la linea termian con sus caracteres en minuscula, sin stopwords, 
// sin espacios multiples y unicamente con caracteres alfanumericos
void Parser::procesarLinea(string& line) {
	this->toLowerCase(line);
	this->eliminarStopwords(line);
	this->quitarNotAlfaNum(line);
	this->limpiarEspaciosMultiples(line);
}

// Devuelve un shingle del archivo
string Parser::obtenerShingle() {
	string aux = (this->lineaActual.substr(0,this->k));
	this->lineaActual.erase(0,1);
	return aux;
}

// Devuelve true en caso de haber shingles que se pueden extraer del documento
bool Parser::tieneShingle() {
	if(this->lineaActual == "") {
		getline(this->archivo,this->lineaActual);
		this->procesarLinea(this->lineaActual);
	}
	
	while (this->lineaActual.length() < k) {
		string lineaSiguiente = "";
		if(archivo.good()){
			getline(this->archivo,lineaSiguiente);
			if (!lineaSiguiente.empty()) {
				this->lineaActual += ( " " + lineaSiguiente);
				this->procesarLinea(this->lineaActual);
			}
		}else {
			return false;
		}
	}
	return true;
}
