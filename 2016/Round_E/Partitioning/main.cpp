#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <queue>
#include <stack>
#include <deque>

typedef long long ll;

using namespace std;

unordered_map<ll, ll> memo1{};
unordered_map<ll, ll> memo2{};

ll sol(ll n, ll c, ll space) {
  if (n < c) return 0;
  if (n == c) return 1;
  ll ans = n % c == 0 ? 1 : 0;
  switch (space) {
    case 0:
      break;
    case 1:
      if (memo1[n * 200000 + c] != 0) return memo1[n * 200000 + c];
      for (ll i = 1; i <= n / c; ++i) {
        ll rest = n - c * i;
        ans += sol(rest, c + 1, 0);
      }
      memo1[n * 200000 + c] = ans;
      break;
    default:
      if (memo2[n * 200000 + c] != 0) return memo2[n * 200000 + c];
      for (ll i = 1; i <= n / c; ++i) {
        ll rest = n - c * i;
        ans += sol(rest, c + 1, 1) + sol(rest, c + 2, 0);
      }
      memo2[n * 200000 + c] = ans;
  }
  return ans;
}

void solve(int case_num) {
  ll n, d;
  cin >> n >> d;
  ll c = d;
  ll ans = 0;
  while (c <= n) {
    ans += sol(n, c, 2);
    c += d;
  }
  cout << "Case #" << case_num << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}