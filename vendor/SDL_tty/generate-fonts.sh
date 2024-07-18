#!/bin/sh

FONTDUMP="./result/bin/sdltty-fontdump"
ASCII_CHARS=$'\x7f'" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\`abcdefghijklmnopqrstuvwxyz{|}~"

$FONTDUMP font8x8 data/font8x8.png 8 8 "$ASCII_CHARS" > src/font8x8.h

# EOF #
