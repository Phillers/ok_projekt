#pragma once
#include "Zadanie.h"
#include"Rozwiazanie.h"
class Instancja
{
	int n, k;
	Zadanie* zadania;
	Przerwa* przerwy;
	int pierwszaWartosc = 0;

public:
	Rozwiazanie* generujLosowe();
	int z();
	Zadanie z(int i);
	int p();
	Przerwa p(int i);
	Instancja(int n,Zadanie*,int k,Przerwa*);
	~Instancja();
};

