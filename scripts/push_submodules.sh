

SCRIPT_DIR=`dirname $0`
PREFIX_PATH=".."
BASE_PATH=`pwd`
BASE_DIR=`basename $BASE_PATH` 


if [ $BASE_DIR != "$SCRIPT_DIR" ]; then
	PREFIX_PATH=`dirname $SCRIPT_DIR`
fi

EXTERN_DIR=$PREFIX_PATH"/extern/tmx-loader";


cd $EXTERN_DIR
git checkout master
git commit -a -m "commit in submodule"
git push
cd $BASE_PATH
git add 
git commit -m "Updated submodule"