2048-EZX
========

![2048-EZX Motorola E6 Screenshot 1](../image/2048-EZX-E6-Screenshot1.png) ![2048-EZX Motorola E6 Screenshot 2](../image/2048-EZX-E6-Screenshot2.png) ![2048-EZX Motorola E6 Screenshot 3](../image/2048-EZX-E6-Screenshot3.png) ![2048-EZX Motorola E6 Screenshot 4](../image/2048-EZX-E6-Screenshot4.png)

The "2048" game for the EZX OS by Motorola.

## Toolchain & SDK

Motorola A1200, E6, E2: // TODO: Add normal link mirrored to forum.motofan.ru

Motorola A780, E680: // TODO: Add normal link mirrored to forum.motofan.ru

Download MotoEZX Toolchains & SDK from [this link](http://www.mediafire.com/?meqnmgujgjq).

Download E680 Toolchains & SDK from [this link](https://code.google.com/archive/p/moto-e680-develop/downloads).

## Install Tools & Build

CentOS 7 General Prepare Recipe:

```sh
sudo yum -y install epel-release

sudo yum -y install @development
sudo yum -y install glibc.i686 libstdc++.i686
sudo yum -y install p7zip

cd ~/Projects/
git clone https://github.com/EXL/2048
```

Install MotoEZX Toolchains & SDK for A1200, E6, E2:

```sh
sudo mkdir -p /opt/toolchains/
sudo tar -C /opt/toolchains/ -xzvf ~/Downloads/motoezx-toolchains*.tar.gz*
```

Install MotoEZX Toolchains & SDK for A780, E680:

```sh
sudo mkdir -p /opt/toolchains/
sudo tar -C /opt/toolchains/ -xzvf ~/Downloads/motoe680-toolchains*.tar.gz*
sudo ln -s /opt/toolchains/motoe680 /usr/local/arm
```

Build for A1200, E6:

```sh
cd ~/Projects/2048/2048-EZX/
. /opt/toolchains/motoezx/setenv-a1200-devezx.sh
make clean
make
make mpkg
```

Build for E2:

```sh
cd ~/Projects/2048/2048-EZX/
. /opt/toolchains/motoezx/setenv-e2.sh
make -f Makefile.e2 clean
make -f Makefile.e2
make -f Makefile.e2 mpkg
```

Build for A780, E680:

```sh
cd ~/Projects/2048/2048-EZX/
. /opt/toolchains/motoe680/setenv-e680.sh
make -f Makefile.e680 clean
make -f Makefile.e680
make -f Makefile.e680 mpkg
```

## Copy executable file to A1200, E6, E2 and run it

FTP:

```sh
ftp 192.168.16.2
User: ezx
ftp> binary
ftp> cd /mmc/mmca1/
ftp> put 2048-EZX
ftp> quit
```

Telnet:

```sh
telnet 192.168.16.2
User: root
# cd /mmc/mmca1/
# . /home/native/.profile
# ./2048-EZX
```

## Create project file and Makefile

*Note.* This step is optional and is presented simply as an example of creating project and building files. This project contains ready-to-build generated Makefile and project files, so this section can be skipped.

Generate project and building files for A1200, E6:

```sh
cd ~/Projects/2048/2048-EZX/
mkdir -p 2048-EZX-E6-Project
cd 2048-EZX-E6-Project/
cp ../2048-EZX.cpp .
cp ../../src/2048.* .
. /opt/toolchains/motoezx/setenv-a1200-devezx.sh
progen CONFIG+=thread -o 2048-EZX_E6.pro
tmake 2048-EZX_E6.pro -o Makefile.e6
make -f Makefile.e6 clean
make -f Makefile.e6
```

Generate project and building files for E2:

```sh
cd ~/Projects/2048/2048-EZX/
mkdir -p 2048-EZX-E2-Project
cd 2048-EZX-E2-Project/
cp ../2048-EZX_E2.cpp .
cp ../../src/2048.* .
. /opt/toolchains/motoezx/setenv-e2.sh
progen CONFIG+=thread -o 2048-EZX_E2.pro
tmake 2048-EZX_E2.pro -o Makefile.e2
make -f Makefile.e2 clean
make -f Makefile.e2
```

Generate project and building files for A780, E680:

```sh
cd ~/Projects/2048/2048-EZX/
mkdir -p 2048-EZX-E680-Project
cd 2048-EZX-E680-Project/
cp ../2048-EZX.cpp .
cp ../../src/2048.* .
. /opt/toolchains/motoe680/setenv-e680.sh
progen CONFIG+=thread -o 2048-EZX_E680.pro
tmake 2048-EZX_E680.pro -o Makefile.e680
make -f Makefile.e680 clean
make -f Makefile.e680
```

## Additional Stuff

EZX OS screenshots from Motorola ROKR E6:

![EZX Motorola E6 Screenshot 1 Main Desktop Screen](../image/EZX-Screenshot1.png) ![EZX Motorola E6 Screenshot 2 Main Menu](../image/EZX-Screenshot2.png) ![EZX Motorola E6 Screenshot 3 SysInfo Ultimate Application](../image/EZX-Screenshot3.png) ![EZX Motorola E6 Screenshot 4 EKonsole Application](../image/EZX-Screenshot4.png)

2048-EZX running on Motorola ROKR E6:

![2048-EZX application running on Motorola E6 Photo](../image/2048-EZX-E6-Photo.jpg)

## Versions

Any Linux distro with support for running 32-bit x86 applications and tools.

Compiler for A1200, E6, E2:

```sh
arm-linux-gnu-gcc --version | head -1
arm-linux-gnu-gcc (GCC) 3.3.6

arm-linux-gnu-g++ --version | head -1
arm-linux-gnu-g++ (GCC) 3.3.6
```

Compiler for A780, E680:

```sh
arm-linux-gcc --version | head -1
arm-linux-gcc (GCC) 3.3

arm-linux-g++ --version | head -1
arm-linux-g++ (GCC) 3.3
```

Qt Embedded version 2.3.6/2.3.8

## Information

Additional information about porting in [NotesMotoEZX.md](../doc/NotesMotoEZX.md) document file.
