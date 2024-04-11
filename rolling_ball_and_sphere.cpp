#include <iostream>
#include <cmath>

#define G 9.81
#define DT 0.1
#define END_T 10
#define PI 3.14159265358979323846

double X0 = 0; // start location x
double Y0 = 0; // start location y
double velocityX0 = 10, velocityY0 = 5; // start velocity
double radius0;
double mass0;
double t = 0;

class Object {
public:
    double x, y; // location
    double velocityX, velocityY;
    double radius;
    double mass;

    Object(double x0, double y0, double vx0, double vy0, double r0, double m0) {
        x = x0;
        y = y0;
        velocityX = vx0;
        velocityY = vy0;
        radius = r0;
        mass = m0;
    }

    void move() {
        double accelerationX = -G * sin(angleOfRotation());
        double accelerationY = -G * cos(angleOfRotation());
        double vmid_x = velocityX + accelerationX * DT / 2;
        double vmid_y = velocityY + accelerationY * DT / 2;
        x += vmid_x * DT; // move by x
        y += vmid_y * DT; // move by y
        accelerationX = -G * sin(angleOfRotation()); // new acceleration by x
        accelerationY = -G * cos(angleOfRotation()); // new acceleration by y
        velocityX += accelerationX * DT;
        velocityY += accelerationY * DT;
    }

    double angleOfRotation() {
        return atan2(velocityY, velocityX);
    }

    double getRotX() {
        
    }
};

int main() {
    std::string objectType;
    std::cout << "Podaj typ obiektu [kula/sfera]: ";
    std::cin >> objectType;

    std::cout << "Podaj promien [m]: ";
    std::cin >> radius0;

    std::cout << "Podaj mase [kg]: ";
    std::cin >> mass0;

    if (objectType == "sfera")
        mass0 = mass0 * 4 / 3 * PI * pow(radius0, 3);

    Object obj(X0, Y0, velocityX0, velocityY0, radius0, mass0);

    while (t < END_T) {
        obj.move();
        t += DT;
        std::cout << "czas=" << t << " x=" << obj.x << " y=" << obj.y << " kat obrotu=" << obj.angleOfRotation() << std::endl;
    }

    return 0;
}