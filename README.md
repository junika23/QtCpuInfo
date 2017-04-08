# QtCpuInfo

A small Qt application (QtQuick, QML and c++) which:
- reads the std output of "cat /proc/cpuinfo" (Linux) or "sysctl -a | grep machdep.cpu" (Mac OS),
- process the std output data into custom data container for the data model,
- display the data model as TreeView UI (based on ListView),
- and optionally, automatic refresh the CPU MHz information (supported only in Linux)

Pre-requirements:
1) Linux system 32 or 64 bit e.g. Ubuntu
2) git 
How to install: 
e.g. Ubuntu via: 
```
sudo apt-get install git
```
3) Qt >= 5.4
How to install:
go to https://www.qt.io/ and download the installation file e.g. qt-unified-linux-x64-2.0.5-2-online.run.
Once downloaded, type:
```
chmod +x qt-unified-linux-x64-2.0.5-2-online.run 
```
and then run:
```
./qt-unified-linux-x64-2.0.5-2-online.run
```
install wherever and whatever you want e.g. Qt 5.8 Linux gcc and QtCreator tool.

How to build:
1) Get the repository cloned locally:
```
cd <some folder>
git checkout https://github.com/junika23/QtCpuInfo.git
```
2. Compile the codes
2.1. Using QtCreator IDE:
- Open project -> select QtCpuInfo.pro file
- Compile and run application

2.2 Using command line console:
- Create output folder
```
mkdir ../debug (or release)
```
- Go to the output folder
```
cd ../debug (or release)
```
- run qmake to the project or .pro file
```
qmake QtCpuInfo.pro
```
- run make
```
make
```
