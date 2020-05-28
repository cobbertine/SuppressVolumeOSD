#include "Main.h"

int main(int argc, char *argv)
{
    HWND osdWindowHandle = getOsdWindowHandle();

    if(osdWindowHandle == NULL)
    {
        printf("%s", "Failed to get Volume OSD Window Handle.\n");
        return askUserToQuit(1);
    }

    DWORD processId = 0;
    DWORD threadId =  GetWindowThreadProcessId(osdWindowHandle, &processId);
    HMODULE dllHandle = LoadLibraryA("OSDThreadHook.dll");
    HOOKPROC procPointer = (HOOKPROC)GetProcAddress(dllHandle, "suppressVolumeMessage");
    HHOOK hookHandle = SetWindowsHookExA(WH_GETMESSAGE, procPointer, dllHandle, threadId);

    if(hookHandle == NULL)
    {
        printf("%s", "Failed to hook into thread.\n");
        return askUserToQuit(1);
    }

    shakeVolume(); // Forces module to be loaded; the DLL is not actually loaded until a relevant message occurs.

    printf("%s", "Success! Program is suppressing volume OSD messages. Quitting will stop suppression.\n");
    askUserToQuit(0);

    WINBOOL isUnhooked = UnhookWindowsHookEx(hookHandle);
    WINBOOL isDLLFree = FreeLibrary(dllHandle);

    printf("Unhook %s\n", isUnhooked == FALSE ? "failed." : "succeeded.");
    printf("DLL unload %s\n", isDLLFree == FALSE ? "failed." : "succeeded.");

    Sleep(1000);

    return 0;
}

int askUserToQuit(int statusCode)
{
    printf("%s","Press enter to quit: ");
    unsigned char *input = getInput();
    free(input);
    printf("%s", "User has quit.\n");
    Sleep(1000);
    return statusCode;
}

unsigned char* getInput()
{
    unsigned char *buff = (unsigned char*)calloc(MAX_INPUT_BUFFER_SIZE + 1, sizeof(unsigned char));
    int count = 0;

    while(TRUE) 
    {
        int receivedChar = getchar();

        if(receivedChar != EOF && receivedChar != '\n')
        {
            if(count < MAX_INPUT_BUFFER_SIZE)
            {
                buff[count] = receivedChar;
                count++;
            }
        }
        else
        {
            return buff;
        }
    }
}

INPUT createValidKeystroke(WORD vKey)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki = (KEYBDINPUT){vKey,0,0,0,0};
    return input;
}

void shakeVolume()
{
    INPUT volUp = createValidKeystroke(VK_VOLUME_UP);
    INPUT volDown = createValidKeystroke(VK_VOLUME_DOWN);
    INPUT inputs[] = {volUp,volDown};
    SendInput(2, inputs, sizeof(INPUT));
}

HWND getOsdWindowHandle()
{
    shakeVolume(); // The OSD window may not always exist (For example, it does not exist on Windows startup) but changing the volume will create it if needed.
    Sleep(1000);

    HWND osdWindowHandle = FindWindowExA(NULL, NULL, OSD_WINDOW_CLASS, NULL);

    if(FindWindowExA(NULL, osdWindowHandle, OSD_WINDOW_CLASS, NULL) != NULL)  // Make sure there are no sibling NativeHWNDHosts
    {
        printf("%s","Multiple windows found; unable to determine correct volume OSD window.\n");
        return NULL;
    }   

    if(FindWindowExA(osdWindowHandle, NULL, OSD_WINDOW_CLASS, NULL) != NULL) // Make sure there are no child NativeHWNDHosts 
    {
        printf("%s","Multiple windows found; unable to determine correct volume OSD window.\n");
        return NULL;
    }

    return osdWindowHandle;
}