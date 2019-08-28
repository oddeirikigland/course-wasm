#!/bin/bash

mkdir -p out
emcc -std=c++14 -g -s MODULARIZE=1 -s EXPORTED_FUNCTIONS='["_move"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -s WASM=1 -s MODULARIZE=1 -Isrc/solver src/solver/main.cpp src/solver/*.cpp -o solver.js

echo "export { Module as default }" >> solver.js
