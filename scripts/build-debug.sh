#!/bin/bash
if [ ! -d "build" ]; then
    scripts/configure-debug.sh
fi
cmake --build build --config Debug --parallel
