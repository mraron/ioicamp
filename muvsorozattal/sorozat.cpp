#include <iostream>
#include <stdlib.h>
#include "sorozat.h"

using namespace std;
const long INF = 200000000;

int Eszam=0;

void Vege(int pont, string S){
   cout<<pont<<endl;
   cout<<S<<endl;
  exit(0);
}  /*Vege*/

int main(){

   int n,x,y,k;
   cin>>n;
   int M;

   for(int i=0;i<n;i++){
      M=rand()%5;
      switch(M) {
      case 0:
         x=rand();
         if(Eszam==0) k=1; else k=rand()%Eszam+1;
         Eszam++;
         Beszur(k,x);
         break;
      case 1:
         int e;
         e=Elemszam();
         if(e!=Eszam) Vege(0,"Hibás elemszám");
         break;
      case 2:
         if(Eszam==0) break;{
         int k=rand()%Eszam +1;
         int x=Kadik(k); }
         break;
      case 3:
         if(Eszam==0) break;{
         int x=rand()%INF;
         int k=rand()%Eszam +1;
         Modosit(k, x);}
         break;
      case 4:
         if(Eszam==0) break;{
         int k=rand()%Eszam +1;
         Eszam--;
         Torol(k); }
         break;
      }
   }
   Vege(1,"Helyes");
   return 0;
}
