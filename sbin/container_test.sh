#!/bin/bash

cd ../build
if [ ! -d ./test_bin/ ]; then
    mkdir ./test_bin
fi
./test/test_rigel
if [ -d ./test_bin/ ]; then
    rm -r ./test_bin
fi