#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits> 

class Matrix
{
private:
    static int count;

protected:
    int size;
    int **data;

public:
    // Конструкторы, деструктор, методы...
    Matrix();
    Matrix(int n);
    Matrix(const Matrix &other);
    virtual ~Matrix(); // Make the destructor virtual

    virtual void trans();
    virtual void print() const;
    virtual Matrix sumatr(const Matrix &other) const;
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    Matrix &operator++();
    Matrix operator++(int);
    operator int *();
    virtual void fillRandom();
    virtual int getData(int i, int j) const;
    virtual void setData(int i, int j, int value);

    static int getCount();

    // Перегрузка операторов ввода и вывода
    friend std::istream &operator>>(std::istream &in, Matrix &m);
    friend std::ifstream &operator>>(std::ifstream &in, Matrix &m);

    friend std::ofstream &operator<<(std::ofstream &out, const Matrix &m);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

    // Методы для записи и чтения из файлов
    virtual void saveToTextFile(std::ofstream &file) const;
    static std::vector<Matrix> loadAllFromTextFile(const std::string &filename);

    virtual void saveToBinaryFile(std::ofstream &file) const;
    static std::vector<Matrix> loadAllFromBinaryFile(const std::string &filename);

    virtual bool isSquare() const { return true; }
    virtual int getRows() const { return size; }
    virtual int getCols() const { return size; }
};