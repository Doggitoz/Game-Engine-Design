#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> Split(string s, string delimiter) {
  vector<string> result;
  int start = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s.at(i) == delimiter.at(0)) {
      if (start == i)
        result.push_back("");
      else
        result.push_back(s.substr(start, i - start));
      start = i + 1;
    }
  }

  if (start < s.length())
    result.push_back(s.substr(start));

  return result;
}

class Node {
public:
  string name;
  vector<Node *> children;

  Node(string name) { this->name = name; }
};

class Tree {
public:
  Node *root;

  Tree() { this->root = new Node(""); }

  Tree(Node *node) { this->root = node; }

  void operator+=(string path) {
    vector<string> parts = Split(path, ",");
    Node *currentNode = root;
    

    for (const string &part : parts) {
      Node *childNode = nullptr;
      for (Node *child : currentNode->children) {
        if (child->name == part) {
          childNode = child;
          break;
        }
      }

      if (childNode == nullptr) {
        childNode = new Node(part);
        currentNode->children.push_back(childNode);
      }

      currentNode = childNode;
    }
  }

  void printTree(Node *node, int depth) {
    if (node == nullptr)
      return;
    for (int i = 0; i < depth; i++)
      cout << "  ";
    cout << node->name << endl;

    for (Node *child : node->children) {
      printTree(child, depth + 1);
    }
  }
};

ostream &operator<<(ostream &os, Tree t) {
  t.printTree(t.root, 0);
  cout << endl;
  return os;
}

ostream &operator<<(ostream &os, vector<string> list) {
  for (auto element : list)
    cout << element << "-";
  cout << endl;
  return os;
}

string nextLine(string hint) {
  cout << hint;
  string s;
  getline(cin, s);
  return s;
}

int main() {
  auto tree = Tree();
  for (string s = "tree+=", path = nextLine(s); path != "NULL";
       path = nextLine(s)) {
    tree += path;
  }
  cout << tree;
  return 0;
}