/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dp on trees, rerooting, connect component approach
 * @idea
 *    - use a dp(node, is_terminal_subtree).
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
const int mod = 1e9 + 7;
const int maxn = 5e5 + 10;
vector<ii> g[maxn];
ll dp[maxn][2];
vector<ll> aux[maxn];
bool camp[maxn];
int sz[maxn];
const ll inf = 1e18;

void dfs(int x, int p) {
    sz[x] = camp[x];
    dp[x][1] = 0;
    trav(v, g[x]) {
        if (v.first == p) continue;
        dfs(v.first, x);
        sz[x] += sz[v.first];
        dp[x][1] += dp[v.first][1] + (sz[v.first] > 0) * 2 * v.second;
    }
    if (sz[x] == camp[x]) {
        dp[x][0] = 0;
        return;
    }
    aux[x] = {inf, inf};
    trav(v, g[x]) {
        if (v.first == p) continue;
        aux[x].push_back(dp[x][1] - dp[v.first][1] - (sz[v.first] > 0) * v.second + dp[v.first][0]);
        sort(all(aux[x]));
        aux[x].pop_back();
    }
    dp[x][0] = aux[x][0];
}

void dfs_reroot(int x, int p, int e) {
    if (p != 0) {
        ll delta = dp[x][1] + (sz[x] > 0) * 2 * e;
        ll temp = dp[p][1] - delta;
        ll temp2 = (dp[p][1] - delta + (sz[x] > 0) * e + dp[x][0] == aux[p][0] ? aux[p][1] : aux[p][0]) - delta;
        if (sz[p] - sz[x] == camp[p]) temp2 = 0;
        dp[x][1] += temp + (sz[p] - sz[x] > 0) * 2 * e;
        aux[x] = {inf, inf};
        trav(v, g[x]) {
            if (v.first == p) {
                aux[x].push_back(dp[x][1] - temp - (sz[p] - sz[x] > 0) * e + temp2);
            } else {
                aux[x].push_back(dp[x][1] - dp[v.first][1] - (sz[v.first] > 0) * v.second + dp[v.first][0]);
            }
            sort(all(aux[x]));
            aux[x].pop_back();
        }
        sz[x] = sz[p];
        dp[x][0] = aux[x][0];
        if (sz[x] == camp[x]) dp[x][0] = 0;
    }
    trav(v, g[x]) {
        if (v.first == p) continue;
        dfs_reroot(v.first, x, v.second);
    }
}

class Kamp {
public:

    void solveOne(istream& in, ostream& out) {
        int n, k;
        in >> n >> k;
        re(i, 1, n+1) {
            g[i].clear();
        }
        re(i, 1, n) {
            int a, b, c;
            in >> a >> b >> c;
            g[a].eb(b, c);
            g[b].eb(a, c);
        }
        memset(camp, 0, sizeof camp);
        re(i, 0, k) {
            int x;
            in >> x;
            camp[x] = 1;
        }
        dfs(1, 0);
        dfs_reroot(1, 0, 0);
        re(i, 1, n+1) {
            out << dp[i][0] << endl;
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
    Kamp solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}