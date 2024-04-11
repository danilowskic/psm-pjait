#include <iostream>
#include <iomanip>
#include <cmath>

#define A 10.0
#define B 25.0
#define C 2.66 // 8/3
#define DT 0.03

double x = 1.0, y = 1.0, z = 1.0;

double dx(double x, double y);
double dy(double x, double y, double z);
double dz(double x, double y, double z);

void euler(double& x, double& y, double& z);
void midpoint(double& x, double& y, double& z);
void rk4(double& x, double& y, double& z);

int main() 
{
    std::cout << "EULER" << std::endl;

    for (double t = 0.0; t < 1.0; t += DT)
    {
        euler(x, y, z);

        std::cout << x << " " << y << " " << z << std::endl;
    }

    std::cout << std::endl;

    x = 1.0;
    y = 1.0;
    z = 1.0;

    std::cout << "MIDPOINT" << std::endl;

    for (double t = 0.0; t < 10.0; t += DT) {
        midpoint(x, y, z);

        std::cout << x << " " << y << " " << z << std::endl;
    }

    std::cout << std::endl;

    x = 1.0;
    y = 1.0;
    z = 1.0;

    std::cout << "RK4" << std::endl;

    for (double t = 0.0; t < 10.0; t += DT) {
        rk4(x, y, z);

        std::cout << x << " " << y << " " << z << std::endl;
    }

    std::cout << std::endl;

    return 0;
}

double dx(double x, double y)
{
    return A * y - A * x;
}

double dy(double x, double y, double z)
{
    return -x * z + B * x - y;
}

double dz(double x, double y, double z)
{
    return x * y - C * z;
}

void euler(double& x, double& y, double& z)
{
    double x1 = x + DT * dx(x, y);
    double y1 = y + DT * dy(x, y, z);
    double z1 = z + DT * dz(x, y, z);

    x = x1;
    y = y1;
    z = z1;
}

void midpoint(double& x, double& y, double& z)
{
    double x_half = x + 0.5 * DT * dx(x, y);
    double y_half = y + 0.5 * DT * dy(x, y, z);
    double z_half = z + 0.5 * DT * dz(x, y, z);

    double x1 = x + DT * dx(x_half, y_half);
    double y1 = y + DT * dy(x_half, y_half, z_half);
    double z1 = z + DT * dz(x_half, y_half, z_half);

    x = x1;
    y = y1;
    z = z1;
}

void rk4(double& x, double& y, double& z)
{
    double k1x = DT * dx(x, y);
    double k1y = DT * dy(x, y, z);
    double k1z = DT * dz(x, y, z);

    double k2x = DT * dx(x + 0.5 * k1x, y + 0.5 * k1y);
    double k2y = DT * dy(x + 0.5 * k1x, y + 0.5 * k1y, z + 0.5 * k1z);
    double k2z = DT * dz(x + 0.5 * k1x, y + 0.5 * k1y, z + 0.5 * k1z);

    double k3x = DT * dx(x + 0.5 * k2x, y + 0.5 * k2y);
    double k3y = DT * dy(x + 0.5 * k2x, y + 0.5 * k2y, z + 0.5 * k2z);
    double k3z = DT * dz(x + 0.5 * k2x, y + 0.5 * k2y, z + 0.5 * k2z);

    double k4x = DT * dx(x + k3x, y + k3y);
    double k4y = DT * dy(x + k3x, y + k3y, z + k3z);
    double k4z = DT * dz(x + k3x, y + k3y, z + k3z);

    double x1 = x + (1.0 / 6.0) * (k1x + 2 * k2x + 2 * k3x + k4x);
    double y1 = y + (1.0 / 6.0) * (k1y + 2 * k2y + 2 * k3y + k4y);
    double z1 = z + (1.0 / 6.0) * (k1z + 2 * k2z + 2 * k3z + k4z);

    x = x1;
    y = y1;
    z = z1;
}
