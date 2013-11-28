#ifndef __PERSISTOR_H__
#define __PERSISTOR_H__

#include "minHash.h"
#include "Cluster.h"
#include <vector>

class Persistor {

public:
	Persistor();

	~Persistor();

	void saveClusters(const std::vector<std::vector<uint64_t>* >& hashDocs, const std::vector<Cluster*>& clusters);

	void cargarClusteroides(std::vector<std::vector<uint64_t>* >& hashDocs);

};
#endif // __PERSISTOR_H__
