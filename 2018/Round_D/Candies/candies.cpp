#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>

#define ll long long

using namespace std;

// Binary search the right most valid position.
int last_valid(vector<ll> &count, int left, int odd) {
  int l = left;
  int r = count.size() - 1;
  if (count[r] - count[l - 1] <= odd) {
    return r;
  }

  while (l <= r) {
    int mid = l + (r - l) / 2;
    int curr = count[mid] - count[left - 1];
    if (curr == odd && count[mid + 1] - count[left - 1] > odd) {
      return mid;
    }
    if (curr <= odd) {
      l = mid + 1;
      continue;
    }
    r = mid - 1;
  }

  return -1;
}

void solve(int case_num) {
  ll n, o, d, x1, x2, a, b, c, m, l;
  ll max = LLONG_MIN;
  multiset<ll, greater<> > tree;
  vector<ll> x, sum, count;
  cin >> n >> o >> d;
  cin >> x1 >> x2 >> a >> b >> c >> m >> l;
  x.push_back(x1);
  x.push_back(x2);
  for (int j = 2; j < n; ++j) {
    x.push_back((a * x[j - 1] + b * x[j - 2] + c) % m);
  }
  sum.push_back(0);
  count.push_back(0);
  for (int j = 0; j < n; ++j) {
    x[j] += l;
    sum.push_back(sum[sum.size() - 1] + x[j]);
    count.push_back(count[count.size() - 1]);
    if (x[j] % 2 != 0) {
      count[count.size() - 1] += 1;
    }
  }

  int tree_left = 0;
  int tree_right = 0;
  tree.insert(sum[0]);

  for (int left = 1; left <= n; ++left) {
    int right_most = last_valid(count, left, o);
    if (right_most == -1) {
      continue;
    }
    ll bound = sum[left - 1] + d;

    for (int j = tree_right + 1; j <= right_most; ++j) {
      tree.insert(sum[j]);
    }
    tree_right = right_most;

    for (int j = tree_left; j < left; ++j) {
      auto hit(tree.find(sum[j]));
      if (hit != tree.end())
        tree.erase(hit);
    }
    tree_left = left;

    ll choose;
    auto lower_bound(tree.lower_bound(bound));
    if (lower_bound != tree.end())
      choose = *lower_bound;
    else if (*tree.rbegin() > bound) {
      continue;
    } else choose = *tree.rbegin();

    ll new_max = choose - sum[left - 1];

    // Update global max.
    if (new_max > max) {
      max = new_max;

      // Early exit when meeting target value.
      if (max == d) {
        break;
      }
    }
  }

  if (max == LLONG_MIN) {
    cout << "Case #" << case_num << ": IMPOSSIBLE" << endl;
  } else {
    cout << "Case #" << case_num << ": " << max << endl;
  }
}

int main() {
  int t;

  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}