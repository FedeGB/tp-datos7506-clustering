#ifndef _GENERADORCLUSTER_H_
#define _GENERADORCLUSTER_H_

#include <vector>
#include "Cluster.h"

class GeneradorCluster {
	private:
		std::vector<Cluster*>* conjuntoClusters;
				
	public:
		GeneradorCluster();
		~GeneradorCluster();
		double calidad();
		void obtenerClusters(int k, LSH& lsh);
		void KMeans(LSH& lsh);

};


#endif
