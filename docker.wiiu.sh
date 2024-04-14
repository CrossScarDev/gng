#!/bin/env bash
cp Dockerfile.wiiu Dockerfile
sed -i 's/{workdir}/`pwd`/g' Dockerfile
docker build -t wiiu-builder
docker run -it --rm -v ${PWD}:`pwd` wiiu-builder
rm -rf Dockerfile
