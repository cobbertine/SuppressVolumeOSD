#include "OSDThreadHook.h"

DllExport LRESULT CALLBACK suppressVolumeMessage(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    MSG *msg = (MSG*)lParam;

    if(msg->message == SMSG_VOL_CHANGE_ID && msg->wParam == SMSG_VOL_CHANGE_WPARAM && SMSG_VOL_CHANGE_LPARAM_ALL((msg->lParam & SMSG_VOL_CHANGE_LPARAM_MASK)))
    {
        msg->message = WM_NULL;
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}