#include <iostream>
#include <stack>
#include <stdlib.h>
#include "grundy.h"
#define _maxN 10001
#define _maxG 201

using namespace std;
int _Gt[_maxN];
int _L[_maxN];
int _Van[_maxN];
int _N;

int _hany=0;
int _digi = 129723562;
void _Vege(int pont, string S){
   cout<<_digi<<endl;
   cout<<pont<<endl;
   cout<<S<<endl;
  exit(0);
}  /*Vege*/

int _SG(int n){
   if(_Gt[n]>=0) return _Gt[n];
   bool Mex[n+1];
   for(int x=0;x<=n;x++) Mex[x]=false;

   for(int k=1;k<(n+1)/2;k++){
      int p=_SG(k) ^ _SG(n-k);
      if(p==0) _L[n]=k;
      Mex[p]=true;
   }
   int m=0;
   while(m<=n && Mex[m]) m++;
   _Gt[n]=m;
   return m;
}
int main(){
   cin>>_N;
   _Gt[0]=0; _Gt[1]=0; _Gt[2]=0;
   _Van[1]=0;_Van[2]=0;
   for(int i=3;i<=_N;i++){
      _Van[i]=0;
      _Gt[i]=-1;
   }
   _Van[_N]=_N;
   _hany=1;
   _SG(_N);
   Kezd(_N);
   int m,k;
   for(;;){
      EnLepesem(m,k);
      if(m<=2 ||k<1 || m>_maxN || k>=m || k==m-k)
         _Vege(0,"Hibás lépés");
      if(_Van[m]==0){
         _Vege(0,"Hibás lépés");
      }
      _Van[m]--;
      _hany--;
      if(k>2){
            _Van[k]++;
            _hany++;
      }
      if(m-k>2){
         _Van[m-k]++;
         _hany++;
      }
      if(_hany==0) _Vege(1,"Helyes");
//ellenfél
      m=1;
      while(m<=_N && _Van[m]==0) m++;
      if(m>_N) _Vege(1,"Helyes");
      k=_L[m];
      if(k==0) k=1;
      _Van[m]--;
      _hany--;
      if(k>2) {_Van[k]++; _hany++; }
      if(m-k>2) {_Van[m-k]++;_hany++; }
      if(_hany==0) _Vege(0,"Vesztettél!");
      TeLepesed(m,k);
   }
   return 0;
}
