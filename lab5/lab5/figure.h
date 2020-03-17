#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QPainter>
#include <map>
#include <iterator>
#include "matr_pr.h"

using namespace std;

class MyPoligon{
public:
    QPolygonF polygon;
    QColor brush;
    QPen pen;
    int index;
    QVector<QVector3D> points;
    double z;
    MyPoligon():pen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap)) ,brush(Qt::NoBrush),z(0) {}
    MyPoligon(QPolygonF a1, QColor brush1, QPen pen1, double z1):polygon(a1), brush(brush1), pen(pen1), z(z1) { }
};



class Figure{
public:
    //вектор полигонов
    QVector<MyPoligon> polygones;
    //Вектор полигонов для сортировки фигуры
    multimap<double, MyPoligon*> sortpolygones;


    Figure();
    void draw(QPainter *painter);
    void addPolygon(int n, QVector3D *arr, QColor color);
    void rewritePolygone();
    int selectionPolygon(QPointF a);
    void sortPolygone();
    void pushPolygon();
    ~Figure() {};

private:
    bool testPoint(MyPoligon a, QPointF p);
};


#endif // FIGURE_H
