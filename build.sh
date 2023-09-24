#!/bin/env sh
cd $(dirname $(realpath $0))
mkdir build 2>/dev/null
g++ tik.cpp -o build/tiktaktoe