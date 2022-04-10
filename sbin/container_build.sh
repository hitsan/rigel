#!/bin/bash

if [ ! -d /rigel/build ]; then
    mkdir /rigel/build
fi
cd ../build
cmake ..
make