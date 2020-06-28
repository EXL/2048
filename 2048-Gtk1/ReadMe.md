2048-Gtk1
=========

![2048-Gtk1 Fedora 32 Screenshot](../images/2048-Gtk1-Screenshot.png)

## Build & Run

CentOS 7:

```sh
sudo yum -y localinstall --nogpgcheck https://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm https://download1.rpmfusion.org/nonfree/el/rpmfusion-nonfree-release-7.noarch.rpm # Install EPEL & RPM Fusion repositories.
sudo yum -y install @development # Install all development tools.
sudo yum -y install gtk1-devel # Install GTK+1 development environment.
sudo yum -y install xorg-x11-fonts-ISO8859-1-100dpi # Install X.Org fonts.

cd ~/Projects
git clone https://github.com/EXL/2048
cd 2048/2048-Gtk1/
cmake3 -DCMAKE_BUILD_TYPE=Release .
make VERBOSE=1
strip -s 2048-Gtk1

./2048-Gtk1
```
