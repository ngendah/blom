FROM ubuntu:22.04
RUN apt-get update \
    && apt-get install -y cmake ninja-build build-essential gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi
RUN apt-get install -y vim
RUN useradd -Umu 1000 workspace
WORKDIR /home/workspace/blom

