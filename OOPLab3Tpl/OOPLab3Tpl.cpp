#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <new>

using namespace std;

// =========================================================
// КЛАС ДЛЯ ЗАВДАННЯ 1: РОМБ
// =========================================================
class Rhombus {
private:
    double side, diagonal;
    string color;
public:
    Rhombus(double s, double d, string c) : color(c) {
        if (s > 0 && d > 0 && d < 2 * s) { side = s; diagonal = d; }
        else { side = 1; diagonal = 1; } // Захист від некоректних даних
    }
    void print() {
        double d2 = sqrt(4 * pow(side, 2) - pow(diagonal, 2));
        cout << "[Ромб] Колір: " << color << ", Сторона: " << side
            << ", Площа: " << (diagonal * d2) / 2.0 << endl;
    }
};

// =========================================================
// КЛАС ДЛЯ ЗАВДАННЯ 2: ВЕКТОР
// =========================================================
class Vector3D {
private:
    float x, y, z;
    static int count;
public:
    Vector3D(float val) : x(val), y(val), z(val) { count++; }
    ~Vector3D() { count--; }
    void print() { cout << "[Вектор] (" << x << ", " << y << ", " << z << ")" << endl; }
    static int getCount() { return count; }
};
int Vector3D::count = 0;

// =========================================================
// КЛАС ДЛЯ ЗАВДАННЯ 3: МАТРИЦЯ
// =========================================================
class Matrix {
private:
    double** data;
    int rows, cols;
    int state;
    static int count;

    void allocate(int r, int c) {
        rows = r; cols = c;
        data = new (nothrow) double* [rows];
        if (!data) { state = 1; return; }
        for (int i = 0; i < rows; ++i) {
            data[i] = new (nothrow) double[cols];
            if (!data[i]) { state = 1; return; }
        }
    }

    void cleanup() {
        if (data) {
            for (int i = 0; i < rows; ++i) delete[] data[i];
            delete[] data;
            data = nullptr;
        }
    }

public:
    Matrix(int n, int m, double val) : state(0) { allocate(n, m); fill(val); count++; }
    Matrix(const Matrix& other) : state(other.state) {
        allocate(other.rows, other.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) data[i][j] = other.data[i][j];
        count++;
    }
    ~Matrix() { cleanup(); count--; }

    void fill(double val) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) data[i][j] = val;
    }

    void add(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) { state = 2; return; }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) data[i][j] += other.data[i][j];
    }

    void divide(int scalar) {
        if (scalar == 0) { state = 3; return; }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) data[i][j] /= scalar;
    }

    void print() {
        if (state != 0) { cout << "Помилка матриці! Код: " << state << endl; return; }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) cout << setw(6) << data[i][j] << " ";
            cout << endl;
        }
    }
    static int getCount() { return count; }
};
int Matrix::count = 0;

// =========================================================
// VOID-ФУНКЦІЇ ДЛЯ ВИКЛИКУ ЗАВДАНЬ
// =========================================================

void executeTask1() {
    cout << "\n>>> ЗАПУСК ЗАВДАННЯ 1: РОМБ <<<" << endl;
    Rhombus r(7, 10, "Жовтий");
    r.print();
}

void executeTask2() {
    cout << "\n>>> ЗАПУСК ЗАВДАННЯ 2: ВЕКТОР <<<" << endl;
    Vector3D v1(5.5);
    v1.print();
    cout << "Кількість активних векторів: " << Vector3D::getCount() << endl;
}

void executeTask3() {
    cout << "\n>>> ЗАПУСК ЗАВДАННЯ 3: МАТРИЦЯ <<<" << endl;
    Matrix m1(2, 2, 10.0);
    Matrix m2(2, 2, 5.0);

    cout << "Матриця А:" << endl; m1.print();
    cout << "Матриця B (додаємо до А):" << endl; m2.print();

    m1.add(m2); // Додаємо через void метод
    cout << "Результат А + В:" << endl; m1.print();

    m1.divide(3); // Ділимо через void метод
    cout << "Результат ділення на 3:" << endl; m1.print();

    cout << "Кількість активних матриць: " << Matrix::getCount() << endl;
}

// =========================================================
// ГОЛОВНА ПРОГРАМА (МЕНЮ)
// =========================================================
int main() {
    setlocale(LC_ALL, "Ukrainian");
    int choice;

    do {
        cout << "\n--- ГОЛОВНЕ МЕНЮ ---" << endl;
        cout << "1. Виконати Завдання 1 (Ромб)" << endl;
        cout << "2. Виконати Завдання 2 (Вектор)" << endl;
        cout << "3. Виконати Завдання 3 (Матриця)" << endl;
        cout << "0. Вийти з програми" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1: executeTask1(); break;
        case 2: executeTask2(); break;
        case 3: executeTask3(); break;
        case 0: cout << "До побачення!" << endl; break;
        default: cout << "Неправильний вибір!" << endl;
        }
    } while (choice != 0);

    return 0;
}