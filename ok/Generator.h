#pragma once
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;
class Generator
{
	//static int nr;
	int dlugoscOperacji,liczbaPrzerw;
public:
	static int nr;
	static const int n = 50;
	void generuj(int seed);
	Generator(int dlugoscOperacji, int liczbaPrzerw);
	~Generator();
};

