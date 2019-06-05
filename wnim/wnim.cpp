#include <bits/stdc++.h>
#include "wnim.h"

using namespace std;

int _M=0,_N=0;

void _Vege(int pont, string S){
   cout<<pont<<endl;
   cout<<S<<endl;
  exit(0);
}  /*Vege*/

int main(){
  cin>>_M>>_N;
  Kezd(_M,_N);
  int a,b,aa,bb;
  for(;;){
      EnLepesem(a,b);
      if(a<0||b<0)_Vege(0,"Hibás_lépés");
      if(!(a==0&&b<=_N || b==0&&a<=_M || a==b&&a<=_M&&a<=_N)){
        _Vege(0,"Hibás_lépés");
      }
      _M-=a; _N-=b;
      if(_M==0 && _N==0) _Vege(1,"Helyes");
//ellenfél
      if(_M==_N || _M==0 || _N==0) _Vege(0,"Vesztettél!");
      if(_M<_N){
        aa=0; bb=1;
      }else{//_N<_M
        aa=1; bb=0;
      }
      _M-=aa; _N-=bb;
      TeLepesed(aa,bb);
   }
   return 0;
}

