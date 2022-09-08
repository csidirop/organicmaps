FROM ubuntu:22.10

RUN apt-get update && apt-get install -y \
    && apt-get install -y \
        git \
        cmake \
        libboost-all-dev \
        qtbase5-dev \
        qtchooser \
        qt5-qmake \
        qtbase5-dev-tools \
        python3-pip \
        build-essential \
        clang \
        ninja-build \
        python3 \
        qtbase5-dev \
        libc++-dev \
        libfreetype-dev \
        libglu1-mesa-dev \
        libicu-dev \
        libqt5svg5-dev \
        libsqlite3-dev \
        zlib1g-dev

WORKDIR /organicmaps

RUN git submodule update --init --recursive
RUN ./configure.sh
RUN tools/unix/build_omim.sh -rs generator_tool world_roads_builder_tool

WORKDIR /organicmaps/tools/python/maps_generator

RUN pip3 install -r requirements_dev.txt
RUN cp var/etc/map_generator.ini.default var/etc/map_generator.ini


ENTRYPOINT ["tail", "-f", "/dev/null"]