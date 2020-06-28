2048-Qt1
========

![2048-Qt1 Fedora 32 Screenshot](../image/2048-Qt1-Screenshot.png)

## Build & Run

CentOS 7 Recipe:

```sh
sudo yum -y install epel-release

sudo yum -y install @development
sudo yum -y install cmake3
sudo yum -y install byacc mesa-libGL-devel
sudo yum -y install xorg-x11-fonts-ISO8859-1-100dpi

cd ~/Projects/
git clone https://github.com/heliocastro/qt1
cd qt1/
cmake3 -DCMAKE_BUILD_TYPE=Release .
make VERBOSE=1

cd ~/Projects/
git clone https://github.com/EXL/2048
cd 2048/2048-Qt1/
cmake3 -DCMAKE_BUILD_TYPE=Release .
make VERBOSE=1
strip -s 2048-Qt1

./2048-Qt1
```
