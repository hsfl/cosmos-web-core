FROM ubuntu:20.04

SHELL ["/bin/bash",  "--login", "-c"]

WORKDIR /root
# Install apt packages
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt update && apt upgrade -y
RUN apt install git cmake python3 -y

# Get the emsdk repo
RUN git clone https://github.com/emscripten-core/emsdk.git
# Enter that directory
WORKDIR /root/emsdk
# Fetch the latest version of the emsdk (not needed the first time you clone)
RUN git pull
# Download and install the latest SDK tools.
RUN ./emsdk install latest

# Copy this project's files over
WORKDIR /root/cosmos/source/projects/cosmos-web-core/
COPY . .

# Use base cosmos image libraries
RUN git clone https://github.com/hsfl/cosmos-core.git /root/cosmos/source/core 
# COPY --from=hsfl2/core /root/cosmos/source/core/libraries /root/cosmos/source/core/libraries
WORKDIR /root/cosmos/source/projects/cosmos-web-core/scripts

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
RUN /root/emsdk/emsdk activate latest; \
# Activate PATH and other environment variables in the current terminal
    source /root/emsdk/emsdk_env.sh; \
    # Build emscripten project
    ./do_cmake_emcc

# # Leave user in project directory
# WORKDIR /root/cosmos/source/projects/cosmos-web-core/

