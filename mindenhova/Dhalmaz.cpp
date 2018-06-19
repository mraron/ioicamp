#include <bits/stdc++.h>
#define maxN 300001

using namespace std;
struct Dhalmaz{
	int Hol[maxN];
	vector<int> S;
};
void Letesit(Dhalmaz &H, int m, int n){
	for(int x=m;x<=n;x++) H.Hol[x]=-1;
}
void Betesz(Dhalmaz &H, int x){
	if(H.Hol[x]<0){
		H.Hol[x]=H.S.size();
		H.S.push_back(x);
	}
}
int Kivesz(Dhalmaz &H){
	if(H.S.size()==0) return 0;
	int x=H.S.back();
	H.Hol[x]=-1;
	H.S.pop_back();
	return x;
}
bool Elemee(Dhalmaz &H, int x){
	return H.Hol[x]>=0;
}
void Torol(Dhalmaz &H, int x){
	if(H.Hol[x]<0) return;
	int i=H.Hol[x];
	H.Hol[x]=-1;
	if(i+1<H.S.size()){
		H.S[i]=H.S.back();
		H.Hol[H.S[i]]=i;
	}
	H.S.pop_back();
}
int Elemszam(Dhalmaz &H){
