#include "Rozwiazanie.h"



void Rozwiazanie::uporzadkuj2m()
{
	int n = inst->z();
	int k = inst->p();
	konce = new int[n];
	start1 = new int[n];
	Zadanie z1 = inst->z(kolejnosc1[0]);
	start1[0] = z1.r;
	konce[kolejnosc1[0]] = z1.t1 + start1[0];
	int j = 0;
	while (j < k&&inst->p(j).k <= start1[0])j++;
	while (j < k&&inst->p(j).s < konce[kolejnosc1[0]]) {
		start1[0] = inst->p(j).k;
		konce[kolejnosc1[0]] = z1.t1 + start1[0];
		j++;
	}
	for (int i = 1; i < n; i++) {
		z1 = inst->z(kolejnosc1[i]);
		start1[i] = (z1.r>konce[kolejnosc1[i - 1]] ? z1.r : konce[kolejnosc1[i - 1]]);
		konce[kolejnosc1[i]] = z1.t1 + start1[i];
		while (j < k&&inst->p(j).k <= start1[i])j++;
		while (j < k&&inst->p(j).s < konce[kolejnosc1[i]]) {
			start1[i] = inst->p(j).k;
			konce[kolejnosc1[i]] = z1.t1 + start1[i];
			j++;
		}
	}
	z1 = inst->z(kolejnosc2[0]);
	start2 = new int[n];
	start2[0] = konce[kolejnosc2[0]];
	konce2 = new int[n];
	konce2[kolejnosc2[0]] = start2[0] + z1.t2;
	for (int i = 1; i < n; i++) {
		z1 = inst->z(kolejnosc2[i]);
		start2[i] = konce[kolejnosc2[i]]>konce2[kolejnosc2[i - 1]] ? konce[kolejnosc2[i]] : konce2[kolejnosc2[i - 1]];
		konce2[kolejnosc2[i]] = start2[i] + z1.t2;
	}

	for (int i = 1; i < n; i++) {
		z1= inst->z(kolejnosc2[i]);
		if (konce[kolejnosc2[i]] + z1.t2 < start2[0]) {
			int tmp = kolejnosc2[i];
			for (int j = i; j > 0; j--) {
				
				kolejnosc2[j] = kolejnosc2[j - 1];
				start2[j] = start2[j - 1];
				konce2[kolejnosc2[j]] = konce2[kolejnosc2[j - 1]];
			}
			kolejnosc2[0] = tmp;
			start2[0] = konce[kolejnosc2[0]];
			konce2[kolejnosc2[0]] = start2[0] + z1.t2;

		}else {
			int j = 1;
			while (konce[kolejnosc2[i]]>start2[j])j++;
			for (; j < i; j++) {
				int x = (konce2[kolejnosc2[j - 1]] > konce[kolejnosc2[i]] ? konce2[kolejnosc2[j - 1]] : konce[kolejnosc2[i]]);
				if (start2[j]>(x + z1.t2)) {
					int tmp = kolejnosc2[i];
					for (int l = i; l >j; l--) {
						
						kolejnosc2[l] = kolejnosc2[l - 1];
						start2[l] = start2[l - 1];
						konce2[kolejnosc2[l]] = konce2[kolejnosc2[l - 1]];
					}
					
					kolejnosc2[j] = tmp;
					start2[j] = x;
					konce2[kolejnosc2[j]] = x + z1.t2;
					continue;
				}
			}
		}

	}
	wartosc = 0;
	for (int i = 0; i < n; i++)wartosc += (konce[i] + konce2[i]);
}

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
	uporzadkuj2m();

}

Rozwiazanie::Rozwiazanie()
{
}

void Rozwiazanie::print()
{
	for (int i = 0; i < inst->z(); i++) {
		cout << kolejnosc1[i] << "\t"<< konce[kolejnosc1[i]] <<"\t" << konce2[kolejnosc1[i]] <<"\t"<< kolejnosc2[i] <<"\t" <<konce2[kolejnosc2[i]]<< endl;
	}
}

Rozwiazanie * Rozwiazanie::mutacja(int x)
{
	int n = inst->z();
	srand(time(0));
	cout << rand() << endl;
	Rozwiazanie* res = new Rozwiazanie();
	res->inst = inst;
	res->kolejnosc1 = new int[n];
	res->kolejnosc2 = new int[n];
	for (int i = 0; i < n; i++) {
		res->kolejnosc1[i] = kolejnosc1[i];
		res->kolejnosc2[i] = kolejnosc2[i];
	}
	int i1 = rand() % (n);
	int tmp = res->kolejnosc1[i1];
	for (int i = 1; i < x; i++) {
		int j = rand() % n;
		res->kolejnosc1[i1] = res->kolejnosc1[j];
		i1 = j;
	}
	res->kolejnosc1[i1] = tmp;
	i1 = rand() % (n = inst->z());
	tmp = res->kolejnosc2[i1];
	for (int i = 1; i < x; i++) {
		int j = rand() % n;
		res->kolejnosc2[i1] = res->kolejnosc2[j];
		i1 = j;
	}
	res->kolejnosc2[i1] = tmp;
	res->uporzadkuj2m();
	return res;
}

Rozwiazanie * Rozwiazanie::krzyzowanie(Rozwiazanie * partner)
{
	int n = inst->z();
	Rozwiazanie* res = new Rozwiazanie();
	res->inst = inst;
	res->kolejnosc1 = new int[n];
	res->kolejnosc2 = new int[n];
	int* used = new int[n];
	for (int i = 0; i < n; i++) {
		used[i] = 0;

	}
	for (int i = 0; i < n/2; i++) {
		res->kolejnosc1[i] = kolejnosc1[i];
		used[kolejnosc1[i]] |= 1;
		res->kolejnosc2[i] = kolejnosc2[i];
		used[kolejnosc2[i]] |= 2;

	}
	int j = 0, j2 = 0;


	for(int i = n/2; i < n; i++) {

		while (used[partner->kolejnosc1[j]] %2==1) {

			j++;
		}
		res->kolejnosc1[i] = partner->kolejnosc1[j++];
		while (used[partner->kolejnosc2[j2]] >1) {

			j2++;
		}
		res->kolejnosc2[i] = partner->kolejnosc2[j2++];

	}
	res->uporzadkuj2m();
	return res;
}

int Rozwiazanie::w() {
	return wartosc;
}

void Rozwiazanie::zapisz(int nr, int wartosc_poczatkowa) {
	int n = inst->z();
	stringstream nazwa;
	nazwa << "rozwiazania\\roz" << nr;
	ofstream plik;
	plik.open(nazwa.str());
	plik << "**** " << nr <<" ****"<<endl;
	plik << wartosc << "," << wartosc_poczatkowa << endl;

	int p_konserwujaca[2];
	int p_idle[4];
	for(int j=0; j < 4; j++) {
		p_idle[j] = 0;
	}
	p_konserwujaca[0] = 0;
	p_konserwujaca[1] = 0;

	plik << "M1:";
	int i=0;
	int czas=0;
	while(i < n-1) {
		if(czas == start1[0]) {//wykonywanie operacji
			plik << " op1_" << kolejnosc1[i] << ", " << start1[i] << ", " << konce[kolejnosc1[i]]-start1[i] << ";";
			czas = konce[kolejnosc1[i]];
			i++;
		}
		else
			if(czas == inst->p(p_konserwujaca[0]).s) {//przerwa konserwujaca
				plik << " maint" << p_konserwujaca[0] << "_M1, " << inst->p(p_konserwujaca[0]).s << ", "
					 << inst->p(p_konserwujaca[0]).t << ";";
				czas = inst->p(p_konserwujaca[0]).k;
				p_konserwujaca[1]+=inst->p(p_konserwujaca[0]).t;
				p_konserwujaca[0]++;
			}
			else {//nic sie nie dzieje
				int tmp = (inst->p(p_konserwujaca[0]).s < start1[i] ? inst->p(p_konserwujaca[0]).s : start1[i]);
				int tmp2 = tmp-czas;
				plik << " idle" << p_idle[0] << "_M1, " << czas << ", " << tmp2 << ";";			
				p_idle[1]+=tmp2;
				czas=tmp;
				p_idle[0]++;
			}
	}
	plik << endl;

	plik << "M2:";
	i = 0;
	czas = 0;
	while(i < n-1) {
		if(czas == start2[0]) {//wykonywanie operacji
			plik << " op2_" << kolejnosc2[i] << ", " << start2[i] << ", " << konce[kolejnosc2[i]]-start2[i] << ";";
			czas = konce[kolejnosc2[i]];
			i++;
		}
		else {//nic sie nie dzieje
			int tmp = start2[i];
			int tmp2 = tmp-czas;
			plik << " idle" << p_idle[0] << "_M2, " << czas << ", " << tmp2 << ";";			
			p_idle[3]+=tmp2;
			czas=tmp;
			p_idle[2]++;
			}
	}
	plik << endl;
	
	plik << p_konserwujaca[0] << ", " << p_konserwujaca[1] << endl;
	plik << "0, 0" << endl;
	plik << p_idle[0] << ", " << p_idle[1] << endl;
	plik << p_idle[2] << ", " << p_idle[3] << endl;
	plik << "*** EOF ***";
	plik.close();
}

Rozwiazanie::~Rozwiazanie()
{
	delete[]kolejnosc1,kolejnosc2, start1, start2, konce, konce2;
}
