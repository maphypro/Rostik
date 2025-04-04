#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

#include "Matrix.h"
#include "IdentityMatrix.h"
#include "RectangularMatrix.h"

using namespace std;

void lr4()
{
    cout << "Не существует виртуальных операторов, во втором выводе вызывается '<<' перегруженный для Matrix.\n"
         << "И второй cout не работает:(\n"
         << "Полиморфизма нет, очень грустно\n------\n"
         << "RectangularMatrix rm1(3, 2);\n"
         << "rm1.fillRandom();\n"
         << "cout << rm1 << endl;\n"
         << "Matrix *rm2 = new RectangularMatrix(rm1);\n"
         << "cout << (*rm2) << endl;" << endl
         << "------\n";

    RectangularMatrix rm1(3, 2);
    rm1.fillRandom();
    cout << rm1 << endl;
    Matrix *rm2 = new RectangularMatrix(rm1);
    cout << (*rm2) << endl;

    cout << "А если используем виртуальную функцию print\n"
         << "То полиморфизм есть, вызывается переопределенная для класса RectangularMatrix ф-ия\n"
         << "Несмотря на то, что rm2 имеет тип Matrix* "
         << "Полиморфизм есть, очень радостно\n------\n"
         << "rm1.print();\n"
         << "rm2->print();\n"
         << "------\n";

    rm1.print();
    rm2->print();

    cout << "А на примере ниже мы видим, как полиморфизм и работа виртуальных функций не позволили\n"
    << "испортить единичную матрицу, при попытке заполнить её рандомными числами\n"
    << "А так же позволили вызвать корректный метод для транспонирования прямоугольной матрицы\n"
    << "И всё это с учетом типа Matrix для объектов (*im2) и (*rm3)\n------\n"

    << "IdentityMatrix im1(4);\n"
    << "Matrix *im2 = new IdentityMatrix(im1);\n"
    << "\n"
    << "im1.print();\n"
    << "im2->print();\n"
    << "im2->fillRandom();\n"
    << "im2->print();\n"
    << "\n"
    << "Matrix *rm3 = new RectangularMatrix(3, 5);\n"
    << "rm3->fillRandom();\n"
    << "rm3->print();\n"
    << "rm3->trans();\n"
    << "rm3->print();\n"

    << "------\n";


    IdentityMatrix im1(4);
    Matrix *im2 = new IdentityMatrix(im1);

    im1.print();
    im2->print();
    im2->fillRandom();
    im2->print();

    Matrix *rm3 = new RectangularMatrix(3, 5);
    rm3->fillRandom();
    rm3->print();
    rm3->trans();
    rm3->print();


}

int main()
{
    lr4();

    return 0;
}