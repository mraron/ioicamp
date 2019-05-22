#include "query.h"
#include <bits/stdc++.h>

#define MaxN            30001
#define MaxL            16
using namespace std;

 int _Init = true;
 char _B[2];
 int _FullS, _NQ;   /*# queries*/
 unsigned int _N, _M, _Half;
 int _T[MaxN + 1];
 int _D[MaxN + 1];
string _signo="x7Wah65Asb3";

static void EndQuery(void){
  cout<<"0"<<endl;
  cout<<_signo<<endl;
  exit(0);
}

static void Start(){
  int i;

  _B[0] = 0;
  _B[1] = 1;
  cin>>_N;

  for (int i = 1; i <= _N; i++) {
    _T[i] = -1;
    _D[i] = 0;
  }
  _T[0] = 0;
  _D[0] = 0;
  if (_N & 1)
    _M = _N;
  else
    _M = _N - 1;
  _Half = _M / 2 + 1;

  _Init = false;
  _NQ = 0;
  _FullS = 0;
  for (int i = 0; i < MaxL; i++) {
    if ( ((1 << i) & _M) != 0 )
      _FullS++;
  }
}

static int Find(int x){
  int Nx, xx;

  Nx = x;
  while (_T[Nx] > 0)
    Nx = _T[Nx];
  while (x != Nx) {  /*path compression*/
    xx = _T[x];
    _T[x] = Nx;
    x = xx;
  }
  return Nx;
}

static void Union(int& Nx, int& Ny){
  int X;

  if (Nx == 0) {
    Nx = Ny;
    return;
  }
  if (Ny == 0)
    return;
  if (_T[Nx] > _T[Ny]) {
    X = Nx;
    Nx = Ny;
    Ny = X;
  }
  _T[Nx] += _T[Ny];
  _T[Ny] = Nx;
}

int Size(void){
  if (_Init)
    Start();
  return _N;
}

int Member(int i, int j){
  int Result, Ri, Rj, Di, Dj, Si, Sj, Ui, Vi, Uj, Vj, SDi, SDj;
  unsigned int X;
  int Ans;

  if (_Init) {
    cout<<"ERROR: Illegal dialog. Size must be called first!\n";
    EndQuery();
  }
  if (i < 1 || i > _N || j < 1 || j > _N) {
    cout<<"ERROR: Value out of range"<<endl;
    EndQuery();
  }

  _NQ++;
  Ans = false;
  Ri = Find(i);
  Rj = Find(j);
  Di = _D[Ri];
  Dj = _D[Rj];
  if (Ri == Rj) {
    return 1;
  }
  if (Ri == Dj || Rj == Di) {
    return 0;
  }
  Si = abs(_T[Ri]);
  Sj = abs(_T[Rj]);
  SDi = abs(_T[Di]);
  SDj = abs(_T[Dj]);
  if (Si >= SDi) {
    Ui = Ri;
    Vi = Di;
  } else {
    Ui = Di;
    Vi = Ri;
    X = Si;
    Si = SDi;
    SDi = X;
  }
  if (Sj >= SDj) {
    Uj = Rj;
    Vj = Dj;
  } else {
    Uj = Dj;
    Vj = Rj;
    X = Sj;
    Sj = SDj;
    SDj = X;
  }
  if (Si + Sj >= _Half) {
    Union(Ui, Vj);
    Union(Vi, Uj);
    _D[Ui] = Vi;
    if (Vi != 0)
      _D[Vi] = Ui;
    Ans = (Find(i)==Find(j));
  } else {
    if (Si + Sj <= SDi + SDj + 2) {
      Union(Ui, Uj);
      Union(Vi, Vj);
      _D[Ui] = Vi;
      if (Vi != 0)
	_D[Vi] = Ui;
      Ans = (Find(i)==Find(j));
    } else {
      if (Si + SDj == Sj + SDi) {
	X = Si + SDj + Sj + SDi;
	if ((X & _M) == X) {
	  Union(Ui, Vj);
	  Union(Vi, Uj);
	  _D[Ui] = Vi;
	  if (Vi != 0)
	    _D[Vi] = Ui;
	    _M &= ~X;
	  _Half += -Si - SDj;
          Ans = (Find(i)==Find(j));
	} else {
	  Union(Ui, Uj);
	  Union(Vi, Vj);
	  _D[Ui] = Vi;
	  if (Vi != 0)
	    _D[Vi] = Ui;
         Ans = (Find(i)==Find(j));
	}
      } else {  /*Si+SDj<>Sj+SDi*/
	Union(Ui, Vj);
	Union(Vi, Uj);
	_D[Ui] = Vi;
	if (Vi != 0)
	  _D[Vi] = Ui;
       Ans = (Find(i)==Find(j));
      }
    }
  }

  Result = _B[Ans];
  return Result;
}

void Answer(int i){
  int Ri, Di, x, y, Nx, Sum;
  int OK;
  int G[MaxN + 1];
  int a, b, FORLIM;

  if (_Init) {
    cout<<"ERROR: Illegal dialog. Size must be called first!\n";
    EndQuery();
  }
  if (i < 1 || i > _N) {
    cout<<"ERROR: Value out of range\n";
    EndQuery();
  }

  Ri = Find(i);
  Di = _D[Ri];
  Sum = 0;

  for (int x = 1; x <= _N; x++) {
    Nx = Find(x);
    G[x] = (Nx != Ri && (_T[Nx] < _T[_D[Nx]] ||
			 _T[Nx] == _T[_D[Nx]] && Nx < _D[Nx] || Nx == Di));
  }
  for (x = 1; x <= _N; x++) {
    if (_T[x] < 0 && x != Di && x != Ri) {
      y = _D[x];
      if (_T[x] < _T[y])
	Sum += abs(_T[x]);
      else
	Sum += abs(_T[y]);
      _T[x] = 0;
      _T[y] = 0;
    }
  }
  /*for x=1.._N*/
  Sum += abs(_T[Di]);
  OK = (Sum <= _N / 2);
  if (OK) {
    cout<<"Correct"<<endl;
    } else {
    cout<<"Not Correct"<<endl;
  }
//  fprintf(OutF, "\nNumber of Queries: %d \n", _NQ);

  if (OK) {
    Sum = _N - _NQ;
    if (Sum < 0)
      Sum = 0;
//    fprintf(OutF, "Full Possible Score: %d\n", _FullS);
    cout<<Sum<<endl;
    cout<<_signo<<endl;
  } else {
    cout<<0<<endl;
    cout<<_signo<<endl;
  }
  exit(0);
}

