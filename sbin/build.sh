#!/bin/bash

cd ../docker
docker-compose run --rm build cmake ..
docker-compose run --rm build make