# SuppressVolumeOSD
Intercepts and removes certain Window Messages to prevent the Volume OSD from being rendered by Windows 10.

## Platform Support
Windows 10 x64 only. Tested on version 1909.

## How to use
* Download the binary and double click on it 
* You will be informed if it has successfully blocked the Window Messages related to the rendering of the Volume OSD
* The program will then prompt you to hit enter when you want the Volume OSD to return. 

The Volume OSD will only be hidden while the program is running; it is not permanent. In the off-chance that closing the program does not make the Volume OSD return, restart your computer or restart the explorer.exe process.

## Compiling
Binary file and DLL were compiled with gcc as follows:

```
// Binary
gcc -o SuppressVolumeOSD.exe Main.c
```

```
// DLL
gcc -shared -o OSDThreadHook.dll OSDThreadHook.c
```
