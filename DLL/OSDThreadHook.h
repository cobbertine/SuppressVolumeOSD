#ifndef KILLOSDTHREAD_H
#define KILLOSDTHREAD_H

// Values were discovered by attaching to explorer.exe with x64dbg and reading the MSG struct after a PeekMessage call in the 'windows.immersiveshell.serviceprovider.dll' module
#define SMSG_VOL_CHANGE_ID 0xC028
#define SMSG_VOL_CHANGE_WPARAM 0x0C
// LPARAM's Least Significant Byte may be 0x01 or 0x02 depending if the left or right mouse button is held down at the same time as the volume is being changed. e.g. 0x0A0002. This byte isn't useful in regards to identifying a relevant message, so I remove it (plus the byte inbetween) with the mask before calling the _ALL macro.
#define SMSG_VOL_CHANGE_LPARAM_VOL_MUTE 0x080000
#define SMSG_VOL_CHANGE_LPARAM_VOL_DOWN 0x090000
#define SMSG_VOL_CHANGE_LPARAM_VOL_UP 0x0A0000
#define SMSG_VOL_CHANGE_LPARAM_MASK 0xFF0000
#define SMSG_VOL_CHANGE_LPARAM_ALL(arg) (arg == SMSG_VOL_CHANGE_LPARAM_VOL_MUTE || arg == SMSG_VOL_CHANGE_LPARAM_VOL_DOWN || arg == SMSG_VOL_CHANGE_LPARAM_VOL_UP)

#define _WIN32_WINNT 0x0A00 // Win10 minimum compatibility.
#define DllExport   __declspec( dllexport )

#include <windows.h>
#include <stdio.h>

DllExport LRESULT CALLBACK suppressVolumeMessage(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

#endif