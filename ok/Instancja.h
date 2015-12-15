#pragma once
#include "Zadanie.h"

class Instancja
{
	int n, k;
	Zadanie* zadania;
	Przerwa* przerwy;
	int pierwszaWartosc = 0;

public:
	int z();
	Zadanie z(int i);
	int p();
	Przerwa p(int i);
	Instancja(int n,Zadanie*,int k,Przerwa*);
	~Instancja();
};

