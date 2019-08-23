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

void solve(int case_num) {
  string pattern;
  cin >> pattern;
  ll length = pattern.size();
  ll l, r;
  cin >> l >> r;
  l--;
  r--;

  ll ans = 0;
  ll nl = l / length;
  ll nr = r / length;
  ll ml = l % length;
  ll mr = r % length;

  ll b_count = 0;
  for (const auto &c : pattern) if (c == 'B') b_count++;

  if (nr > nl + 1) ans += (nr - nl - 1) * b_count;
  if (nr > nl) {
    for (int i = ml; i < length; ++i) if (pattern[i] == 'B') ans++;
    for (int i = 0; i <= mr; ++i) if (pattern[i] == 'B') ans++;
  } else {
    for (int i = ml; i <= mr; ++i) if (pattern[i] == 'B') ans++;
  }

  cout << "Case #" << case_num << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}