CC="gcc"
SOURCES=$(find . -name '*.c')
CFLAGS="-Wall -g"
LD_FLAGS="-Lsrc/voxine/thirdparty/lib -lglfw3 -lglad -lm"
INCLUDES="-Isrc"
OUT_DIR="."

set -xe

$CC $SOURCES $CFLAGS $INCLUDES $LD_FLAGS -o $OUT_DIR/main
