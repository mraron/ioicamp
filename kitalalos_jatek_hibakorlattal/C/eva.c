#include <stdio.h>
#include <stdlib.h>

#include "eva.h"

#define MaxH            15
#define MaxM            4000001L
#define true 1
#define false 0

int Init = true;
long _N, _H, _M, _A;
long _L[MaxH][MaxM];
long _bal, _jobb, _mH, _Kerd, _optM;

void Vege(int ki, char *msg)

{
	printf("%s\n", msg);
	exit(1-ki);
}  /*Vege*/

void Elofel() {
	long seed=0;
	scanf("%ld%ld%ld%*[^\n]", &_N, &_H, &seed);
	srand(seed);
	_A=rand()%_N+1;
	_bal = 1;
	_jobb = _N;
	_Kerd = 0;
	Init = false;
}  /*Elofel*/

long GetN() {
	if (Init) {
		Elofel();
		Init = false;
	}
	return _N;
}  /*GetN*/

int GetH() {
	if (Init) {
		Elofel();
		Init = false;
	}
	return _H;
}  /*GetH*/

int Kerdes(long A, long B) {
	long v;

	if (Init) {
		Vege(0, "hiba, el?ször GetN-t kell hívni");
	}
	if (A < 1 || A > _N || B < 1 || B > _N || A > B) {
		Vege(0, "hiba, érvénytelen paraméter Kerdes-ben");
	}

	
	if(_A<A) {
		return -1;
	}else if(A<=_A && _A<=B) {
		return 0;
	}else {
		return 1;
	}
	_Kerd++;
	return v;
}  /*Kerdes*/

void Megoldas(long x) {
	if (Init) {
		Vege(0, "hiba, el?ször GetN-t kell hívni");
	}

	if (x != _A)
		Vege(0, "hiba, rossz válasz");
	Vege(1, "helyes");
}  /*Megoldas*/
