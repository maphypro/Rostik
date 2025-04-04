#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Matrix.h"

class IdentityMatrix : public Matrix
{
public:
    IdentityMatrix(int n);
    IdentityMatrix(const IdentityMatrix &other);
    ~IdentityMatrix() override;

    void print() const override;
    void fillRandom() override; // Prevent random filling
    Matrix sumatr(const Matrix &other) const override;
    void trans() override; // Transpose does nothing for identity matrix
    void saveToTextFile(std::ofstream &file) const override;
    void saveToBinaryFile(std::ofstream &file) const override;
};