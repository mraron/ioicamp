#include <iostream>
#include <stdlib.h>
#include "rendminta.h"

using namespace std;
const long INF = 200000000;
int Eszam=0;

void Vege(int pont, string S){
   cout<<pont<<endl;
   cout<<S<<endl;
  exit(0);
}  /*Vege*/

int main(){
   int n,M,x,xx,k,kk;
   cin>>n;

   for(int i=0;i<n;i++){
      M=rand()%4;
      switch(M) {
      case 0:
         x=rand();
         Eszam++;
         Adat(x);
         break;
      case 1:
         if(Eszam==0) break;
         int e;
         e=Elemszam();
         break;
      case 2:
         if(Eszam==0) break;
         k=rand()%Eszam +1;
         x=Kadik(k);
         break;
      case 3:
         if(Eszam==0) break;
         kk=rand()%Eszam +1;
         xx=Kadik(kk);
         k=Hanyadik(xx);
         if(k!=kk) Vege(0,"Hibás Hanyadik");
         break;
      }
   }
   Vege(1,"Helyes");
   return 0;
}
