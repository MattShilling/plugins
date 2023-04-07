#!/bin/bash

set -e

docker run \
  --rm \
  -v $(pwd):/plugin \
  -p 8080:8080 \
  -it \
  plugin-dev \
  /bin/bash
