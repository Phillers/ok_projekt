#include "Instancja.h"




int Instancja::z()
{
	return n;
}

Zadanie Instancja::z(int i)
{
	return zadania[i];
}

int Instancja::p()
{
	return k;
}

Przerwa Instancja::p(int i)
{
	return przerwy[i];
}

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
