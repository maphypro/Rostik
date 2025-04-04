#include "RectangularMatrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <string>

// Implementation of RectangularMatrix
RectangularMatrix::RectangularMatrix(int rows, int cols) : rows(rows), cols(cols)
{
    this->data = new int *[this->rows];
    for (int i = 0; i < rows; ++i)
    {
        this->data[i] = new int[this->rows];
    }
}

RectangularMatrix::RectangularMatrix(const RectangularMatrix &other) : Matrix(other), rows(other.rows), cols(other.cols)
{
    this->data = new int *[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->data[i] = new int[this->cols];
        for (int j = 0; j < this->cols; ++j)
        {
            this->data[i][j] = other.data[i][j];
        }
    }
}

RectangularMatrix::~RectangularMatrix()
{
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->data[i];
    }
    delete[] this->data;
}

void RectangularMatrix::print() const
{
    std::cout << "Rectangular Matrix " << this->rows << "x" << this->cols << ":" << std::endl;
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void RectangularMatrix::trans()
{
    int **transposedData = new int *[this->cols];
    for (int i = 0; i < this->cols; ++i)
    {
        transposedData[i] = new int[this->rows];
        for (int j = 0; j < this->rows; ++j)
        {
            transposedData[i][j] = this->data[j][i];
        }
    }
    // Clean up old data
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->data[i];
    }
    delete[] this->data;
    // Assign new dimensions and data
    std::swap(this->rows, this->cols);
    this->data = transposedData;
}

RectangularMatrix RectangularMatrix::sumatr(const RectangularMatrix &other) const
{
    if (this->rows != other.rows || this->cols != other.cols)
    {
        throw std::invalid_argument("Rectangular matrices must have the same dimensions for addition.");
    }
    RectangularMatrix result(this->rows, this->cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }
    return result;
}

void RectangularMatrix::fillRandom()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            this->data[i][j] = std::rand() % 100; // Example range 0-99
        }
    }
}

std::istream &operator>>(std::istream &in, RectangularMatrix &m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            in >> m.data[i][j];
        }
    }
    return in;
}


std::ostream &operator<<(std::ostream &out, const RectangularMatrix &m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            out << m.data[i][j] << (j == m.cols - 1 ? "" : " ");
        }
        out << "\n";
    }
    return out;
}

std::ofstream &operator<<(std::ofstream &out, const RectangularMatrix &m)
{
    out << "" << m.rows << " " << m.cols << std::endl;
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            out << "" << m.data[i][j] << (j == m.cols - 1 ? "" : " ");
        }
        out << "\n";
    }
    out << "-----\n";
    out.flush();
    return out;
}

void RectangularMatrix::saveToTextFile(std::ofstream &file) const
{
    if (!file.is_open())
    {
        throw std::ios_base::failure("Не удалось открыть файл для записи.");
    }

    file << "" << this->rows << " " << this->cols << std::endl;
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            file << "" << this->data[i][j] << (j == this->cols - 1 ? "" : " ");
        }
        file << "\n";
    }

    file << "-----\n";
    file.flush(); 
}

void RectangularMatrix::saveToBinaryFile(std::ofstream &file) const
{
    file.write(reinterpret_cast<const char *>(&(this->rows)), sizeof(this->rows));
    file.write(reinterpret_cast<const char *>(&(this->cols)), sizeof(this->cols));
    for (int i = 0; i < this->rows; ++i)
    {
        file.write(reinterpret_cast<const char *>(this->data[i]), this->cols * sizeof(int));
    }
}