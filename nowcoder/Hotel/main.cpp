#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

#define ASSERT_WITH_MESSAGE(condition, message) do { \
if (!(condition)) { cout << (message) << endl; } \
assert ((condition)); } while(false)

using namespace std;

struct Interval {
  int begin;
  int end;
};

struct CustomCompare {
  bool operator()(const Interval &a, const Interval &b) {
    return a.begin < b.begin || (a.begin == b.begin && a.end < b.end);
  }
};

enum DEBUG_MODE {
  ON,
  OFF,
};

class IntervalSet {

  int limit_;
  set<Interval, CustomCompare> interval_set_;
  DEBUG_MODE debug_mode_;

  void debug() {
    if (debug_mode_ == DEBUG_MODE::OFF) return;

    if (interval_set_.empty()) cout << "所有房间都已被占满" << endl;
    else {
      cout << "当前空闲区间为 ";
      for (const auto &interval : interval_set_) {
        cout << "[" << interval.begin << "," << interval.end << "] ";
      }
      cout << endl;
    }
  }

public:

  explicit IntervalSet(int n, DEBUG_MODE debug_mode = DEBUG_MODE::OFF) {
    limit_ = n;
    interval_set_ = set<Interval, CustomCompare>{Interval{1, n}};
    debug_mode_ = debug_mode;
  }

  int take(int di) {
    int ans = 0;
    Interval to_del{};
    for (const auto &interval : interval_set_) {
      if (interval.end - interval.begin + 1 >= di) {
        ans = interval.begin;
        to_del = interval;
        interval_set_.erase(to_del);
        break;
      }
    }
    if (to_del.end - to_del.begin + 1 > di) {
      interval_set_.insert({to_del.begin + di, to_del.end});
    }

    debug();
    return ans;
  }

  void release(int xi, int di) {
    ASSERT_WITH_MESSAGE(xi > 0, "xi should be a positive integer!");
    ASSERT_WITH_MESSAGE(di > 0, "di should be a positive integer!");
    ASSERT_WITH_MESSAGE(xi + di - 1 <= limit_, "Exceeding hotel room limit!");

    auto new_int = Interval{xi, xi + di - 1};
    if (interval_set_.empty()) {
      interval_set_.insert(new_int);
      debug();
      return;
    }

    int new_begin = new_int.begin, new_end = new_int.end;
    auto left = interval_set_.lower_bound(new_int);
    auto right = interval_set_.lower_bound(Interval{new_int.end + 2, new_int.end + 2});

    if (left == interval_set_.end()) {
      --left;
      if (left->end >= new_int.end) return;
      else if (left->end >= new_int.begin - 1) {
        new_begin = left->begin;
        interval_set_.erase(left);
      }
    } else {
      if (left != interval_set_.begin()) --left;
      if (left->end >= new_int.begin - 1) new_begin = min(new_begin, left->begin);
      else ++left;
      if (right != interval_set_.begin()) {
        --right;
        new_end = max(new_end, right->end);
        ++right;
      }
      interval_set_.erase(left, right);
    }

    interval_set_.insert(Interval{new_begin, new_end});
    debug();
  }

};

int main() {
  int n, m;
  cin >> n >> m;
  auto interval_set = IntervalSet(n, DEBUG_MODE::ON);
  for (int i = 0; i < m; ++i) {
    int t, di, xi;
    cin >> t;
    ASSERT_WITH_MESSAGE(t == 1 || t == 2, "Operation type unrecognized!");
    if (t == 1) {
      cin >> di;
      cout << interval_set.take(di) << endl;
    } else {
      cin >> xi >> di;
      interval_set.release(xi, di);
    }
  }
  return 0;
}