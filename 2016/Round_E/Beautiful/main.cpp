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

ll exp(ll n, ll k) {
  if (k == 0) return 1;
  ll half = exp(n / 2, k);
  ll ans = half * half;
  if (n % 2 == 1) ans *= k;
  return ans;
}

ll search(ll n, ll k) {
  if (k == 2) return n-1;
  else {
    
  }
}

void solve(int case_num) {
  ll n;
  cin >> n;
  ll upper_bound = log2(n) + 1;
  cout << "Case #" << case_num << ": " << n << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}