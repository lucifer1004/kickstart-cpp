#include <iostream>

using namespace std;
typedef long long ll;

ll exp(ll a, ll x, ll p) {
  if (x == 0) return 1;
  ll half = exp(a, x / 2, p);
  ll res = half * half % p;
  if (x % 2 == 1) res = res * a % p;
  return res;
}

ll solve(ll a, ll n, ll p) {
  ll ans = a;
  for (ll j = 1; j <= n; ++j) {
    ans = exp(ans, j, p);
  }
  return ans;
}

int main() {
  ll t;
  cin >> t;
  for (ll i = 1; i <= t; ++i) {
    ll a, n, p;
    cin >> a >> n >> p;
    cout << "Case #" << i << ": " << solve(a, n, p) << endl;
  }

  return 0;
}