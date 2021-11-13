#!/bin/sh

SCRIPT_DIR=`dirname $0`
PREFIX_PATH=".."
BASE_PATH=`pwd`
BASE_DIR=`basename $BASE_PATH` 


if [ "$BASE_DIR" != "$SCRIPT_DIR" ]; then
	PREFIX_PATH=`dirname $SCRIPT_DIR`
fi

EXTERN_DIR=$PREFIX_PATH"/extern"
cd $EXTERN_DIR/tmx-loader/
git submodule update --init