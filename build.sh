set -xe

CC="gcc"
SOURCES="main.c shader.c"
FLAGS="-Wall -Werror -pedantic"
LINKER="-Llib -lm -lglad -lglfw"

$CC $SOURCES $FLAGS $LINKER -o main 
