#!/bin/bash

if [ $1 = "-l" ]; then
    docker build -t make_rigel -f Dockerfile.lightweight .
else
    docker build -t make_rigel -f Dockerfile .
fi