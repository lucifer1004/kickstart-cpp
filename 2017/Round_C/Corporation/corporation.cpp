#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <string>
#include <cmath>

// Considering the range of input (<=10000), it is reasonable to set the search upper limit to 100000.
#define UPPER_LIMIT 100000

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
    count = 3;
    while (true) {
      if (count > UPPER_LIMIT) {
        cout << "Case #" << case_num << ": " << "IMPOSSIBLE" << endl;
        return;
      }
      int k = count / 2;
      if (count % 2 == 1) {
        int left = MIN * k + MEDIAN * k + MAX;
        int right = MIN + MEDIAN * k + MAX * k;
        if (MEAN * count >= left && MEAN * count <= right) break;
      } else {
        int left = MIN * (k - 1) + MEDIAN * k + MAX;
        int right = MIN + MEDIAN * k + MAX * (k - 1);
        if (MEAN * count >= left && MEAN * count <= right) break;
      }
      count++;
    }
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