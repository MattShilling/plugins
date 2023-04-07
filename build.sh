#!/bin/bash

# Stop on errors.
set -e

# Check if an argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Change to the provided directory
cd "$1" || exit

# Format.
clang-format-11 *.h *.cc -i

# Configure the build, passing the JUCE install path
cmake -B cmake-build -DCMAKE_PREFIX_PATH=/opt/juce -G Ninja

# Build the project
cmake --build cmake-build
