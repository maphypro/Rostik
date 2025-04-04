#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm> // Для std::remove_if
#include <limits>    // Для std::numeric_limits
#include <cctype>    // Для ::isspace

class Matrix
{
private:
    int size;
    int **data;
    static int count;

public:
    // Конструкторы, деструктор, методы...
    Matrix();
    Matrix(int n);
    Matrix(const Matrix &other);
    ~Matrix();

    void trans();
    void print() const;
    Matrix sumatr(const Matrix &other) const;
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    Matrix &operator++();
    Matrix operator++(int);
    operator int *();
    void fillRandom();
    static int getCount();

    // Перегрузка операторов ввода и вывода
    friend std::istream &operator>>(std::istream &in, Matrix &m);
    friend std::ifstream &operator>>(std::ifstream &in, Matrix &m);

    friend std::ofstream &operator<<(std::ofstream &out, const Matrix &m);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

    // Методы для записи и чтения из файлов
    // void saveToTextFile(const std::string& filename) const;

    void saveToTextFile(std::ofstream &file) const;
    static std::vector<Matrix> loadAllFromTextFile(const std::string &filename);

    void saveToBinaryFile(std::ofstream &file) const;
    static std::vector<Matrix> loadAllFromBinaryFile(const std::string &filename);
};