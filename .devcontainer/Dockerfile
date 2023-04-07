FROM docker.io/eyalamirmusic/juce_dev_machine:latest AS base

# Install JUCE globally in the container.
RUN git clone https://github.com/juce-framework/JUCE.git
# Go to JUCE directory
RUN cd JUCE && \
     cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=/opt/juce && \
     cmake --build cmake-build-install --target install

RUN DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libasound2-dev

WORKDIR /plugin
