#!/bin/bash

curPath=$(readlink -f "$(dirname "$0")")
cd $curPath

mkdir build
cd build
cmake .. \
	-DBABELTRADER_BUILD_SHARED_LIB=ON \
	-DBABELTRADER_BUILD_TESTING=ON \
	-DBABELTRADER_BUILD_EXAMPLE=ON \
	-DMUGGLE_BUILD_SHARED_LIB=OFF \
	-DMUGGLE_CPP_BUILD_SHARED_LIB=OFF \
	-Dgtest_force_shared_crt=ON \
	-DCMAKE_PREFIX_PATH=~/c_pkg \
	-DCMAKE_INSTALL_PREFIX=$curPath/build/pkg
