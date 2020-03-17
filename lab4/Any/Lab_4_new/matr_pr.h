#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <QMatrix4x4>

class Matrix {
public:

    static QMatrix4x4 prj(int t);
    static QMatrix4x4 prj_c(double h);

};


#endif // MATRIX_H
