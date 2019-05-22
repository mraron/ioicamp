#include "zar.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

map<pair<int, char>, int> AT;
vector<bool> NT;
string w;
int n, a;
bool init = true, rossz = true;

void vege(int wut, string msg) {
	cout << msg << endl;
	if(!wut) exit(-1);
	exit(0);
}

void atmenetEpit() {
	for (int i = 0; i <= n + 1; ++i) {
		for (char x = '0'; x <= '9'; ++x) {
			AT[{i, x}] = (i < n && x == w[i]) ? i + 1 : n + 1;
		}
	}
	NT[n] = true;
	if (n > 4) {
		cerr<<"hihi\n";
		bool volt=false;
		for(int i=0;i<n+1;++i) {
			if(rand()%4==0 || (!volt && i==n)) {
				volt=true;
				char c;
				do {
					c='0'+(rand()%10);
				}while(i<n && c==w[i]);
				int hova=rand()%n+1;
				cerr<<i<<"-"<<c<<" "<<hova<<"\n";
				AT[{i, c}] = hova;
			}
		}
	}
	else {
		rossz = false;
	}
}

void kezd() {
	cin >> w;
	n = w.length();
	NT.resize(n + 2, false);
	a = 0;
	atmenetEpit();
	init = false;
}

void resetA() {
	if (init) { kezd(); }
	a = 0;
}

std::string jelszo() {
	if (init) { kezd(); }
	return w;
}

void be(char x) {
	if (init) { kezd(); }
	if (x < '0' || x > '9') {
		vege(0, "hiba, érvénytelen Be paraméter");
	}
	a = AT[{a, x}];
}

bool nyito() {
	if (init) { kezd(); }
	return NT[a];
}

void nyit(std::string k) {
	if (init) { kezd(); }
	if (rossz) {
		if (k == w) {
			vege(0, "hiba, nem találtad meg a rossz jelszót");
		}
		else {
			resetA();
			for (char c : k) {
				if (c < '0' || c > '9') {
					vege(0, "hiba, érvénytelen Nyit paraméter");
				}
				be(c);
			}
			if (nyito()) {
				vege(1, "helyes");
			}
			else {
				vege(0, "hiba, a megadott jelszó nem nyitja a zárat");
			}
		}
	}
	else {
		if (k == w) {
			vege(1, "helyes");
		}
		else {
			vege(0, "hiba, nem ismerted fel, hogy jó a zár");
		}
	}
}
