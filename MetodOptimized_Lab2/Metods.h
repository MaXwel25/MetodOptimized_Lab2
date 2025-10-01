#pragma once
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long double function_main(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

void dichotomy_method(double a, double b, double c, double min_gr, double max_gr, long double epsilon = 0.2) {
    cout << endl <<"Метод Дихотомии" << endl;

    // объявляем границы здесь, чтобы не вызывать их каждый раз как параметр функции
    double left = min_gr;
    double right = max_gr;

    long double delta = epsilon / (right - left); // малый параметр
    int it = 0; // количество итераций
    //int function_calls = 0; // если нужно подсчитать сложность алгоритма

    cout << "Длина текущего отрезка: "<<(right - left)<<endl;
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
        //function_calls += 2;

        cout << "Итерация " << it << ":" << endl;
        cout << "  Отрезок: [" << left << ", " << right << "], длина: " << (right - left) << endl;
        cout << "  x1 = " << y0 << ", f(x1) = " << f1 << endl;
        cout << "  x2 = " << z0 << ", f(x2) = " << f2 << endl;

        // сравниваем значения функции и сужаем отрезок
        if (f1 < f2) {
            right = z0;
            cout << "  f(x1) < f(x2) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        else {
            left = y0;
            cout << "  f(x1) >= f(x2) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        
        cout << "--------------------------------------------------------" << endl;
    }
    cout << "Условие выполнено: L = " << (right - left) << " < e = " << epsilon;
}


void golden_section_method(double a, double b, double c, double min_gr, double max_gr, double epsilon = 0.2) {
    cout << "     Метод золотого сечения" << endl;

    const long double phi = (sqrt(5.0) - 1.0) / 2.0; // ≈ 0.618
    int iterations = 0;
    int function_calls = 0;

    double left = min_gr;
    double right = max_gr;

    cout << "Начальный отрезок: [" << left << ", " << right << "]" << endl;
    cout << "Точность: " << epsilon << ", phi: " << phi << endl;
    cout << "Итерационный процесс:" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Вычисляем начальные точки
    double x1 = right - phi * (right - left);
    double x2 = left + phi * (right - left);

    double f1 = function_main(a, b, c, x1);
    double f2 = function_main(a, b, c, x2);
    function_calls += 2;

    cout << "Начальные точки:" << endl;
    cout << "x1 = " << x1 << ", f(x1) = " << f1 << endl;
    cout << "x2 = " << x2 << ", f(x2) = " << f2 << endl;
    cout << "--------------------------------------------------------" << endl;

    while ((right - left) > epsilon) {
        iterations++;

        cout << "Итерация " << iterations << ":" << endl;
        cout << "  Отрезок: [" << left << ", " << right << "], длина: " << (right - left) << endl;
        cout << "  x1 = " << x1 << ", f(x1) = " << f1 << endl;
        cout << "  x2 = " << x2 << ", f(x2) = " << f2 << endl;

        if (f1 < f2) {
            // Минимум слева - отбрасываем правую часть
            right = x2;
            x2 = x1;
            f2 = f1;
            x1 = right - phi * (right - left);
            f1 = function_main(a, b, c, x1);
            function_calls++;
            cout << "  f(x1) < f(x2) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        else {
            // Минимум справа - отбрасываем левую часть
            left = x1;
            x1 = x2;
            f1 = f2;
            x2 = left + phi * (right - left);
            f2 = function_main(a, b, c, x2);
            function_calls++;
            cout << "  f(x1) >= f(x2) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }

        cout << "  Новые точки: x1 = " << x1 << ", x2 = " << x2 << endl;
        cout << "--------------------------------------------------------" << endl;
    }

    double x_min = (left + right) / 2.0;
    double f_min = function_main(a, b, c, x_min);
    function_calls++;

    cout << "РЕЗУЛЬТАТЫ МЕТОДА ЗОЛОТОГО СЕЧЕНИЯ:" << endl;
    cout << "Найденный минимум: x = " << x_min << endl;
    cout << "Значение функции в минимуме: f(x) = " << f_min << endl;
    cout << "Количество итераций: " << iterations << endl;
    cout << "Количество вычислений функции: " << function_calls << endl;
    cout << "Длина конечного отрезка: " << (right - left) << endl;

    double exact_x_min = -b / (2.0 * a);
    double exact_f_min = function_main(a, b, c, exact_x_min);

    cout << "\nСРАВНЕНИЕ С АНАЛИТИЧЕСКИМ РЕШЕНИЕМ:" << endl;
    cout << "Точное решение: x = " << exact_x_min << ", f(x) = " << exact_f_min << endl;
    cout << "Погрешность по x: " << fabs(x_min - exact_x_min) << endl;
    cout << "Погрешность по f(x): " << fabs(f_min - exact_f_min) << endl;

    cout << "\nПРЕИМУЩЕСТВА МЕТОДА ЗОЛОТОГО СЕЧЕНИЯ:" << endl;
    cout << "- Всего 1 вычисление функции на итерацию (после первой)" << endl;
    cout << "- Коэффициент сокращения отрезка: 0.618" << endl;
    cout << "- Оптимален для бесконечного процесса" << endl;
}


vector<long long> generate_fibonacci_sequence(int n) {
    vector<long long> fib(n + 2);
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib;
}

void fibonacci_method(double a, double b, double c, double min_gr, double max_gr, double epsilon = 0.2) {
    cout << "\n=== МЕТОД ФИБОНАЧЧИ ===" << endl;

    int iterations = 0;
    int function_calls = 0;
    double left = min_gr;
    double right = max_gr;
    double L0 = right - left;

    cout << "Начальный отрезок: [" << left << ", " << right << "], длина: " << L0 << endl;
    cout << "Точность: " << epsilon << endl;

    // Определяем необходимое число итераций
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
    double x1 = left + (double)fib[n - 2] / fib[n] * (right - left);
    double x2 = left + (double)fib[n - 1] / fib[n] * (right - left);

    double f1 = function_main(a, b, c, x1);
    double f2 = function_main(a, b, c, x2);
    function_calls += 2;

    cout << "Начальные точки:" << endl;
    cout << "x1 = " << x1 << ", f(x1) = " << f1 << " (F[" << n - 2 << "]/F[" << n << "] = "
        << (double)fib[n - 2] / fib[n] << ")" << endl;
    cout << "x2 = " << x2 << ", f(x2) = " << f2 << " (F[" << n - 1 << "]/F[" << n << "] = "
        << (double)fib[n - 1] / fib[n] << ")" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Основной цикл
    for (int k = 1; k <= n - 2; k++) {
        iterations++;

        cout << "Итерация " << iterations << " (k = " << k << "):" << endl;
        cout << "  Отрезок: [" << left << ", " << right << "], длина: " << (right - left) << endl;
        cout << "  x1 = " << x1 << ", f(x1) = " << f1 << endl;
        cout << "  x2 = " << x2 << ", f(x2) = " << f2 << endl;
        cout << "  Коэффициенты: F[" << n - k - 1 << "]/F[" << n - k + 1 << "] = "
            << (double)fib[n - k - 1] / fib[n - k + 1] << ", F[" << n - k << "]/F[" << n - k + 1 << "] = "
            << (double)fib[n - k] / fib[n - k + 1] << endl;

        if (f1 < f2) {
            // Минимум слева
            right = x2;
            x2 = x1;
            f2 = f1;
            x1 = left + (double)fib[n - k - 2] / fib[n - k] * (right - left);
            f1 = function_main(a, b, c, x1);
            function_calls++;
            cout << "  f(x1) < f(x2) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }
        else {
            // Минимум справа
            left = x1;
            x1 = x2;
            f1 = f2;
            x2 = left + (double)fib[n - k - 1] / fib[n - k] * (right - left);
            f2 = function_main(a, b, c, x2);
            function_calls++;
            cout << "  f(x1) >= f(x2) => новый отрезок: [" << left << ", " << right << "]" << endl;
        }

        cout << "  Новые точки: x1 = " << x1 << ", x2 = " << x2 << endl;
        cout << "--------------------------------------------------------" << endl;
    }

    // Финальная итерация (k = n-1)
    iterations++;
    cout << "Финальная итерация " << iterations << " (k = " << n - 1 << "):" << endl;

    // На последней итерации добавляем δ для различения точек
    double delta = epsilon / 10.0;
    x2 = x1 + delta;
    f2 = function_main(a, b, c, x2);
    function_calls++;

    cout << "  x1 = " << x1 << ", f(x1) = " << f1 << endl;
    cout << "  x2 = " << x2 << ", f(x2) = " << f2 << endl;

    if (f1 < f2) {
        right = x2;
        cout << "  f(x1) < f(x2) => финальный отрезок: [" << left << ", " << right << "]" << endl;
    }
    else {
        left = x1;
        cout << "  f(x1) >= f(x2) => финальный отрезок: [" << left << ", " << right << "]" << endl;
    }

    double x_min = (left + right) / 2.0;
    double f_min = function_main(a, b, c, x_min);
    function_calls++;

    cout << "--------------------------------------------------------" << endl;
    cout << "РЕЗУЛЬТАТЫ МЕТОДА ФИБОНАЧЧИ:" << endl;
    cout << "Найденный минимум: x = " << x_min << endl;
    cout << "Значение функции в минимуме: f(x) = " << f_min << endl;
    cout << "Количество итераций: " << iterations << endl;
    cout << "Количество вычислений функции: " << function_calls << endl;
    cout << "Длина конечного отрезка: " << (right - left) << endl;
    cout << "Коэффициент сокращения: " << (right - left) / L0 << endl;

    double exact_x_min = -b / (2.0 * a);
    double exact_f_min = function_main(a, b, c, exact_x_min);

    cout << "\nСРАВНЕНИЕ С АНАЛИТИЧЕСКИМ РЕШЕНИЕМ:" << endl;
    cout << "Точное решение: x = " << exact_x_min << ", f(x) = " << exact_f_min << endl;
    cout << "Погрешность по x: " << fabs(x_min - exact_x_min) << endl;
    cout << "Погрешность по f(x): " << fabs(f_min - exact_f_min) << endl;

    cout << "\nОСОБЕННОСТИ МЕТОДА ФИБОНАЧЧИ:" << endl;
    cout << "- Оптимален для заданного числа итераций" << endl;
    cout << "- Максимальное сокращение отрезка неопределенности" << endl;
    cout << "- Требует предварительного определения числа итераций" << endl;
    cout << "- Коэффициенты меняются на каждой итерации" << endl;
}