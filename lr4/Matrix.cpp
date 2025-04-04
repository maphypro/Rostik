#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <string>

int Matrix::count = 0;

// Конструктор по умолчанию
Matrix::Matrix() : size(0), data(nullptr)
{
    ++count;
}

// Конструктор с параметром (порядок матрицы)
Matrix::Matrix(int n) : size(n)
{
    ++count;
    this->data = new int *[this->size];
    for (int i = 0; i < this->size; ++i)
    {
        this->data[i] = new int[this->size];
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix &other) : size(other.size)
{
    ++count;
    this->data = new int *[this->size];
    for (int i = 0; i < this->size; ++i)
    {
        this->data[i] = new int[this->size];
        for (int j = 0; j < this->size; ++j)
        {
            this->data[i][j] = other.data[i][j];
        }
    }
}

// Деструктор
Matrix::~Matrix()
{
    for (int i = 0; i < this->size; ++i)
    {
        delete[] this->data[i];
    }
    delete[] this->data;
    --count;
}

// Метод для транспонирования матрицы
void Matrix::trans()
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = i + 1; j < this->size; ++j)
        {
            std::swap(this->data[i][j], this->data[j][i]);
        }
    }
}

// Метод для вывода матрицы
void Matrix::print() const
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Метод для сложения двух матриц
Matrix Matrix::sumatr(const Matrix &other) const
{
    if (this->size != other.size)
    {
        throw std::invalid_argument("Матрицы разного порядка!!!");
    }
    Matrix result(this->size);
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Дружественная функция для вычитания матриц
Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    if (m1.size != m2.size)
    {
        throw std::invalid_argument("Матрицы разного порядка!!!");
    }
    Matrix result(m1.size);
    for (int i = 0; i < m1.size; ++i)
    {
        for (int j = 0; j < m1.size; ++j)
        {
            result.data[i][j] = m1.data[i][j] - m2.data[i][j];
        }
    }
    return result;
}

// Префиксный инкремент
Matrix &Matrix::operator++()
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            ++(this->data[i][j]); // Увеличиваем все элементы на 1
        }
    }
    return *this;
}

// Постфиксный инкремент
Matrix Matrix::operator++(int)
{
    Matrix temp(*this); // Сохраняем текущий объект
    ++(*this);          // Применяем префиксный инкремент
    return temp;        // Возвращаем старое значение
}

int Matrix::getData(int i, int j) const
{
    return this->data[i][j];
}

void Matrix::setData(int i, int j, int value)
{
    this->data[i][j] = value;
}

// Приведение матрицы к одномерному массиву
Matrix::operator int *()
{
    int *arr = new int[this->size * this->size];
    int index = 0;
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            arr[index++] = this->data[i][j];
        }
    }
    return arr;
}

void Matrix::fillRandom()
{
    // Инициализация генератора случайных чисел с использованием текущего времени
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Заполнение матрицы случайными значениями
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->data[i][j] = std::rand() % 100; // Заполнение числами от 0 до 99
        }
    }
}

// Перегрузка оператора ввода
std::istream &operator>>(std::istream &in, Matrix &m)
{
    for (int i = 0; i < m.size; ++i)
    {
        for (int j = 0; j < m.size; ++j)
        {
            in >> m.data[i][j];
        }
    }
    return in;
}

std::ifstream &operator>>(std::ifstream &file, Matrix &m)
{
    std::string line;

    std::getline(file, line);

    if (line.find("x") != std::string::npos)
    {
        size_t x_pos = line.find('x');
        char left_char = line[x_pos - 1];
        char right_char = line[x_pos + 1];
        int left_num = left_char - '0';
        int right_num = right_char - '0';

        // Читаем данные матрицы
        for (int i = 0; i < left_num; ++i)
        {
            for (int j = 0; j < right_num; ++j)
            {
                file >> m.data[i][j];
            }
        }

        // Пропускаем оставшиеся символы до разделителя
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (std::getline(file, line) && line != "-----")
        {
        }
    }

    return file;
}

// Перегрузка оператора вывода
std::ostream &operator<<(std::ostream &out, const Matrix &m)
{
    for (int i = 0; i < m.size; ++i)
    {
        for (int j = 0; j < m.size; ++j)
        {
            out << m.data[i][j] << (j == m.size - 1 ? "" : " ");
        }
        out << "\n";
    }
    return out;
}

// Вывод матрицы в файл
std::ofstream &operator<<(std::ofstream &out, const Matrix &m)
{
    out << "" << m.size << " " << m.size << std::endl;

    for (int i = 0; i < m.size; ++i)
    {
        for (int j = 0; j < m.size; ++j)
        {
            int element = m.data[i][j];
            out << "" << element;
            if (j < m.size - 1)
                out << " ";
        }
        out << "\n";
    }
    out << "-----\n";
    out.flush();

    return out;
}

void Matrix::saveToTextFile(std::ofstream &file) const
{
    if (!file.is_open())
    {
        throw std::ios_base::failure("Не удалось открыть файл для записи.");
    }

    file << "" << this->size << "x" << this->size << "\n";

    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            file << "" << this->data[i][j];
            if (j < this->size - 1)
                file << " ";
        }
        file << "\n";
    }

    file << "-----\n";
    file.flush(); // Гарантируем запись данных на диск
}

std::vector<Matrix> Matrix::loadAllFromTextFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Файл не найден или не может быть открыт: " + filename);
    }

    std::vector<Matrix> matrices;
    std::string line;

    while (std::getline(file, line))
    {
        // Пропускаем пустые строки
        if (line.empty())
            continue;

        if (line.find("x") != std::string::npos)
        {
            try
            {

                size_t x_pos = line.find('x');
                char left_char = line[x_pos - 1];
                char right_char = line[x_pos + 1];
                int left_num = left_char - '0';
                int right_num = right_char - '0';

                Matrix m(right_num);
                // Читаем данные матрицы
                for (int i = 0; i < left_num; ++i)
                {
                    for (int j = 0; j < right_num; ++j)
                    {
                        file >> m.data[i][j];
                    }
                }
                matrices.push_back(m);

                // Пропускаем оставшиеся символы до разделителя
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                while (std::getline(file, line) && line != "-----")
                {
                }
            }
            catch (const std::exception &e)
            {
                file.close();
                throw std::runtime_error("Ошибка чтения матрицы: " + std::string(e.what()));
            }
        }
    }

    file.close();

    if (matrices.empty())
    {
        throw std::runtime_error("Файл не содержит матриц в правильном формате");
    }

    return matrices;
}

// Метод для сохранения матрицы в бинарный файл
void Matrix::saveToBinaryFile(std::ofstream &file) const
{
    // Проверка, открылся ли файл
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file for writing");
    }

    // Записываем размер матрицы
    file.write(reinterpret_cast<const char *>(&(this->size)), sizeof(this->size));

    // Записываем данные матрицы
    for (int i = 0; i < this->size; ++i)
    {
        file.write(reinterpret_cast<const char *>(this->data[i]), this->size * sizeof(int));
    }
}

// Метод для загрузки матриц из бинарного файла
std::vector<Matrix> Matrix::loadAllFromBinaryFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    std::vector<Matrix> matrices; // Вектор для хранения матриц

    // Проверяем, открыт ли файл
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file");
    }

    while (file.peek() != EOF)
    { // Читаем, пока не достигнем конца файла
        int n;
        file.read(reinterpret_cast<char *>(&n), sizeof(n)); // Читаем размер матрицы

        if (file.gcount() != sizeof(n))
        {
            throw std::ios_base::failure("Failed to read matrix size");
        }

        // Создаем матрицу нужного размера
        Matrix m(n);

        // Читаем данные матрицы
        for (int i = 0; i < n; ++i)
        {
            file.read(reinterpret_cast<char *>(m.data[i]), n * sizeof(int));
            if (file.gcount() != n * sizeof(int))
            {
                throw std::ios_base::failure("Failed to read matrix data");
            }
        }

        matrices.push_back(m); // Добавляем матрицу в вектор
    }
    file.close();
    return matrices; // Возвращаем вектор матриц
}

// Статический метод для получения количества объектов
int Matrix::getCount()
{
    return count;
}