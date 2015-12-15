#include "Rozwiazanie.h"



int Rozwiazanie::policz()
{
	return 0;
}

Rozwiazanie::Rozwiazanie(Instancja* inst)
{
	srand(time(0));
	this->inst = inst;
	int n = inst->z();
	kolejnosc1 = new int[n];
	kolejnosc2 = new int[n];
	for (int i = 0; i < 50; i++) {
		kolejnosc1[i] = i;
		kolejnosc2[i] = i;
	}
	for (int i = 0; i < n; i++) {
		int a = rand() % n, b = rand() % n;
		int tmp = kolejnosc1[a];
		kolejnosc1[a] = kolejnosc1[b];
		kolejnosc1[b] = tmp;
		a = rand() % n;
		b = rand() % n;
		tmp = kolejnosc2[a];
		kolejnosc2[a] = kolejnosc2[b];
		kolejnosc2[b] = tmp;
	}

}

Rozwiazanie::Rozwiazanie()
{
}

void Rozwiazanie::print()
{
	for (int i = 0; i < inst->z(); i++) {
		cout << kolejnosc1[i] << "\t" << kolejnosc2[i] << endl;
	}
}


Rozwiazanie::~Rozwiazanie()
{
}
