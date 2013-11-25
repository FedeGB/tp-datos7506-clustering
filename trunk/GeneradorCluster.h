#ifndef _GENERADORCLUSTER_H_
#define _GENERADORCLUSTER_H_

#include <vector>
#include "Cluster.h"

class GeneradorCluster {	
	public:
		GeneradorCluster();
		~GeneradorCluster();
		double calidad(std::vector<Cluster*>& conjuntoClusters);
		void obtenerClusters(unsigned k, bool multiple, std::vector<Document*>& documentos, std::vector<Cluster*>& conjuntoClusters, LSH& lsh) ;
		void KMeans(unsigned N, bool multiple, std::vector<Document*>* documentos, std::vector<Cluster*>* conjuntoClusters, LSH& lsh) ;

};


#endif
