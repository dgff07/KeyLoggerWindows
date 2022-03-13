# Keylogger for windows

Simple keylogger for windows to capture the keystrokes and also take a screenshot from the target.

## Building steps 

```
gcc -Wall -O2  -c main.c -o Release\main.o

gcc  -o  Release\KeyloggerWindows.exe Release\main.o -lgdi32
```
If you use vscode, this is already configured on `launch.json` and `tasks.json`
