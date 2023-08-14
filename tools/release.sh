cd build
cmake ..
make
cd ..

RELEASE_PATH="dist/sism-$1"

rm -rf "$RELEASE_PATH" 

mkdir dist
mkdir "$RELEASE_PATH"
mkdir "$RELEASE_PATH/scripts"

cp build/sism "$RELEASE_PATH"
cp tools/dependencies-fedora.sh "$RELEASE_PATH/scripts"
cp tools/dependencies-ubuntu.sh "$RELEASE_PATH/scripts"
cp tools/install.sh "$RELEASE_PATH"

cd dist
zip -r "sism-$1.zip" "sism-$1" 