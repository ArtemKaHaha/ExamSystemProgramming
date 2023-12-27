#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "library.h" // Библиотека для task1
#define MAX_LENGTH 100 // Максимальная длинна строки для task4

int task1()
{
    printf("Задача №1\n");

    int a = 10;
    int b = 5;

    int rez1 = add(a, b);
    int rez2 = subtract(a, b);

    printf("Сумма: %d\n", rez1);
    printf("Разность: %d\n", rez2);

    return 0;
}

int task2()
{
    printf("\nЗадача №2\n");
}

int task4()
{
    printf("\nЗадача №4\n");

    FILE* inputFile, * outputFile;
    char str[MAX_LENGTH];

    inputFile = fopen("1.txt", "r");
    outputFile = fopen("2.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Ошибка открытия файлов\n");
        return 1;
    }

    fgets(str, MAX_LENGTH, inputFile);

    fprintf(outputFile, "%s", str);

    fclose(inputFile);
    fclose(outputFile);

    printf("В файл успешно записана строка из другого файла\n");
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
        perror("Ошибка открытия входного файла");
        exit(EXIT_FAILURE);
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        perror("Ошибка открытия выходного файла");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, 100, input_file) != NULL)
    {
        fputs(buffer, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("Данные успешно скопированы из файла %s в файл %s\n", input_filename, output_filename);

    return 0;
}

HHOOK g_hKeyboardHook; // Создаём HOOK для task6

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
                MessageBoxA(NULL, keyName, "Нажата клавиша", MB_OK);
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
        printf("Ошибка установки хука\n");

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

LRESULT CALLBACK KeyboardProcASCII(int nCode, WPARAM wParam, LPARAM lParam) // HOOK для task7
{

    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        char key = (char)kbdStruct->vkCode;
        char message[50];

        sprintf(message, "Нажата клавиша: %c", key);
        MessageBoxA(NULL, message, "Ку", MB_OK);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int task7()
{
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProcASCII, NULL, 0);

    if (hook == NULL)
    {
        MessageBox(0, L"Ошибка с HOOKом", L"Ошибка", MB_OK);
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

void intToString(int number, char* str) // Функция для преобразования числа в строку
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

void concatStrings(const char* str1, const char* str2, char* result) // Функция для склейки двух строк
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
    printf("Число в строку: %s\n", numberStr);

    const char* str1 = "Строка №1";
    const char* str2 = " строка №2";
    char result[50];
    concatStrings(str1, str2, result);
    printf("Объединенная строка: %s\n", result);

    return 0;
}

int stringToNumber(LPWSTR str) // Функция для перобразования строки в число
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
            printf("Ошибка\n");
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

    printf("Введите строку: ");
    fgets(buffer, sizeof(buffer), stdin);

    printf("Введено: %s", buffer);

    return 0;
}

CRITICAL_SECTION cs; // Критическая секция для task11

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{

    for (int i = 0; i < 10000; i++)
    {
        EnterCriticalSection(&cs);

        printf("Поток %d выполняет работу в критической секции\n", GetCurrentThreadId());

        LeaveCriticalSection(&cs);
    }
    return 0;
}

int task11()
{
    HANDLE hThread[2];
    DWORD dwThreadId;
    InitializeCriticalSection(&cs); // Инициализация критической секции

    for (int i = 0; i < 2; i++)
    {
        hThread[i] = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &dwThreadId);

        if (hThread[i] == NULL)
        {
            fprintf(stderr, "Ошибка при создании потока\n");
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
    char input[100]; // Ввод пользователя
    int values[50]; // Массив для хранения числовых значений
    int count = 0; // Счетчик числовых значений

    printf("Введите числовые значения (разделенные пробелом): ");
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, " "); // Выделение первого числа из ввода
    while (token != NULL)
    {
        values[count] = atoi(token); // Преобразование числа из строки в int и запись в массив
        count++;
        token = strtok(NULL, " "); // Получение следующего числа
    }

    printf("Введенные числовые значения: ");

    for (int i = 0; i < count; i++)
    {
        printf("%d ", values[i]); // Вывод числовых значений
    }
    printf("\n");

    return 0;
}

int task14()
{
    HKEY hKey;
    char* regPath = "Software\\MyCompany\\MyProgram"; // Путь в реестре

    if (RegCreateKeyEx(HKEY_CURRENT_USER, regPath, 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) // Запись значения в реестр
    {
        const char* value = "Тест";
        if (RegSetValueEx(hKey, "MyParameter", 0, REG_SZ, (const BYTE*)value, strlen(value) + 1) == ERROR_SUCCESS)
        {
            printf("Строковое значение успешно записано в реестр\n");
        }

        else
        {
            printf("Ошибка при записи значения в реестр\n");
        }
        RegCloseKey(hKey);
    }

    else
    {
        printf("Ошибка при создании ключа в реестре\n");
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, regPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) // Считывание значения из реестра
    {
        char buffer[100];
        DWORD bufferSize = sizeof(buffer);

        if (RegQueryValueEx(hKey, "MyParameter", NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS)
        {
            printf("Считанное значение из реестра: %s\n", buffer);
        }

        else
        {
            printf("Ошибка при считывании значения из реестра\n");
        }
        RegCloseKey(hKey);
    }

    else
    {
        printf("Ошибка при открытии ключа в реестре\n");
    }

    return 0;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) // HOOK для task15
{
    if (nCode >= 0 && wParam == WM_LBUTTONDOWN)
    {
        MessageBoxA(NULL, "Нажата левая кнопка мыши", "Ку", MB_OK);
    }

    if (nCode >= 0 && wParam == WM_RBUTTONDOWN)
    {
        MessageBoxA(NULL, "Нажата правая кнопка мыши", "КУ", MB_OK);
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
            strcpy(pszText, "текст для буфера обмена");
            GlobalUnlock(hMem);
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();
            printf("Строка успешно записана в буфер обмена\n");
        }

        else
        {
            CloseClipboard();
            printf("Ошибка при выделении памяти для буфера обмена\n");
            return 1;
        }
    }

    else
    {
        printf("Ошибка при открытии буфера обмена\n");
        return 1;
    }

    if (OpenClipboard(NULL)) // Считывание из буфера обмена
    {
        HANDLE hData = GetClipboardData(CF_TEXT);

        if (hData != NULL)
        {
            char* pszData = (char*)GlobalLock(hData);
            printf("Считанная строка из буфера обмена: %s\n", pszData);
            GlobalUnlock(hData);
        }

        else
        {
            printf("Ошибка при получении данных из буфера обмена\n");
        }
        CloseClipboard();
    }

    else
    {
        printf("Ошибка при открытии буфера обмена для чтения\n");
    }

    return 0;
}

int task17()
{
    HKEY hKey;
    char* regPath = "Software\\MyCompany\\MyProgram"; // Путь в реестре
    DWORD dwValue = 12345;

    if (RegCreateKeyEx(HKEY_CURRENT_USER, regPath, 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) // Запись числового значения в реестр
    {
        if (RegSetValueEx(hKey, "MyNumber", 0, REG_DWORD, (const BYTE*)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
        {
            printf("Числовое значение успешно записано в реестр\n");
        }

        else
        {
            printf("Ошибка при записи значения в реестр\n");
        }
        RegCloseKey(hKey);
    }

    else
    {
        printf("Ошибка при создании ключа в реестре\n");
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, regPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) // Считывание числового значения из реестра
    {
        DWORD dwType;
        DWORD dwData;
        DWORD dwDataSize = sizeof(DWORD);

        if (RegQueryValueEx(hKey, "MyNumber", 0, &dwType, (LPBYTE)&dwData, &dwDataSize) == ERROR_SUCCESS && dwType == REG_DWORD)
        {
            printf("Считанное числовое значение из реестра: %d\n", dwData);
        }

        else
        {
            printf("Ошибка при считывании значения из реестра\n");
        }

        RegCloseKey(hKey);
    }

    else
    {
        printf("Ошибка при открытии ключа в реестре\n");
    }

    return 0;
}

int seconds = 0; // Глобальная переменная для отсчета времени
HANDLE hMutex; // Мьютекс для защиты доступа к глобальной переменной
DWORD WINAPI stopwatch(LPVOID lpParam) // Функция для task18
{
    while (1)
    {
        Sleep(1000); // Задержка на 1 секунду
        WaitForSingleObject(hMutex, INFINITE); // Захватываем мьютекс
        seconds++; // Увеличиваем счетчик времени
        ReleaseMutex(hMutex); // Освобождаем мьютекс
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
        fprintf(stderr, "Ошибка при создании потока\n");
        return 1;
    }

    while (1) // Основной поток управления секундомером
    {
        WaitForSingleObject(hMutex, INFINITE); // Захватываем мьютекс
        printf("Секундомер: %d секунд\n", seconds); // Печатаем время
        ReleaseMutex(hMutex); // Освобождаем мьютекс
        Sleep(2000); // Задержка на 2 секунды
    }

    CloseHandle(hThread); // Закрываем дескриптор потока
    CloseHandle(hMutex); // Закрываем дескриптор мьютекса

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
        printf("Ошибка: неверное значение числа. Число должно быть >= 0\n");
        return 1;
    }

    int result = factorial(number);
    printf("Факториал числа %d равен %d\n", number, result);

    return 0;
}

int task19()
{
    int number;

    printf("Введите число: ");
    scanf("%d", &number);

    HANDLE threadHandle = CreateThread(NULL, 0, threadFunc, &number, 0, NULL);

    if (threadHandle == NULL)
    {
        printf("Ошибка при создании потока\n");
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

        MessageBoxW(NULL, buffer, L"Пример текста из файла", MB_OK | MB_ICONINFORMATION);
    }

    else
    {
        MessageBox(NULL, "Не удалось открыть файл", "Ошибка", MB_OK | MB_ICONERROR);
    }

    return 0;
}

int task21()
{
    FILE* file = fopen("external_process.c", "w");

    if (file == NULL)
    {
        printf("Ошибка при создании файла\n");
        return 1;
    }

    fprintf(file, "#include <stdio.h>\n\nint main() {\n");
    fprintf(file, "    printf(\"Привет, я сторонний процесс\");\n");
    fprintf(file, "    return 0;\n}\n");
    fclose(file);

    printf("Запуск стороннего процесса...\n");
    int result = system("gcc -o external_process external_process.c && ./external_process");

    if (result != 0)
    {
        printf("Ошибка при запуске стороннего процесса\n");
        return 1;
    }

    return 0;
}

int task22()
{
    DWORD fileAttributes = GetFileAttributesA("file.txt"); // Функция возвращает атрибуты файла

    if (fileAttributes != INVALID_FILE_ATTRIBUTES)
    {

        if (fileAttributes & FILE_ATTRIBUTE_HIDDEN)
        {
            printf("Файл скрыт\n");
        }

        if (fileAttributes & FILE_ATTRIBUTE_READONLY)
        {
            printf("Файл только для чтения\n");
        }
    }

    else
    {
        printf("Не удалось получить атрибуты файла\n");
    }

    HKEY hKey;
    LONG result = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft", 0, KEY_READ, &hKey); // Функция открывает раздел в реестре

    if (result == ERROR_SUCCESS)
    {
        printf("Раздел реестра успешно открыт\n");
    }

    else if (result == ERROR_FILE_NOT_FOUND)
    {
        printf("Раздел реестра не найден\n");
    }

    else
    {
        printf("Не удалось открыть раздел реестра\n");
    }

    HANDLE hMutex = CreateMutexA(NULL, FALSE, "MyMutex"); // Функция создает или открывает объект мьютекса

    if (hMutex != NULL)
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            printf("Мьютекс уже существует\n");
        }

        else
        {
            printf("Мьютекс успешно создан\n");
        }
    }
    else {
        printf("Не удалось создать мьютекс\n");
    }

    return 0;
}

typedef struct
{
    float x1, y1;
    float x2, y2;
} Point;

float calculateLength(Point p) // Функция для task23
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
        printf("Ошибка загрузки DLL\n");
        return 1;
    }

    CalculateLengthFunc calculateLength = (CalculateLengthFunc)GetProcAddress(dll, "calculateLength");

    if (calculateLength == NULL)
    {
        printf("Ошибка получения адреса функции\n");
        return 1;
    }

    Point p = { 1.0f, 2.0f, 4.0f, 6.0f };
    float length = calculateLength(p);

    printf("Длина отрезка: %f\n", length);
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
            printf("Ошибка при чтении из канала\n");
            break;
        }

        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            printf("Полученные данные: %s\n", buffer);

            char response[] = "Сообщение получено";
            DWORD bytesWritten;

            if (WriteFile(pipe, response, sizeof(response), &bytesWritten, NULL) == 0)
            {
                printf("Ошибка при записи в канал\n");
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
        printf("Ошибка при подключении к именованному каналу\n");
        return 1;
    }

    char message[] = "Привет, сервер!";
    if (WriteFile(pipe, message, sizeof(message), &bytesWritten, NULL) == 0) {
        printf("Ошибка при записи в канал\n");
        CloseHandle(pipe);
        return 1;
    }

    if (ReadFile(pipe1, buffer1, sizeof(buffer) - 1, &bytesRead1, NULL) != 0)
    {
        if (bytesRead1 > 0)
        {
            buffer1[bytesRead1] = '\0';
            printf("Ответ от сервера: %s\n", buffer1);
        }
        else
        {
            printf("Сервер закрыл соединение\n");
        }
    }
    else
    {
        printf("Ошибка при чтении из канала\n");
    }

    CloseHandle(pipe1);
    return 0;
}

int task26()
{
    FILE* file = fopen("bin.bin", "rb");

    if (file == NULL)
    {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    int number;
    fread(&number, sizeof(int), 1, file);

    fclose(file);

    printf("Считанное значение: %d\n", number);

    return 0;
}

int task27(int argc, char* argv[])
{
    printf("Аргументы из командной строки:\n");

    for (int i = 0; i < argc; i++) // Способ 1: Использование argc и argv

    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    char** ptr = argv; // Способ 2: Использование указателя на массив argv

    while (*ptr != NULL)
    {
        printf("arg: %s\n", *ptr);
        ptr++;
    }

    char* arg; // Способ 3: Использование альтернативной формы объявления argc и argv

    for (int i = 1; i < argc; i++)
    {
        arg = *(argv + i);
        printf("arg: %s\n", arg);
    }

    return 0;
}

DWORD WINAPI BackgroundProcess(LPVOID lpParam) // Создание фонового процесса для task30
{
    int counter = 0;

    while (1)
    {
        Sleep(5000); // Подождать 5 секунд
        counter++;
        char message[100];
        sprintf(message, "Значение счетчика: %d", counter);
        MessageBoxA(NULL, message, "Сообщение", MB_OK);
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
        printf("Ошибка создания потока\n");
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE); // Ждем, пока поток отработает

    CloseHandle(hThread);

    return 0;
}

int main()
{
    system("chcp 1251>nul");

    //task1();
    //task2();
    //task4(); // Задача сделана, но без функций WinApi
    //task5();
    //task6(); // Нажатая клавиша не соотвествует своему названию (всё норм)
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
;   //task27(3, "arg1", "arg2", "arg3", "arg4"); // Не работает
    //task30(); // Для вызова task30 необходимо закомментировать task6
}