# QtCpuInfo

A small Qt application (QtQuick, QML and c++) which:
- reads the std output of "cat /proc/cpuinfo" (Linux) or "sysctl -a | grep machdep.cpu" (Mac OS),
- process the std output data into custom data container for the data model,
- display the data model as TreeView UI (based on ListView),
- and optionally, automatic refresh the CPU MHz information (supported only in Linux)

Pre-requirements:
- Linux system 32 or 64 bit e.g. Ubuntu
- Qt >= 5.4

Steps using QtCreator IDE:
- Open project -> select QtCpuInfo.pro file
- Compile and run application
