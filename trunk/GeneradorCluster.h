#ifndef _GENERADORCLUSTER_H_
#define _GENERADORCLUSTER_H_

#include <vector>
#include "Cluster.h"

class GeneradorCluster {	
	public:
		GeneradorCluster();
		~GeneradorCluster();
		double calidad(std::vector<Cluster*>& conjuntoClusters);
		void obtenerClusters(unsigned, bool, std::vector<Document*>&, std::vector<Cluster*>&, LSH&, std::vector<unsigned>* = NULL);
		void KMeans(unsigned N, bool multiple, std::vector<Document*>& documentos, std::vector<Cluster*>& conjuntoClusters, LSH& lsh);

};


#endif
