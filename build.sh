#! /bin/bash

gcc -O3 -DHAVE_ATTRIBUTE_TARGET_AVX512_SKX_WITH_INTRINSICS -march=icelake-client test.c -o test -lm 
