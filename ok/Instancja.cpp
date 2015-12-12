#include "Instancja.h"






Instancja::Instancja(int n,Zadanie *zadania,int k,Przerwa *przerwy)
{
	this->zadania = zadania;
	this->przerwy = przerwy;
	this->k = k;
	this->n = n;
}

Instancja::~Instancja()
{
}
