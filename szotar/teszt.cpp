#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define sz(x) (int)(x).size()
#define pb push_back
int sub[800001][26];
int vg[800001];
int ans[800001];
int sz[800001];
int id=1;
int cnt=0;
void insert(char t[]) {
	int akt=0;
	int res=0;
	int ind=0;
	char i=t[0];
	for(;i!='\0';) {
		sz[akt]++;
		res+=sz[akt];
	//	cerr<<sz[akt]<<"("<<akt<<")"<<" ";
		if(sub[akt][i-'a']==0) {
			sub[akt][i-'a']=id++;
		}
		akt=sub[akt][i-'a'];
		i=t[++ind];
	}
	sz[akt]++;	
//	cerr<<sz[akt]<<"("<<akt<<")"<<"\n";
	res+=sz[akt];
	
	
	vg[akt]=++cnt;
	ans[vg[akt]]=res;
	//cerr<<"ansfor "<<t<<" "<<res<<"\n";
	
}


int search(char t[]) {
	int akt=0;
	int res=0;
	bool bad=false;
	int ind=0;
	char i=t[0];
	for(;i!='\0';) {
		res+=sz[akt];
		
		if(sub[akt][i-'a']==0) {
			bad=true;
			break ;
		}
		else {
			akt=sub[akt][i-'a'];	
		}
		
		i=t[++ind];
	}
	if(!bad) res+=sz[akt];
	//cerr<<(vg[akt]>0?"found":"not found")<<"\n";
	if(!bad && vg[akt]>0) return ans[vg[akt]];
	return res;
}



#define gc getchar_unlocked
int getint() {
	int ans=0;
	char c;
	while((c=gc()) && !(c>='0' && c<='9'));
	
	do {
		ans=(ans*10)+c-'0';
	}while((c=gc()) && (c>='0' && c<='9'));
	return ans;
}

void ttt(char buf[]) {
	
	int ind=0;
	char c;
	while((c=gc()) && (c==' ' || c=='\n' || c=='\r'));
	do {
		buf[ind++]=c;
	}while((c=gc()) && !(c==' ' || c=='\n' || c=='\r'));
	buf[ind]='\0';

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	n=getint();
	char buf[32];
	for(int i=0;i<n;++i) {
		
		ttt(buf);
		insert(buf);
	}
	
	

	
	m=getint();
	for(int j=0;j<m;++j) {
		ttt(buf);
		cout<<search(buf)<<"\n";
	}
	
    return 0;
}

