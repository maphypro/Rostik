#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

#include "headers.h"

int main()
{

    int n = 0;
    std::cout << "Введите порядок матрицы: ";
    std::cin >> n;

    // Создание и ввод матриц
    Matrix m1(n), m2(n);
    std::cout << "Введите элементы матрицы 1:\n";
    std::cin >> m1;
    std::cout << "Введите элементы матрицы 2:\n";
    std::cin >> m2;

    // Вывод матриц
    std::cout << "\nМатрица 1:\n"
              << m1 << "Матрица 2:\n"
              << m2;

    // Транспонирование
    m1.trans();
    m2.trans();
    std::cout << "\nПосле транспонирования:\nМатрица 1:\n"
              << m1 << "Матрица 2:\n"
              << m2;

    // Операции с матрицами
    try
    {
        Matrix m3 = m1.sumatr(m2);
        std::cout << "Сумма матриц:\n"
                  << m3;
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка сложения: " << e.what() << std::endl;
    }

    try
    {
        Matrix m4 = m1 - m2;
        std::cout << "Разность матриц:\n"
                  << m4;
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка вычитания: " << e.what() << std::endl;
    }

    // // Инкременты
    // std::cout << "\nПосле инкрементов:\n";
    // std::cout << "Матрица 1 (префиксный):\n" << ++m1;
    // std::cout << "Матрица 2 (постфиксный):\n" << m2++;

    // Сохранение в текстовый файл
    const std::string text_filename = "matrices.txt";
    try
    {
        // Открываем файл, удаляя старое содержимое
        std::ofstream outputFile(text_filename, std::ios::trunc);

        if (!outputFile.is_open())
        {
            throw std::runtime_error("Не удалось создать/открыть файл: " + text_filename);
        }

        outputFile << m1 << m2;
        // m1.saveToTextFile(outputFile);
        // m2.saveToTextFile(outputFile);

        outputFile.close();
        std::cout << "\nМатрицы успешно сохранены в " << text_filename << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка сохранения: " << e.what() << std::endl;
    }

    // Загрузка из текстового файла
    try
    {
        std::ifstream inputFile(text_filename);
        Matrix m3(n);
        Matrix m4(n);
        inputFile >> m3 >> m4;
        std::cout << "Загруженная из txt матрица 1\n"
                  << m3 << "Загруженная из txt матрица 2\n"
                  << m4;
        inputFile.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка загрузки: " << e.what() << std::endl;
    }

    // Сохранение в бинарный файл
    const std::string bin_filename = "matrices.bin";
    try
    {
        std::ofstream file(bin_filename, std::ios::binary | std::ios::trunc);

        m1.saveToBinaryFile(file);
        m2.saveToBinaryFile(file);

        std::cout << "\nМатрицы успешно сохранены в " << bin_filename << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка сохранения: " << e.what() << std::endl;
    }

    // Загрузка из бинарного файлов
    try
    {
        std::vector<Matrix> loaded = Matrix::loadAllFromBinaryFile(bin_filename);
        std::cout << "Успешно загружено " << loaded.size() << " матриц:\n";
        for (size_t i = 0; i < loaded.size(); ++i)
        {
            std::cout << "Матрица " << i + 1 << ":\n"
                      << loaded[i] << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка загрузки: " << e.what() << std::endl;
    }

    // Дополнительная информация
    int *arr = (int *)m1;
    std::cout << "\nМатрица 1 как массив: ";
    for (int i = 0; i < n * n; ++i)
        std::cout << arr[i] << " ";
    delete[] arr;

    std::cout << "\n\nВсего создано матриц: " << Matrix::getCount() << std::endl;
    return 0;
}