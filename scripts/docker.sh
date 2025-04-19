#!/bin/bash

source ./init.sh

cd "$RPP_IMP_ROOT"

docker build -t rpp-imp .
docker run rpp-imp:latest