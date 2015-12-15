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
	konce2[0] = start2[0] + z1.t2;
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
				konce2[j] = konce2[j - 1];
			}
			kolejnosc2[0] = tmp;
			start2[0] = konce[kolejnosc2[0]];
			konce2[0] = start2[0] + z1.t2;
		}else {
			int j = 1;
			while (konce[kolejnosc2[i]]>start2[j])j++;
			for (; j < i; j++) {
				int x = (konce2[j - 1] > konce[kolejnosc2[i]] ? konce2[j - 1] : konce[kolejnosc2[i]]);
				if (start2[j]>(x + z1.t2)) {
					int tmp = kolejnosc2[i];
					for (int l = i; l >j; l--) {
						kolejnosc2[l] = kolejnosc2[l - 1];
						start2[l] = start2[l - 1];
						konce2[l] = konce2[l - 1];
					}
					kolejnosc2[j] = tmp;
					start2[j] = x;
					konce2[j] = x + z1.t2;
				}
			}
		}
	}
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
		cout << kolejnosc1[i] << "\t"<< (konce!=0?konce[kolejnosc1[i]]:0) <<"\t" << kolejnosc2[i] <<"\t" <<konce2[kolejnosc2[i]]<< endl;
	}
}


Rozwiazanie::~Rozwiazanie()
{
	delete[]kolejnosc1,kolejnosc2, start1, start2, konce, konce2;
}
