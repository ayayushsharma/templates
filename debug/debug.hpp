#ifndef CP_DEBUG_H
#define CP_DEBUG_H

#if defined(DEBUG_GRAPH)
#include "graph/graph.hpp"
#else
#define graph(...)
#endif

#define echo(...)                                      \
  debugging::__debug_print(#__VA_ARGS__, __VA_ARGS__); \
  cout << "\n";
#define TESTCASE cout << "case " << i << ": " << endl;
#define fast_io ios_base::sync_with_stdio(true), std::cin.tie(0);
#define tab "    "
#define smalltab "  "

namespace debugging {
template <typename T>
void _print(T c) {
  std::cout << c;
}

template <typename T, typename V>
void _print(std::pair<T, V> c) {
  std::cout << "{";
  debugging::_print(c.first);
  std::cout << ",";
  debugging::_print(c.second);
  std::cout << "}";
}

template <typename T>
void _print(std::priority_queue<T> c) {
  std::cout << '{';
  if (c.empty()) {
    std::cout << "}";
    return;
  }
  while (c.size() > 1) {
    debugging::_print(c.top());
    c.pop();
    std::cout << ",";
  }
  debugging::_print(c.top());
  std::cout << "}";
}

template <typename T>
void _print(std::priority_queue<T, std::vector<T>, std::greater<T>> c) {
  std::cout << '{';
  if (c.empty()) {
    std::cout << "}";
    return;
  }
  while (c.size() > 1) {
    debugging::_print(c.top());
    c.pop();
    std::cout << ",";
  }
  debugging::_print(c.top());
  std::cout << "}";
}

template <typename T>
void _print(std::vector<T> c) {
  int f = 0;
  std::cout << '{';
  for (auto i : c) std::cout << (f++ ? "," : ""), debugging::_print(i);
  std::cout << "}";
}

template <typename T>
void _print(std::vector<std::vector<T>> c) {
  std::cout << "\n" smalltab "{\n" tab;
  int f = 0;
  for (auto &i : c) {
    std::cout << (f++ ? ",\n" tab : ""), debugging::_print(i);
  }
  std::cout << "\n" smalltab "}\n ";
}

template <typename T>
void _print(std::set<T> c) {
  int f = 0;
  std::cout << '{';
  for (auto &i : c) std::cout << (f++ ? ", " : ""), debugging::_print(i);
  std::cout << "}";
}

template <typename T>
void _print(std::multiset<T> c) {
  int f = 0;
  std::cout << '{';
  for (auto &i : c) std::cout << (f++ ? ", " : ""), debugging::_print(i);
  std::cout << "}";
}

template <typename T, typename V>
void _print(std::map<T, V> c) {
  std::cout << "\n";
  for (auto x : c) {
    std::cout << smalltab;
    debugging::_print(x.first);
    std::cout << "  ";
    debugging::_print(x.second);
    std::cout << "\n";
  }
}

template <typename T>
void __deb(std::istringstream &ss, T arg) {
  std::string n;
  getline(ss, n, ',');
  const auto pos(n.find_first_not_of(" "));
  n.erase(0, pos);
  std::cout << "[" << n << ": ";
  debugging::_print(arg);
  std::cout << "] ";
}
template <typename... T>
void __debug_print(const char *n, T &&...args) {
  std::istringstream ss(n);
  (__deb(ss, args), ...);
}
}  // namespace debugging

#endif
