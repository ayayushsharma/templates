// IF YOU WANT TO USE THE GRAPH UTILS, USE DEBUG_GRAPH flag during compilation
// also install vv-sixel, boost graoh for dot file conversions
// and use a sixel compatible terminal. Konsole works

#ifndef CP_GRAPHUTILS_H

#define CP_GRAPHUTILS_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>

const std::string GRAPH_DOT_FILE_LOCATION = "/tmp/graph.dot";
const std::string GRAPH_SVG_FILE_LOCATION = "/tmp/graph.svg";
const int GRAPH_DEFAULT_HEIGHT = 600;
const int GRAPH_DEFAULT_WIDTH = 600;

namespace graphUtils {
/**
 * returns the vertices in the order a < b in a set of {a, b} on whatever output
 * you give to it
 */
std::pair<int, int> distinctEdge(int a, int b) {
    if (a > b) std::swap(a, b);
    return std::make_pair(a, b);
}

/**
 * This function finds number of "new line" ('\n') in the string to approximate
 * the number of edges in the graph
 */
int numberOfEdgesFromDotFile(const std::string &graphDotString) {
    int count = 0;
    for (size_t i = 0; i < graphDotString.length(); i++)
        if (graphDotString[i] == '\n') ++count;
    return count;
}

/**
 *
 */
void exec(std::string &command_str) {
    const char *COMMAND = command_str.c_str();
    system(COMMAND);
}
/**
 * Write the supplied string to the configured dot file.
 * Also returns the string supplied
 */
void dotFile(const std::string &graphDotString) {
    std::ofstream graphDotFile(GRAPH_DOT_FILE_LOCATION);
    graphDotFile << graphDotString;
    graphDotFile.close();
}

/**
 * Create a SVG from the dot file
 */
void createGraphSVG() {
    std::string COMMAND = "dot -Tsvg " + GRAPH_DOT_FILE_LOCATION + " -o " +
                          GRAPH_SVG_FILE_LOCATION;
    graphUtils::exec(COMMAND);
}

/**
 * Prints the svg in form of sixel in height * width
 */
void createGraphSixel(int HEIGHT, int WIDTH) {
    std::string COMMAND =
        "vv --preview-size=" + std::to_string(max(HEIGHT, WIDTH)) +
        " --geometry=" + std::to_string(HEIGHT) + "x" + std::to_string(WIDTH) +
        " " + GRAPH_SVG_FILE_LOCATION;
    graphUtils::exec(COMMAND);
}
/**
 * Prints the svg in form of sixel and resizes it automatically
 */
void createGraphSixel(int number_of_edges) {
    int FACTOR = std::sqrt(number_of_edges);
    int HEIGHT = min(1000, FACTOR * GRAPH_DEFAULT_HEIGHT / 2),
        WIDTH = min(1800, FACTOR * GRAPH_DEFAULT_WIDTH / 2);
    graphUtils::createGraphSixel(HEIGHT, WIDTH);
}

/**
 * Print the graph String in sixel format in console
 */
void printSixelGraph(const std::string &graphString) {
    int numberOfEdges = graphUtils::numberOfEdgesFromDotFile(graphString);
    graphUtils::dotFile(graphString);
    graphUtils::createGraphSVG();
    graphUtils::createGraphSixel(numberOfEdges);
}
}  // namespace graphUtils

#endif
