#include <iostream>
#include <climits>
#include <queue>

using namespace std;

struct Node {
  int x;
  int y;
  int step;
};

const int SAFE_TIME = 10000;
const int SEARCH_RADIUS = 303;

int main() {
  int m;
  int map[SEARCH_RADIUS][SEARCH_RADIUS]{};
  bool used[SEARCH_RADIUS][SEARCH_RADIUS]{};
  int direction[4][2]{0, -1, 1, 0, 0, 1, -1, 0};

  for (int i = 0; i < SEARCH_RADIUS; ++i) {
    for (int j = 0; j < SEARCH_RADIUS; ++j) {
      map[i][j] = SAFE_TIME;
    }
  }

  cin >> m;
  for (int i = 0; i < m; ++i) {
    int xi, yi, ti;
    cin >> xi >> yi >> ti;
    if (map[xi][yi] > ti) map[xi][yi] = ti;
    for (const auto& d : direction) {
      int x = xi + d[0];
      int y = yi + d[1];
      if (x < 0 || y < 0 ) continue;
      if (map[x][y] > ti) map[x][y] = ti;
    }
  }

  queue<Node> bfs;
  bfs.push({0, 0, 0});
  used[0][0] = true;

  do {
    auto current = bfs.front();
    int xi = current.x;
    int yi = current.y;
    int ti = current.step;
    if (map[xi][yi] == SAFE_TIME) {
      cout << ti << endl;
      return 0;
    }
    for (const auto& d : direction) {
      int x = xi + d[0];
      int y = yi + d[1];
      if (x < 0 || y < 0 || map[x][y] <= ti + 1 || used[x][y]) continue;
      used[x][y] = true;
      bfs.push({x, y, ti+1});
    }
    bfs.pop();
  } while (!bfs.empty());

  cout << -1 << endl;

  return 0;
}