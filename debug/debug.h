#ifndef CP_DEBUG_H

#if defined(DEBUG_GRAPH)
#include "graph/graph.h"
#else
#define graph(...)
#endif

#define CP_DEBUG_H
#define echo(...)                                      \
  debugging::__debug_print(#__VA_ARGS__, __VA_ARGS__); \
  cout << endl;
#define TESTCASE cout << "case " << i << ": " << endl;
#define fast_io ios_base::sync_with_stdio(true), std::cin.tie(0);
#define tab "    "
#define smalltab "  "

namespace debugging {
template <typename T>
void _print(T c) {
  cout << c;
}

template <typename T, typename V>
void _print(pair<T, V> c) {
  cout << "{";
  debugging::_print(c.first);
  cout << ",";
  debugging::_print(c.second);
  cout << "}";
}

template <typename T>
void _print(priority_queue<T> c) {
  cout << '{';
  if (c.empty()) {
    cout << "}";
    return;
  }
  while (c.size() > 1) {
    debugging::_print(c.top());
    c.pop();
    cout << ",";
  }
  debugging::_print(c.top());
  cout << "}";
}

template <typename T>
void _print(priority_queue<T, vector<T>, greater<T>> c) {
  cout << '{';
  if (c.empty()) {
    cout << "}";
    return;
  }
  while (c.size() > 1) {
    debugging::_print(c.top());
    c.pop();
    cout << ",";
  }
  debugging::_print(c.top());
  cout << "}";
}

template <typename T>
void _print(vector<T> c) {
  int f = 0;
  cout << '{';
  for (auto i : c) cout << (f++ ? "," : ""), debugging::_print(i);
  cout << "}";
}

template <typename T>
void _print(vector<vector<T>> c) {
  cout << "\n" smalltab "{\n" tab;
  int f = 0;
  for (auto &i : c) {
    cout << (f++ ? ",\n" tab : ""), debugging::_print(i);
  }
  cout << "\n" smalltab "}\n ";
}

template <typename T>
void _print(set<T> c) {
  int f = 0;
  cout << '{';
  for (auto &i : c) cout << (f++ ? ", " : ""), debugging::_print(i);
  cout << "}";
}

template <typename T>
void _print(multiset<T> c) {
  int f = 0;
  cout << '{';
  for (auto &i : c) cout << (f++ ? ", " : ""), debugging::_print(i);
  cout << "}";
}

template <typename T, typename V>
void _print(map<T, V> c) {
  cout << endl;
  for (auto x : c) {
    cout << smalltab;
    debugging::_print(x.first);
    cout << "  ";
    debugging::_print(x.second);
    cout << endl;
  }
}

template <typename T>
void __deb(istringstream &ss, T arg) {
  string n;
  getline(ss, n, ',');
  const auto pos(n.find_first_not_of(" "));
  n.erase(0, pos);
  cout << "[" << n << ": ";
  debugging::_print(arg);
  cout << "] ";
}
template <typename... T>
void __debug_print(const char *n, T &&...args) {
  istringstream ss(n);
  (__deb(ss, args), ...);
}
}  // namespace debugging

#endif
