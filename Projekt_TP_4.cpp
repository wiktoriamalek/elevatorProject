#include "framework.h"
#include "Resource.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

HWND hwndButton;
std::vector <HWND> hWndHumanCount;
std::vector <int> cnt;
std::vector <HWND> hWndElevatorCount;
std::vector <int> elevCnt;

struct human {
    int start = -1;
    int destination = -1;
    int inside = -1;
};

std::vector <human> humans;

int X = 100;
int Y = 100;
int W = 2000;
int H = 900;

RECT drawArea = { X, Y, W, H };

int level = 4;
int movement = -1;
int j = 0;
int weight = 0;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void humanCounter(int change, int i, std::vector <int> &counter, std::vector <HWND> &handler){
    counter[i] += change;

    if (counter[i] < 0)
        counter[i] = 0;

    char buff[10];
    _itoa_s(counter[i], buff, 10, 10);
    LPSTR n = buff;
    SetWindowTextA(handler[i], n);
}

void showHuman(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen1, int i) {
    if (humans[i].start >= 0 && humans[i].destination >= 0)
    {
        if (humans[i].start % 2 == 0)
            graphics.DrawRectangle(&pen1, X + 290 + humans[i].destination * 60, Y + 80 + (4 - humans[i].start) * 150, 50, 75);
        else
            graphics.DrawRectangle(&pen1, X + 960 + humans[i].destination * 60, Y + 80 + (4 - humans[i].start) * 150, 50, 75);
    }
}

void hopIn(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen1, Gdiplus::Pen &pen2, int i) {
    if (humans[i].start == 4 - level and movement == -1 and weight + 70 < 600) {
        weight = weight + 70;

        if (humans[i].start == 0) {
            if (humans[i].destination == 1)
                humanCounter(-1, 0, cnt, hWndHumanCount);
            else if (humans[i].destination == 2)
                humanCounter(-1, 1, cnt, hWndHumanCount);
            else if (humans[i].destination == 3)
                humanCounter(-1, 2, cnt, hWndHumanCount);
            else if (humans[i].destination == 4)
                humanCounter(-1, 3, cnt, hWndHumanCount);
        }
        else if (humans[i].start == 1) {
            if (humans[i].destination == 0)
                humanCounter(-1, 4, cnt, hWndHumanCount);
            else if (humans[i].destination == 2)
                humanCounter(-1, 5, cnt, hWndHumanCount);
            else if (humans[i].destination == 3)
                humanCounter(-1, 6, cnt, hWndHumanCount);
            else if (humans[i].destination == 4)
                humanCounter(-1, 7, cnt, hWndHumanCount);
        }
        else if (humans[i].start == 2) {
            if (humans[i].destination == 0)
                humanCounter(-1, 8, cnt, hWndHumanCount);
            else if (humans[i].destination == 1)
                humanCounter(-1, 9, cnt, hWndHumanCount);
            else if (humans[i].destination == 3)
                humanCounter(-1, 10, cnt, hWndHumanCount);
            else if (humans[i].destination == 4)
                humanCounter(-1, 11, cnt, hWndHumanCount);
        }
        else if (humans[i].start == 3) {
            if (humans[i].destination == 0)
                humanCounter(-1, 12, cnt, hWndHumanCount);
            else if (humans[i].destination == 1)
                humanCounter(-1, 13, cnt, hWndHumanCount);
            else if (humans[i].destination == 2)
                humanCounter(-1, 14, cnt, hWndHumanCount);
            else if (humans[i].destination == 4)
                humanCounter(-1, 15, cnt, hWndHumanCount);
        }
        else if (humans[i].start == 4) {
            if (humans[i].destination == 0)
                humanCounter(-1, 16, cnt, hWndHumanCount);
            else if (humans[i].destination == 1)
                humanCounter(-1, 17, cnt, hWndHumanCount);
            else if (humans[i].destination == 2)
                humanCounter(-1, 18, cnt, hWndHumanCount);
            else if (humans[i].destination == 3)
                humanCounter(-1, 19, cnt, hWndHumanCount);
        }

        if (humans[i].destination == 0)
            humanCounter(1, 0, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 1)
            humanCounter(1, 1, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 2)
            humanCounter(1, 2, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 3)
            humanCounter(1, 3, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 4)
            humanCounter(1, 4, elevCnt, hWndElevatorCount);

        if (humans[i].start % 2 == 0) {
            graphics.DrawRectangle(&pen2, X + 290 + humans[i].destination * 60, Y + 80 + level * 150, 50, 75);
            graphics.DrawRectangle(&pen1, X + 620 + humans[i].destination * 60, Y + 80 + level * 150, 50, 75);
        }
        else {
            graphics.DrawRectangle(&pen2, X + 960 + humans[i].destination * 60, Y + 80 + level * 150, 50, 75);
            graphics.DrawRectangle(&pen1, X + 620 + humans[i].destination * 60, Y + 80 + level * 150, 50, 75);
        }

        humans[i].start = -1;
        humans[i].inside = 1;
    }

}

void hopOut(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen1, Gdiplus::Pen& pen2, int i) {
    if (humans[i].destination == 4 - level and humans[i].inside == 1) {
        if (humans[i].destination % 2 == 0) {
            graphics.DrawRectangle(&pen2, X + 620 + humans[i].destination, Y + 10 + level * 150, 50, 75);
            graphics.DrawRectangle(&pen1, X + 290 + humans[i].destination * 60, Y + 10 + level * 150, 50, 75);
        }
        else {
            graphics.DrawRectangle(&pen2, X + 620 + humans[i].destination, Y + 10 + level * 150, 50, 75);
            graphics.DrawRectangle(&pen1, X + 960 + humans[i].destination * 60, Y + 10 + level * 150, 50, 75);
        }

        if (humans[i].destination == 0)
            humanCounter(-1, 0, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 1)
            humanCounter(-1, 1, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 2)
            humanCounter(-1, 2, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 3)
            humanCounter(-1, 3, elevCnt, hWndElevatorCount);
        else if (humans[i].destination == 4)
            humanCounter(-1, 4, elevCnt, hWndElevatorCount);

        weight = weight - 70;

        humans[i].inside = -1;
        humans[i].destination = -1;

        if (humans.size() > i + 1)
            humans.erase(humans.begin() + i);
    }
}

void ride(Gdiplus::Graphics &graphics, Gdiplus::Pen &pen1, int i) {
    if (humans[i].inside > -1) {
        graphics.DrawRectangle(&pen1, X + 620 + humans[i].destination * 60, Y + 80 + level * 150, 50, 75);
    }
}

void elevatorPaint(HDC hdc, int level) {
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
    Gdiplus::Pen pen1(Gdiplus::Color(255, 0, 0, 255));
    Gdiplus::Pen pen2(Gdiplus::Color(255, 255, 255, 255));

    graphics.DrawRectangle(&pen, X + 590, Y, 360, 770);

    graphics.DrawLine(&pen, X + 590 - 300, Y + 150 + 10, X + 590, Y + 150 + 10);
    graphics.DrawLine(&pen, X + 350 + 600, Y + 2 * 150 + 10, X + 350 + 600 + 300, Y + 2 * 150 + 10);
    graphics.DrawLine(&pen, X + 590 - 300, Y + 3 * 150 + 10, X + 590, Y + 3 * 150 + 10);
    graphics.DrawLine(&pen, X + 350 + 600, Y + 4 * 150 + 10, X + 350 + 600 + 300, Y + 4 * 150 + 10);
    graphics.DrawLine(&pen, X + 590 - 300, Y + 5 * 150 + 10, X + 590, Y + 5 * 150 + 10);

    graphics.DrawRectangle(&pen, X + 600, Y + level * 150 + 10, 340, 150);
    MoveWindow(hWndElevatorCount[0], X + 630, Y + 100 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[1], X + 630 + 60, Y + 100 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[2], X + 630 + 2 * 60, Y + 100 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[3], X + 630 + 3 * 60, Y + 100 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[4], X + 630 + 4 * 60, Y + 100 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[5], X + 630, Y + 50 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[6], X + 630 + 60, Y + 50 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[7], X + 630 + 2 * 60, Y + 50 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[8], X + 630 + 3 * 60, Y + 50 + level * 150, 30, 30, false);
    MoveWindow(hWndElevatorCount[9], X + 630 + 4 * 60, Y + 50 + level * 150, 30, 30, false);

    for (int i = 0; i < signed(humans.size()); i++) {
        showHuman(graphics, pen1, i);

        hopIn(graphics, pen1, pen2, i);

        hopOut(graphics, pen1, pen2, i);

        ride(graphics, pen1, i);
    }
}

void repaintElevatorWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int level) {
    if (drawArea == NULL)
        InvalidateRect(hWnd, NULL, TRUE);
    else
        InvalidateRect(hWnd, drawArea, TRUE);

    hdc = BeginPaint(hWnd, &ps);
    elevatorPaint(hdc, level);
    EndPaint(hWnd, &ps);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJEKTTP4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    for (int i = 0; i < 20; i++)
        hWndHumanCount.push_back(nullptr);

    for (int i = 0; i < 20; i++)
        cnt.push_back(0);

    for (int i = 0; i < 10; i++)
        hWndElevatorCount.push_back(nullptr);

    for (int i = 0; i < 5; i++)
        elevCnt.push_back(0);

    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJEKTTP4));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJEKTTP4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJEKTTP4);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    hwndButton = CreateWindow(TEXT("button"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X, Y + 80, 50, 50, hWnd, (HMENU)ID_BUTTON2, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 50, Y + 80, 50, 50, hWnd, (HMENU)ID_BUTTON3, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 2 * 50, Y + 80, 50, 50, hWnd, (HMENU)ID_BUTTON4, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 3 * 50, Y + 80, 50, 50, hWnd, (HMENU)ID_BUTTON5, hInstance, nullptr);

    hwndButton = CreateWindow(TEXT("button"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 1300, Y + 80 + 150, 50, 50, hWnd, (HMENU)ID_BUTTON6, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 50 + 1300, Y + 80 + 150, 50, 50, hWnd, (HMENU)ID_BUTTON7, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 2 * 50 + 1300, Y + 80 + 150, 50, 50, hWnd, (HMENU)ID_BUTTON8, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 3 * 50 + 1300, Y + 80 + 150, 50, 50, hWnd, (HMENU)ID_BUTTON9, hInstance, nullptr);

    hwndButton = CreateWindow(TEXT("button"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X, Y + 80 + 2 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON10, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 50, Y + 80 + 2 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON11, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 2 * 50, Y + 80 + 2 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON12, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 3 * 50, Y + 80 + 2 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON13, hInstance, nullptr);

    hwndButton = CreateWindow(TEXT("button"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 1300, Y + 80 + 3 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON14, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 50 + 1300, Y + 80 + 3 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON15, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 2 * 50 + 1300, Y + 80 + 3 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON16, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 3 * 50 + 1300, Y + 80 + 3 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON17, hInstance, nullptr);

    hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X, Y + 80 + 4 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON18, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 50, Y + 80 + 4 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON19, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 2 * 50, Y + 80 + 4 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON20, hInstance, nullptr);
    hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTER, X + 3 * 50, Y + 80 + 4 * 150, 50, 50, hWnd, (HMENU)ID_BUTTON21, hInstance, nullptr);

    CreateWindow(TEXT("static"), TEXT("1."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 60, Y + 50 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("2."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 2 * 60, Y + 50 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("3."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 3 * 60, Y + 50 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("4."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 4 * 60, Y + 50 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndHumanCount[0] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 60, Y + 100 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[1] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 2 * 60, Y + 100 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[2] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 3 * 60, Y + 100 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[3] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 4 * 60, Y + 100 + 4 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    CreateWindow(TEXT("static"), TEXT("0."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970, Y + 50 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("2."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 2 * 60, Y + 50 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("3."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 3 * 60, Y + 50 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("4."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 4 * 60, Y + 50 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndHumanCount[4] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970, Y + 100 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[5] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 2 * 60, Y + 100 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[6] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 3 * 60, Y + 100 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[7] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 4 * 60, Y + 100 + 3 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    CreateWindow(TEXT("static"), TEXT("0."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300, Y + 50 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("1."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 60, Y + 50 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("3."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 3 * 60, Y + 50 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("4."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 4 * 60, Y + 50 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndHumanCount[8] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300, Y + 100 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[9] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 60, Y + 100 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[10] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 3 * 60, Y + 100 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[11] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 4 * 60, Y + 100 + 2 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    CreateWindow(TEXT("static"), TEXT("0."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970, Y + 50 + 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("1."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 1 * 60, Y + 50 + 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("2."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 2 * 60, Y + 50 + 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("4."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 4 * 60, Y + 50 + 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndHumanCount[12] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970, Y + 100 + 1 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[13] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 60, Y + 100 + 1 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[14] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 2 * 60, Y + 100 + 1 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[15] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 970 + 4 * 60, Y + 100 + 1 * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    CreateWindow(TEXT("static"), TEXT("0."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300, Y + 50, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("1."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 60, Y + 50, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("2."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 2 * 60, Y + 50, 30, 30, hWnd, nullptr, nullptr, nullptr);
    CreateWindow(TEXT("static"), TEXT("3."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 3 * 60, Y + 50, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndHumanCount[16] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300, Y + 100, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[17] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 60, Y + 100, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[18] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 2 * 60, Y + 100, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndHumanCount[19] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 300 + 3 * 60, Y + 100, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndElevatorCount[5] = CreateWindow(TEXT("static"), TEXT("0."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630, Y + 50 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[6] = CreateWindow(TEXT("static"), TEXT("1."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 60, Y + 50 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[7] = CreateWindow(TEXT("static"), TEXT("2."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 2 * 60, Y + 50 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[8] = CreateWindow(TEXT("static"), TEXT("3."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 3 * 60, Y + 50 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[9] = CreateWindow(TEXT("static"), TEXT("4."), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 4 * 60, Y + 50 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    hWndElevatorCount[0] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630, Y + 100 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[1] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 60, Y + 100 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[2] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 2 * 60, Y + 100 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[3] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 3 * 60, Y + 100 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);
    hWndElevatorCount[4] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, X + 630 + 4 * 60, Y + 100 + level * 150, 30, 30, hWnd, nullptr, nullptr, nullptr);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    human h;

    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    int highest = 0;

    switch (message) {
    case WM_CREATE:
    {
        SetTimer(hWnd, Timer1, 1000, nullptr);
        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_COMMAND:
    {
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break; 
        case ID_BUTTON2:
            h.start = 4;
            h.destination = 0;
            humans.push_back(h);
            humanCounter(1, 16, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON3:
            h.start = 4;
            h.destination = 1;
            humans.push_back(h);
            humanCounter(1, 17, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON4:
            h.start = 4;
            h.destination = 2;
            humans.push_back(h);
            humanCounter(1, 18, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON5:
            h.start = 4;
            h.destination = 3;
            humans.push_back(h);
            humanCounter(1, 19, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON6:
            h.start = 3;
            h.destination = 0;
            humans.push_back(h);
            humanCounter(1, 12, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON7:
            h.start = 3;
            h.destination = 1;
            humans.push_back(h);
            humanCounter(1, 13, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON8:
            h.start = 3;
            h.destination = 2;
            humans.push_back(h);
            humanCounter(1, 14, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON9:
            h.start = 3;
            h.destination = 4;
            humans.push_back(h);
            humanCounter(1, 15, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON10:
            h.start = 2;
            h.destination = 0;
            humans.push_back(h);
            humanCounter(1, 8, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON11:
            h.start = 2;
            h.destination = 1;
            humans.push_back(h);
            humanCounter(1, 9, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON12:
            h.start = 2;
            h.destination = 3;
            humans.push_back(h);
            humanCounter(1, 10, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON13:
            h.start = 2;
            h.destination = 4;
            humans.push_back(h);
            humanCounter(1, 11, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON14:
            h.start = 1;
            h.destination = 0;
            humans.push_back(h);
            humanCounter(1, 4, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON15:
            h.start = 1;
            h.destination = 2;
            humans.push_back(h);
            humanCounter(1, 5, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON16:
            h.start = 1;
            h.destination = 3;
            humans.push_back(h);
            humanCounter(1, 6, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON17:
            h.start = 1;
            h.destination = 4;
            humans.push_back(h);
            humanCounter(1, 7, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON18:
            h.start = 0;
            h.destination = 1;
            humans.push_back(h);
            humanCounter(1, 0, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON19:
            h.start = 0;
            h.destination = 2;
            humans.push_back(h);
            humanCounter(1, 1, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON20:
            h.start = 0;
            h.destination = 3;
            humans.push_back(h);
            humanCounter(1, 2, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        case ID_BUTTON21:
            h.start = 0;
            h.destination = 4;
            humans.push_back(h);
            humanCounter(1, 3, cnt, hWndHumanCount);
            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        elevatorPaint(hdc, 4);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_TIMER:
        switch (wParam) 
        {
            case Timer1:
                for (int i = 0; i < signed(humans.size()); i++) {
                    if (humans[i].start > highest) {
                        highest = humans[i].start;
                    }
                }
                for (int i = 0; i < signed(humans.size()); i++) {
                    if (humans[i].inside == 1 and humans[i].destination > 4 - level) {
                        movement = 1;
                    }
                }
                for (int i = 0; i < signed(humans.size()); i++) {
                    if (humans[i].inside == 1 and humans[i].destination < 4 - level) {
                        movement = -1;
                    }
                }
                j = 0;
                for (int i = 0; i < signed(humans.size()); i++) {
                    if (humans[i].inside == -1) {
                        j = j + 1;
                    }
                }
                if (highest > 0 and highest > 4 - level and (j == signed(humans.size()) or level == 4)) {
                    movement = 1;
                }
                if (j == signed(humans.size()) and highest < 4 - level) {
                    movement = -1;
                }
                if (movement == 1 and 4 - level < 4) {
                    level = level - 1;
                }
                if (movement == -1 and 4 - level > 0) {
                    level = level + 1;
                }
                if (highest == 4 - level) {
                    movement = -1;
                    highest = 0;
                }

            repaintElevatorWindow(hWnd, hdc, ps, &drawArea, level);
            SetTimer(hWnd, Timer1, 1000, nullptr);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}