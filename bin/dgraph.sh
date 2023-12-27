#!/bin/bash

echo 'Executing for debugging graph problems'

g++ -std=c++20 -DLOCAL -DDEBUG_GRAPH $1 -o /tmp/graph.out

if [ ! -f /tmp/graph.out ]; then
  echo "Compilation Failed!"
else
  /tmp/graph.out <~/projects/cp/test.graph
  rm /tmp/graph.out
  rm /tmp/graph.svg
  rm /tmp/graph.dot
fi
