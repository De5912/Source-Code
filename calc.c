#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BTN_0 100
#define BTN_1 101
#define BTN_2 102
#define BTN_3 103
#define BTN_4 104
#define BTN_5 105
#define BTN_6 106
#define BTN_7 107
#define BTN_8 108
#define BTN_9 109
#define BTN_ADD 110
#define BTN_SUB 111
#define BTN_MUL 112
#define BTN_DIV 113
#define BTN_EQ  114
#define BTN_C   115
#define BTN_BK  116  // Backspace button

char expression[256] = "";  // Stores the input expression
HWND hEdit;  // Handle for text box

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddButton(HWND hwnd, int id, char* text, int x, int y);
double EvaluateExpression(const char* expr);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = { 0 };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"Calculator";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(L"Calculator", L"Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 300, 400, NULL, NULL, NULL, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        hEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_READONLY,
            20, 20, 240, 30, hwnd, NULL, NULL, NULL);

        // Number buttons
        int x = 20, y = 60;
        for (int i = 1; i <= 9; i++) {
            AddButton(hwnd, BTN_0 + i, (char[2]) { '0' + i, '\0' }, x, y);
            x += 60;
            if (i % 3 == 0) { x = 20; y += 60; }
        }
        AddButton(hwnd, BTN_0, "0", 80, y);  // Zero in the middle

        // Operator buttons
        AddButton(hwnd, BTN_ADD, "+", 200, 60);
        AddButton(hwnd, BTN_SUB, "-", 200, 120);
        AddButton(hwnd, BTN_MUL, "*", 200, 180);
        AddButton(hwnd, BTN_DIV, "/", 200, 240);
        AddButton(hwnd, BTN_EQ, "=", 140, 240);
        AddButton(hwnd, BTN_C, "C", 20, 240);
        AddButton(hwnd, BTN_BK, "←", 80, 240);  // Backspace

        break;

    case WM_COMMAND:
        if (HIWORD(wp) == BN_CLICKED) {
            int id = LOWORD(wp);

            if (id == BTN_C) {
                expression[0] = '\0';  // Clear expression
            } else if (id == BTN_BK) {
                if (strlen(expression) > 0) {
                    expression[strlen(expression) - 1] = '\0';  // Backspace
                }
            } else if (id == BTN_EQ) {
                double result = EvaluateExpression(expression);
                if (result == -99999999) {
                    strcpy(expression, "ERROR");
                } else {
                    sprintf(expression, "%.2f", result);
                }
            } else if (strlen(expression) < 255) {
                char newChar[2] = { '0' + (id - BTN_0), '\0' };
                strcat(expression, newChar);
            }

            SetWindowText(hEdit, expression);
        }
        break;

    case WM_CHAR:
        if (isalnum(wp) || wp == '+' || wp == '-' || wp == '*' || wp == '/') {
            if (strlen(expression) < 255) {
                char newChar[2] = { (char)wp, '\0' };
                strcat(expression, newChar);
            }
        } else if (wp == '\b' && strlen(expression) > 0) {
            expression[strlen(expression) - 1] = '\0';  // Backspace
        } else if (wp == '\r') {
            double result = EvaluateExpression(expression);
            if (result == -99999999) {
                strcpy(expression, "ERROR");
            } else {
                sprintf(expression, "%.2f", result);
            }
        }
        SetWindowText(hEdit, expression);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

void AddButton(HWND hwnd, int id, char* text, int x, int y) {
    CreateWindow("button", text, WS_VISIBLE | WS_CHILD, x, y, 50, 50, hwnd, (HMENU)(intptr_t)id, NULL, NULL);
}

double EvaluateExpression(const char* expr) {
    double num1, num2;
    char op;
    if (sscanf(expr, "%lf %c %lf", &num1, &op, &num2) == 3) {
        switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return (num2 != 0) ? num1 / num2 : -99999999;
        }
    }
    return -99999999;  // Error
}
