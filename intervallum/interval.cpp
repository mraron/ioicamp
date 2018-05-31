#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include "interval.h"
using namespace std;
const long INF = 200000000;
int _Eszam=0;

void Vege(int pont, string S){
   cout<<pont<<endl;
   cout<<S<<endl;
  exit(0);
}  /*Vege*/

int main(){
   int n,x,y,a,b;
   cin>>n;
   int M;

   for(int i=0;i<n;i++){
      M=rand()%3;
      switch(M) {
      case 0:
         //x,y?
         Bovit(x, y);
         break;
      case 1:
         //x,y?
         Torol(x,y);
         break;
      case 2:
         //x,y?
         MetszKeres(x,y, a, b);
         break;
      }
   }

   return 0;
}

