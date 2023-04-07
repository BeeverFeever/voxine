#!/bin/sh
set -xe

CC="gcc"
SOURCES=$(find . -name *.c)
CFLAGS="-Wall"
LD_FLAGS="-Lsrc/voxine/thirdparty/lib -lglfw3 -lglad -lm"
INCLUDES="-Isrc"
OUT_DIR="."

$CC $SOURCES $CFLAGS -o $OUT_DIR/main $INCLUDES $LD_FLAGS 
