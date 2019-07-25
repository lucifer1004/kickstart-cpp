#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <iterator>
#include <string>

using namespace std;

int max(int a, int b, int c) {
  return max(a, max(b, c));
}

class Star {
  int xl_, yl_, zl_, xh_, yh_, zh_;

public:
  Star() = default;

  Star(int xl, int yl, int zl, int xh, int yh, int zh) {
    xl_ = xl;
    yl_ = yl;
    zl_ = zl;
    xh_ = xh;
    yh_ = yh;
    zh_ = zh;
  }

  static bool contain(Star &a, Star &b) {
    return (
      a.xl_ <= b.xl_ &&
      a.yl_ <= b.yl_ &&
      a.zl_ <= b.zl_ &&
      a.xh_ >= b.xh_ &&
      a.yh_ >= b.yh_ &&
      a.zh_ >= b.zh_
    );
  }
};

class Galaxy {
  int xl_, yl_, zl_, xh_, yh_, zh_;
  vector<Star> stars_;
  enum CONTAIN {
    LLL,
    LLH,
    LHL,
    LHH,
  };

  bool can_contain(int edge, CONTAIN type) {
    int xle = xl_ + edge;
    int yle = yl_ + edge;
    int zle = zl_ + edge;
    int xhe = xh_ - edge;
    int yhe = yh_ - edge;
    int zhe = zh_ - edge;

    Star left, right;

    switch (type) {
      case LLL:
        left = Star(xl_, yl_, zl_, xle, yle, zle);
        right = Star(xhe, yhe, zhe, xh_, yh_, zh_);
        break;
      case LLH:
        left = Star(xl_, yl_, zhe, xle, yle, zh_);
        right = Star(xhe, yhe, zl_, xh_, yh_, zle);
        break;
      case LHL:
        left = Star(xl_, yhe, zl_, xle, yh_, zle);
        right = Star(xhe, yl_, zhe, xh_, yle, zh_);
        break;
      case LHH:
        left = Star(xl_, yhe, zhe, xle, yh_, zh_);
        right = Star(xhe, yl_, zl_, xh_, yle, zle);
        break;
      default:
        break;
    }

    for (auto &star : stars_) {
      if (!Star::contain(left, star) && !Star::contain(right, star)) return false;
    }

    return true;
  }

public:
  Galaxy() {
    xl_ = yl_ = zl_ = INT_MAX;
    xh_ = yh_ = zh_ = INT_MIN;
  };

  void add_star(int x, int y, int z, int r) {
    int xl = x - r;
    xl_ = min(xl_, xl);
    int yl = y - r;
    yl_ = min(yl_, yl);
    int zl = z - r;
    zl_ = min(zl_, zl);
    int xh = x + r;
    xh_ = max(xh_, xh);
    int yh = y + r;
    yh_ = max(yh_, yh);
    int zh = z + r;
    zh_ = max(zh_, zh);
    stars_.emplace_back(Star(xl, yl, zl, xh, yh, zh));
  }

  int min_edge() {
    int best = INT_MAX;

    for (int type = LLL; type <= LHH; ++type) {
      int l = 1;
      int r = max(xh_ - xl_, yh_ - yl_, zh_ - zl_);

      while (l <= r) {
        int mid = l + (r - l) / 2;
        bool curr = can_contain(mid, (CONTAIN) type);
        bool prev = can_contain(mid - 1, (CONTAIN) type);
        if (!prev && curr) {
          best = min(best, mid);
          break;
        }
        if (!curr) l = mid + 1;
        if (prev) r = mid - 1;
      }
    }

    return best;
  }

};

void solve(int case_num) {
  int n;
  Galaxy galaxy = Galaxy();

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int xi, yi, zi, ri;
    cin >> xi >> yi >> zi >> ri;
    galaxy.add_star(xi, yi, zi, ri);
  }
  cout << "Case #" << case_num << ": " << galaxy.min_edge() << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}