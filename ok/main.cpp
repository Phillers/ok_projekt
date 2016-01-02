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
		a.generuj(1);
		a.generuj(0);
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

void testuj(Instancja *instancja, Rozwiazanie **roz, int nr) {

	instancja=wczytaj(nr);
	instancja->pierwszaWartosc = 0;
	for(int i = 0; i < max_populacja; i++)
			roz[i] = new Rozwiazanie(instancja);

	Rozwiazanie *najlepsze = Rozwiazanie::sprawdz(min_populacja, roz);
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
		
		//krzyzowanie
		for(int i = 0; i < (max_populacja/2); i++)
			roz[i+max_populacja/2] = roz[i]->krzyzowanie(roz[rand()%max_populacja/2]);



		//roz[0]->print();
		//cout << endl;
		//roz[0] = roz[0]->krzyzowanie(roz2);
		//roz[0]->print();
		//cout << endl;

		koncowe = Rozwiazanie::sprawdz(max_populacja, roz);
		if(najlepsze->w() > koncowe->w()) {
			najlepsze = koncowe;
		}
		cout << koncowe->w() << endl;
		roz = Rozwiazanie::selekcja(min_populacja, max_populacja, roz);
		endtime = clock();
	}
	najlepsze->zapisz(nr);



}



int main() {
	//generuj();

	//to x dodalem zeby mozna bylo latwiej manipulowac iloscia instancji do testowania bez tworzenia
	//calkowicie nowego pliku bo wtedy Generator::nr by sie nie zwiekszal jak funkcja generuj() jest zakomentowana
	int x = Generator::nr;
	x = 1;//tylko plik inst0
	Instancja** instancja = new Instancja *[x];
	Rozwiazanie*** roz = new Rozwiazanie **[x];
	for(int i = 0; i < x; i++)
		roz[i] = new Rozwiazanie *[max_populacja];


	
	for(int nr = 0; nr < x; nr++)
		testuj(instancja[nr], roz[nr], nr);



	system("pause");

	//cout << endl;


	
	//W zasadzie to delete mozna pominac co nie? Bo i tak w momencie zakonczenia programu uruchamiaja sie destruktory
	//delete instancja, najlepsze, koncowe;

	//for(int i = 0; i < max_populacja; i++) {
	//	delete roz[i];
	//}
	//delete [] roz;
}