#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

class Document {
	private:
		bool clusteroide;
	
	public:
		std::string name;
		unsigned int number;
		
		Document(const std::string nombre, unsigned int numero);
		~Document();
		bool isClusteroid();
		void makeClusteroid(); // pasa a ser un clusteroide
		void notClusteroid(); // deja de ser clusteroide
	
};

#endif
