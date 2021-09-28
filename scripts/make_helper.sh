#!/bin/sh

SCRIPT_DIR=`dirname $0`
PREFIX_PATH=".."
BASE_PATH=`pwd`
BASE_DIR=`basename $BASE_PATH` 

echo $BASE_PATH

if [ $BASE_DIR != "$SCRIPT_DIR" ]; then
	PREFIX_PATH=`dirname $SCRIPT_DIR`
fi

BUILD_DIR=$PREFIX_PATH"/build";
BINARY_DIR=$PREFIX_PATH"/bin";
MAKEFILE_PATH=$PREFIX_PATH"/Makefile";

if [ $1 = "build" ]; then
	echo $1;
	if [ -d $BUILD_DIR ]; then
        	cd $BUILD_DIR;
        	if [ -f $MAKEFILE_PATH ]; then
                	make -j;
        	else
                	cmake ..;
                	make -j;
        	fi
	else
        	mkdir $BUILD_DIR;
        	cd $BUILD_DIR;
        	cmake ..;
        	make -j;
	fi
elif [ $1 = "clean" ]; then
	echo "$BINARY_DIR/*";
	rm -rf $BINARY_DIR/*;
	if [ -d $BUILD_DIR ]; then
		cd  $BUILD_DIR;
		echo `pwd`;
		make clean-headers;
		cd $BASE_PATH;
		echo `pwd`;
		rm -rf $BUILD_DIR;
	fi
elif [ $1 = "clean-headers" ]; then
	if [ -d $BUILD_DIR ]; then
		cd  $BUILD_DIR;
		echo `pwd`;
		make clean-headers;
		cd $BASE_PATH;
	fi
else
	exit 0;
fi
