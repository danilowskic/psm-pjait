#include <iostream>
#include <cmath>

#define G 6.6743e-11
#define SUN_MASS 1.9891e30
#define EARTH_MASS 5.9722e24
#define MOON_MASS 7.342e22
#define DISTANCE_SE 1.49597870691e11
#define DISTANCE_EM 3.844e8
#define VELOCITY_SE 29783.0
#define DT 86400.0

double d2(double r);
double d2_e(double r);
double d2_m(double r);

int main() {
    double x_earth = 0.0, y_earth = DISTANCE_SE, vx_earth = -VELOCITY_SE, vy_earth = 0.0; // Położenie i prędkość Ziemi wokół Słońca
    double x_moon = DISTANCE_EM, y_moon = 0.0, vx_moon = 0.0, vy_moon = 1022.0; // Położenie i prędkość Księżyca względem Ziemi

    double t_max = 31536000.0; // rok w sekundach
    int n_steps = t_max / DT; // Liczba kroków czasowych

    for (int i = 0; i < n_steps; ++i) {
        double d2_et = d2_e(sqrt(pow(x_earth, 2) + pow(y_earth, 2)));
        double ax_earth = -d2_et * x_earth / sqrt(pow(x_earth, 2) + pow(y_earth, 2));
        double ay_earth = -d2_et * y_earth / sqrt(pow(x_earth, 2) + pow(y_earth, 2));
        vx_earth += ax_earth * DT;
        vy_earth += ay_earth * DT;
        x_earth += vx_earth * DT;
        y_earth += vy_earth * DT;

        // Obliczanie nowych prędkości i położeń Księżyca względem Ziemi
        double d2_mt = d2_m(sqrt(pow(x_moon - x_earth, 2) + pow(y_moon - y_earth, 2)));
        double ax_moon = -d2_mt * (x_moon - x_earth) / sqrt(pow(x_moon - x_earth, 2) + pow(y_moon - y_earth, 2));
        double ay_moon = -d2_mt * (y_moon - y_earth) / sqrt(pow(x_moon - x_earth, 2) + pow(y_moon - y_earth, 2));
        vx_moon += ax_moon * DT;
        vy_moon += ay_moon * DT;
        x_moon += vx_moon * DT;
        y_moon += vy_moon * DT;

        std::cout << "Ksiezyc: x=" << x_moon << " m, y=" << y_moon << " m" << std::endl;
        std::cout << "Ziemia: x=" << x_earth << " m, y=" << y_earth << " m" << std::endl << std::endl;
    }

    return 0;
}

double d2(double r) {
    return G * SUN_MASS / pow(r, 2); // Przyspieszenie grawitacyjne
}

double d2_e(double r) {
    return G * SUN_MASS / pow(r, 2) + pow(VELOCITY_SE, 2) / pow(DISTANCE_SE, 2); // Przyspieszenie grawitacyjne Ziemi wokół Słońca
}

double d2_m(double r) {
    return G * EARTH_MASS / pow(r, 2); // Przyspieszenie grawitacyjne Księżyca wokół Ziemi
}