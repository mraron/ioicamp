#include <bits/stdc++.h>
#include "valasz.h"
#define maxN 10001
using namespace std;

int _r[maxN];
int _n, _db=0;
bool _Init = false;

void Vege(string pont, string s){
   cout<<pont<<endl;
   cout<<s<<endl;
   exit(0);
}
int induloszam(){
   cin>>_n;
   _db=0;
   for(int i=1; i<=_n; i++) {
      cin>>_r[i];
   }
   _Init=true;
   return _n;
}
void megoldas(int m){
   if(!_Init) Vege("0","Protokoll hiba");
   if(m==_r[_n]){
      if(_db<=2*_n-2){
         Vege("1","Helyes, kérdésszám <= 2*n-2");
      }else if(_db<=3*_n-4){
         Vege("0.4","Helyes, kérdésszám <= 3*n-4");
      }else if(_db<=10*_n){
         Vege("0.2","Helyes, kérdésszám <= 10*n");
      }else{
         Vege("0","Helyes, de a kérdésszám >10*n");
      }
   }else{
      Vege("0","Hibás megoldás");
   }
   return;
}

int kerdes(int i, int j){
   if(!_Init) Vege("0","Protokoll hiba");
   _db++;
   int v=0;
   if(i>=1 && i<_n && j>=0 && j<=31){
      v=(_r[i] >> j) %2;
      return v;
   }else{
      Vege("0","Protokoll hiba");
   }

   return v;
}

