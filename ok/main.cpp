#include"Generator.h"
#include"Zadanie.h"
#include"Instancja.h"
#include"Rozwiazanie.h"
#include <time.h>

#define max_populacja 200
#define min_populacja 50
//niech zawsze daja reszte z dzielenia 0(i najlepiej podzielne przez 2)
//bo inaczej w selekcji nie beda braly udzial wszystkie rozwiazania


void generuj() {
	//20
	for (int i = 1; i <= 5; i++) {
		Generator a(20, i * Generator::n/10);
		a.generuj(0);
		a.generuj(1);
	}
	//200
	for (int i = 1; i <= 5; i++) {
		Generator a(200, i * Generator::n / 10);
		a.generuj(0);
		a.generuj(1);
	}
	


}

Instancja* wczytaj(int nr) {
	stringstream nazwa;
	nazwa << "instancje\\inst" << nr;
	ifstream plik;
	plik.open(nazwa.str());
	string a;
	getline(plik,a);
	int n,k;
	char x;
	plik >> n;
	Zadanie* zadania=new Zadanie[n];
	for (int i = 0; i < n; i++) {
		int a, b, c;

		plik >> a >>x>> b >> x >> c >> x;
		//cout <<" "<< a << " " << b << " " << c<<endl;
		zadania[i].t1 = a;
		zadania[i].t2 = b;
		zadania[i].r = c;
	}
	plik >> k;
	Przerwa* przerwy = new Przerwa[k];
	for (int i = 0; i < k; i++) {
		int a, b;
		plik >> a >> x >> b >> x;
		//cout << " " << a << " " << b << endl;
		przerwy[i].t = a;
		przerwy[i].s = b;
		przerwy[i].k = a+b;
	}
	plik.close();
	Instancja* inst=new Instancja(n, zadania, k, przerwy);
	return inst;
}



int main() {
	//generuj();
	Instancja* instancja=wczytaj(0);
	instancja->pierwszaWartosc = 0;
	Rozwiazanie** roz = new Rozwiazanie *[max_populacja];
	for(int i = 0; i < max_populacja; i++)
		roz[i] = new Rozwiazanie(instancja);
	Rozwiazanie *poczatkowe = Rozwiazanie::sprawdz(min_populacja, roz);
	Rozwiazanie *najlepsze = poczatkowe;
	Rozwiazanie *koncowe = najlepsze;
	clock_t endtime = clock();
	clock_t starttime = clock();
	while( ((double)(endtime-starttime)/CLOCKS_PER_SEC) < 15 )//po ilu sekundach przerwac
	{

		//Mutacja pierwszych elementow
		for(int i = 0; i < max_populacja/4; i++)
			roz[i+min_populacja] = roz[i]->mutacja(10);
		//cout << endl;
		//Rozwiazanie* roz2 = roz[0]->mutacja(10);
		//roz2->print();
		//cout << endl;
		//roz[0] = roz[0]->mutacja(10);
		
		//krzyzowanie niezmutowanych z niezmutowanymi
		for(int i = 0; i < ((max_populacja/4) - 1); i++)
			roz[i+max_populacja/4] = roz[i]->krzyzowanie(roz[i+1]);
		roz[max_populacja/2-1] = roz[min_populacja-1]->krzyzowanie(roz[0]);

		//krzyzowanie niezmutowanych ze zmutowanymi
		for(int i = 0; i < max_populacja/4; i++)
			roz[i+max_populacja/2] = roz[i]->krzyzowanie(roz[i+max_populacja/4]);

		//krzyzowanie zmutowanych ze zmutowanymi
		for(int i = 0; i < ((max_populacja/4) - 1); i++)
			roz[i+(3*max_populacja/4)] = roz[i+min_populacja]->krzyzowanie(roz[i+min_populacja+1]);
		roz[max_populacja-1] = roz[3*max_populacja/4]->krzyzowanie(roz[max_populacja-2]);

		//roz[0]->print();
		//cout << endl;
		//roz[0] = roz[0]->krzyzowanie(roz2);
		//roz[0]->print();
		//cout << endl;

		koncowe = Rozwiazanie::sprawdz(max_populacja, roz);
		if(najlepsze->w() > koncowe->w()) {
			najlepsze = koncowe;
		}

		roz = Rozwiazanie::selekcja(min_populacja, max_populacja, roz);
		endtime = clock();
	}


	najlepsze->zapisz(0);
	system("pause");

	cout << endl;

	delete instancja, poczatkowe, najlepsze, koncowe;

	for(int i = 0; i < max_populacja; i++) {
		delete roz[i];
	}
	delete [] roz;
}