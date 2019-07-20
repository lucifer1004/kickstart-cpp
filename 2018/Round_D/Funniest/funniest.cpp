#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <string>

#define ll long long

using namespace std;

const int MAX_SIZE = 101;

ll gcd(ll a, ll b) {
  ll max_num = max(a, b);
  ll min_num = min(a, b);
  if (max_num % min_num == 0)
    return min_num;
  else
    return gcd(min_num, max_num % min_num);
}

void solve(int case_num) {
  int r, c, w;
  ll fun = 0, cost = 1, count = 0;
  char mat[MAX_SIZE][MAX_SIZE] = {};
  ll lr[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {};
  ll tb[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {};
  ll lr_acc[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {};
  ll tb_acc[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {};
  string s;
  vector<string> words[MAX_SIZE] = {};

  cin >> r >> c >> w;

  int max_len = max(r, c);

  for (int i = 1; i <= r; ++i) {
    cin >> s;
    for (int j = 1; j <= s.length(); j++) {
      mat[i][j] = s[j-1];
    }
  }

  for (int i = 0; i < w; ++i) {
    cin >> s;
    int len = s.length();
    if (len > max_len) {
      continue;
    }
    words[len].push_back(s);
    string rev(s);
    reverse(rev.begin(), rev.end());
    words[len].push_back(rev);
  }

  for (int i = 1; i <= r; ++i)
    for (int j = 1; j <= c; ++j) {
      string curr;

      // Left => Right
      for (int k = 1; k <= c - j + 1; ++k) {
        curr += mat[i][j + k - 1];
        lr[i][j][k] += lr[i][j][k - 1];
        for (const auto &word : words[k]) {
          if (curr == word) {
            lr[i][j][k] += k;
          }
        }
      }

      // Top => Bottom
      curr = "";
      for (int k = 1; k <= r - i + 1; ++k) {
        curr += mat[i + k - 1][j];
        tb[i][j][k] += tb[i][j][k - 1];
        for (const auto &word : words[k]) {
          if (curr == word) {
            tb[i][j][k] += k;
          }
        }
      }
    }

  for (int j = 1; j <= c; ++j)
    for (int v = j; v <= c; ++v)
      for (int i = 1; i <= r; ++i) {
        lr_acc[j][v][i] += lr_acc[j][v][i-1];
        for (int k = j; k <= v; ++k) {
          lr_acc[j][v][i] += lr[i][k][v-k+1];
        }
      }

  for (int i = 1; i <= r; ++i)
    for (int u = i; u <= r; ++u)
      for (int j = 1; j <= c; ++j) {
        tb_acc[i][u][j] += tb_acc[i][u][j-1];
        for (int k = i; k <= u; ++k) {
          tb_acc[i][u][j] += tb[k][j][u-k+1];
        }
      }

  for (int i = 1; i <= r; ++i)
    for (int j = 1; j <= c; ++j) {
      for (int u = i; u <= r; ++u)
        for (int v = j; v <= c; ++v) {
          ll curr_fun = lr_acc[j][v][u] - lr_acc[j][v][i-1] + tb_acc[i][u][v] - tb_acc[i][u][j-1];
          ll curr_cost = u + v - i - j + 2;
          ll curr = curr_fun * cost;
          ll old = fun * curr_cost;
          if (curr > old) {
            cost = curr_cost;
            fun = curr_fun;
            count = 1;
          } else if (curr == old) {
            count++;
          }
        }
    }

  if (fun == 0) cost = 1;
  else {
    ll gcd_ = gcd(fun, cost);
    fun /= gcd_;
    cost /= gcd_;
  }

  cout << "Case #" << case_num << ": " << fun << "/" << cost << " " << count << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}