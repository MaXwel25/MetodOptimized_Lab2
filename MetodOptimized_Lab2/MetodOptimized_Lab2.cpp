#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "Metods.h"
using namespace std;


int main() {
    setlocale(LC_ALL, "ru");
    float min_gr = -3.0, max_gr = 7.0;
    double a, b, c;

    cout << "Введите коэффициент a: ";
    cin >> a;
    cout << "Введите коэффициент b: ";
    cin >> b;
    cout << "Введите коэффициент c: ";
    cin >> c;
    cout << "Выберите метод для которого нужно производить вычисления: " << endl;
    cout << "Метод Дихотомии - 1 " << endl;
    cout << "Метод золотого сечения - 2 " << endl;
    cout << "Метод Фибоначи - 3 " << endl;
    cout << "Введите цифру: ";
    int n;  cin >> n;
    if (n == 1)
        dichotomy_method(a, b, c, min_gr, max_gr);
    else if (n == 2)
        golden_section_method(a, b, c, min_gr, max_gr);
    else if (n == 3)
        fibonacci_method(a, b, c, min_gr, max_gr);
    else
    {
        cout << "Некорректный запрос";
        return 1;
    }
    return 0;
}