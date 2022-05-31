2048-Qt4-Qtopia4
================

A simple implementation of the 2048 puzzle game for Qtopia 4 platform using Qt 4 framework.

## Build for x86 Qtopia 4 simulator

```sh
source /opt/Qtopia/SDK/scripts/devel-x86.sh
qtopiamake "CONFIG += release"
make clean
make
strip -s 2048-Qt4-Qtopia4
gph -p # Create QPK-package
gph -i # Install QPK-package
```

## Build for ARM Qtopia 4 device

```sh
source /opt/Qtopia/SDK/scripts/devel-greenphone.sh
qtopiamake "CONFIG += release"
make clean
make
arm-linux-strip -s 2048-Qt4-Qtopia4
gph -p # Create QPK-package
```

## Create QPK-packages and populate feed repository

```sh
cp pkg/* ~/Repository
cd ~/Repository
mkPackages
python3 -m http.server
```

## Transfer files from/to virtual machine

```sh
scp -oHostKeyAlgorithms=+ssh-rsa -P 2222 archive.tgz user@localhost:
scp -oHostKeyAlgorithms=+ssh-rsa -P 2222 user@localhost:archive.tgz .
login:pass root:root
login:pass user:user
```
