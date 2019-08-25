#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
  int _n;
  vector<int> f;
  vector<int> s;

  int find(int a) {
    int a0 = a;
    while (f[a] != a) a = f[a];
    f[a0] = a;
    return a;
  }

public:
  explicit UnionFind(int n) {
    _n = n;
    for (int i = 0; i < n; ++i) {
      f.emplace_back(i);
      s.emplace_back(1);
    }
  }

  void connect(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    if (fa == fb) return;
    if (s[fa] > s[fb]) {
      f[fb] = fa;
      s[fa] += s[fb];
    } else {
      f[fa] = fb;
      s[fb] += s[fa];
    }
  }

  int count() {
    int ans = 0;
    for (int i = 0; i < _n; ++i) {
      if (f[i] == i && s[i] > 1) ans += s[i] - 1;
    }
    return ans;
  }
};

void solve(int case_num) {
  int n, m;
  cin >> n >> m;
  UnionFind uf = UnionFind(n);
  for (int i = 0; i < m; ++i) {
    int ai, bi;
    cin >> ai >> bi;
    uf.connect(ai - 1, bi - 1);
  }
  int count = uf.count();
  int ans = count + 2 * (n - 1 - count);
  cout << "Case #" << case_num << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}