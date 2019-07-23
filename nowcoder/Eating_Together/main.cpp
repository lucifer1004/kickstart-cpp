#include <iostream>
#include <vector>

using namespace std;

int min (int a, int b, int c) {
  return min(a, min(b, c));
}

int main() {
  int n;
  vector<int> f1, g1, f2, g2, f3, g3;
  cin >> n;
  f1.push_back(0);
  g1.push_back(0);
  f2.push_back(0);
  g2.push_back(0);
  f3.push_back(0);
  g3.push_back(0);
  for (int i = 0; i < n; ++i) {
    int xi;
    cin >> xi;
    switch (xi) {
      case 1:
        f1.push_back(f1[i]);
        g1.push_back(min(g1[i], g2[i], g3[i]));
        f2.push_back(min(f1[i], f2[i]) + 1);
        g2.push_back(min(g2[i], g3[i]) + 1);
        f3.push_back(min(f1[i], f2[i], f3[i]) + 1);
        g3.push_back(g3[i] + 1);
        break;
      case 2:
        f1.push_back(f1[i] + 1);
        g1.push_back(min(g1[i], g2[i], g3[i]) + 1);
        f2.push_back(min(f1[i], f2[i]));
        g2.push_back(min(g2[i], g3[i]));
        f3.push_back(min(f1[i], f2[i], f3[i]) + 1);
        g3.push_back(g3[i] + 1);
        break;
      case 3:
        f1.push_back(f1[i] + 1);
        g1.push_back(min(g1[i], g2[i], g3[i]) + 1);
        f2.push_back(min(f1[i], f2[i]) + 1);
        g2.push_back(min(g2[i], g3[i]) + 1);
        f3.push_back(min(f1[i], f2[i], f3[i]));
        g3.push_back(g3[i]);
        break;
    }
  }
  cout << min(min(f1[n], f2[n], f3[n]), min(g1[n], g2[n], g3[n])) << endl;

  return 0;
}