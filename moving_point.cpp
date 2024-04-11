#include <iostream>
#include <cmath>
#include <ctime>

#define N 4 // variables number
#define H 0.01 // time step
#define TMAX 10.0 // end time
#define G 9.81 // gravity

double m; // weight
double q; // opus factor
int n = int(TMAX / H); // steps number

void calculateDerivatives(double t, double y[], double dydt[]);

int main() {
    q = (double)rand() / RAND_MAX;
    q = ((int) (q * 100)) / 100.0;

    double y[N], dydt[N], y1[N], dydt1[N], t;

    std::cout << "Podaj mase punktu: ";
    std::cin >> m;

    y[0] = 0.0; // x
    y[1] = 0.0; // y
    y[2] = 10.0; // vx
    y[3] = 10.0; // vy

    // For loop solves by Euler method
    for (int i = 0; i < n; i++) {
        t = i * H;

        calculateDerivatives(t, y, dydt);

        y1[0] = y[0] + H * dydt[0];
        y1[1] = y[1] + H * dydt[1];
        y1[2] = y[2] + H * dydt[2];
        y1[3] = y[3] + H * dydt[3];

        // For better Euler metchod
        calculateDerivatives(t + H, y1, dydt1);

        y[0] += 0.5 * H * (dydt[0] + dydt1[0]);
        y[1] += 0.5 * H * (dydt[1] + dydt1[1]);
        y[2] += 0.5 * H * (dydt[2] + dydt1[2]);
        y[3] += 0.5 * H * (dydt[3] + dydt1[3]);

        std::cout << "time step = " << t << ", x = " << y[0] << ", y = " << y[1] << std::endl;
    }

    return 0;
}

void calculateDerivatives(double t, double y[], double dydt[]) {
    dydt[0] = y[2];
    dydt[1] = y[3];
    dydt[2] = -q * y[2] / m;
    dydt[3] = -G - q * y[3] / m;
}