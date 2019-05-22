//Gyakorló könvtári modul
#include <iostream>
#include <stdlib.h>
#include "tudakozo.h"

using namespace std;

int _N,_C,_K;
int _kerd=0;
int _Init=true;

int hany(){
  if (_Init) {
    cin>>_N>>_C>>_K;
    _Init = false;
    _kerd=0;
  }
  return _N;
} /*hany*/

int kerdes(int x, int y){
  if(_Init){
    cout<<"HIBA: előbb hívd a hany műveletet!"<<endl;
    exit(1);
  }
  _kerd++;
  if(_kerd>3*_N){
    cout<<"HIBA: túl sok kérdés volt!"<<endl;
    exit(1);
  }
  if(x<1 || x>_N || y<1 || y>_N){
    cout<<"HIBA: hibás sorszám!"<<endl;
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
    cout<<"HIBA: hibás sorszám"<<endl;
    exit(1);
  }
  if(m==_C)
    if (_kerd<=2*_N)
    cout<<"HELYES, centrum= "<<m<<" kérdésszám= "<<_kerd<<"<=2*N"<<endl;
    else
      cout<<"HELYES, centrum= "<<m<<" kérdésszám= "<<_kerd<<"<=3*N"<<endl;
  else
    cout<<"HIBÁS"<<endl;
  exit(0);
}
