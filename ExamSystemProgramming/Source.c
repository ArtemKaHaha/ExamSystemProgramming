#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "library.h" // ���������� ��� task1
#define MAX_LENGTH 100 // ������������ ������ ������ ��� task4

int task1()
{
    printf("������ �1\n");

    int a = 10;
    int b = 5;

    int rez1 = add(a, b);
    int rez2 = subtract(a, b);

    printf("�����: %d\n", rez1);
    printf("��������: %d\n", rez2);

    return 0;
}

int task2()
{
    printf("\n������ �2\n");
}

int task4()
{
    printf("\n������ �4\n");

    FILE* inputFile, * outputFile;
    char str[MAX_LENGTH];

    inputFile = fopen("1.txt", "r");
    outputFile = fopen("2.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("������ �������� ������\n");
        return 1;
    }

    fgets(str, MAX_LENGTH, inputFile);

    fprintf(outputFile, "%s", str);

    fclose(inputFile);
    fclose(outputFile);

    printf("� ���� ������� �������� ������ �� ������� �����\n");
    return 0;
}

int task5()
{
    FILE* input_file, * output_file;
    char input_filename[] = "3.txt";
    char output_filename[] = "4.txt";
    char buffer[100];

    input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        perror("������ �������� �������� �����");
        exit(EXIT_FAILURE);
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        perror("������ �������� ��������� �����");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, 100, input_file) != NULL)
    {
        fputs(buffer, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("������ ������� ����������� �� ����� %s � ���� %s\n", input_filename, output_filename);

    return 0;
}

HHOOK g_hKeyboardHook; // ������ HOOK ��� task6

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)

    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN)
        {
            char keyName[30];
            int result = GetKeyNameTextA(p->vkCode << 16, keyName, 30);

            if (result != 0)
            {
                MessageBoxA(NULL, keyName, "������ �������", MB_OK);
            }
        }
    }

    return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}

int task6()
{
    g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);

    if (g_hKeyboardHook == NULL)
    {
        printf("������ ��������� ����\n");

        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(g_hKeyboardHook);
    return 0;
}

LRESULT CALLBACK KeyboardProcASCII(int nCode, WPARAM wParam, LPARAM lParam) // HOOK ��� task7
{

    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        char key = (char)kbdStruct->vkCode;
        char message[50];

        sprintf(message, "������ �������: %c", key);
        MessageBoxA(NULL, message, "��", MB_OK);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int task7()
{
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProcASCII, NULL, 0);

    if (hook == NULL)
    {
        MessageBox(0, L"������ � HOOK��", L"������", MB_OK);
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);

    return 0;
}

void intToString(int number, char* str) // ������� ��� �������������� ����� � ������
{
    int i = 0;

    if (number < 0)
    {
        str[i++] = '-';
        number = -number;
    }

    int count = 0;
    int temp = number;

    while (temp > 0)
    {
        temp /= 10;
        count++;
    }

    for (int j = count - 1; j >= 0; j--)
    {
        str[i++] = '0' + (number / (int)pow(10, j)) % 10;
    }

    str[i] = '\0';
}

void concatStrings(const char* str1, const char* str2, char* result) // ������� ��� ������� ���� �����
{
    int i = 0;

    while (*str1 != '\0')
    {
        result[i++] = *str1++;
    }

    while (*str2 != '\0')
    {
        result[i++] = *str2++;
    }

    result[i] = '\0';
}


int task8()
{
    int number = 12345;
    char numberStr[20];
    intToString(number, numberStr);
    printf("����� � ������: %s\n", numberStr);

    const char* str1 = "������ �1";
    const char* str2 = " ������ �2";
    char result[50];
    concatStrings(str1, str2, result);
    printf("������������ ������: %s\n", result);

    return 0;
}

int stringToNumber(LPWSTR str) // ������� ��� �������������� ������ � �����
{
    int result = 0;
    int sign = 1;
    int index = 0;

    if (str[0] == L'-')
    {
        sign = -1;
        index = 1;
    }

    while (str[index] != L'\0')
    {
        if (str[index] >= L'0' && str[index] <= L'9')
        {
            result = result * 10 + (str[index] - L'0');
        }

        else
        {
            printf("������\n");
            return 0;
        }

        index++;
    }

    return result * sign;
}

int task9()
{
    LPWSTR str = L"12345";
    int number = stringToNumber(str);

    wprintf(L"Number: %d\n", number);
    return 0;
}

int task10()
{
    char buffer[100];

    printf("������� ������: ");
    fgets(buffer, sizeof(buffer), stdin);

    printf("�������: %s", buffer);

    return 0;
}

CRITICAL_SECTION cs; // ����������� ������ ��� task11

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{

    for (int i = 0; i < 10000; i++)
    {
        EnterCriticalSection(&cs);

        printf("����� %d ��������� ������ � ����������� ������\n", GetCurrentThreadId());

        LeaveCriticalSection(&cs);
    }
    return 0;
}

int task11()
{
    HANDLE hThread[2];
    DWORD dwThreadId;
    InitializeCriticalSection(&cs); // ������������� ����������� ������

    for (int i = 0; i < 2; i++)
    {
        hThread[i] = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &dwThreadId);

        if (hThread[i] == NULL)
        {
            fprintf(stderr, "������ ��� �������� ������\n");
            return 1;
        }
    }

    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    for (int i = 0; i < 2; i++)
    {
        CloseHandle(hThread[i]);
    }

    DeleteCriticalSection(&cs);
    return 0;
}

int task13()
{
    char input[100]; // ���� ������������
    int values[50]; // ������ ��� �������� �������� ��������
    int count = 0; // ������� �������� ��������

    printf("������� �������� �������� (����������� ��������): ");
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, " "); // ��������� ������� ����� �� �����
    while (token != NULL)
    {
        values[count] = atoi(token); // �������������� ����� �� ������ � int � ������ � ������
        count++;
        token = strtok(NULL, " "); // ��������� ���������� �����
    }

    printf("��������� �������� ��������: ");

    for (int i = 0; i < count; i++)
    {
        printf("%d ", values[i]); // ����� �������� ��������
    }
    printf("\n");

    return 0;
}

int task14()
{
    HKEY hKey;
    char* regPath = "Software\\MyCompany\\MyProgram"; // ���� � �������

    if (RegCreateKeyEx(HKEY_CURRENT_USER, regPath, 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) // ������ �������� � ������
    {
        const char* value = "����";
        if (RegSetValueEx(hKey, "MyParameter", 0, REG_SZ, (const BYTE*)value, strlen(value) + 1) == ERROR_SUCCESS)
        {
            printf("��������� �������� ������� �������� � ������\n");
        }

        else
        {
            printf("������ ��� ������ �������� � ������\n");
        }
        RegCloseKey(hKey);
    }

    else
    {
        printf("������ ��� �������� ����� � �������\n");
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, regPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) // ���������� �������� �� �������
    {
        char buffer[100];
        DWORD bufferSize = sizeof(buffer);

        if (RegQueryValueEx(hKey, "MyParameter", NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS)
        {
            printf("��������� �������� �� �������: %s\n", buffer);
        }

        else
        {
            printf("������ ��� ���������� �������� �� �������\n");
        }
        RegCloseKey(hKey);
    }

    else
    {
        printf("������ ��� �������� ����� � �������\n");
    }

    return 0;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) // HOOK ��� task15
{
    if (nCode >= 0 && wParam == WM_LBUTTONDOWN)
    {
        MessageBoxA(NULL, "������ ����� ������ ����", "��", MB_OK);
    }

    if (nCode >= 0 && wParam == WM_RBUTTONDOWN)
    {
        MessageBoxA(NULL, "������ ������ ������ ����", "��", MB_OK);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int task15()
{
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
    return 0;
}

int task16()
{
    if (OpenClipboard(NULL))
    {
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, 100);

        if (hMem != NULL)
        {
            char* pszText = GlobalLock(hMem);
            strcpy(pszText, "����� ��� ������ ������");
            GlobalUnlock(hMem);
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();
            printf("������ ������� �������� � ����� ������\n");
        }

        else
        {
            CloseClipboard();
            printf("������ ��� ��������� ������ ��� ������ ������\n");
            return 1;
        }
    }

    else
    {
        printf("������ ��� �������� ������ ������\n");
        return 1;
    }

    if (OpenClipboard(NULL)) // ���������� �� ������ ������
    {
        HANDLE hData = GetClipboardData(CF_TEXT);

        if (hData != NULL)
        {
            char* pszData = (char*)GlobalLock(hData);
            printf("��������� ������ �� ������ ������: %s\n", pszData);
            GlobalUnlock(hData);
        }

        else
        {
            printf("������ ��� ��������� ������ �� ������ ������\n");
        }
        CloseClipboard();
    }

    else
    {
        printf("������ ��� �������� ������ ������ ��� ������\n");
    }

    return 0;
}

int task17()
{
    HKEY hKey;
    char* regPath = "Software\\MyCompany\\MyProgram"; // ���� � �������
    DWORD dwValue = 12345;

    if (RegCreateKeyEx(HKEY_CURRENT_USER, regPath, 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) // ������ ��������� �������� � ������
    {
        if (RegSetValueEx(hKey, "MyNumber", 0, REG_DWORD, (const BYTE*)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
        {
            printf("�������� �������� ������� �������� � ������\n");
        }

        else
        {
            printf("������ ��� ������ �������� � ������\n");
        }
        RegCloseKey(hKey);
    }

    else
    {
        printf("������ ��� �������� ����� � �������\n");
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, regPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) // ���������� ��������� �������� �� �������
    {
        DWORD dwType;
        DWORD dwData;
        DWORD dwDataSize = sizeof(DWORD);

        if (RegQueryValueEx(hKey, "MyNumber", 0, &dwType, (LPBYTE)&dwData, &dwDataSize) == ERROR_SUCCESS && dwType == REG_DWORD)
        {
            printf("��������� �������� �������� �� �������: %d\n", dwData);
        }

        else
        {
            printf("������ ��� ���������� �������� �� �������\n");
        }

        RegCloseKey(hKey);
    }

    else
    {
        printf("������ ��� �������� ����� � �������\n");
    }

    return 0;
}

int seconds = 0; // ���������� ���������� ��� ������� �������
HANDLE hMutex; // ������� ��� ������ ������� � ���������� ����������
DWORD WINAPI stopwatch(LPVOID lpParam) // ������� ��� task18
{
    while (1)
    {
        Sleep(1000); // �������� �� 1 �������
        WaitForSingleObject(hMutex, INFINITE); // ����������� �������
        seconds++; // ����������� ������� �������
        ReleaseMutex(hMutex); // ����������� �������
    }
    return 0;
}

int task18()
{
    HANDLE hThread;
    DWORD dwThreadId;
    hMutex = CreateMutex(NULL, FALSE, NULL);

    hThread = CreateThread(NULL, 0, stopwatch, NULL, 0, &dwThreadId);
    if (hThread == NULL)
    {
        fprintf(stderr, "������ ��� �������� ������\n");
        return 1;
    }

    while (1) // �������� ����� ���������� ������������
    {
        WaitForSingleObject(hMutex, INFINITE); // ����������� �������
        printf("����������: %d ������\n", seconds); // �������� �����
        ReleaseMutex(hMutex); // ����������� �������
        Sleep(2000); // �������� �� 2 �������
    }

    CloseHandle(hThread); // ��������� ���������� ������
    CloseHandle(hMutex); // ��������� ���������� ��������

    return 0;
}

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    else
    {
        return n * factorial(n - 1);
    }
}

DWORD WINAPI threadFunc(LPVOID lpParam)
{
    int number = *(int*)lpParam;

    if (number < 0)
    {
        printf("������: �������� �������� �����. ����� ������ ���� >= 0\n");
        return 1;
    }

    int result = factorial(number);
    printf("��������� ����� %d ����� %d\n", number, result);

    return 0;
}

int task19()
{
    int number;

    printf("������� �����: ");
    scanf("%d", &number);

    HANDLE threadHandle = CreateThread(NULL, 0, threadFunc, &number, 0, NULL);

    if (threadHandle == NULL)
    {
        printf("������ ��� �������� ������\n");
        return 1;
    }

    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);

    return 0;
}

int task20()
{
    FILE* file;
    file = _wfopen(L"unicode.txt", L"r, ccs=UTF-8");

    if (file != NULL)
    {
        wchar_t buffer[1000];
        fgetws(buffer, 1000, file);
        fclose(file);

        MessageBoxW(NULL, buffer, L"������ ������ �� �����", MB_OK | MB_ICONINFORMATION);
    }

    else
    {
        MessageBox(NULL, "�� ������� ������� ����", "������", MB_OK | MB_ICONERROR);
    }

    return 0;
}

int task21()
{
    FILE* file = fopen("external_process.c", "w");

    if (file == NULL)
    {
        printf("������ ��� �������� �����\n");
        return 1;
    }

    fprintf(file, "#include <stdio.h>\n\nint main() {\n");
    fprintf(file, "    printf(\"������, � ��������� �������\");\n");
    fprintf(file, "    return 0;\n}\n");
    fclose(file);

    printf("������ ���������� ��������...\n");
    int result = system("gcc -o external_process external_process.c && ./external_process");

    if (result != 0)
    {
        printf("������ ��� ������� ���������� ��������\n");
        return 1;
    }

    return 0;
}

int task22()
{
    DWORD fileAttributes = GetFileAttributesA("file.txt"); // ������� ���������� �������� �����

    if (fileAttributes != INVALID_FILE_ATTRIBUTES)
    {

        if (fileAttributes & FILE_ATTRIBUTE_HIDDEN)
        {
            printf("���� �����\n");
        }

        if (fileAttributes & FILE_ATTRIBUTE_READONLY)
        {
            printf("���� ������ ��� ������\n");
        }
    }

    else
    {
        printf("�� ������� �������� �������� �����\n");
    }

    HKEY hKey;
    LONG result = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft", 0, KEY_READ, &hKey); // ������� ��������� ������ � �������

    if (result == ERROR_SUCCESS)
    {
        printf("������ ������� ������� ������\n");
    }

    else if (result == ERROR_FILE_NOT_FOUND)
    {
        printf("������ ������� �� ������\n");
    }

    else
    {
        printf("�� ������� ������� ������ �������\n");
    }

    HANDLE hMutex = CreateMutexA(NULL, FALSE, "MyMutex"); // ������� ������� ��� ��������� ������ ��������

    if (hMutex != NULL)
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            printf("������� ��� ����������\n");
        }

        else
        {
            printf("������� ������� ������\n");
        }
    }
    else {
        printf("�� ������� ������� �������\n");
    }

    return 0;
}

typedef struct
{
    float x1, y1;
    float x2, y2;
} Point;

float calculateLength(Point p) // ������� ��� task23
{
    float length;

    length = sqrt(pow(p.x2 - p.x1, 2) + pow(p.y2 - p.y1, 2));

    return length;
}

typedef float (*CalculateLengthFunc)(Point);

int task23()
{
    HMODULE dll = LoadLibrary("dlltask23.dll");

    if (dll == NULL)
    {
        printf("������ �������� DLL\n");
        return 1;
    }

    CalculateLengthFunc calculateLength = (CalculateLengthFunc)GetProcAddress(dll, "calculateLength");

    if (calculateLength == NULL)
    {
        printf("������ ��������� ������ �������\n");
        return 1;
    }

    Point p = { 1.0f, 2.0f, 4.0f, 6.0f };
    float length = calculateLength(p);

    printf("����� �������: %f\n", length);
    FreeLibrary(dll);

    return 0;
}

int task24()
{
    HANDLE pipe;
    char buffer[1024];
    DWORD bytesRead;

    pipe = CreateNamedPipe("\\\\.\\pipe\\myNamedPipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        1024,
        1024,
        0,
        NULL);

    while (1)
    {
        if (ReadFile(pipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) == 0)
        {
            printf("������ ��� ������ �� ������\n");
            break;
        }

        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            printf("���������� ������: %s\n", buffer);

            char response[] = "��������� ��������";
            DWORD bytesWritten;

            if (WriteFile(pipe, response, sizeof(response), &bytesWritten, NULL) == 0)
            {
                printf("������ ��� ������ � �����\n");
                break;
            }
        }
    }

    CloseHandle(pipe);
    return 0;

    HANDLE pipe1;
    char buffer1[1024];
    DWORD bytesRead1, bytesWritten;

    pipe1 = CreateFile("\\\\.\\pipe\\myNamedPipe",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (pipe1 == INVALID_HANDLE_VALUE)
    {
        printf("������ ��� ����������� � ������������ ������\n");
        return 1;
    }

    char message[] = "������, ������!";
    if (WriteFile(pipe, message, sizeof(message), &bytesWritten, NULL) == 0) {
        printf("������ ��� ������ � �����\n");
        CloseHandle(pipe);
        return 1;
    }

    if (ReadFile(pipe1, buffer1, sizeof(buffer) - 1, &bytesRead1, NULL) != 0)
    {
        if (bytesRead1 > 0)
        {
            buffer1[bytesRead1] = '\0';
            printf("����� �� �������: %s\n", buffer1);
        }
        else
        {
            printf("������ ������ ����������\n");
        }
    }
    else
    {
        printf("������ ��� ������ �� ������\n");
    }

    CloseHandle(pipe1);
    return 0;
}

int task26()
{
    FILE* file = fopen("bin.bin", "rb");

    if (file == NULL)
    {
        printf("������ �������� �����\n");
        return 1;
    }

    int number;
    fread(&number, sizeof(int), 1, file);

    fclose(file);

    printf("��������� ��������: %d\n", number);

    return 0;
}

int task27(int argc, char* argv[])
{
    printf("��������� �� ��������� ������:\n");

    for (int i = 0; i < argc; i++) // ������ 1: ������������� argc � argv

    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    char** ptr = argv; // ������ 2: ������������� ��������� �� ������ argv

    while (*ptr != NULL)
    {
        printf("arg: %s\n", *ptr);
        ptr++;
    }

    char* arg; // ������ 3: ������������� �������������� ����� ���������� argc � argv

    for (int i = 1; i < argc; i++)
    {
        arg = *(argv + i);
        printf("arg: %s\n", arg);
    }

    return 0;
}

DWORD WINAPI BackgroundProcess(LPVOID lpParam) // �������� �������� �������� ��� task30
{
    int counter = 0;

    while (1)
    {
        Sleep(5000); // ��������� 5 ������
        counter++;
        char message[100];
        sprintf(message, "�������� ��������: %d", counter);
        MessageBoxA(NULL, message, "���������", MB_OK);
    }
    return 0;
}

int task30()
{
    HANDLE hThread;
    DWORD threadId;

    hThread = CreateThread(NULL, 0, BackgroundProcess, NULL, 0, &threadId);

    if (hThread == NULL)
    {
        printf("������ �������� ������\n");
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE); // ����, ���� ����� ����������

    CloseHandle(hThread);

    return 0;
}

int main()
{
    system("chcp 1251>nul");

    //task1();
    //task2();
    //task4(); // ������ �������, �� ��� ������� WinApi
    //task5();
    //task6(); // ������� ������� �� ������������ ������ �������� (�� ����)
    //task7();
    //task8();
    //task9();
    //task10();
    //task11();
    //task13();
    //task14();
    //task15();
    //task16();
    //task17();
    //task18();
    //task19();
    //task20();
    //task21();
    //task22();
    //task23();
    task24();
    //task26();
;   //task27(3, "arg1", "arg2", "arg3", "arg4"); // �� ��������
    //task30(); // ��� ������ task30 ���������� ���������������� task6
}