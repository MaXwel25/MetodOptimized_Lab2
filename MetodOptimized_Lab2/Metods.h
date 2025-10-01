#pragma once
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long double function_main(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

void dichotomy_method(double a, double b, double c, double min_gr, double max_gr, long double epsilon) {
    cout << endl <<"Метод Дихотомии" << endl;

    // объявляем границы здесь, чтобы не вызывать их каждый раз как параметр функции
    double left = min_gr;
    double right = max_gr;

    long double delta = epsilon / (right - left); // малый параметр
    int it = 0; // количество итераций
    int count = 0; // если нужно подсчитать сложность алгоритма

    cout << "Начальный отрезок: [" << left << ", " << right << "]" << endl;
    cout << "Точность: " << epsilon << endl;
    cout << "Дельта: " << delta << endl;
    cout << "Итерационный процесс:" << endl;
    cout << "--------------------------------------------------------" << endl;

    while ((right - left) > epsilon) {
        it++;

        // вычисляем две симметричные точки
        long double y0 = (left + right - delta) / 2.0;
        long double z0 = (left + right + delta) / 2.0;

        // вычисляем значения функции
        long double f1 = function_main(a, b, c, y0);
        long double f2 = function_main(a, b, c, z0);
        count += 2;

        cout << "Итерация " << it << ":" << endl;
        cout << "  Отрезок: [" << left << ", " << right << "], длина: " << (right - left) << endl;
        cout << "  y = " << y0 << ", f(y) = " << f1 << endl;
        cout << "  z = " << z0 << ", f(z) = " << f2 << endl;

        // сравниваем значения функции и сужаем отрезок
        if (f1 < f2) {
            right = z0;
            cout << "  f(y) < f(z) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        else {
            left = y0;
            cout << "  f(y) >= f(z) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        
        cout << "--------------------------------------------------------" << endl;
    }
    cout << endl << "Условие выполнено: L = " << (right - left) << "  <  e = " << epsilon<<endl;
    double x_min = (left + right) / 2.0;
    double f_min = function_main(a, b, c, x_min);
    count++;

    cout << endl << "РЕЗУЛЬТАТЫ МЕТОДА ДИХОТОМИИ:" << endl;
    cout << "Найденный минимум: x = " << x_min << endl;
    cout << "Значение функции в минимуме: f(x) = " << f_min << endl;
    cout << "Количество итераций: " << it << endl;
    cout << "Количество вычислений функции: " << count << endl;
}


void golden_section_method(double a, double b, double c, double min_gr, double max_gr, double epsilon) {
    cout << endl << "Метод золотого сечения" << endl;

    const long double phi = (sqrt(5.0) - 1.0) / 2.0; // ~ 0.618 (золотое сечение)
    int it = 0;
    int count = 0;
    cout << phi;
    double left = min_gr;
    double right = max_gr;

    cout << "Начальный отрезок: [" << left << ", " << right << "]" << endl;
    cout << "Точность: " << epsilon << ", phi: " << phi << endl;
    cout << "Итерационный процесс:" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Вычисляем начальные точки
    double y0 = right - phi * (right - left);
    double z0 = left + phi * (right - left);

    double f1 = function_main(a, b, c, y0);
    double f2 = function_main(a, b, c, z0);
    count += 2;

    cout << "Начальные точки:" << endl;
    cout << "y = " << y0 << ", f(y) = " << f1 << endl;
    cout << "z = " << z0 << ", f(z) = " << f2 << endl;
    cout << "--------------------------------------------------------" << endl;

    while ((right - left) > epsilon) {
        it++;
        cout << "Итерация " << it << ":" << endl;
        cout << "  Отрезок: [" << left << ", " << right << "], длина: " << (right - left) << endl;
        cout << "  y = " << y0 << ", f(y) = " << f1 << endl;
        cout << "  z = " << z0 << ", f(z) = " << f2 << endl;

        if (f1 < f2) {
            // минимум слева - отбрасываем правую часть
            right = z0;
            z0 = y0;
            f2 = f1;
            y0 = right - phi * (right - left);
            f1 = function_main(a, b, c, y0);
            count++;
            cout << "  f(y) < f(z) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        else {
            // минимум справа - отбрасываем левую часть
            left = y0;
            y0 = z0;
            f1 = f2;
            z0 = left + phi * (right - left);
            f2 = function_main(a, b, c, z0);
            count++;
            cout << "  f(y) >= f(z) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }

        cout << "  Новые точки: y = " << y0 << ", z = " << z0 << endl;
        cout << "--------------------------------------------------------" << endl;
    }
    cout <<endl<< "Условие выполнено: L = " << (right - left) << "  <  e = " << epsilon << endl;
    double x_min = (left + right) / 2.0;
    double f_min = function_main(a, b, c, x_min);
    count++;

    cout << endl << "РЕЗУЛЬТАТЫ МЕТОДА ЗОЛОТОГО СЕЧЕНИЯ:" << endl;
    cout << "Найденный минимум: x = " << x_min << endl;
    cout << "Значение функции в минимуме: f(x) = " << f_min << endl;
    cout << "Количество итераций: " << it << endl;
    cout << "Количество вычислений функции: " << count << endl;

}


// вычисление чисел фибоначи
vector<long long> generate_fibonacci_sequence(int n) {
    vector<long long> fib(n + 2);
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib;
}

void fibonacci_method(double a, double b, double c, double min_gr, double max_gr, double epsilon) {
    cout << endl << "Метод Фибоначи" << endl;

    int it = 0;
    int count = 0;
    long double left = min_gr;
    long double right = max_gr;
    double L0 = right - left;

    cout << "Начальный отрезок: [" << left << ", " << right << "], длина: " << L0 << endl;
    cout << "Точность: " << epsilon << endl;

    // определяем необходимое число итераций
    int n = 1;
    while (generate_fibonacci_sequence(n)[n] < (L0 / epsilon)) {
        n++;
    }

    vector<long long> fib = generate_fibonacci_sequence(n);

    cout << "Число Фибоначчи F[" << n << "] = " << fib[n] << endl;
    cout << "Планируемое количество итераций: " << n << endl;
    cout << "Итерационный процесс:" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Начальные точки
    long double y = left + (double)fib[n - 2] / fib[n] * (right - left);
    long double z = left + (double)fib[n - 1] / fib[n] * (right - left);

    long double f1 = function_main(a, b, c, y);
    long double f2 = function_main(a, b, c, z);
    count += 2;

    cout << "Начальные точки:" << endl;
    cout << "y = " << y << ", f(y) = " << f1 << " (F[" << n - 2 << "]/F[" << n << "] = "
        << (double)fib[n - 2] / fib[n] << ")" << endl;
    cout << "z = " << z << ", f(z) = " << f2 << " (F[" << n - 1 << "]/F[" << n << "] = "
        << (double)fib[n - 1] / fib[n] << ")" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Основной цикл
    for (int k = 1; k <= n - 2; k++) {
        it++;

        cout << "Итерация " << it << " (k = " << k << "):" << endl;
        cout << "  Отрезок: [" << left << ", " << right << "], длина: " << (right - left) << endl;
        cout << "  y = " << y << ", f(y) = " << f1 << endl;
        cout << "  z = " << z << ", f(z) = " << f2 << endl;
        cout << "  Коэффициенты: F[" << n - k - 1 << "]/F[" << n - k + 1 << "] = "
            << (double)fib[n - k - 1] / fib[n - k + 1] << ", F[" << n - k << "]/F[" << n - k + 1 << "] = "
            << (double)fib[n - k] / fib[n - k + 1] << endl;

        if (f1 < f2) {
            // Минимум слева
            right = z;
            z = y;
            f2 = f1;
            y = left + (double)fib[n - k - 2] / fib[n - k] * (right - left);
            f1 = function_main(a, b, c, y);
            count++;
            cout << "  f(y) < f(z) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        else {
            // Минимум справа
            left = y;
            y = z;
            f1 = f2;
            z = left + (double)fib[n - k - 1] / fib[n - k] * (right - left);
            f2 = function_main(a, b, c, z);
            count++;
            cout << "  f(y) >= f(z) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }

        cout << "  Новые точки: y = " << y << ", z = " << z << endl;
        cout << "--------------------------------------------------------" << endl;
    }

    // Финальная итерация (k = n-1)
    it++;
    cout << "Финальная итерация " << it << " (k = " << n - 1 << "):" << endl;

    // На последней итерации добавляем δ для различения точек
    double delta = epsilon / 10.0;
    z = y + delta;
    f2 = function_main(a, b, c, z);
    count++;

    cout << "  y = " << y << ", f(y) = " << f1 << endl;
    cout << "  z = " << z << ", f(z) = " << f2 << endl;

    if (f1 < f2) {
        right = z;
        cout << "  f(y) < f(z) => финальный отрезок: [" << left << ", " << right << "]" << endl;
    }
    else {
        left = y;
        cout << "  f(y) >= f(z) => финальный отрезок: [" << left << ", " << right << "]" << endl;
    }

    double x_min = (left + right) / 2.0;
    double f_min = function_main(a, b, c, x_min);
    count++;

    cout << "--------------------------------------------------------" << endl;
    cout << endl << "РЕЗУЛЬТАТЫ МЕТОДА ФИБОНАЧЧИ:" << endl;
    cout << "Найденный минимум: x = " << x_min << endl;
    cout << "Значение функции в минимуме: f(x) = " << f_min << endl;
    cout << "Количество итераций: " << it << endl;
    cout << "Количество вычислений функции: " << count << endl;
    cout << "Длина конечного отрезка: " << (right - left) << endl;

}