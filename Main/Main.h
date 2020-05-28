#ifndef MAIN_H
#define MAIN_H

#define _WIN32_WINNT 0x0A00 // Win10 minimum compatibility.
#define MAX_INPUT_BUFFER_SIZE 1

// Class name discovered by attaching to explorer.exe with x64dbg and reading the MSG struct after a PeekMessage call in the 'windows.immersiveshell.serviceprovider.dll' module
// The Target Handle in the MSG struct points to "NativeHWNDHost". WinSpy was used to determine the handle ID's class name.
#define OSD_WINDOW_CLASS "NativeHWNDHost"

#include <windows.h>
#include <stdio.h>
#include <ctype.h>

int askUserToQuit(int statusCode);
unsigned char *getInput();
INPUT createValidKeystroke(WORD vKey);
HWND getOsdWindowHandle();
void shakeVolume();

#endif