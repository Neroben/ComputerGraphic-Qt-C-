#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QPainter>




class WorldToScreenConverter
{
public:
    WorldToScreenConverter(double x1, double x2, double y1, double y2);
    // Экранная система координат
    QRect screen;
    //Коэффициент
    double kx, ky;
    // Мировая система координат
    double x1, x2, y1, y2;
    // Функция преобразует координаты точки (x, y) из мировой системы координат в экранную
    QPoint convert(double x, double y);
    // Функция преобразует значение ординаты Y из экранной системы координат в мировую
    double y(int Y);
    // Функция возвращает значение абсциссы в мировой системе координат по её значению X в экранной
    double x(int X);
};

class Axis
{
public:
    static void step(double& k, double& h, int& m, int& n);
};

class AbscissaAxis : Axis
{
public:
    void draw(QPainter *painter, WorldToScreenConverter *converter, double H);
};

class OrdinateAxis : Axis
{
public:
    void draw(QPainter *painter, WorldToScreenConverter *converter, double H);
};

class CurveData
{
    QColor curveColor; 	// Цвет кривой
    QPen curvePen;		// Стиль пера
public:
    virtual double func(double x) { return 0; } // Функция для рисования
    QColor getCurveColor();
    void setCurveColor(QColor color);
    QPen getCurvePen();
    void setCurvePen(QPen pen);
};



// Класс для рисования синуса
class SinCurveData : public CurveData
{
public:
    qreal func(double x);
};



// Класс для рисования косинуса
class CosCurveData : public CurveData
{
public:
    qreal func(double x);
};



// Класс для рисования тангенса
class TanCurveData : public CurveData
{
public:
    qreal func(double x);
};


class Chart : public QWidget
{
    Q_OBJECT
public:

    explicit Chart(QWidget *parent = 0);

    // Массив указателей на структуры, содержащие информацию о функциях f(x)
    QVector<CurveData*> curves;

    // Функция устанавливает область определения графика функции
    void setRangeX(double x1, double x2);

private:

    // Объект для преобразования мировых координат в экранные и наоборот
    WorldToScreenConverter converter;
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // CHART_H
