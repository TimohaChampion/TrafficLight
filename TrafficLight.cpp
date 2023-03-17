#include <iostream>
#include <conio.h>
#include< Windows.h>
#include<stdlib.h>
#include<windows.system.h>
using namespace std;
//Win
//Светофор ( Графика )
int col[6][3] =
{ 255,0,0,
 255,255,0,
0,255,0,
196,30,58,
255,191,0,
3,192,60,
};
class myCircle
{
public:
    int x, y;
    int cl, r;
    myCircle(int c);
    ~myCircle();
    void turn_on();
    void turn_off();
};// myCircle
myCircle::myCircle(int c)
{
    HWND hwnd = GetConsoleWindow();
    RECT rt;
    GetClientRect(hwnd, &rt);
x = (rt.right / 2);
y = (rt.bottom / 2);
//отступы для размещения картинки посередине
    r = 40;//радиус
cl = c;
    DestroyWindow(hwnd);
}
myCircle::~myCircle()
{
cout << "\n /deleted/" << cl; }// ~myCircle()
void myCircle::turn_on()
{
    if (cl >= 3)cl -= 3;
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

HPEN hpen;
HBRUSH hbrush;
hpen = CreatePen ( PS_SOLID, 2, RGB( col[cl][0], col[cl][1], col[cl][2]) ); hbrush = CreateSolidBrush( RGB(col[cl][0], col[cl][1], col[cl][2]) ); SelectObject(hdc, hpen);
SelectObject(hdc, hbrush);
    Ellipse(hdc, x - r, y - r, x + r, y + r);
    DeleteObject(hbrush);
    DeleteObject(hpen);
    DeleteDC(hdc);
    DestroyWindow(hwnd);
}// turn_on
void myCircle:: turn_off()
{
    cl += 3;
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    HPEN hpen;
    HBRUSH hbrush;
hpen = CreatePen(PS_SOLID, 2, RGB(col[cl][0], col[cl][1], col[cl][2])); hbrush = CreateSolidBrush(RGB(col[cl][0], col[cl][1], col[cl][2]));
    SelectObject(hdc, hpen);
    SelectObject(hdc, hbrush);
    Ellipse(hdc, x - r, y - r, x + r, y + r);
    DeleteObject(hbrush);
    DeleteObject(hpen);
    DeleteObject(hdc);
    DeleteDC(hdc);
}//turn_off
class myTimer
{
public:
    int x, y;
    int cl;
    myTimer();
    ~myTimer();
    void set(double t);
};// myTimer
myTimer:: myTimer()
{
    HWND hwnd = GetConsoleWindow();
    RECT rt;
    GetClientRect(hwnd, &rt);
x = (rt.right / 2); y = (rt.bottom / 2);
    DestroyWindow(hwnd);
}//meTimer

myTimer::~myTimer()
{
    cout << "\n /deleted/";
}
void myTimer::set(double t)
{
    HWND hwnd = GetConsoleWindow();
    HDC hdc;
    HPEN hpen;
    double del;
    int m;
char s[20];
    del = int(t / 9.0);
    for (m = 9;m >= 0;m--)
    {
        _itoa_s(m, s, 10);
        hdc = GetDC(hwnd);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 250));
        TextOutA(hdc, x - 4, y - 5, s, strlen(s));
        ReleaseDC(hwnd, hdc);
        Sleep(int(del));
        hdc = GetDC(hwnd);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(col[cl][0], col[cl][1], col[cl][2]));
        TextOutA(hdc, x - 4, y - 5, s, strlen(s));
        ReleaseDC(hwnd, hdc);
    }// for
    DestroyWindow(hwnd);
}// set(double t)
void main()
{  setlocale(0, "Rus");
int z=0;
myCircle a1(0), a2(1), a3(2);
myTimer tmr;
a1.y -= 100;
a3.y += 100;
a1.turn_on();
a2.turn_off();
a3.turn_off();
while (1) {
    tmr.y = a1.y;
    tmr.cl = a2.cl;

tmr.set(3000);
    a1.turn_off();
    a2.turn_on();
    tmr.y = a2.y;
    tmr.cl = a2.cl;
    tmr.set(1000);
    a2.turn_off();
    a3.turn_on();
    tmr.y = a3.y;
    tmr.cl = a3.cl;
    tmr.set(3000);
    for (int i = 1;i <= 5;i++)
    {
        Sleep(500);
        a3.turn_on();
        Sleep(500);
        a3.turn_off();
}// for
    a2.turn_on();
    tmr.y = a2.y;
    tmr.cl = a2.cl;
    tmr.set(1000);
    a2.turn_off();
    a1.turn_on();
if (_kbhit()) { z ++;if (z == 1)break; } }//while
}//main
