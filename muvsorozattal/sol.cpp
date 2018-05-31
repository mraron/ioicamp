#include<bits/stdc++.h>
#include "sorozat.h"
using namespace std;

struct Treap {
	int key, pri;
	int val;
	int sz;
	int lazy=0;
	
	Treap *L,*R;
	
	Treap() {}
	
	Treap(int hely, int v) : L(NULL), R(NULL) {
		key=hely;
		val=v;
		pri=rand();
	}
};

typedef Treap * pTreap;

void update(pTreap& root) {
	if(root==NULL) return ;
	
	root->sz=(root->L==NULL?0:root->L->sz)+(root->R==NULL?0:root->R->sz)+1;
	root->key+=root->lazy;
	if(root->L!=NULL) root->L->lazy+=root->lazy;
	if(root->R!=NULL) root->R->lazy+=root->lazy;
	root->lazy=0;
}

void split(pTreap root, int key, pTreap& L, pTreap& R) {
	update(root);
	update(L);
	update(R);
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

void erase(pTreap& root, int key) {
	update(root);

	if(root->key == key) {
		merge(root, root->L, root->R);
	}else {
		erase(key< root->key ? root->L : root->R, key);
	}
	
	update(root);
}

int bal(pTreap root) {
	if(root->L==NULL) return -1;
	return root->L->key;
}


int jobb(pTreap root) {
	if(root->R==NULL) return -1;
	return root->R->key;
}

void print(pTreap root) {
	if(root==NULL) return ;
	//update(root);

cout<<root->key<<"("<<bal(root)<<","<<jobb(root)<<")"<<" ";
	print(root->L);
	
	print(root->R);
}

void assignLazyToBigger(pTreap& root, int key, int val) {
	//cerr<<key<<" "<<val<<" altb\n";
	if(root==NULL) return ;
	
	update(root);
	
	if(key<root->key) {
		root->key+=val;

		if(root->R!=NULL) {
			root->R->lazy+=val;
			update(root->R);
		}
		
		assignLazyToBigger(root->L, key, val);
	}else if(key>=root->key) {
		assignLazyToBigger(root->R, key, val);
	}
	
	update(root);
}

int meret(pTreap root) {
	
	if(root==NULL) return 0;
	return root->sz;
}


pTreap kthquery(pTreap& root, int k) {
	update(root);
	
	if(meret(root->L)==k-1) return root;
	else if(meret(root->L)<k-1) return kthquery(root->R, k-meret(root->L)-1);
	return kthquery(root->L, k);
	
	update(root);
}

pTreap root=NULL;

void Beszur(int i, int x) {
//	print(root);cerr<<"\n";
//	cerr<<"Beszur "<<i<<" "<<x<<"\n";
	assignLazyToBigger(root, i-1, 1);
	insert(root, new Treap(i, x));
}

int Elemszam() {
//	print(root);cerr<<"\n";
//	cerr<<"Elemszam\n";
	
	return meret(root);
}

int Kadik(int k) {
//	print(root);cerr<<"\n";
//	cerr<<"Kadik("<<k<<")\n";
	
	return kthquery(root, k)->val;
}

void Torol(int k) {
//	print(root);cerr<<"\n";
//	cerr<<"Torol("<<k<<")\n";
	
	erase(root, k);
	assignLazyToBigger(root, k, -1);
}

void Modosit(int k, int x) {
//	print(root);cerr<<"\n";
//	cerr<<"Modosit("<<k<<","<<x<<")\n";
	kthquery(root,k)->val=x;
}



