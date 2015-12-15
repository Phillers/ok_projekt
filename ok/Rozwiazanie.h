#pragma once
#include<cstdlib>
#include<ctime>
#include<iostream>
#include"Zadanie.h"
#include"Instancja.h"

using namespace std;
class Rozwiazanie
{
	Instancja* inst;
	int* kolejnosc1;
	int* kolejnosc2;
	int wartosc;
public:
	int policz();
	Rozwiazanie(Instancja* inst);
	Rozwiazanie();
	void print();
	~Rozwiazanie();
};

