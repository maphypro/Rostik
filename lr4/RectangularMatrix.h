#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Matrix.h"

class RectangularMatrix : public Matrix
{
private:
    int rows;
    int cols;

public:
    RectangularMatrix(int rows, int cols);
    RectangularMatrix(const RectangularMatrix &other);
    ~RectangularMatrix() override;

    int getRows() const override { return rows; }
    int getCols() const override { return cols; }
    bool isSquare() const override { return false; }

    void print() const override;
    void trans() override;
    RectangularMatrix sumatr(const RectangularMatrix &other) const;
    void fillRandom() override;

    friend std::istream &operator>>(std::istream &in, RectangularMatrix &m);
    friend std::ostream &operator<<(std::ostream &out, const RectangularMatrix &m);
    
    friend std::ofstream &operator<<(std::ofstream &out, const RectangularMatrix &m);

    void saveToTextFile(std::ofstream &file) const override;
    void saveToBinaryFile(std::ofstream &file) const override;
};