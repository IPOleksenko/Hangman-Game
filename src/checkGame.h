#pragma once
#include <windows.h>
#include <string>

void checkGame(HWND hwnd, LPCWSTR word, std::wstring secret_word, int i)
{
    if (i == 6)
    {
        MessageBox(hwnd, L"Game Over!", L"Message", MB_OK | MB_ICONINFORMATION);
        DestroyWindow(hwnd);
    }
    else if (word == secret_word) {
        MessageBox(hwnd, L"You Win!", L"Message", MB_OK | MB_ICONINFORMATION);
        DestroyWindow(hwnd);
    }
}