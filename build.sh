#!/bin/bash

WORKDIR=$(pwd)

DIR_DIST_TARGET=${WORKDIR}/dist-target
DIR_DIST_SIMULATOR=${WORKDIR}/dist-simulator

mkdir -p "${DIR_DIST_TARGET}" && cd "${DIR_DIST_TARGET}"

cmake -DCROSS_COMPILE=1 .. && make -j

cd ${WORKDIR}

ln -sf "${DIR_DIST_TARGET}/demo" ./demo

mkdir -p "${DIR_DIST_SIMULATOR}" && cd "${DIR_DIST_SIMULATOR}"

cmake .. && make -j

cd ${WORKDIR}

ln -sf "${DIR_DIST_SIMULATOR}/demo" ./simulator