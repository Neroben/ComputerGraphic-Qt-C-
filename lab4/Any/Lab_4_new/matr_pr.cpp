#include "matr_pr.h"
#include "stdio.h"

QMatrix4x4 Matrix::prj_c(double h)
{
    return QMatrix4x4 (1, 0,    0, 0,
                       0, 1,    0, 0,
                       0, 0,    0, 0,
                       0, 0, -1/h, 1);
}

QMatrix4x4 Matrix::prj(int t)
{
    QMatrix4x4 M;

    // 1 тип - Ортографическая проекция с z = 0
    if (t == 1)
        M = QMatrix4x4(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 1);
    /*2 тип - Триметрическая проекция (поворот на 30 вокруг Y
    поворот на 45 вокруг X и проецирование на Z = 0)*/
    if (t == 2)
        M =
    QMatrix4x4(sqrt(3)/2, 0,          1/2,       0,
           sqrt(2)/4, sqrt(2)/2, -sqrt(6)/4, 0,
           0,         0,          0,         0,
           0,         0,          0,         1);
    //3 тип - Косоугольная Свободная , т.к угол = pi/4
    if (t == 3)
       M = QMatrix4x4(1, 0, sqrt(2)/2, 0,
                  0, 1, sqrt(2)/2, 0,
                  0, 0, 0,         0,
                  0, 0, 0,         1);
    //4 тип - Косоугольная Кабинетная , т.к угол = 1/2 * pi/4
    if (t == 4)
        M = QMatrix4x4(1, 0, sqrt(2)/4, 0,
                   0, 1, sqrt(2)/4, 0,
                   0, 0, 0,         0,
                   0, 0, 0,         1);
    return M;
}
