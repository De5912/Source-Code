#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BTN_ADD 101
#define BTN_SUB 102
#define BTN_MUL 103
#define BTN_DIV 104
#define BTN_EQ  105
#define BTN_C   106

char expression[256] = "";

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddButton(HWND hwnd, int id, char* text, int x, int y);

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
    static HWND hEdit;

    switch (msg) {
    case WM_CREATE:
        hEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT,
            20, 20, 240, 30, hwnd, NULL, NULL, NULL);

        AddButton(hwnd, BTN_ADD, "+", 20, 60);
        AddButton(hwnd, BTN_SUB, "-", 80, 60);
        AddButton(hwnd, BTN_MUL, "*", 140, 60);
        AddButton(hwnd, BTN_DIV, "/", 200, 60);
        AddButton(hwnd, BTN_EQ, "=", 20, 120);
        AddButton(hwnd, BTN_C, "C", 80, 120);
        break;

    case WM_COMMAND:
        if (HIWORD(wp) == BN_CLICKED) {
            int id = LOWORD(wp);

            if (id == BTN_C) {
                expression[0] = '\0';
            } else if (id == BTN_EQ) {
                // Simple evaluation (not safe, just for basic use)
                double result;
                if (sscanf(expression, "%lf", &result) == 1) {
                    sprintf(expression, "%.2f", result);
                } else {
                    strcpy(expression, "ERROR");
                }
            } else if (strlen(expression) < 255) {
                if (id == BTN_ADD) strcat(expression, "+");
                else if (id == BTN_SUB) strcat(expression, "-");
                else if (id == BTN_MUL) strcat(expression, "*");
                else if (id == BTN_DIV) strcat(expression, "/");
            }
            SetWindowText(hEdit, expression);
        }
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

