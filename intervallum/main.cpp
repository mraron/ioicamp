/*
ID: noszaly1
TASK: {TASK}
LANG: C++11               
*/

//Noszály Áron 10o Debreceni Fazekas Mihály Gimnázium

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<cassert>
#include<cassert>
#include<unordered_map>
#include<unordered_set>
#include<functional>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<numeric>
#include "interval.h"
using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define xx first
#define yy second
#define sz(x) (int)(x).size()
#define gc getchar
#define IO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const double PI=acos(-1);

template<typename T> T getint() {
	T val=0;
	char c;
	
	bool neg=false;
	while((c=gc()) && !(c>='0' && c<='9')) {
		neg|=c=='-';
	}

	do {
		val=(val*10)+c-'0';
	} while((c=gc()) && (c>='0' && c<='9'));

	return val*(neg?-1:1);
}


struct Treap {
	int key;
	pair<int,int> val;
	int pri;
	int sz;
	int mi;
	
	Treap *L,*R;
	
	Treap() {}
	
	Treap(int item, pair<int,int> v) : L(NULL), R(NULL) {
		key=item;
		val=v;
		pri=rand();
	}
};

typedef Treap * pTreap;

void update(pTreap& root) {
	if(root==NULL) return ;
	
	root->sz=(root->L==NULL?0:root->L->sz)+(root->R==NULL?0:root->R->sz)+1;
	root->mi=min(root->val.xx, min((root->L==NULL?(int)1e9:root->L->mi),(root->R==NULL?(int)1e9:root->R->mi)));
}

void split(pTreap root, int key, pTreap& L, pTreap& R) {
	if(root==NULL) {
		L=NULL;
		R=NULL;
	}else if(key < root->key) {
		split(root->L, key, L, root->L);
		R=root;
	}else {
		split(root->R, key, root->R, R);
		L=root;	
	}
	
	update(root);
}

void insert(pTreap& root, pTreap item) {
	update(root);
	
	if(root==NULL) {
		root=item;
	}else if(root->pri < item->pri) {
		split(root, item->key, item->L, item->R);
		root=item;
	}else {
		insert(item->key < root->key ? root->L : root->R, item);
	}
	
	update(root);
}

void merge(pTreap& root, pTreap L, pTreap R) {
	update(root);
	update(L);
	update(R);
	
	if(L==NULL || R==NULL) {
		root=(L!=NULL?L:R);
	}else if(L->pri < R->pri) {
		merge(R->L, L, R->L);
		root=R;
	}else {
		merge(L->R, L->R, R);
		root=L;
	}
	
	update(root);
}

void erase(pTreap& root, int key, pair<int,int> val) {
	if(root->key == key && val==root->val) {
		merge(root, root->L, root->R);
	}else {
		erase(key < root->key ? root->L : root->R, key, val);
	}
	
	update(root);
}

int meret(pTreap root) {
	if(root==NULL) return 0;
	return root->sz;
}

pTreap kthquery(pTreap& root, int k) {
	if(meret(root->L)==k-1) return root;
	else if(meret(root->L)<k-1) return kthquery(root->R, k-meret(root->L)-1);
	return kthquery(root->L, k);
}

void query(pTreap& root, pair<int,int> p, pair<int,int>& res) {
	if()
}

void print(pTreap root) {
	if(root==NULL) return ;
	print(root->L);
	cout<<root->key<<" ";
	print(root->R);
}

pTreap root=NULL;

void Bovit(int a, int b) {
	insert(root, new Treap(b, {a,b}));
}

void Torol(int a, int b) {
	erase(root, b, {a,b});
}

void Metszkeres(int xa, int xb, int& a, int& b) {
	
}
