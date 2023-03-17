// Светофор.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<conio.h>
#include<Windows.h>
#include <windows.system.h>
#include<stdlib.h>

using namespace std;

// RGB - (Red--Green--Blue)
int col[6][3] =
{​​
255,0,0, // red [0][0]
255,255,0, // yellow [0][1]
0,255,0, // green [0][2]

/* мигание */

196,30,58, // темнокрасный
255,191,0, // горчичный
3,192,60 // салатовый
}​​;

class MyRectangle
{​​
public:
int x, y;

MyRectangle();
~MyRectangle();

void Draw();
}​​;

MyRectangle::MyRectangle()
{​​
HWND hwnd = GetConsoleWindow();
RECT rt;

GetClientRect(hwnd, &rt);

x = (rt.right / 2);
y = (rt.bottom / 2);

DestroyWindow(hwnd); // Обязательное удаление открывшегося потока с данными

}​​;

MyRectangle::~MyRectangle()
{​​
cout << " / deleted /";
}​​;

void MyRectangle::Draw()
{​​
HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
HPEN hpen;
HBRUSH hbrush;

hpen = CreatePen(PS_SOLID, 2, RGB(105,105,105));
hbrush = CreateSolidBrush(RGB(105,105,105));

SelectObject(hdc, hpen);//взятие в инструменты пера
SelectObject(hdc, hbrush);//взятие в инструменты кисти
// вырисовывание фигуры
Rectangle(hdc, x-100, y-230, x+100,y+230);
/*
1)Координаты верхнего левого угла
2)Координаты нижнего правого угла
*/
DeleteDC(hdc);
DestroyWindow(hwnd);
//удаление потоков и инструментов

}​​;


class MyCircle // создание класса для дальнейшего обращения
{​​
public: // видимый доступ к данным

int x, y;// координаты
int cl, r; // cl - динамический цвет , r- радиус будущей окружности

MyCircle(int c);// конструктор с следующей за ним переменной c
~MyCircle();// диструктор

void turn_on();// функция включения
void turn_off();// функция выключения

}​​; // class MyCircle


MyCircle::MyCircle(int c)// заходим в сам конструктор
{​​
HWND hwnd = GetConsoleWindow(); // получение дескриптора экрана (функции, описывающей окно )
RECT rt; // просто прямоугольник с указателем на rt

GetClientRect(hwnd, &rt); // получение информации о прямоугольнике окна, и внесение данных в переменную rt

x = (rt.right / 2); // правый нижний угол прямоугольника
y = (rt.bottom / 2); //

// можно для левого верхнего угла : x=(rt/left/2);y=(rt.top/2)

// координаты середины
//отступы для размещения картинки посередине

r = 40;//радиус

cl = c; // преследующая перемменная

DestroyWindow(hwnd); // Обязательное удаление открывшегося потока с данными
}​​

MyCircle::~MyCircle()
{​​
cout << " / deleted / " << cl;
}​​// удаление и оповещение о месте удаления

void MyCircle::turn_on() // яркость цвета
{​​

if (cl >= 3)cl -= 3;// переход цвета

HWND hwnd = GetConsoleWindow(); // открытие потока информации об окне Windows
HDC hdc = GetDC(hwnd);// получение контекта дисплея для возможности рисования...

HPEN hpen;// обращение к дескриптору пера через указатель
HBRUSH hbrush;// обращение к дескриптору кисти через указатель

hpen = CreatePen(PS_SOLID, 2, RGB(col[cl][0], col[cl][1], col[cl][2]));
/* непосредственное создание пера
1)Его специфика(сплошная линия,прерывистая и т.д.
2)Толщина линии
3)Цвет (можно создавать по разному)
Для кисти только цвет...*/
hbrush = CreateSolidBrush(RGB(col[cl][0], col[cl][1], col[cl][2]));

SelectObject(hdc, hpen);//взятие в инструменты пера
SelectObject(hdc, hbrush);//взятие в инструменты кисти
// вырисовывание фигуры
Rectangle(hdc, x - sqrt(2)*r , y -sqrt(2) * r, x +sqrt(2) * r, y + sqrt(2) * r);

// черечение и мгновенная заливка
/*1) Дескриптор контекста дисплея
2,3) Координаты левого вернего угла
4,5) Ширина и длина прямоугольника, в который впишется эллипс(круг)
*/

DeleteObject(hbrush);
DeleteObject(hpen);
DeleteDC(hdc);
DestroyWindow(hwnd);
//удаление потоков и инструментов
}​​// turn_on

void MyCircle::turn_off() // приглушение цвета
{​​
cl += 3;// переход цвета

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

HPEN hpen;
HBRUSH hbrush;

hpen = CreatePen(PS_SOLID, 2, RGB(col[cl][0], col[cl][1], col[cl][2]));
hbrush = CreateSolidBrush(RGB(col[cl][0], col[cl][1], col[cl][2]));

SelectObject(hdc, hpen);
SelectObject(hdc, hbrush);
Rectangle(hdc, x - sqrt(2)*r , y -sqrt(2) * r, x +sqrt(2) * r, y + sqrt(2) * r);

DeleteObject(hbrush);
DeleteObject(hpen);
DeleteObject(hdc);
DeleteDC(hdc);

}​​//turn_off

class myTimer // создание класса таймер для живости картины
{​​
public:
int x, y;
int cl;

myTimer();
~myTimer();

void set(double t); // цифры в центрах окружностей

}​​;// myTimer

myTimer::myTimer()
{​​
HWND hwnd = GetConsoleWindow();
RECT rt;
GetClientRect(hwnd, &rt);

x = (rt.right / 2);
y = (rt.bottom / 2);

DestroyWindow(hwnd);

}​​//meTimer

myTimer::~myTimer()
{​​
cout << "\n /deleted/";
}​​

void myTimer::set(double t)
{​​

HWND hwnd = GetConsoleWindow();
HDC hdc;
HPEN hpen;

double del;
int m;

char s[20];

del = int(t / 9.0);

for (m = 9; m >= 0; m--)
{​​
_itoa_s(m, s, 10);
hdc = GetDC(hwnd);
SetBkMode(hdc, TRANSPARENT);// прозрачность прямоугольника при сииволе
SetTextColor(hdc, RGB(0, 0, 250)); // настройка цвета текста
TextOutA(hdc, x - 4, y - 5, s, strlen(s));// вывод текста

ReleaseDC(hwnd, hdc);/*
Функция ReleaseDC освобождает контекст устройства (DC), освобождая его для использования другими
приложениями. Эффект функции ReleaseDC зависит от типа постоянного тока.
Он освобождает только общие и оконные DCS. Это никак не влияет на классовые или частные DC.
*/

Sleep(int(del));// задержка между переходами

hdc = GetDC(hwnd);
SetBkMode(hdc, TRANSPARENT);
SetTextColor(hdc, RGB(col[cl][0], col[cl][1], col[cl][2]));

TextOutA(hdc, x - 4, y - 5, s, strlen(s));
ReleaseDC(hwnd, hdc);

}​​// for

DestroyWindow(hwnd);
}​​// set(double t)

void main() // основная функция , куда вставляем всю работу
{​​
setlocale(0, "Rus");

int z = 0;
MyRectangle a;
a.Draw();
MyCircle a1(0), a2(1), a3(2); // создание трех окружностей
myTimer tmr; // указатель на таймер

a1.y -= 150; // смещение кругов красный вниз
a3.y += 150; // зеленый вниз

a1.turn_on();
a2.turn_off();
a3.turn_off();

while (1) // бесконечный цикл работы светофора
{​​
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

for (int i = 1; i <= 5; i++)
{​​
Sleep(500);
a3.turn_on();
Sleep(500);
a3.turn_off();
}​​// for


a2.turn_on();
tmr.y = a2.y;
tmr.cl = a2.cl;
tmr.set(1000);

a2.turn_off();
a1.turn_on();

if (_kbhit()) {​​ z++; if (z == 1)break; }​​ // функция _khbit () при нажатии любой клавиши возвращает 1;

}​​//while

}​​//main
