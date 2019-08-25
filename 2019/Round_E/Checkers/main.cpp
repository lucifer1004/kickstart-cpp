#include <iostream>
#include <vector>

using namespace std;

vector<int> primes{2,3,5,7,11,13,17,19};

bool is_prime(int n) {
  bool prime = true;
  int j = 0;
  while (primes[j] * primes[j] <= n) {
    if (n % primes[j] == 0) {
      prime = false;
      break;
    }
    j++;
  }
  return prime;
}

bool possible(int n) {
  if (n <= 2) return true;
  if (n % 2 == 1) {
    return is_prime(n);
  } else {
    int half = n / 2;
    if (half % 2 == 1) return true;
    else {
      int hh = half / 2;
      if (is_prime(hh)) return true;
    }
  }
  return false;
}

void solve(int case_num) {
  int l, r;
  cin >> l >> r;
  int ans = 0;
  for (int i = l; i <= r; ++i) if (possible(i)) ans++;
  cout << "Case #" << case_num << ": " << ans << endl;
}

int main()
{
  for (int i = 10; i < 50000; ++i) {
    int n = 2 * i + 1;
    int j = 0;
    bool prime = true;
    while (primes[j] * primes[j] <= n) {
      if (n % primes[j] == 0) {
        prime = false;
        break;
      }
      j++;
    }
    if (prime) primes.emplace_back(n);
  }
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}