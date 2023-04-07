#!/bin/bash

# Stop on errors.
set -e

# Check if an argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Set the argument as X
X=$1

# Change to the provided directory
cd "$X" || exit

# Configure the build, passing the JUCE install path
cmake -B cmake-build -DCMAKE_PREFIX_PATH=/opt/juce -G Ninja

# Build the project
cmake --build cmake-build
