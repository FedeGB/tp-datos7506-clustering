#include "Parser.h"


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

Parser::Parser(const string& path){
	this->archivo.open(path.c_str());
	if (!this->archivo.good()){
		this->archivo.close();
	}
}
Parser::~Parser(){
	if (this->archivo != NULL){
		this->archivo.close();
	}
}
//Devuelve true si se llego al fin del archivo
bool Parser::eofDocument(){
	return this->archivo.eof();
}

//Convierte palabra a minúscula
void Parser::toLowerCase(string& palabra){
	int i=0;
	for(string::iterator it = palabra.begin(); it!=palabra.end(); ++it){
    		palabra.at(i) = tolower(palabra.at(i));
		i++;
   	}
}
//Devuelve true si el caracter es una stopword
bool Parser::esStopword(const string& palabra,string stopwords[]){
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


void Parser::quitarStopword(const string& stpWord, string& line){
	unsigned posIni = line.find(stpWord);
	if (posIni != line.npos) {
		line.erase(posIni,stpWord.length()+1);
	}
}
void Parser::quitarNotAlfaNum(string& line) {
	unsigned i;
	for(i = 0; i < line.length(); i++) {
		int num_ascii = (int) line[i];
		// Si no es una letra en minuscula, numero o espacio
		if( !( ( (96 < num_ascii) && (num_ascii < 123) ) 
			|| ( (47 < num_ascii) && (num_ascii < 58) ) 
			|| (num_ascii == 32 ) ) ) {
			line.erase(i, 1);
		}
	}			
}


void Parser::procesarArchivo(){
	string line;
	while(getline(this->archivo,line)){
		string aux;
		this->toLowerCase(line);
		quitarNotAlfaNum(line);
		stringstream stream(line);
		while (getline(stream,aux, ' ')){
			if (this->esStopword(aux,this->stopwords))
				this->quitarStopword(aux,line);
		}
	}
}




