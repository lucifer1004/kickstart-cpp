#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <string>
#include <bitset>

#define M 101

using namespace std;

struct Choice {
  int point {0};
  bitset<M> tea {bitset<M> {0}};
};

struct compare_choice {
  bool operator()(const Choice &t1, const Choice &t2) const {
    return t1.point < t2.point;
  }
};

void solve(int case_num) {
  int n, m, p, best_point {0};
  int count[M] {};
  string s;
  vector<bitset<M>> bans;
  vector<int> point;
  multiset<Choice, compare_choice> best, tmp;
  cin >> n >> m >> p;

  for (int i = 0; i < n; ++i) {
    cin >> s;
    for (int j = 1; j <= p; ++j) {
      if (s[p-j] == '0') count[j]++;
    }
  }

  for (int i = 0; i < m; ++i) {
    cin >> s;
    bitset<M> bset {s + "0"};
    bans.push_back(bset);
  }

  auto sentinel = Choice();
  best.insert(sentinel);

  for (int i = 1; i <= p; i++) {
    for (const auto &choice : best) {
      auto choose = Choice();
      choose.tea = bitset<M> {choice.tea};
      choose.tea.set(i);
      choose.point = choice.point + count[i];
      tmp.insert(choose);

      auto skip = Choice();
      skip.tea = bitset<M> {choice.tea};
      skip.point = choice.point + n - count[i];
      tmp.insert(skip);
    }
    best.swap(tmp);
    tmp.clear();

    while (best.size() > m + 1) {
      best.erase(prev(best.end()));
    }
  }

  for (const auto& choice : best) {
    bool banned = false;
    for (const auto& ban : bans) {
      if (choice.tea == ban) {
        banned = true;
        break;
      }
    }
    if (!banned) {
      best_point = choice.point;
      break;
    }
  }

  cout << "Case #" << case_num << ": " << best_point << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}