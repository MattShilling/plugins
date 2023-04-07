#!/bin/bash

set -e -x

docker pull docker.io/eyalamirmusic/juce_dev_machine:latest

cd .devcontainer && docker build -t plugin-dev .
