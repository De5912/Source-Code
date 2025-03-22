#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> // Include for intptr_t

#define SCREEN_ID 1
#define BTN_0 10
#define BTN_1 11
#define BTN_2 12
#define BTN_3 13
#define BTN_4 14
#define BTN_5 15
#define BTN_6 16
#define BTN_7 17
#define BTN_8 18
#define BTN_9 19
#define BTN_ADD 20
#define BTN_SUB 21
#define BTN_MUL 22
#define BTN_DIV 23
#define BTN_EQ  24
#define BTN_CLR 25

char expression[256] = ""; // Stores input like "12+3*5"
HWND hScreen; // Display screen

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddButton(HWND hwnd, int id, char* text, int x, int y) {
    CreateWindow("button", text, WS_VISIBLE | WS_CHILD, x, y, 50, 50, hwnd, (HMENU)(intptr_t)id, NULL, NULL);
}

void AddButtons(HWND hwnd) {
    hScreen = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT, 10, 10, 230, 30, hwnd, (HMENU)SCREEN_ID, NULL, NULL);
    
    int x = 10, y = 50;
    int ids[] = {BTN_7, BTN_8, BTN_9, BTN_DIV, BTN_4, BTN_5, BTN_6, BTN_MUL, BTN_1, BTN_2, BTN_3, BTN_SUB, BTN_0, BTN_CLR, BTN_EQ, BTN_ADD};
    char* labels[] = {"7", "8", "9", "/", "4", "5", "6", "*", "1", "2", "3", "-", "0", "C", "=", "+"};

    for (int i = 0; i < 16; i++) {
        AddButton(hwnd, ids[i], labels[i], x, y);
        x += 60;
        if ((i + 1) % 4 == 0) { x = 10; y += 60; }
    }
}

void UpdateScreen(HWND hwnd) {
    SetWindowText(hScreen, expression);
}

void Calculate() {
    int result = 0;
    // Basic parsing logic (can be improved)
    result = atoi(expression); // Convert to int (simple logic, replace with better parser)
    sprintf(expression, "%d", result);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            AddButtons(hwnd);
            break;
        case WM_COMMAND:
            if (wp >= BTN_0 && wp <= BTN_9) {
                char num[2] = {(char)(wp - BTN_0 + '0'), '\0'};
                strcat(expression, num);
            } else if (wp == BTN_ADD) strcat(expression, "+");
            else if (wp == BTN_SUB) strcat(expression, "-");
            else if (wp == BTN_MUL) strcat(expression, "*");
            else if (wp == BTN_DIV) strcat(expression, "/");
            else if (wp == BTN_EQ) Calculate();
            else if (wp == BTN_CLR) strcpy(expression, "");

            UpdateScreen(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "Calculator";
    wc.lpfnWndProc = WindowProcedure;

    RegisterClass(&wc);
    HWND hwnd = CreateWindow("Calculator", "WinAPI Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 270, 350, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

