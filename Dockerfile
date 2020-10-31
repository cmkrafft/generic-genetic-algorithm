FROM ubuntu:rolling

ARG CMAKE_VERSION=3.19.0-rc2

RUN apt update && apt install clang libomp-dev build-essential wget openssl libssl-dev valgrind doxygen git -y

WORKDIR /tmp
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz
RUN tar -zxvf cmake-${CMAKE_VERSION}.tar.gz

WORKDIR /tmp/cmake-${CMAKE_VERSION}
RUN ./bootstrap
RUN make
RUN make install

RUN rm -rf /tmp/cmake-${CMAKE_VERSION}
RUN rm /tmp/cmake-${CMAKE_VERSION}.tar.gz
RUN rm -rf /var/lib/apt/lists/*

RUN cmake --version
