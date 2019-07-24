#include <iostream>
#include <climits>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

struct Node {
  string mother;
  vector<string> children;
  int depth;
};

class FamilyTree {
  unordered_map<string, Node> nodes_;

  void update_down(const string &name, int depth) {
    auto node = nodes_.find(name);
    node->second.depth = depth + 1;
    for (const auto &child_name : node->second.children) update_down(child_name, depth + 1);
  }

  string lca(string a, string b) {
    auto node_a = nodes_.find(a);
    auto node_b = nodes_.find(b);

    int da = node_a->second.depth;
    int db = node_b->second.depth;

    if (da > db) {
      swap(a, b);
      swap(node_a, node_b);
      swap(da, db);
    }

    while (db > da) {
      node_b = nodes_.find(node_b->second.mother);
      db--;
    }

    while (da >= 0) {
      if (node_a->first == node_b->first) return node_a->first;
      node_a = nodes_.find(node_a->second.mother);
      node_b = nodes_.find(node_b->second.mother);
      da--;
      db--;
    }

    return "";
  }

public:
  FamilyTree() = default;

  auto add_name(const string &a, int depth = 0) {
    return nodes_.insert(pair<string, Node>{a, Node{}}).first;
  }

  void add_relationship(const string &mother_name, const string &child_name) {
    auto mother = nodes_.find(mother_name);
    auto child = nodes_.find(child_name);
    if (mother == nodes_.end()) mother = add_name(mother_name);
    mother->second.children.push_back(child_name);
    if (child == nodes_.end()) child = add_name(child_name);
    child->second.mother = mother_name;
    update_down(child->first, mother->second.depth);
  }

  void query(string a, string b) {
    auto node_a = nodes_.find(a);
    auto node_b = nodes_.find(b);
    auto ancestor = lca(a, b);
    if (ancestor.empty()) cout << "NOT RELATED" << endl;
    else {
      int da = node_a->second.depth;
      int db = node_b->second.depth;
      int d = nodes_.find(ancestor)->second.depth;
      if (da == db) {
        if (da - d == 1) cout << "SIBLINGS" << endl;
        else cout << "COUSINS" << endl;
      } else {
        if (da > db) {
          swap(a, b);
          swap(da, db);
        }
        switch(da - d) {
          case 0:
            switch (db - da) {
              case 1:
                cout << a << " is the mother of " << b << endl;
                break;
              default:
                cout << a << " is the ";
                for (int i = 0; i < db - da - 2; ++i) cout << "great-";
                cout << "grand-mother of " << b << endl;
            }
            break;
          case 1:
            cout << a << " is the ";
            for (int i = 0; i < db - da - 1; ++i) cout << "great-";
            cout << "aunt of " << b << endl;
            break;
          default:
            cout << "COUSINS" << endl;
        }
      }
    }
  }
};

int main() {
  int n;
  string a, b;

  auto ft = FamilyTree();

  cin >> n >> a >> b;
  ft.add_name(a);
  ft.add_name(b);

  for (int i = 0; i < n; ++i) {
    string mother, child;
    cin >> mother >> child;
    ft.add_relationship(mother, child);
  }

  ft.query(a, b);

  return 0;
}