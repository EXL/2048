2048-Gtk2
=========

![2048-Gtk2 Fedora 32 Screenshot](../image/2048-Gtk2-Screenshot.png)

## Build & Run

CentOS 7 Recipe:

```sh
sudo yum -y install epel-release

sudo yum -y install @development
sudo yum -y install cmake3
sudo yum -y install gtk2-devel

cd ~/Projects
git clone https://github.com/EXL/2048
cd 2048/2048-Gtk2/
cmake3 -DCMAKE_BUILD_TYPE=Release .
make VERBOSE=1
strip -s 2048-Gtk2

./2048-Gtk2
```
