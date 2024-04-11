#include <iostream>
#include <cmath>

#define G 9.81 // gravity
#define DT 0.01 // time step
#define TMAX 10.0 // end time

std::string welcome = "(1) METODA EULERA\n(2) METODA EULERA ULEPSZONA\n(3) METODA RUNGE KUTTA";

double l; // length
int choice;

double f(double alpha);
void euler(); // euler method
void eulerBetter(); // better euler method
void rungeKutta(); // RK4

int main()
{
    std::cout << "Podaj dlugosc wahadla [m]: ";
    std::cin >> l;
    
    std::cout << welcome << std::endl << std::endl;
    std::cout << "Wybierz metode numeryczna, cyfra od 1 do 3: ";
    std::cin >> choice;

    std::cout << std::endl;

    if (choice == 1)
        euler();
    else
    {
        if (choice == 2)
            eulerBetter();
        else
            rungeKutta();
    }

    std::cout << std::endl;

    return 0;
}

double f(double alpha)
{
    return -G / l * sin(alpha);
}

void euler()
{
    double alpha = 1.0;   // initial angle [radians]
    double omega = 0.0;   // initial angular velocity [radians/s]

    for (double t = 0.0; t <= TMAX; t += DT)
    {
        double alpha_new = alpha + omega * DT;
        double omega_new = omega + f(alpha) * DT;

        alpha = alpha_new;
        omega = omega_new;

        std::cout << "time step = " << t << ", angle = " << alpha << ", angular velocity = " << omega << std::endl;
    }
}

void eulerBetter()
{
    double alpha = 1.0;   // initial angle [radians]
    double omega = 0.0;   // initial angular velocity [radians/s]

    for (double t = 0.0; t <= TMAX; t += DT)
    {
        omega += f(alpha) * DT;
        alpha += omega * DT;

        //std::cout << "time step = " << t << ", angle = " << alpha << ", angular velocity = " << omega << std::endl;
        std::cout << alpha << ";" << omega << std::endl;
    }
}

void rungeKutta()
{
    double alpha = 1.0;   // initial angle [radians]
    double omega = 0.0;   // initial angular velocity [radians/s]

    for (double t = 0.0; t <= TMAX; t += DT)
    {
        double k1_alpha = omega;
        double k1_omega = f(alpha);
        double k2_alpha = omega + k1_omega * DT / 2;
        double k2_omega = f(alpha + k1_alpha * DT / 2);
        double k3_alpha = omega + k2_omega * DT / 2;
        double k3_omega = f(alpha + k2_alpha * DT / 2);
        double k4_alpha = omega + k3_omega * DT;
        double k4_omega = f(alpha + k3_alpha * DT);

        alpha += (k1_alpha + 2 * k2_alpha + 2 * k3_alpha + k4_alpha) * DT / 6;
        omega += (k1_omega + 2 * k2_omega + 2 * k3_omega + k4_omega) * DT / 6;

        //std::cout << "time step = " << t << ", angle = " << alpha << ", angular velocity = " << omega << std::endl;
        std::cout << alpha << ";" << omega << std::endl;

    }
}