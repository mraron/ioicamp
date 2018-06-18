#include <bits/stdc++.h>



using namespace std;



using ll = long long;

using ii = pair<int, int>;

using vb = vector<bool>;

using vi = vector<int>;

using vll = vector<ll>;

using vvi = vector<vi>;

using vvll = vector<vll>;

using vii = vector<ii>;

const ll MOD = 1000000007;

const int INF = 1000000000;

const double PI = 3.14159265358979323846;

#define fi first

#define se second

#define pb push_back

#define sz(cont) static_cast<int>((cont).size())

#define all(cont) (cont).begin(),(cont).end()

#define REP(n) for(int i=0, _i=(n); i<_i; ++i)

#define FOR(i,n) for(int i=0, _##i=(n); i<_##i; ++i)

#define DWN(i,n) for(int i=(n); i>=0; --i)

#define FORI(i,l,r) for(int i=(l), _##i=(r); i<_##i; ++i)



int can_be_root(vi const& a) {

    int min_elem = a[0], max_elem = a[0];

    FORI(i, 1, sz(a))

        if (a[i] < min_elem)

            min_elem = a[i];

        else if (a[i] > max_elem)

            max_elem = a[i];

        else

            return i - 2;

    return sz(a) - 1;

}



int main() {

    ios::sync_with_stdio(false);

    const int max_n = 3000000;

    vll fact(2 * max_n + 1), ifact(max_n + 2), catalan(max_n + 1);

    fact[0] = ifact[0] = ifact[1] = 1;

    FORI(i, 1, sz(fact))

        fact[i] = i*fact[i - 1] % MOD;

    FORI(i, 2, sz(ifact))

        ifact[i] = MOD - MOD / i * ifact[MOD%i] % MOD;

    FORI(i, 2, sz(ifact))

        ifact[i] = ifact[i - 1] * ifact[i] % MOD;

    FOR(i, sz(catalan))

        catalan[i] = fact[2 * i] * ifact[i + 1] % MOD * ifact[i] % MOD;

    int t;

    for (cin >> t; t--;) {

        int n, k;

        cin >> n >> k;

        if (k == 0) {

            cout << catalan[n] << '\n';

            continue;

        }

        vi a(k);

        REP(k) cin >> a[i];

        int prefix = can_be_root(a);

        reverse(all(a));

        int suffix = k - 1 - can_be_root(a);

        if (prefix < suffix) {

            cout << 0 << '\n';

            continue;

        }
	
		//cerr<<(prefix-suffix+1)<<"ANS\n";
        sort(all(a));

        ll ans = (prefix - suffix + 1) * catalan[a.front() + n - a.back()] % MOD;

        REP(k - 1)

            ans = ans * catalan[a[i + 1] - a[i] - 1] % MOD;

        cout << ans << '\n';

    }

}
