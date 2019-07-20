#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

void solve(int case_num) {
  int MIN, MAX, MEAN, MEDIAN;
  int count{0};
  cin >> MIN >> MAX >> MEAN >> MEDIAN;

  if (
    MIN > MAX ||
    MEAN > MAX ||
    MEAN < MIN ||
    MEDIAN > MAX ||
    MEDIAN < MIN ||
    (MIN < MAX && (MEAN == MIN || MEAN == MAX))
    ) {
    cout << "Case #" << case_num << ": " << "IMPOSSIBLE" << endl;
    return;
  }

  if (MIN == MAX) count = 1;
  else if (MIN + MAX == 2 * MEAN && MEAN == MEDIAN) count = 2;
  else {
    if (2 * MEAN >= MEDIAN + MAX || 2 * MEAN <= MIN + MEDIAN) {
      cout << "Case #" << case_num << ": " << "IMPOSSIBLE" << endl;
      return;
    }

    // even case
    int left = ceil((double) (MAX - MIN) / (2 * MEAN - MIN - MEDIAN));
    int right = ceil((double) (MAX - MIN) / (MAX + MEDIAN - 2 * MEAN));
    int k = max(left, right);
    int even = 2 * k;

    // odd case
    left = ceil((double) (MAX - MEAN) / (2 * MEAN - MIN - MEDIAN));
    right = ceil((double) (MEAN - MIN) / (MAX + MEDIAN - 2 * MEAN));
    k = max(left, right);
    int odd = 2 * k + 1;
    count = min(even, odd);
  }

  cout << "Case #" << case_num << ": " << count << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}