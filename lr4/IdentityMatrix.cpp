#include "identityMatrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <string>

// Implementation of IdentityMatrix
IdentityMatrix::IdentityMatrix(int n) : Matrix(n)
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->data[i][j] = (i == j ? 1 : 0);
        }
    }
}

IdentityMatrix::IdentityMatrix(const IdentityMatrix &other) : Matrix(other) {};

IdentityMatrix::~IdentityMatrix() {}

void IdentityMatrix::print() const
{
    std::cout << "Identity Matrix " << this->size << "x" << this->size << ":" << std::endl;
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void IdentityMatrix::fillRandom()
{
    std::cerr << "Error: Cannot fill an identity matrix with random values." << std::endl;
}

Matrix IdentityMatrix::sumatr(const Matrix &other) const
{
    if (this->size != other.getRows() || this->size != other.getCols())
    {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }
    Matrix result(this->size);
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            result.setData(i, j, this->data[i][j] + other.getData(i, j));
        }
    }
    return result;
}

void IdentityMatrix::trans()
{
    // Transpose of an identity matrix is itself, so no action needed.
}

void IdentityMatrix::saveToTextFile(std::ofstream &file) const
{
    file << "" << this->size << " " << this->size << std::endl;
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            file << "" << this->data[i][j] << (j == this->size - 1 ? "" : " ");
        }
        file << std::endl;
    }
}

void IdentityMatrix::saveToBinaryFile(std::ofstream &file) const
{
    int n = this->size;
    file.write(reinterpret_cast<char *>(&n), sizeof(n));
    for (int i = 0; i < this->size; ++i)
    {
        file.write(reinterpret_cast<char *>(this->data[i]), this->size * sizeof(int));
    }
}
