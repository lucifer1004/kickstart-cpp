#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <stack>

#define CAPACITY 100000
using namespace std;

struct Interval {
  int l;
  int r;
  int k;
};

bool IntervalCompare(const Interval &a, const Interval &b) {
  return a.r < b.r;
}

class Tree {
  int n, h;
  array<int, CAPACITY> t{}, d{}, len{};

  void build(int l, int r) {
    int k = 2;
    for (l += n, r += n - 1; l > 1; k <<= 1) {
      l >>= 1, r >>= 1;
      for (int i = r; i >= l; --i) calc(i, k);
    }
  }

  void calc(int p, int k) {
    if (d[p] == 0) t[p] = t[p << 1] + t[p << 1 | 1];
  }

  int apply(int p, int value, int k) {
    if (value <= 0) return 0;
    int remain = value - (k - t[p]);
    int updated = min(t[p] + value, k);
    if (p < n) d[p] = updated - t[p];
    t[p] = updated;
    return remain;
  }

  void push(int l, int r) {
    int s = h;
    for (l += n, r += n - 1; s > 0; --s)
      for (int i = l >> s; i <= r >> s; ++i)
        if (d[i] != 0) {
          int remain = apply(i << 1 | 1, d[i], len[i << 1 | 1]);
          apply(i << 1, remain, len[i << 1]);
          d[i] = 0;
        }
  }

public:
  explicit Tree(int n) {
    this->n = n;
    this->h = sizeof(int) * 8 - __builtin_clz(n);
    for (int i = 0; i < n; ++i) len[n + i] = 1;
    for (int i = n - 1; i > 0; --i) len[i] = len[i << 1] + len[i << 1 | 1];
  }

  void update(int l, int r, int target) {
    int remain = target - query(l, r);
    if (remain <= 0) return;

    stack<int> lp;

    int l0 = l, r0 = r;
    for (l += n, r += n; remain > 0 && l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        lp.push(l);
        ++l;
      }
      if (r & 1) {
        --r;
        remain = apply(r, remain, len[r]);
      }
    }

    while (remain > 0 && !lp.empty()) {
      l = lp.top();
      lp.pop();
      remain = apply(l, remain, len[l]);
    }

    build(l0, l0 + 1);
    build(r0 - 1, r0);
  }

  int query(int l, int r) {
    push(l, l + 1);
    push(r - 1, r);
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res += t[l++];
      if (r & 1) res += t[--r];
    }
    return res;
  }
};

int main() {
  int n, m, li, ri, ki;
  vector<Interval> intervals;
  cin >> n >> m;
  auto tree = Tree(n);
  for (int i = 0; i < m; ++i) {
    cin >> li >> ri >> ki;
    intervals.emplace_back(Interval{li, ri, ki});
  }
  sort(intervals.begin(), intervals.end(), IntervalCompare);
  for (const auto &interval : intervals) {
    int l = interval.l;
    int r = interval.r;
    int k = interval.k;
    tree.update(l - 1, r, k);
  }
  cout << tree.query(0, n) << endl;
}