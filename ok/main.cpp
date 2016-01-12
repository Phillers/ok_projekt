#include"Generator.h"
#include"Zadanie.h"
#include"Instancja.h"
#include"Rozwiazanie.h"
#include <time.h>

#define max_populacja 100
#define min_populacja 50
//niech zawsze daja reszte z dzielenia 0(i najlepiej podzielne przez 4 max_populacja)
//bo inaczej w selekcji nie beda braly udzial wszystkie rozwiazania

#define stopien_mutacji 10
#define ilosc_mutacji 30
//ilosc mutacji musi byc z przedzialu <0;max_populacja-min_populacja>

void generuj() {
	//20
	srand(time(NULL));
	int przerw;
	for (int i = 0; i <= 1; i++) {

		przerw = (rand() % (Generator::n / 2 - 2)) + 2;
		Generator a1(20, przerw);
		a1.generuj(i);

		przerw = (rand() % (Generator::n / 2 - 2)) + 2;
		Generator a2(200, przerw);
		a2.generuj((i + 1) % 2);
	}


}

Instancja* wczytaj(int nr) {
	stringstream nazwa;
	nazwa << "instancje\\inst" << nr;
	ifstream plik;
	plik.open(nazwa.str());
	string a;
	getline(plik, a);
	int n, k;
	char x;
	plik >> n;
	Zadanie* zadania = new Zadanie[n];
	for (int i = 0; i < n; i++) {
		int a, b, c;

		plik >> a >> x >> b >> x >> c >> x;
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
		przerwy[i].k = a + b;
	}
	plik.close();
	Instancja* inst = new Instancja(n, zadania, k, przerwy);
	return inst;
}

void testuj(Instancja *instancja, Rozwiazanie **roz, int nr) {

	instancja = wczytaj(nr);
	instancja->pierwszaWartosc = 0;
	for (int i = 0; i < min_populacja; i++)
		roz[i] = new Rozwiazanie(instancja);

	Rozwiazanie *najlepsze = Rozwiazanie::sprawdz(min_populacja, roz);
	Rozwiazanie *koncowe;
	clock_t endtime = clock();
	clock_t starttime = clock();
	stringstream nazwa1, nazwa2;
	nazwa1 << "wykres\\wart" << nr << ".txt";
	nazwa2 << "wykres\\czas" << nr << ".txt";
	ofstream plik1, plik2;
	plik1.open(nazwa1.str());
	plik2.open(nazwa2.str());
	plik1 << najlepsze->w() << endl;
	plik2 << "0" << endl;
	while (((double)(endtime - starttime) / CLOCKS_PER_SEC) < 5)//po ilu sekundach przerwac
	{

		//Mutacja pierwszych elementow
		for (int i = 0; i < ilosc_mutacji; i++)
			roz[i + min_populacja] = roz[i]->mutacja(stopien_mutacji);
		//cout << endl;
		//Rozwiazanie* roz2 = roz[0]->mutacja(10);
		//roz2->print();
		//cout << endl;
		//roz[0] = roz[0]->mutacja(10);

		//krzyzowanie
		for (int i = ilosc_mutacji + min_populacja; i < (max_populacja); i++)
			roz[i] = roz[rand() % (ilosc_mutacji + min_populacja)]->krzyzowanie(roz[rand() % (ilosc_mutacji + min_populacja)]);



		//roz[0]->print();
		//cout << endl;
		//roz[0] = roz[0]->krzyzowanie(roz2);
		//roz[0]->print();
		//cout << endl;



		roz = Rozwiazanie::selekcja(min_populacja, max_populacja, roz);


		koncowe = Rozwiazanie::sprawdz(min_populacja, roz);

		if (najlepsze->w() <= 0 || najlepsze->w() > koncowe->w()) {
			najlepsze = koncowe;
		}

		endtime = clock();
		plik1 << koncowe->w() << endl;
		plik2 << ((double)(endtime - starttime) / CLOCKS_PER_SEC) << endl;
	}
	//najlepsze->print();
	najlepsze->zapisz(nr);

	plik1.close();
	plik2.close();

}



int main() {
	//generuj();

	//to x dodalem zeby mozna bylo latwiej manipulowac iloscia instancji do testowania bez tworzenia
	//calkowicie nowego pliku bo wtedy Generator::nr by sie nie zwiekszal jak funkcja generuj() jest zakomentowana
	int x = Generator::nr;
	//x = 20;//do inst19
	x = 4;//do inst3
	Instancja** instancja = new Instancja *[x];
	Rozwiazanie*** roz = new Rozwiazanie **[x];
	for (int i = 0; i < x; i++)
		roz[i] = new Rozwiazanie *[max_populacja];



	for (int nr = 0; nr < x; nr++)
		testuj(instancja[nr], roz[nr], nr);


	cout << endl;
	system("pause");

	//cout << endl;



	//W zasadzie to delete mozna pominac co nie? Bo i tak w momencie zakonczenia programu uruchamiaja sie destruktory
	//delete instancja, najlepsze, koncowe;

	//for(int i = 0; i < max_populacja; i++) {
	//	delete roz[i];
	//}
	//delete [] roz;
}