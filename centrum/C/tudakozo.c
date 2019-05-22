//Gyakorló könvtári modul
#include <stdio.h>
#include <stdlib.h>
#include "tudakozo.h"
#define true 1
#define false 0

int _N,_C,_K;
int _kerd=0;
int _Init=true;

int hany(){
  if (_Init) {
    scanf("%d %d %d",&_N, &_C, &_K);
    _Init = false;
    _kerd=0;
  }
  return _N;
} /*hany*/

int kerdes(int x, int y){
  if(_Init){
    printf("HIBA: előbb hívd a hany műveletet!\n");
    exit(1);
  }
  _kerd++;
  if(_kerd>3*_N){
    printf("HIBA: túl sok kérdés volt!\n");
    exit(1);
  }
  if(x<1 || x>_N || y<1 || y>_N){
    printf("HIBA: hibás sorszám!\n");
    exit(1);
  }
  if (x==_K && y!=_C || y==_K && x!=_C){
    return 0;
  }else
    return 1;
}
void megoldas(int m){
//Itt ellenörzik, hogy a feltett kérdések apalján m lehet-e centrum
  if (m<1 ||m>_N){
    printf("HIBA: hibás sorszám\n");
    exit(1);
  }
  if(m==_C)
    if (_kerd<=2*_N)
      printf("HELYES, centrum= %d kérdésszám= %d <=2*N\n", m,_kerd);
    else
      printf("HELYES, centrum= %d kérdésszám= %d <=3*N\n", m,_kerd);
  else
    printf("HIBÁS\n");
  exit(0);
}
