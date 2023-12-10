#set -x

if [ "$1" == "" ]; then
    echo 'usage: ./tools/release <version>'
    exit
fi

echo "building project"
cd build
cmake ..
make
make package
cd ..

RELEASE_PATH="dist/sism-$1"

DEB_PACKAGE_NAME="sism-$1-1_amd64"
RPM_PACKAGE_NAME="sism-$1-1.fc39.x86_64"

echo "preparing release structure"
rm -rf "$RELEASE_PATH" 

mkdir dist
mkdir "$RELEASE_PATH"
mkdir "$RELEASE_PATH/scripts"
mkdir "dist/$DEB_PACKAGE_NAME"

echo "copying build artifacts"
cp build/sism "$RELEASE_PATH"
cp tools/dependencies-fedora.sh "$RELEASE_PATH/scripts"
cp tools/dependencies-ubuntu.sh "$RELEASE_PATH/scripts"
cp tools/install.sh "$RELEASE_PATH"
cp assets/sism.svg "$RELEASE_PATH"
cp assets/sism.desktop "$RELEASE_PATH"

echo "preparing DEB build"
rm -rf mkdir "dist/$DEB_PACKAGE_NAME"
mkdir -p "dist/$DEB_PACKAGE_NAME/bin"
mkdir -p "dist/$DEB_PACKAGE_NAME/DEBIAN"
cat tools/control | sed "s/<<version>>/$1-1/" > dist/$DEB_PACKAGE_NAME/DEBIAN/control
cp build/sism "dist/$DEB_PACKAGE_NAME/bin"

echo "preparing RPM build"
rm -rf "build/sism-$1"
mkdir -p "build/sism-$1"
cp "$RELEASE_PATH/sism" "build/sism-$1/"
cp assets/sism.desktop "build/sism-$1/"
cp assets/sism.svg "build/sism-$1/"
cd build
tar --create --file "sism-$1.tar.gz" "sism-$1"
cd ..
rm -rf build/rpmbuild
mkdir -p build/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
cat assets/sism.spec | sed "s/<<version>>/$1/" > "build/rpmbuild/SPECS/sism.spec"
cp "build/sism-$1.tar.gz" build/rpmbuild/SOURCES/

cd dist
echo "zipping binary files"
zip -r "sism-$1.zip" "sism-$1" 

echo "building DEB package"
dpkg-deb --root-owner-group --build "$DEB_PACKAGE_NAME"

echo "building RPM package"
cd ../build/rpmbuild
rpmbuild --define "_topdir `pwd`" -bb ./SPECS/sism.spec
cd ../..
cp "build/rpmbuild/RPMS/x86_64/$RPM_PACKAGE_NAME.rpm" dist/

echo "Release packaged successfully!"
echo "Executable: $RELEASE_PATH.zip"
echo "RPM Package: dist/$RPM_PACKAGE_NAME.rpm"
echo "DEB Package: dist/$DEB_PACKAGE_NAME.deb"