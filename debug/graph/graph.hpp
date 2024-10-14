// IF YOU WANT TO USE THE GRAPH UTILS, USE DEBUG_GRAPH flag during compilation
// also install vv-sixel, boost graoh for dot file conversions
// and use a sixel compatible terminal. Konsole works

#ifndef CP_GRAPH_H
#define CP_GRAPH_H

#include "graphUtils.hpp"

#include <set>
#include <string>
#include <vector>

#define graph(x, y) graph::printGraph(x, y)

namespace graph {

inline std::string undirectedGraphDotString(
    const std::vector<std::vector<int>> &graph) {
  // to store distinct edges between to vertices
  std::set<std::pair<int, int>> edge;

  // creating edges
  for (int parent = 0; parent < graph.size(); parent++) {
    for (int child = 0; child < graph[parent].size(); child++) {
      edge.insert(graphUtils::distinctEdge(parent, graph[parent][child]));
    }
  }

  // making a string to put into the graph.dot file
  std::string dotString = "graph {\n";
  for (auto vertices : edge) {
    dotString += std::to_string(vertices.first) + " -- " +
                 std::to_string(vertices.second) + ";\n";
  }
  dotString += "}";

  // return the dot string
  return dotString;
}

inline std::string directedGraphDotString(
    const std::vector<std::vector<int>> &graph) {
  // to store distinct edges between to vertices
  std::set<std::pair<int, int>> edge;

  // creating edges
  for (int parent = 0; parent < graph.size(); parent++) {
    for (int child = 0; child < graph[parent].size(); child++) {
      edge.insert(std::make_pair(parent, graph[parent][child]));
    }
  }

  // making a string to put into the graph.dot file
  std::string dotString = "digraph {\n";
  for (auto vertices : edge) {
    dotString += std::to_string(vertices.first) + " -> " +
                 std::to_string(vertices.second) + ";\n";
  }
  dotString += "}";

  // return the dot string
  return dotString;
}

inline void printUndirectedGraph(const std::vector<std::vector<int>> &graph) {
  std::string graphString = graph::undirectedGraphDotString(graph);
  graphUtils::printSixelGraph(graphString);
}

inline void printDirectedGraph(const std::vector<std::vector<int>> &graph) {
  std::string graphString = graph::directedGraphDotString(graph);
  graphUtils::printSixelGraph(graphString);
}

/**
 * Defaults to print graph
 */
inline void printGraph(const std::vector<std::vector<int>> &graph, char type) {
  switch (type) {
  case 'U':
  case 'u':
    graph::printUndirectedGraph(graph);
    break;
  case 'D':
  case 'd':
    graph::printDirectedGraph(graph);
    break;
  default:
    graph::printUndirectedGraph(graph);
    break;
  }
}

}  // namespace graph
#endif
