#!/bin/bash

WORKDIR=$(pwd)

DIR_DIST_TARGET=${WORKDIR}/dist-target
DIR_DIST_SIMULATOR=${WORKDIR}/dist-simulator

if [ ! -f "${WORKDIR}/compile_commands.json" ]; then
    echo "can't find compile_commands.json"
    mkdir -p "${WORKDIR}/tmp" && pushd "${WORKDIR}/tmp"
    cmake -DCROSS_COMPILE=1 .. && bear -- make -j
    cp compile_commands.json "${WORKDIR}/"
    popd
    rm -rf tmp/
else
    echo "compile_commands.json exists"
fi

mkdir -p "${DIR_DIST_TARGET}" && cd "${DIR_DIST_TARGET}"

cmake -DCROSS_COMPILE=1 -G Ninja  .. && ninja

cd ${WORKDIR}

ln -sf "${DIR_DIST_TARGET}/demo" ./demo

mkdir -p "${DIR_DIST_SIMULATOR}" && cd "${DIR_DIST_SIMULATOR}"

cmake .. -G Ninja && ninja

cd ${WORKDIR}

ln -sf "${DIR_DIST_SIMULATOR}/demo" ./simulator