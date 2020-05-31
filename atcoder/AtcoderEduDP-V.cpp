/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dp on trees, rerooting with in/out approach
 * @idea
 *      - dp on trees, rerooting application
 */

#include <bits/stdc++.h>
#define sz(x) (int)x.size()
#define trav(v, x) for (auto v : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define set_to(x, v) fill(all(x), v)
#define eb emplace_back
#define lso(x) ((x)&-(x))
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
const int maxn = 1e5 + 10;
int mod = 1e9 + 7;
int n;
vi g[maxn];
int dp[maxn];

int add(int a, int b) {
    return (a + b) % mod;
}

int mul(ll a, ll b) {
    return a * b % mod;
}

vi L[maxn];
vi R[maxn];
void dfs(int x, int p) {
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
    }
    int m = sz(g[x]);
    L[x].resize(m);
    R[x].resize(m);
    for (int i = 0; i < m; ++i) {
        int v = g[x][i];
        if (i == 0) L[x][i] = v == p ? 1 : add(1, dp[v]);
        else L[x][i] = mul(L[x][i-1], v == p ? 1 : add(1, dp[v]));
    }
    for (int i = m-1; i >= 0; --i) {
        int v = g[x][i];
        if (i == m-1) R[x][i] = v == p ? 1 : add(1, dp[v]);
        else R[x][i] = mul(R[x][i+1], v == p ? 1 : add(1, dp[v]));
    }
    dp[x] = L[x][m-1];
}

void dfs_reroot(int x, int p, int id, int temp = 1) {
    if (p != 0) {
        dp[x] = mul(dp[x], temp = add(1, mul(temp, mul(id == 0 ? 1 : L[p][id-1], id == sz(g[p]) - 1 ? 1 : R[p][id+1]))));
    }
    re(i, 0, sz(g[x])) {
        int v = g[x][i];
        if (v == p) continue;
        dfs_reroot(v, x, i, temp);
    }
}

class VSubtree {
public:

    void solveOne(istream& in, ostream& out) {
        in >> n >> mod;
        if (n == 1) {
            out << 1 << endl;
            return;
        }
        re(i, 1, n+1) {
            g[i].clear();
            L[i].clear();
            R[i].clear();
        }
        re(i, 1, n) {
            int a, b;
            in >> a >> b;
            g[a].eb(b);
            g[b].eb(a);
        }
        dfs(1, 0);
        dfs_reroot(1, 0, 0);
        re(i, 1, n+1) {
            out << dp[i] << endl;
        }
    }

    void solve(istream& in, ostream& out) {
        int testNumber = 1;
        //in >> testNumber;
        re(tc, 1, testNumber+1) {
            //out << "Case #" << tc << ": ";
            solveOne(in, out);
        }
    }
};


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
	VSubtree solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
