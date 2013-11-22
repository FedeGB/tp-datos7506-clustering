#include "Cluster.h"

using std::set;

bool ncomp(Dupla* x, Dupla* y) { 
	return x->sqdistance < y->sqdistance;
}

Dupla::Dupla(Document* doc, double dist) {
	this->documento = doc;
	this->sqdistance = dist;
}

void Dupla::sumarDistancia(double dist) {
	this->sqdistance += dist*dist;
}

Dupla::~Dupla() { }

Cluster::Cluster(Document* lider) {
	bool(*fncompt)(Dupla*, Dupla*) = ncomp;
	set<Dupla*, bool(*)(Dupla*, Dupla*)> documentos(fncompt);
	Dupla* dupla = new Dupla(lider, 0);
	this->documentos.insert(dupla);
	lider->makeClusteroid();
	this->sumSim = 0;	
}

double Cluster::calidad() {
	unsigned int n = this->documentos.size();
	return (this->sumSim / ((n*(n-1))/2));
}


Document* Cluster::getClusteroide() {
	return (*(documentos.begin()))->documento;
}

void Cluster::agregarDoc(Document* doc, LSH& lsh) {
	unsigned numero_act;
	double dist_act, aux;
	Dupla *dupla_act, *dupla_insert, *dupla_reemplazo;
	dupla_insert = new Dupla(doc, 0);
	for(std::set<Dupla*>::iterator it = this->documentos.begin(); it != this->documentos.end(); ++it) {
		dupla_act = *it;
		numero_act = dupla_act->documento->number;
		dist_act = lsh.distancia(numero_act, doc->number);
		this->sumSim += (1-dist_act);
		dupla_insert->sumarDistancia(dist_act);
		dupla_reemplazo = new Dupla(dupla_act->documento, dupla_act->sqdistance);
		dupla_reemplazo->sumarDistancia(dist_act);
		delete dupla_act;
		documentos.erase(it);
		documentos.insert(dupla_reemplazo);
	}
	this->documentos.insert(dupla_insert);		
}

Cluster::~Cluster() { }
