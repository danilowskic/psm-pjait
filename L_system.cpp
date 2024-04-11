#include <iostream>
#include <stack>
#include <cmath>

#define M_PI 3.14159265358979323846
#define ALPHA 25.0

int n;

struct Point 
{
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

std::stack<Point> stack;

std::string generateWord(const std::string& word);
void interpret(const std::string& word);

int main() 
{
    std::cout << "L-SYSTEM - CEZARY DANILOWSKI s25901" << std::endl << std::endl;
    std::cout << "Podaj liczbe n: ";
    std::cin >> n;

    std::string word = "X";

    for (int i = 0; i < n; i++) 
    {
        word = generateWord(word);
    }

    interpret(word);

    return 0;
}

std::string generateWord(const std::string& word) {
    std::string newWord;

    for (char c : word)
    {
        switch (c)
        {
            case 'X':
                newWord += "F+[[X]-X]-F[-FX]+X";
                break;
            case 'F':
                newWord += "FF";
                break;
            default:
                newWord += c;
                break;
        }
    }

    return newWord;
}

void interpret(const std::string& word)
{
    Point currentPosition(0, 0);
    Point newPosition;

    double currentAngle = 0;
    double newX, newY = 0;
    
    for (char character : word)
    {
        switch (character)
        {
            case 'F':
                newX = currentPosition.x + std::cos(currentAngle * M_PI / 180.0);
                newY = currentPosition.y + std::sin(currentAngle * M_PI / 180.0);

                newPosition.x = newX;
                newPosition.y = newY;

                std::cout << currentPosition.x << ";" << currentPosition.y << std::endl;

                currentPosition = newPosition;
                break;
            case '+':
                currentAngle += ALPHA;
                break;
            case '-':
                currentAngle -= ALPHA;
                break;
            case '[':
                stack.push(currentPosition);
                stack.push(Point{ currentAngle, 0.0 });
                break;
            case ']':
                currentAngle = stack.top().x;
                stack.pop();
                currentPosition = stack.top();
                stack.pop();

                std::cout << currentPosition.x << ", " << currentPosition.y << std::endl << std::endl;

                break;
        }
    }

    std::cout << std::endl << "Przekopiuj dane do Excela i zrob wykres" << std::endl;
}
