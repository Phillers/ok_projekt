#pragma once
#include "Zadanie.h"
class Instancja
{
	int n, k;
	Zadanie* zadania;
	Przerwa* przerwy;

public:
	Instancja(int n,Zadanie*,int k,Przerwa*);
	~Instancja();
};

