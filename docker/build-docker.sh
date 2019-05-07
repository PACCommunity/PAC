#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-paccoinpay/paccoind-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/paccoind docker/bin/
cp $BUILD_DIR/src/paccoin-cli docker/bin/
cp $BUILD_DIR/src/paccoin-tx docker/bin/
strip docker/bin/paccoind
strip docker/bin/paccoin-cli
strip docker/bin/paccoin-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
