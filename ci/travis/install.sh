#!/usr/bin/env sh

set -e

FILENAME=
if [ "$TRAVIS_OS_NAME" = "linux" ]; then
    sudo apt-get install -y ninja-build
    sudo apt-get install libopenal-dev libogg-dev libvorbis-dev build-essential automake1.10 autoconf libsdl2-dev libtheora-dev libreadline6-dev libpng12-dev libjpeg62-dev liblua5.1-0-dev libjansson-dev libtool
    FILENAME=cmake-3.3.1-Linux-x86_64
elif [ "$TRAVIS_OS_NAME" = "osx" ]; then
    FILENAME=cmake-3.3.1-Darwin-universal
fi

mkdir -p $HOME/cmake/

wget -O /tmp/cmake.tar.gz http://www.cmake.org/files/v3.3/$FILENAME.tar.gz
tar -xzf /tmp/cmake.tar.gz -C $HOME/cmake/ --strip-components=1
