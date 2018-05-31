#include <iostream>
#include <stdlib.h>
#include "rendminta.h"

using namespace std;
const long INF = 200000000;
int _Eszam=0;

void Vege(int pont, string S){
   cout<<pont<<endl;
   cout<<S<<endl;
  exit(0);
}  /*Vege*/

int main(){
   int n,x,y;
   cin>>n;
   int M;

   for(int i=0;i<n;i++){
      M=rand()%6;
      switch(M) {
      case 0:
         x=rand();
         _Eszam++;
         Adat(x);
         break;
      case 1:
         int e;
         e=Elemszam();
         if(e!=_Eszam) Vege(0,"Hibás elemszám");
         break;
      case 2:
         if(_Eszam==0) break;{
         int k=rand()%_Eszam +1;
         int x=Kadik(k); }
         break;
      case 3:
         if(_Eszam==0) break;{
         int k=rand()%_Eszam +1;
         int x=Kadik(k);
         int kk=Hanyadik(x);
         if(k!=kk) Vege(0,"Hibás Hanyadik");}
         break;
      case 4:
         if(_Eszam==0) break;{
         int k=rand()%_Eszam +1;
         _Eszam--;
         KTorol(k); }
         break;
      case 5:
         if(_Eszam==0) break;{
         int k=rand()%_Eszam +1;
         int x=Kadik(k);
         _Eszam--;
         Torol(x); }
         break;
      }
   }
   Vege(1,"Helyes");
   return 0;
}
