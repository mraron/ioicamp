//Gyakorló könvtári modul
#include <iostream>
#include <stdlib.h>
#include "muszer.h"
#define _maxN 10001

using namespace std;

int _N;
int _kerd=0;
int _Init=true;
int _M[_maxN];
int _Mi[_maxN];
int _S[_maxN];
int Atomszam(){
  if (_Init) {
    cin>>_N;
    _Init = false;
    _kerd=0;
    for(int i=1;i<=_N; i++) {_M[i]=i;}
    for(int i=_N;i>1;i--){
      int x=rand()%i+1;
      int xx=_M[x];
      _M[x]=_M[i];
      _M[i]=xx;
      _S[i]=0;
    }
  }
   for(int ii=1;ii<=_N;ii++)
            cerr<<_M[ii
            ]<<" ";
            cerr<<"\n";
for(int i=1;i<=_N;i++) {
   _Mi[_M[i]]=i;
}
  return _N;
}

int Kozte(int x, int y){
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
    cout<<"HIBA: hibás sorszám1!"<<endl;
    exit(1);
  }
  if(x==y) return x;
  int xi=_Mi[x], yi=_Mi[y];
  if(xi<yi){
      return _M[xi+1];
  }else{
      return _M[yi+1];
  }
}
void Sorrend(int i, int x){
  if (i<1 ||i>_N || x<1 ||x>_N ){
    cout<<"HIBA: hibás sorszám"<<endl;
    exit(1);
  }
  if(x==_S[i]){
   cout<<"HIBA: hibás sorrend2"<<endl;
    exit(1);
  }
  _S[i]=x;
   if(i==_N){
	     for(int ii=1;ii<=_N;ii++)
            cerr<<_M[ii]<<" ";
            
         cerr<<"!!\n";
      if(_M[1]==_S[1]){
         for(int ii=1;ii<=_N;ii++)
         if(_S[ii]!=_M[ii]){
            cout<<"HIBA: hibás sorrend"<<endl;
            exit(1);
         }
      }else{
         for(int ii=1;ii<=_N;ii++)
         if(_S[ii]!=_M[_N-ii+1]){
            cout<<"HIBA: hibás sorrend"<<endl;
            exit(1);
         }
      }
      if (_kerd<=2*_N)
         cout<<"HELYES, a kérdésszám "<<_kerd<<"<=2N"<<endl;
      else if(_kerd<=3*_N)
         cout<<"HELYES, a kérdésszám "<<_kerd<<"<=3N"<<endl;
      else
         cout<<"HIBÁS, túl sokat kérdezett"<<endl;
 exit(0);
   }

}
