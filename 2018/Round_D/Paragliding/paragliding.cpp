#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>

#define ll long long

using namespace std;

struct Tower {
  ll p;
  ll h;
};

struct Balloon {
  ll x;
  ll y;
};

bool compare_tower(Tower &t1, Tower &t2) {
  return t1.p < t2.p;
}

bool compare_balloon(Balloon &b1, Balloon &b2) {
  return b1.x < b2.x;
}

int division(vector<Tower> &towers, int p) {
  int l = 1;
  int r = towers.size() - 1;

  if (towers[r].p <= p) {
    return r;
  }

  while (l <= r) {
    int mid = l + (r - l) / 2;
    int mid_p = towers[mid].p;
    if (mid_p <= p) {
      if (towers[mid + 1].p > p) {
        return mid;
      } else {
        l = mid + 1;
      }
    } else {
      r = mid - 1;
    }
  }

  return 0;
}

int compare(vector<Tower> &towers, vector<Balloon> &balloons) {
  int count = 0;
  for (auto balloon : balloons)
    for (auto tower : towers) {
      if ((abs(tower.p - balloon.x) + balloon.y <= tower.h)) {
        count++;
        break;
      }
    }
  return count;
}

void solve(int case_num) {
  int n, k;
  ll p1, p2, a1, b1, c1, m1;
  ll h1, h2, a2, b2, c2, m2;
  ll x1, x2, a3, b3, c3, m3;
  ll y1, y2, a4, b4, c4, m4;
  vector<ll> p, h, x, y;
  vector<Tower> towers;
  vector<Balloon> balloons;
  multiset<ll, greater<> > left_heap, right_heap;

  cin >> n >> k;
  cin >> p1 >> p2 >> a1 >> b1 >> c1 >> m1;
  cin >> h1 >> h2 >> a2 >> b2 >> c2 >> m2;
  cin >> x1 >> x2 >> a3 >> b3 >> c3 >> m3;
  cin >> y1 >> y2 >> a4 >> b4 >> c4 >> m4;

  p.push_back(p1);
  p.push_back(p2);
  for (int i = 2; i < n; ++i) {
    p.push_back((a1 * p[i - 1] + b1 * p[i - 2] + c1) % m1 + 1);
  }

  h.push_back(h1);
  h.push_back(h2);
  for (int i = 2; i < n; ++i) {
    h.push_back((a2 * h[i - 1] + b2 * h[i - 2] + c2) % m2 + 1);
  }

  x.push_back(x1);
  x.push_back(x2);
  for (int i = 2; i < k; ++i) {
    x.push_back((a3 * x[i - 1] + b3 * x[i - 2] + c3) % m3 + 1);
  }

  y.push_back(y1);
  y.push_back(y2);
  for (int i = 2; i < k; ++i) {
    y.push_back((a4 * y[i - 1] + b4 * y[i - 2] + c4) % m4 + 1);
  }

  // Add a sentinel tower.
  auto tower_sentinel = Tower();
  tower_sentinel.p = 0;
  tower_sentinel.h = 0;
  towers.push_back(tower_sentinel);

  for (int i = 0; i < n; ++i) {
    auto tower = Tower();
    tower.p = p[i];
    tower.h = h[i];
    towers.push_back(tower);
  }

  for (int i = 0; i < k; ++i) {
    auto balloon = Balloon();
    balloon.x = x[i];
    balloon.y = y[i];
    balloons.push_back(balloon);
  }

  // Sort towers and balloons according to x-axis.
  sort(towers.begin(), towers.end(), compare_tower);
  sort(balloons.begin(), balloons.end(), compare_balloon);

  // Initialize the right heap.
  int count = 0;
  int left = 0;
  for (int i = 1; i <= n; ++i) {
    right_heap.insert(towers[i].h - towers[i].p);
  }

  for (auto balloon : balloons) {
    // Find the closest tower to the left of current balloon.
    int lr = division(towers, balloon.x);

    // Update the left heap.
    for (int i = left + 1; i <= lr; ++i) {
      left_heap.insert(towers[i].h + towers[i].p);
    }

    // Update the right heap.
    for (int i = left + 1; i <= lr; ++i) {
      int to_del = towers[i].h - towers[i].p;
      auto hit(right_heap.find(to_del));
      if (hit != right_heap.end())
        right_heap.erase(hit);
    }

    left = lr;
    int left_max = INT_MIN, right_max = INT_MIN;
    if (lr > 0) {
      left_max = *left_heap.begin();
    }
    if (lr < n) {
      right_max = *right_heap.begin();
    }

    // A possible tower exists either to the left or to the right.
    if (left_max >= balloon.x + balloon.y || right_max >= balloon.y - balloon.x) {
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