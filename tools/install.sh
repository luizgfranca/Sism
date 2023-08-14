set -x
set -v

OS_RELEASE=$(awk -F= '/^NAME/{print $2}' /etc/os-release)

if [ "$OS_RELEASE" == '"Fedora Linux"' ]; then
    ./scripts/dependencies-fedora.sh
    cp ./sism "$HOME/.local/bin/"
fi

if [ "$OS_RELEASE" == '"Ubuntu Linux"' ]; then
    ./scripts/dependencies-fedora.sh
    cp ./sism "$HOME/.local/bin/"
fi

echo "Done!"