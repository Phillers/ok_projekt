#pragma once
#include "Zadanie.h"

class Instancja
{
	int n, k;
	Zadanie* zadania;
	Przerwa* przerwy;

public:
	int pierwszaWartosc = 0;
	int z();
	Zadanie& z(int i);
	int p();
	Przerwa& p(int i);
	Instancja(int n,Zadanie*,int k,Przerwa*);
	~Instancja();
};

