#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <string>
#include "GUI.h"
#include "random.h"
#include "words.h"
#include "findChar.h"
#include "checkGame.h"

#define WM_LBUTTONDOWN    0x0201

int stepCount = 0;
LPCWSTR word = GetRandomWord(words, size(words));
wstring secret_word;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Hangman Game";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create secret word
    secret_word = wstring(wcslen(word), L'*');

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Hangman Game",                // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, SW_MAXIMIZE);

    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        CreateKeyboard(hwnd, 100, 500, 80, 80, 13, 26);
        break;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }

    case WM_COMMAND:
    {
        wstring letter(1, L'a' + static_cast<wchar_t>(LOWORD(wParam)));
        LPCWSTR letter_LPCWSTR = letter.c_str();

        bool coincidence = FindCharInSecretWord(letter[0], word);
        for (size_t i = 0; i < wcslen(word); ++i) {
            if ((word[i] == letter_LPCWSTR[0]))
            {
                secret_word[i] = letter[0];
            }
            else if (coincidence == false)
            {
                stepCount += 1;
                break;
            }
        }

        HWND hButton = GetDlgItem(hwnd, LOWORD(wParam));
        DestroyWindow(hButton);

        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        
        checkGame(hwnd, word, secret_word, stepCount);
        
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        DrawText(hdc, 50, 50, secret_word.c_str(), wcslen(secret_word.c_str()));
        DrawHangman(hdc, 100, 100, stepCount);

        EndPaint(hwnd, &ps);
        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}