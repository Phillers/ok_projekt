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
	int* start1;
	int* konce;
	int* kolejnosc2;
	int* start2;
	int* konce2;
	int wartosc;
	void uporzadkuj2m();
public:
	int policz();
	Rozwiazanie(Instancja* inst);
	Rozwiazanie();
	void print();
	~Rozwiazanie();
};

