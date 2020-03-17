#ifndef TORCHER_H
#define TORCHER_H
//Импорт родительского модуля, для уточнения числа N - граней
#include <mainwindow.h>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <vector>
#include "matrix.h"
using namespace std;


class Torcher
{
public:
    //N - число углов
    Torcher(int N);
    void drawTorcher(QPainter *painter, vector<QPolygon> newPolygones, int indexPressedPolygon, int N);
    ~Torcher() {}
    void getPolygones(int N);
    //Вектор точек, содержащих фигуру
    vector <QVector3D> Dots;
    //Вектор полигонов для фигуры
    vector <QPolygon> polygones;
    //Вектор точек для полигонов фигуры
    vector <vector<int>> dotsPolygones;
    //Вектор координат Z
    vector <double> zpVector;
    //Вектор цветов для каждого полигона
    vector<QColor> vectorColor;
    //Вектор состояний - нажат, не нажат
    vector <bool> isPressedVector;
};

#endif // TORCHER_H
