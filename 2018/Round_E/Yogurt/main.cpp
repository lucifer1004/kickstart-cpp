#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <string>
#include <deque>

#define ll long long

using namespace std;

void solve(int case_num) {
  int n, k;
  deque<int> exp;

  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    exp.push_back(d);
  }

  sort(exp.begin(), exp.end());

  int count = 0;
  int day = 0;
  int curr = 0;
  while (exp.size() > 0) {
    int front = exp.front();
    if (front > day) {
      count++;
      curr++;
      if (curr == k) {
        curr = 0;
        day++;
      }
    }
    exp.pop_front();
  }

  cout << "Case #" << case_num << ": " << count << endl;
}

int main()
{
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
  {
    solve(i);
  }
  return 0;
}