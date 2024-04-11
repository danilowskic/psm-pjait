#include <iostream>
#include <cmath>
#define PI 3.14159265358979323846

using std::cout;
using std::endl;
using std::cin;

const std::string welcome =
"*************************************************************\n" 
"**                                                         **\n"
"**          FUNKCJA SIN - CEZARY DANILOWSKI s25901         **\n"
"**                                                         **\n"
"*************************************************************";

int unit;
double angle;
double copyAngle;
std::string unit2;

double transformToRadians(double value);
long factorial(int value);
double standarize(double x);
double mySinus(double angle);

int main()
{
    cout << welcome << endl << endl;
    cout << "(1) stopnie" << endl;
    cout << "(2) radiany" << endl;

    cout << "Wybierz jednoste kata: ";
    cin >> unit;

    cout << "Podaj kat (jesli wybrano w radianach podaj go w postaci ulamka dziesietnego): ";
    cin >> angle;
    copyAngle = angle;

    if (unit == 1)
    {
        angle = transformToRadians(angle);
        unit2 = "stopni";
    }
    else
    {
        unit2 = "pi";
    }

    angle = standarize(angle);

    double sinValue = mySinus(angle);

    cout << "Moj sinus: sin(" << copyAngle << " " << unit2 << ") = " << sinValue << endl;

    double sinLibrary = sin(angle);
    cout << "Biblioteki sinus: sin(" << copyAngle << " " << unit2 << ") = " << sinLibrary << endl;

    double absolute = (sinLibrary - sinValue) < 0 ? (sinLibrary - sinValue) * (-1) : sinLibrary - sinValue;

    cout << "Blad bezwzgledny przyblizenia wynosi " << absolute << endl;
}

double transformToRadians(double value)
{
    double x = value * PI * 2;
    double y = x / 360;

    return y;
}

double standarize(double x)
{
    if (x > 0.5 && x <= 1.0)
        x = 1 - x;
    else if (x > 1 && x <= 1.5)
        x = x - 1;
    else if (x > 1.5 && x < 2)
        x = 2 - x;
    else if (x > 2)
    {   
        int asInt = (int) x;

        if (asInt % 2 == 0)
            x = x - asInt;
        else
            x = x - asInt + 1;
    }

    return x * PI;
}

long factorial(int value)
{                          
    if (value == 0)
        return 1;
    else
        return value * factorial(value - 1);
}

double mySinus(double x)
{
    double result = 0;

    for (int i = 0; i < 10; i++)
    {
        double a = pow(-1, i);

        result += a * pow(x, 2 * i + 1) / factorial(2 * i + 1);
    }

    return result;
}