#ifndef FIGURE_H
#define FIGURE_H

#include <mainwindow.h>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include "matr_pr.h"

using namespace std;


class Figure{
public:
    QVector <QVector3D> Points;

    Figure();
    void set_part(double centerX, double centerY, double centerZ, double x, double y, double z, int angle);
    void draw(QPainter *painter);
    ~Figure() {};
};

#endif // FIGURE_H
