#!/bin/bash

# this script assumes that you are using Competitive Programming helper
#
if [ ! -d ~/projects/cp/.cph ]; then
  echo "./.cph does not exist. Use CPH for this script"
  exit
fi

spinner() {
  PID=$!
  i=1
  sp="/-\|"
  echo -n ' '
  while [ -d /proc/$PID ]; do
    printf "\b${sp:i++%${#sp}:1}"
  done
}
# compiling
g++ -std=c++20 -DLOCAL -DDEBUG_GRAPH $1 -o /tmp/graph.out &
spinner

if [ ! -f /tmp/graph.out ]; then
  echo -en "\rCompilation Failed!\n"
else
  echo -en "\rCompilation Done\n"

  mkdir -p ~/projects/cp/test.graph/

  # read each item in the JSON array to an item in the Bash array
  array="$(cat ./.cph/"."$1* | jq -c -S '.tests[]')"
  readarray -t my_array <<<"$array"

  # iterate through the Bash array
  for item in "${my_array[@]}"; do
    input="$(jq --raw-output '.input' <<<"$item")"
    id="$(jq --raw-output '.id' <<<"$item")"
    echo "$input" >./test.graph/$1.$id.test
  done

  for file in ~/projects/cp/test.graph/$1.*; do
    [ -f "$file" ] && echo "Processing $file" && /tmp/graph.out <"$file"
  done

  rm /tmp/graph.out
  rm /tmp/graph.svg
  rm /tmp/graph.dot
fi
