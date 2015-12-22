#include"Generator.h"
#include"Zadanie.h"
#include"Instancja.h"
#include"Rozwiazanie.h"
#define max_populacja 200

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

	Rozwiazanie** roz = new Rozwiazanie *[max_populacja];
	

	for(int i = 0; i < max_populacja; i++)
		roz[i] = new Rozwiazanie(instancja);
	

	Rozwiazanie *poczatkowe = Rozwiazanie::sprawdz(50, roz);
	int wartosc_poczatkowa=poczatkowe->w();
	Rozwiazanie *najlepsze = poczatkowe;
	roz[0]->print();
	cout << endl;
	Rozwiazanie* roz2 = roz[0]->mutacja(10);
	roz2->print();
	cout << endl;
	roz[0] = roz[0]->mutacja(10);

	roz[0]->print();
	cout << endl;
	roz[0] = roz[0]->krzyzowanie(roz2);
	roz[0]->print();
	cout << endl;
	//for (int i = 0; i < 1000; i++)cout << time(0) << " ";
	Rozwiazanie *koncowe = Rozwiazanie::sprawdz(max_populacja, roz);
	if(najlepsze->w() > koncowe->w()) {
		najlepsze = koncowe;
	}

	roz = Rozwiazanie::selekcja(max_populacja, roz);



	najlepsze->zapisz(0, wartosc_poczatkowa);
	system("pause");

	cout << endl;

	//delete instancja, roz;
}