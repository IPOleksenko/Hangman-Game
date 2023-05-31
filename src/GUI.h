#pragma once

#include <windows.h>


using namespace std;

void DrawText(HDC hdc, int x, int y, LPCWSTR text, int length)
{
    TextOut(hdc, x, y, text, length);
}

HWND CreateButton(HWND hWndParent, int x, int y, int width, int height, LPCWSTR lpCaption, int id, HINSTANCE hInstance)
{
    // Создание кнопки
    HWND hButton = CreateWindow(
        L"BUTTON",           // Класс окна
        lpCaption,          // Текст на кнопке
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,   // Стиль окна
        x, y,               // Координаты кнопки
        width, height,      // Размеры кнопки
        hWndParent,         // Идентификатор родительского окна
        (HMENU)id,          // Идентификатор кнопки
        hInstance,          // Идентификатор экземпляра приложения
        NULL                // Указатель на дополнительные параметры
    );

    return hButton;
}


void CreateKeyboard(HWND hWnd, int x, int y, int buttonWidth, int buttonHeight, int buttonsPerRow, int totalButtons)
{
    int rowCount = totalButtons / buttonsPerRow;
    if (totalButtons % buttonsPerRow > 0)
        rowCount++;

    int buttonCount = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < buttonsPerRow; j++)
        {
            if (buttonCount >= totalButtons)
                return;

            int xPos = x + (j * buttonWidth);
            int yPos = y + (i * buttonHeight);

            wchar_t buttonText[2] = { L'A' + buttonCount, L'\0' };
            CreateButton(hWnd, xPos, yPos, buttonWidth, buttonHeight, buttonText, buttonCount, NULL);

            buttonCount++;
        }
    }
}

void DrawHangman(HDC hdc, int x, int y, int steap)
{
    if (steap >= 1) {
        // Draw head
        Ellipse(hdc, x + 80, y + 30, x + 120, y + 70);
    }
    if (steap > 1) {
        // Draw body
        MoveToEx(hdc, x + 100, y + 70, NULL);
        LineTo(hdc, x + 100, y + 140);
    }
    if (steap > 2) {
        // Draw arms
        MoveToEx(hdc, x + 100, y + 90, NULL);
        LineTo(hdc, x + 60, y + 110);
    }
    if (steap > 3) {
        // Draw arms
        MoveToEx(hdc, x + 100, y + 90, NULL);
        LineTo(hdc, x + 140, y + 110);
    }
    if (steap > 4) {
        // Draw legs
        MoveToEx(hdc, x + 100, y + 140, NULL);
        LineTo(hdc, x + 60, y + 170);
    }
    if (steap > 5) {
        // Draw legs
        MoveToEx(hdc, x + 100, y + 140, NULL);
        LineTo(hdc, x + 140, y + 170);

        // Draw gallows
        MoveToEx(hdc, x + 10, y + 200, NULL);
        LineTo(hdc, x + 110, y + 200);
        LineTo(hdc, x + 60, y + 200);
        LineTo(hdc, x + 60, y);
        LineTo(hdc, x + 100, y);
        LineTo(hdc, x + 100, y + 30);
    }
}
