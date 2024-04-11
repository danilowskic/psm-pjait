#include <iostream>
#include <cmath>
#include <vector>

#define M_PI 3.14159265358979323846

#define L 1.0
#define N 100
#define DX L / (N - 1)
#define DT 0.0001
#define T_MAX 10000

using std::vector;

std::string welcome = "*********************************************\n"
                      "***       CEZARY DANILOWSKI s25901        ***\n"
                      "***              RUCH STRUNY              ***\n"
                      "*********************************************";
                
double energiaPotencjalna(const vector<double>& y, double dx);
double energiaKinetyczna(const vector<double>& y, const vector<double>& vy, double dx);
double energiaCalkowita(const vector<double>& y, const vector<double>& vy, double dx);
vector<double> drugaPochodna(const vector<double>& y, double dx);

int main() 
{
    std::cout << welcome << std::endl << std::endl;

    vector<double> y(N);
    vector<double> vy(N);

    y[0] = y[N - 1] = 0.0;

    for (int i = 1; i < N - 1; i++) 
    {
        y[i] = sin(M_PI * i / (N - 1));
    }

    for (int step = 0; step < T_MAX; step++) 
    {
        vector<double> d2y = drugaPochodna(y, DX);

        // metoda MidPoint do rozwiązania równania ruchu
        for (int i = 1; i < N - 1; i++) 
        {
            double yMid = y[i] + 0.5 * vy[i] * DT;
            double vyMid = vy[i] + 0.5 * d2y[i] * DT;

            y[i] += vyMid * DT;
            vy[i] += d2y[i] * DT;
        }

        if (step % 100 == 0) 
        {
            std::cout << "KROK: " << step << ", ENERGIA POTENCJALNA: " << energiaPotencjalna(y, DX) << ", ENERGIA KINETYCZNA: " << energiaKinetyczna(y, vy, DX) << ", ENERGIA CALKOWITA: " << energiaCalkowita(y, vy, DX) << std::endl;
            //std::cout << step << ";" << energiaPotencjalna(y, DX) << ";" << energiaKinetyczna(y, vy, DX) << ";" << energiaCalkowita(y, vy, DX) << std::endl;
        }
    }

    return 0;
}

double energiaPotencjalna(const vector<double>& y, double dx) 
{
    double pe = 0.0;

    for (int i = 1; i < y.size() - 1; i++) 
    {
        pe += 0.5 * (y[i + 1] - y[i]) * (y[i + 1] - y[i]) * dx;
    }

    return pe;
}

double energiaKinetyczna(const vector<double>& y, const vector<double>& vy, double dx) 
{
    double ke = 0.0;

    for (int i = 0; i < y.size(); i++) 
    {
        ke += 0.5 * vy[i] * vy[i] * dx;
    }

    return ke;
}

double energiaCalkowita(const vector<double>& y, const vector<double>& vy, double dx) 
{
    return energiaKinetyczna(y, vy, dx) + energiaPotencjalna(y, dx);
}

vector<double> drugaPochodna(const vector<double>& y, double dx) 
{
    vector<double> d2y(y.size());
    d2y[0] = d2y[y.size() - 1] = 0.0;

    for (int i = 1; i < y.size() - 1; i++) 
    {
        d2y[i] = (y[i + 1] - 2.0 * y[i] + y[i - 1]) / (dx * dx);
    }

    return d2y;
}