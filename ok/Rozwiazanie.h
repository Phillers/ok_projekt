#pragma once
//#include"Instancja.h"
class Instancja;
class Rozwiazanie
{
	Instancja* inst;
	int* kolejnosc1;
	int* kolejnosc2;
	int wartosc;
public:
	int policz();
	Rozwiazanie(Instancja* inst,int* kolejnosc);
	Rozwiazanie();
	~Rozwiazanie();
};

