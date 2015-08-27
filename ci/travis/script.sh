#!/usr/bin/env sh

set -e

cd travis-build

if [ "$TRAVIS_OS_NAME" = "linux" ]; then
    ninja
elif [ "$TRAVIS_OS_NAME" = "osx" ]; then
    cat "freespace2/fixup_bundle.cmake"
    cat "freespace2/fixup_bundle-$CONFIGURATION.cmake"
    
    xctool ARCHS=$MACOSX_ARCH ONLY_ACTIVE_ARCH=NO -configuration "$CONFIGURATION" -project FS2_Open.xcodeproj -scheme ALL_BUILD build
fi
