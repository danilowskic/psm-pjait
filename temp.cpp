/**
    @author Cezary Daniłowski
    @index s25901
    @method Gaus-Seidel

    Program oblicza rozkład temperatury płytki o rozmiarach 41 na 41 rozgrzanej różnymi temperaturami z każdej strony.
    Graficzna interpretacja w pliku graficznym rozklad_temperatury.png
*/
#include <iostream>
#include <cmath>

#define N 41
#define H 0.025
#define MAX_ITER 10000
#define EPSILON 0.00001

double T[N][N];

void setBoundryConditions();
void solveGaussSeidel();

int main() 
{
    setBoundryConditions();
    solveGaussSeidel();

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
            std::cout << T[i][j] << ";";

        std::cout << std::endl;
    }

    return 0;
}

void setBoundryConditions()
{
    for (int i = 0; i < N; i++)
        T[0][i] = 150.0;
    
    for (int i = 0; i < N; i++)
        T[i][0] = 100.0;

    for (int i = 0; i < N; i++) 
        T[N - 1][i] = 200.0;
    
    for (int i = 0; i < N; i++)
        T[i][N - 1] = 50.0;
}

void solveGaussSeidel()
{
    for (int k = 0; k < MAX_ITER; k++) 
    {
        double max_error = 0.0;

        for (int i = 1; i < N - 1; i++) 
        {
            for (int j = 1; j < N - 1; j++) 
            {
                double T_old = T[i][j];
                T[i][j] = 0.25 * (T[i - 1][j] + T[i + 1][j] + T[i][j - 1] + T[i][j + 1]);

                double error = abs(T[i][j] - T_old);

                if (error > max_error)
                    max_error = error;
            }
        }

        if (max_error < EPSILON)
            break;
    }
}