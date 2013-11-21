#ifndef CLUSTER_H
#define CLUSTER_H

#include <set>
#include "Document.h"

// bool ncomp(Document* x, Document* y);
// bool(*fncompt)(Document*, Document*) = ncomp;

// class Cluster {
// 	private:
// 		std::set<Document*, bool(*)(Document*, Document*)> documentos(fncompt); // documentos pertenecientes al cluster ordenados por numero
// 		Document* clusteroide; // documento clusteroide
// 		float sumSim; // suma de las similaridades entre documentos
		
// 	public:
// 		Cluster(Document* lider);
// 		void agregarDoc(Document* doc, LSH& lsh); // Recibe la referencia del LSH para pedirle similaridades
// 		float calidad();
// 		Document* getClusteroide();
// 		~Cluster();
		
// };


#endif
