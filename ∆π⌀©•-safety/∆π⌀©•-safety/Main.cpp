#include <Windows.h>
#include <windowsx.h>
#include <math.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")

#pragma warning(disable: 4244 4305 4996 4018 4101 4700)

const wchar_t* globalTitleText = L"∆π⌀©•";

typedef LONG(WINAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef VOID(NTAPI* RSPICdef)(BOOLEAN, PBOOLEAN, BOOLEAN);

struct Point3D { float x, y, z; };
struct Point2D { int x, y; };

void RotateX(Point3D& p, float angle) {
    float y = p.y * cos(angle) - p.z * sin(angle);
    float z = p.y * sin(angle) + p.z * cos(angle);
    p.y = y; p.z = z;
}
void RotateY(Point3D& p, float angle) {
    float x = p.x * cos(angle) + p.z * sin(angle);
    float z = -p.x * sin(angle) + p.z * cos(angle);
    p.x = x; p.z = z;
}
void RotateZ(Point3D& p, float angle) {
    float x = p.x * cos(angle) - p.y * sin(angle);
    float y = p.x * sin(angle) + p.y * cos(angle);
    p.x = x; p.y = y;
}
void PlayA(int rate, char* b, int sz) {
    WAVEFORMATEX w = { WAVE_FORMAT_PCM, 1, (DWORD)rate, (DWORD)rate, 1, 8, 0 };
    HWAVEOUT h;
    if (waveOutOpen(&h, WAVE_MAPPER, &w, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
        WAVEHDR hd = { b, (DWORD)sz, 0, 0, 0, 0, NULL, 0 };
        waveOutPrepareHeader(h, &hd, sizeof(WAVEHDR));
        waveOutWrite(h, &hd, sizeof(WAVEHDR));
        Sleep(30000);
        waveOutReset(h);
        waveOutUnprepareHeader(h, &hd, sizeof(WAVEHDR));
        waveOutClose(h);
    }
}
DWORD WINAPI Sound1(LPVOID p) {
    char* b = new char[960000];
    for (int t = 0; t < 960000; ++t) b[t] = (char)(128 * sin((double)(t ^ t % 1001 + t ^ t % 1002)) + 128);
    PlayA(32000, b, 960000); delete[] b; return 0;
}
DWORD WINAPI Sound2(LPVOID p) {
    char* b = new char[480000];
    for (int t = 0; t < 480000; ++t) { int div = 1 + ((t >> 9) & (t >> 8)); b[t] = (div != 0 && t != 0) ? (char)((t * t / div) / t) : 0; }
    PlayA(16000, b, 480000); delete[] b; return 0;
}
DWORD WINAPI Sound3(LPVOID p) {
    char* b = new char[240000];
    for (int t = 0; t < 240000; ++t) b[t] = (char)(0x1124466889 & t + t >> 5 + t << 1);
    PlayA(8000, b, 240000); delete[] b; return 0;
}
DWORD WINAPI Sound4(LPVOID p) {
    char* b = new char[1323000];
    for (int t = 0; t < 1323000; ++t) b[t] = (char)(0x0987654321 * t >> 1 | t << 5 | t >> 6 | t >> 1 | t % 6 << 2);
    PlayA(44100, b, 1323000); delete[] b; return 0;
}
DWORD WINAPI Sound5(LPVOID p) {
    char* b = new char[330750];
    for (int t = 0; t < 330750; ++t) b[t] = (char)((0xDEAD + t << 1 | t >> 3 | t >> 9) + (4));
    PlayA(11025, b, 330750); delete[] b; return 0;
}
DWORD WINAPI Sound6(LPVOID p) {
    char* b = new char[240000];
    for (int t = 0; t < 240000; ++t) b[t] = (char)(10 * (t & 5 * t | t >> 6 | (t & 32768 ? -6 * t / 7 : (t & 65536 ? -9 * t & 100 : -9 * (t & 100)) / 11)));
    PlayA(8000, b, 240000); delete[] b; return 0;
}
DWORD WINAPI Sound7(LPVOID p) {
    char* b = new char[1323000];
    for (int t = 0; t < 1323000; ++t) { int sh = (t & (t >> 12)) - ((t / 1024) % 4 - 3); b[t] = (char)(((t >> sh) & 0x7F) + (8000.0 * (0.0 - (1.0 - (t % 16384) / 10000.0)) / 69.0)); }
    PlayA(44100, b, 1323000); delete[] b; return 0;
}
DWORD WINAPI Sound8(LPVOID p) {
    char* b = new char[661500];
    for (int t = 0; t < 661500; ++t) b[t] = (char)((0x666 + t >> 1 | t << 6 | t >> 9 | t >> 3) * (t >> 1 | t >> 9 | t >> 6 | t >> 2 | t >> 1 | t << 6));
    PlayA(22050, b, 661500); delete[] b; return 0;
}
DWORD WINAPI Sound9(LPVOID p) {
    char* b = new char[330750];
    for (int t = 0; t < 330750; ++t) { int md = t % 4096; b[t] = (char)((100 * ((t << 1 | t >> 5 | t ^ 63) & (t >> 9 | t >> 10))) | (md != 0 ? (40000 / md) : 40000)); }
    PlayA(11025, b, 330750); delete[] b; return 0;
}
DWORD WINAPI Sound10(LPVOID p) {
    char* b = new char[661500];
    for (int t = 0; t < 661500; ++t) b[t] = (char)((t & t >> 12) * (t));
    PlayA(22050, b, 661500); delete[] b; return 0;
}
DWORD WINAPI Sound11(LPVOID p) {
    char* b = new char[240000];
    for (int t = 0; t < 240000; ++t) b[t] = (char)((~t >> 2) * ((127 & t * (7 & t >> 10)) < (245 & t * (2 + (5 & t >> 14)))));
    PlayA(8000, b, 240000); delete[] b; return 0;
}
DWORD WINAPI Sound12(LPVOID p) {
    char* b = new char[240000];
    for (int t = 0; t < 240000; ++t) { unsigned int sh = (t >> 9) & 0x1E; b[t] = (char)(((t * ((0xCA9F8CD8 >> sh) & 0xF))) | (t >> 2)); }
    PlayA(8000, b, 240000); delete[] b; return 0;
}
DWORD WINAPI Payload1(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmi = { { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (!hdc) continue;
        HDC hdcMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hdcMem, hbm); BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        RGBQUAD* px = new RGBQUAD[w * h]; GetDIBits(hdcMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS);
        for (int i = 0; i < w * h; i++) { int g = (px[i].rgbRed + px[i].rgbGreen + px[i].rgbBlue) / 3; px[i].rgbRed = g; px[i].rgbGreen = g; px[i].rgbBlue = g; }
        SetDIBits(hdcMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS); delete[] px;
        BitBlt(hdc, 0, -5, w, h, hdcMem, 0, 0, SRCCOPY); BitBlt(hdc, 0, h - 5, w, 5, hdcMem, 0, 0, SRCCOPY);
        DeleteObject(hbm); DeleteDC(hdcMem); ReleaseDC(NULL, hdc); Sleep(10);
    }
}
DWORD WINAPI Payload2(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), o = 0;
    BITMAPINFO bmi = { { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (!hdc) continue;
        HDC hdcMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hdcMem, hbm); BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        RGBQUAD* px = new RGBQUAD[w * h]; GetDIBits(hdcMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int i = y * w + x, s = (x + y + o) % 3;
                if (s == 0) px[i].rgbRed = (px[i].rgbRed + 5) % 256;
                else if (s == 1) px[i].rgbGreen = (px[i].rgbGreen + 5) % 256;
                else px[i].rgbBlue = (px[i].rgbBlue + 5) % 256;
            }
        }
        o += 5; SetDIBits(hdcMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS); delete[] px;
        BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY); DeleteObject(hbm); DeleteDC(hdcMem); ReleaseDC(NULL, hdc); Sleep(20);
    }
}
DWORD WINAPI Payload3(LPVOID p) {
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN); float a = 0.0f;
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (!hdc) continue;
        int x = rand() % sw, y = rand() % sh, w = rand() % 200 + 50, h = rand() % 200 + 50, o = rand() % 30 - 15;
        if (rand() % 2 == 0) BitBlt(hdc, 0, y + o, sw, h, hdc, 0, y, SRCCOPY); else BitBlt(hdc, x + o, 0, w, sh, hdc, x, 0, SRCCOPY);
        HDC mDC = CreateCompatibleDC(hdc); HBITMAP mBM = CreateCompatibleBitmap(hdc, sw, sh); SelectObject(mDC, mBM);
        BitBlt(mDC, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY); XFORM xf; a += 0.05f; float c = cos(a), s = sin(a);
        xf.eM11 = c; xf.eM12 = s; xf.eM21 = -s; xf.eM22 = c;
        xf.eDx = (float)(sw / 2) - (c * (sw / 2) - s * (sh / 2)); xf.eDy = (float)(sh / 2) - (s * (sw / 2) + c * (sh / 2));
        SetGraphicsMode(hdc, GM_ADVANCED); SetWorldTransform(hdc, &xf); BitBlt(hdc, 0, 0, sw, sh, mDC, 0, 0, SRCCOPY);
        ModifyWorldTransform(hdc, NULL, MWT_IDENTITY); DeleteObject(mBM); DeleteDC(mDC); ReleaseDC(NULL, hdc); Sleep(30);
    }
}
DWORD WINAPI Payload4(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), i = 0;
    BITMAPINFO bmi = { { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            HDC hdcMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h); SelectObject(hdcMem, hbm);
            BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); RGBQUAD* px = new RGBQUAD[w * h]; GetDIBits(hdcMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS);
            for (int y = 0; y < h; y++) { for (int x = 0; x < w; x++) { int idx = y * w + x; px[idx].rgbRed = 0; px[idx].rgbGreen = (x + i) ^ (y + i) % 256; px[idx].rgbBlue = 0; } }
            i += 8; SetDIBits(hdcMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS); delete[] px;
            BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY); DeleteObject(hbm); DeleteDC(hdcMem); ReleaseDC(NULL, hdc);
        }
        Sleep(10);
    }
}
DWORD WINAPI Payload5(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), bx = rand() % (w - 100), by = rand() % (h - 100), br = 50, sx = 8, sy = 8, hu = 0;
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            HBRUSH brush = CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225)); SelectObject(hdc, brush); PatBlt(hdc, 0, 0, w, h, PATINVERT);
            BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCCOPY); DeleteObject(brush); bx += sx; by += sy;
            if (bx <= 0 || bx + (br * 2) >= w) sx = -sx; if (by <= 0 || by + (br * 2) >= h) sy = -sy;
            hu = (hu + 5) % 360; HBRUSH bBrush = CreateSolidBrush(RGB((int)(127 + 127 * sin(hu * 0.0174)), (int)(127 + 127 * sin((hu + 120) * 0.0174)), (int)(127 + 127 * sin((hu + 240) * 0.0174))));
            SelectObject(hdc, bBrush); HPEN nPen = CreatePen(PS_NULL, 0, 0); SelectObject(hdc, nPen); Ellipse(hdc, bx, by, bx + (br * 2), by + (br * 2));
            DeleteObject(bBrush); DeleteObject(nPen); ReleaseDC(NULL, hdc);
        }
        Sleep(10);
    }
}
DWORD WINAPI Payload6(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            int tw = rand() % w + 50, th = rand() % h + 50; HDC hdcMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
            SelectObject(hdcMem, hbm); BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); RECT rc = { 0, 0, w, h };
            FillRect(hdc, &rc, bBrush); DeleteObject(bBrush); StretchBlt(hdc, 0, 0, tw, th, hdcMem, 0, 0, w, h, SRCCOPY);
            if (rand() % 5 == 0) { int ix = rand() % w, iy = rand() % h; int it = rand() % 4; HICON hi = LoadIcon(NULL, it == 0 ? IDI_ERROR : (it == 1 ? IDI_WARNING : (it == 2 ? IDI_INFORMATION : IDI_QUESTION))); if (hi) DrawIcon(hdc, ix, iy, hi); }
            DeleteObject(hbm); DeleteDC(hdcMem); ReleaseDC(NULL, hdc);
        }
        Sleep(50);
    }
}
DWORD WINAPI Payload7(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY); BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
            int size = rand() % 150 + 50; int x = rand() % (w - size), y = rand() % (h - size); BitBlt(hdc, x, y, size, size, hdc, x, y, SRCINVERT); ReleaseDC(NULL, hdc);
        }
        Sleep(10);
    }
}
DWORD WINAPI Payload8(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN); BITMAPINFO bmi = { { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            HDC hMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h); SelectObject(hMem, hbm); StretchBlt(hMem, -2, -2, w + 4, h + 4, hdc, 0, 0, w, h, SRCCOPY);
            RGBQUAD* px = new RGBQUAD[w * h]; GetDIBits(hMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS); RGBQUAD* bl = new RGBQUAD[w * h]; memcpy(bl, px, w * h * sizeof(RGBQUAD));
            for (int y = 1; y < h - 1; y++) {
                for (int x = 1; x < w - 1; x++) {
                    int idx = y * w + x, r = 0, g = 0, b = 0;
                    for (int ky = -1; ky <= 1; ky++) { for (int kx = -1; kx <= 1; kx++) { int k = (y + ky) * w + (x + kx); r += px[k].rgbRed; g += px[k].rgbGreen; b += px[k].rgbBlue; } }
                    bl[idx].rgbRed = r / 9; bl[idx].rgbGreen = g / 9; bl[idx].rgbBlue = b / 9;
                }
            }
            SetDIBits(hMem, hbm, 0, h, bl, &bmi, DIB_RGB_COLORS); delete[] px; delete[] bl; BitBlt(hdc, 0, 0, w, h, hMem, 0, 0, SRCCOPY); DeleteObject(hbm); DeleteDC(hMem); ReleaseDC(NULL, hdc);
        }
        Sleep(30);
    }
}
DWORD WINAPI Payload9(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), step = 0; BITMAPINFO bmi = { { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            HDC hMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h); SelectObject(hMem, hbm); BitBlt(hMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            RGBQUAD* px = new RGBQUAD[w * h]; GetDIBits(hMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS);
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int i = y * w + x; double f = (double)step / 500.0; if (f > 1.0) f = 1.0; double a = (double)(x + y + step) * 0.02;
                    int r = (int)(127 + 127 * sin(a)), g = (int)(127 + 127 * sin(a + 2.09439)), b = (int)(127 + 127 * sin(a + 4.18879));
                    px[i].rgbRed = (px[i].rgbRed + (int)((1.0 - f) * 255.0 + f * r)) / 2; px[i].rgbGreen = (px[i].rgbGreen + (int)(f * g)) / 2; px[i].rgbBlue = (px[i].rgbBlue + (int)(f * b)) / 2;
                }
            }
            step += 2; SetDIBits(hMem, hbm, 0, h, px, &bmi, DIB_RGB_COLORS); delete[] px; BitBlt(hdc, 0, 0, w, h, hMem, 0, 0, SRCCOPY); DeleteObject(hbm); DeleteDC(hMem); ReleaseDC(NULL, hdc);
        }
        Sleep(20);
    }
}
DWORD WINAPI Payload10(LPVOID p) {
    HDC hdcSc = GetDC(0); HDC hMem = CreateCompatibleDC(hdcSc); int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { { sizeof(BITMAPINFO), w, h, 1, 32, 0, 0, 0, 0, 0, 0 } };
    typedef union { COLORREF rgb; struct { BYTE r; BYTE g; BYTE b; BYTE rs; }; } *PRGB; PRGB rgbSc = { 0 };
    HBITMAP hbm = CreateDIBSection(hdcSc, &bmi, NULL, (void**)&rgbSc, NULL, NULL); SelectObject(hMem, hbm);
    while (TRUE) { hdcSc = GetDC(0); BitBlt(hMem, 0, 0, w, h, hdcSc, 0, 0, SRCCOPY); for (int i = 0; i < w * h; i++) { int x = i % w, y = i / w; rgbSc[i].rgb += (x ^ y); } BitBlt(hdcSc, 0, 0, w, h, hMem, 0, 0, SRCCOPY); ReleaseDC(NULL, hdcSc); Sleep(10); }
}
DWORD WINAPI Payload11(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), bx = rand() % (w - 150) + 75, by = rand() % (h - 150) + 75, sx = 6, sy = 6, sz = 40;
    Point3D vt[8] = { {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1}, {-1,-1,1}, {1,-1,1}, {1,1,1}, {-1,1,1} };
    int eg[12][2] = { {0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7} };
    float ax = 0.0f, ay = 0.0f, az = 0.0f; DWORD lTime = GetTickCount(); const wchar_t* libs[4] = { L"moricons.dll", L"shell32.dll", L"user32.dll", L"imageres.dll" };
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            bx += sx; by += sy; if (bx - sz <= 0 || bx + sz >= w) sx = -sx; if (by - sz <= 0 || by + sz >= h) sy = -sy; SetCursorPos(bx, by); ax += 0.03f; ay += 0.02f; az += 0.01f; Point2D pr[8];
            for (int i = 0; i < 8; i++) { Point3D pt = vt[i]; RotateX(pt, ax); RotateY(pt, ay); RotateZ(pt, az); pr[i].x = bx + (int)(pt.x * 60.0f / (pt.z + 2.5f)); pr[i].y = by + (int)(pt.y * 60.0f / (pt.z + 2.5f)); }
            HPEN pen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256)); SelectObject(hdc, pen);
            for (int i = 0; i < 12; i++) { MoveToEx(hdc, pr[eg[i][0]].x, pr[eg[i][0]].y, NULL); LineTo(hdc, pr[eg[i][1]].x, pr[eg[i][1]].y); }
            DeleteObject(pen); if (GetTickCount() - lTime >= 500) { HICON hi = ExtractIconW(GetModuleHandle(NULL), libs[rand() % 4], rand() % 50); if (hi && hi != (HICON)1) { DrawIcon(hdc, rand() % w, rand() % h, hi); DestroyIcon(hi); } lTime = GetTickCount(); }
            ReleaseDC(NULL, hdc);
        }
        Sleep(16);
    }
}
DWORD WINAPI Payload12(LPVOID p) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), bx = rand() % (w - 200) + 100, by = rand() % (h - 200) + 100, br = 60, sx = 7, sy = 7, hu = 0;
    while (TRUE) {
        HDC hdc = GetDC(NULL); if (hdc) {
            int hw = w / 2, hh = h / 2; BitBlt(hdc, -10, -10, hw, hh, hdc, 0, 0, SRCCOPY); BitBlt(hdc, hw + 10, -10, hw, hh, hdc, hw, 0, SRCCOPY); BitBlt(hdc, -10, hh + 10, hw, hh, hdc, 0, hh, SRCCOPY); BitBlt(hdc, hw + 10, hh + 10, hw, hh, hdc, hw, hh, SRCCOPY);
            bx += sx; by += sy; if (bx - br <= 0 || bx + br >= w) sx = -sx; if (by - br <= 0 || by + br >= h) sy = -sy; hu = (hu + 4) % 360;
            HBRUSH brush = CreateSolidBrush(RGB((int)(127 + 127 * sin(hu * 0.01745)), (int)(127 + 127 * sin((hu + 120) * 0.01745)), (int)(127 + 127 * sin((hu + 240) * 0.01745)))); HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, brush); SelectObject(hdc, pen); Ellipse(hdc, bx - br, by - br, bx + br, by + br); DeleteObject(brush); DeleteObject(pen); ReleaseDC(NULL, hdc);
        }
        Sleep(15);
    }
}
BOOL CALLBACK RenameWindowProc(HWND hwnd, LPARAM lParam) { SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)globalTitleText, SMTO_ABORTIFHUNG, 50, NULL); return TRUE; }
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) { RenameWindowProc(hwnd, lParam); EnumChildWindows(hwnd, RenameWindowProc, lParam); return TRUE; }

DWORD WINAPI WindowText(LPVOID lpParam) { while (TRUE) { EnumWindows(EnumWindowsProc, NULL); Sleep(100); } return 0; }
DWORD WINAPI msg(LPVOID lpParam) {
    LPCSTR txt = "∆π⌀©•.exe";
    UINT ic[4] = { MB_ICONERROR, MB_ICONWARNING, MB_ICONINFORMATION, MB_ICONQUESTION };
    while (TRUE) { MessageBoxA(NULL, txt, txt, MB_OK | ic[rand() % 4] | MB_SYSTEMMODAL); Sleep(10); }
}

void RunSoundStage(PTHREAD_START_ROUTINE payloadFunc, PTHREAD_START_ROUTINE soundFunc) {
    HANDLE hEffect = CreateThread(0, 0, payloadFunc, 0, 0, 0);
    HANDLE hSound = CreateThread(0, 0, soundFunc, 0, 0, 0);
    if (hSound != NULL) { WaitForSingleObject(hSound, INFINITE); CloseHandle(hSound); }
    if (hEffect != NULL) { TerminateThread(hEffect, 0); CloseHandle(hEffect); }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (MessageBoxW(NULL, L"Run GDIOnly?", L"∆π⌀©•.exe", MB_YESNO | MB_ICONWARNING) == IDNO) ExitProcess(0);
    if (MessageBoxW(NULL, L"Are you sure?", L"∆π⌀©•.exe", MB_YESNO | MB_ICONWARNING) == IDNO) ExitProcess(0);
    Sleep(2000);

    CreateThread(0, 0, msg, 0, 0, 0);

    CreateThread(0, 0, WindowText, 0, 0, 0);

    Sleep(2000);

    RunSoundStage(Payload1, Sound1);   RunSoundStage(Payload2, Sound2);
    RunSoundStage(Payload3, Sound3);   RunSoundStage(Payload4, Sound4);
    RunSoundStage(Payload5, Sound5);   RunSoundStage(Payload6, Sound6);
    RunSoundStage(Payload7, Sound7);   RunSoundStage(Payload8, Sound8);
    RunSoundStage(Payload9, Sound9);   RunSoundStage(Payload10, Sound10);
    RunSoundStage(Payload11, Sound11); RunSoundStage(Payload12, Sound12);

    ExitProcess(0);
}