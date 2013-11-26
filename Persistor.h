#ifndef __PERSISTOR_H__
#define __PERSISTOR_H__

#include "minHash.h"
#include "Codigos.h"
#include "Cluster.h"
#include <fstream>
#include <vector>

class Persistor {

public:
	Persistor();

	~Persistor();

	void saveClusters(const std::vector<std::vector<uint64_t>* >& hashDocs, const std::vector<Cluster*>& clusters);



};
#endif // __PERSISTOR_H__