

if [ "$1" == "" ]; then
    echo 'usage: ./tools/release <version>'
    exit
fi

cd build
cmake ..
make
make package
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
cp "build/sism-$1-1.x86_64.rpm" "dist/"

cd dist
zip -r "sism-$1.zip" "sism-$1" 

echo "Release packaged successfully!"
echo "Executable: $RELEASE_PATH.zip"
echo "RPM Package: dist/sism-$1-1.x86_64.rpm"