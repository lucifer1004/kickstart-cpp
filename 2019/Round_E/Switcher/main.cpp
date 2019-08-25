#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Day {
  int c;
  int e;
};

bool compare(Day &a, Day &b) {
  return a.c*b.e < b.c*a.e || (a.c == 0 && b.c != 0);
}

void solve(int case_num) {
  int d, s;
  cin >> d >> s;
  vector<Day> days;
  int csum = 0, esum = 0;
  for (int i = 0; i < s; ++i) {
    int ci, ei;
    cin >> ci >> ei;
    days.emplace_back(Day{ci, ei});
    csum += ci;
    esum += ei;
  }
  sort(days.begin(), days.end(), compare);
  vector<int> cacc{0}, eacc{0};
  for (int i = 0; i < s; ++i) {
    cacc.emplace_back(cacc[i]+days[i].c);
    eacc.emplace_back(eacc[i]+days[i].e);
  }
  cout << "Case #" << case_num << ": ";
  for (int i = 0; i < d; ++i) {
    int ai, bi;
    cin >> ai >> bi;
    double c = csum, e = 0;
    if (ai > csum || bi > esum) cout << "N";
    else {
      int delta = csum - ai;
      int mid = (int) (upper_bound(cacc.begin(), cacc.end(), delta)-cacc.begin()) - 1;
      c -= cacc[mid];
      e += eacc[mid];
      if (e >= bi) {
        cout << "Y";
        continue;
      }
      for (int j = mid; j < s; ++j) {
        int ci = days[j].c;
        int ei = days[j].e;
        if (c - ci >= ai) {
          c -= ci;
          e += ei;
          if (e >= bi) {
            cout << "Y";
            break;
          }
        } else {
          double f = (double) (c - ai) / (double) ci;
          e += f * ei;
          if (e >= bi) cout << "Y";
          else cout << "N";
          break;
        }
      }
    }
  }
  cout << endl;
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