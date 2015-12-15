#include "Generator.h"
int Generator::nr = 0;

void Generator::generuj(int seed)
{
	srand(seed);
	ofstream plik;
	stringstream nazwa;
	nazwa << "instancje\\inst" << nr;
	cout << nazwa.str();
	plik.open(nazwa.str());
	plik << "**** "<<nr<<" ****"<<endl;
	plik << n << endl;
	for (int i = 0; i < n; i++) {
		int t1 = rand() % dlugoscOperacji + 1;
		int t2= rand() % dlugoscOperacji + 1;
		int r = rand() % (2 * dlugoscOperacji);
		plik << t1 << ";" << t2 << ";" << r << ";"<< endl;
	}
	int start=0, time=0;
	plik << liczbaPrzerw << endl;
	for (int i = 0; i < liczbaPrzerw; i++) {
		start = rand() % ((n/liczbaPrzerw+1)*dlugoscOperacji) + start + time;
		time = rand() % dlugoscOperacji + 1;
		plik  << time << ";" << start << ";" << endl;
	}
	plik << "**** EOF ****" << endl;
	plik.close();
	nr++;
}

Generator::Generator(int dlugoscOperacji, int liczbaPrzerw)
{
	this->dlugoscOperacji = dlugoscOperacji;
	this->liczbaPrzerw = liczbaPrzerw;

}


Generator::~Generator()
{
}
