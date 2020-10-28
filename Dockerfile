FROM ubuntu:latest

ARG CMAKE_VERSION=3.19.0-rc2

RUN apt update && apt upgrade -y
RUN apt install clang libomp-dev build-essential wget openssl libssl-dev -y

RUN cd /tmp && \
    wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz && \
    tar -zxvf cmake-${CMAKE_VERSION}.tar.gz && \
    cd cmake-${CMAKE_VERSION} && \
    ./bootstrap && \
    make && make install

RUN rm -rf /tmp/cmake-${CMAKE_VERSION}
RUN rm /tmp/cmake-${CMAKE_VERSION}.tar.gz
RUN rm -rf /var/lib/apt/lists/*

RUN cmake --version
