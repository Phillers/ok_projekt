#pragma once
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<fstream>
#include<sstream>
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
	Rozwiazanie* mutacja(int x);
	Rozwiazanie* krzyzowanie(Rozwiazanie* partner);
	int w();
	void zapisz(int nr);
	static Rozwiazanie *sprawdz(int populacja, Rozwiazanie **tmp);
	static Rozwiazanie **selekcja(int min_populacja, int max_populacja, Rozwiazanie **roz);
	~Rozwiazanie();
};
