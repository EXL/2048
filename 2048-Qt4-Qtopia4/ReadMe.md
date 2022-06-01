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

## USB passthrough from host to Qtopia 4 real device and connect feed repository

```sh
sudo iptables -t nat -A POSTROUTING -o wls1 -j MASQUERADE
echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward

sudo ip a add 192.168.10.1/255.255.255.0 dev usb0
```

Go to "Setting" => "Software Packages" => "Downloads" => "Options" => "Edit servers" => "Options" => "New":

```
Name: Local Server
URL: http://192.168.10.1:8000
```

Then push "Back", connect phone via USB and push "Options" on the "Downloads" tab then choose "Connect" => "Local Server".

## Transfer files from/to Qtopia 4 real device and shell

```sh
ssh -c aes128-cbc -oHostKeyAlgorithms=+ssh-dss -oKexAlgorithms=+diffie-hellman-group1-sha1 root@192.168.10.6
scp -c aes128-cbc -oHostKeyAlgorithms=+ssh-dss -oKexAlgorithms=+diffie-hellman-group1-sha1 archive.tar root@192.168.10.6:
scp -c aes128-cbc -oHostKeyAlgorithms=+ssh-dss -oKexAlgorithms=+diffie-hellman-group1-sha1 root@192.168.10.6:archive.tar .
sftp -c aes128-cbc -oHostKeyAlgorithms=+ssh-dss -oKexAlgorithms=+diffie-hellman-group1-sha1 root@192.168.10.6
dir, put, get
login:pass root:root
```

## Transfer files from/to Qtopia 4 virtual machine

```sh
scp -oHostKeyAlgorithms=+ssh-rsa -P 2222 archive.tgz user@localhost:
scp -oHostKeyAlgorithms=+ssh-rsa -P 2222 user@localhost:archive.tgz .
login:pass root:root
login:pass user:user
```
