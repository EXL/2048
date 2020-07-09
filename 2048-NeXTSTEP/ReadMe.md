2048-NeXTSTEP
=============

![2048-NeXTSTEP NeXTSTEP Screenshot](../image/2048-NeXTSTEP.png)

## Developer Tools

Install Developer Tools Packages from **NeXTSTEP_3.3_Developer.iso** CD:

1. NextCD/Packages/DeveloperTools.pkg
2. NextCD/Packages/DeveloperLibs.pkg
3. NextCD/Packages/DeveloperDoc.pkg
4. NextCD/Packages/GNUSource.pkg (optional)

## Create MS-DOS Floppy Disk Image with Source Code

Host CentOS 7 Packing Recipe:

```sh
sudo yum -y install @development

cd ~/Projects/
git clone https://github.com/EXL/2048
cd 2048/
tar -cvf 2048.tar 2048-NeXTSTEP/ src/ image/icon/icon48.tiff image/icon/icon150.tiff image/avatar.tiff

mkfs.msdos -C floppy.img 1440 -n "SRC"
sudo mount floppy.img /mnt/
sudo mv 2048.tar /mnt/ # Omit error TODO
sudo umount /mnt/
```

Now insert **floppy.img** to your emulator or virtual machine.

Guest NeXTSTEP Unpacking Recipe:

Choose *Workspace => Disk => Check for Disks* and open Terminal application from "NextApps/Terminal.app":

```sh
mkdir Projects/
cd Projects/
cp /src/2048.gz .
gzip -d 2048.gz
mv 2048 2048.tar
tar -xvf 2048.tar
rm pax_global_header 2048.tar
```

## Building via Project Builder

## Building via Makefile

## Run

## Create Package

## NeXTSTEP Development Environment

Project Builder:

![Project Builder NeXTSTEP Screenshot](../image/ProjectBuilder-NeXTSTEP-Screenshot.png)

Interface Builder:

![Interface Builder NeXTSTEP Screenshot](../image/InterfaceBuilder-NeXTSTEP-Screenshot.png)
