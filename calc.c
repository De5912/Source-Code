#include <windows.h>

// Function Prototypes
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

// Global Variables for UI Elements
HWND hEdit1, hEdit2, hResult, hButtonAdd, hButtonSub;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.hInstance = hInstance;
    wc.lpszClassName = "CalculatorApp";
    wc.lpfnWndProc = WindowProcedure;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);
    HWND hwnd = CreateWindow("CalculatorApp", "Simple Calculator", WS_OVERLAPPEDWINDOW, 100, 100, 300, 200, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

// Handles Events
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // Create Input Boxes
            hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 20, 80, 20, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 20, 80, 20, hwnd, NULL, NULL, NULL);
            hResult = CreateWindow("STATIC", "Result: ", WS_CHILD | WS_VISIBLE, 50, 50, 180, 20, hwnd, NULL, NULL, NULL);
            
            // Create Buttons
            hButtonAdd = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 50, 80, 40, 30, hwnd, (HMENU)1, NULL, NULL);
            hButtonSub = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 100, 80, 40, 30, hwnd, (HMENU)2, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1 || LOWORD(wParam) == 2) {
                char text1[10], text2[10];
                int num1, num2, result;
                GetWindowText(hEdit1, text1, 10);
                GetWindowText(hEdit2, text2, 10);
                num1 = atoi(text1);
                num2 = atoi(text2);
                
                result = (LOWORD(wParam) == 1) ? (num1 + num2) : (num1 - num2);

                char resText[20];
                sprintf(resText, "Result: %d", result);
                SetWindowText(hResult, resText);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
