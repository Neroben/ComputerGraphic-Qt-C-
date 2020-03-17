#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QtMath>
#include <QPainter>
#include <QResizeEvent>

class WorldToScreenConverter
{
public:
    // Экранная система координат
    QRect screen;

    // Мировая система координат
    QPointF point1, point2;

    // Преобразование из мировой системы координат в экранную
    QPoint convert(QPointF p);

    // Преобразование X из экранной системы координат в мировую
    qreal x(int X);

    // Преобразование Y из экранной системы координат в мировую
    qreal y(int Y);

    // Коэффициенты в формуле перевода кординат
    qreal k_x, k_y;

    // Установить область определения функции [x1, x2]
    void setIntervalX(qreal x1, qreal x2);

    // Установить область определения функции [y1, y2]
    void setIntervalY(qreal y1, qreal y2);
};



// Абстрактный класс для рисования осей и их разметки
class Axis
{
public:
    // Вычисление шага разметки в экранной H и мировой k системах координат
    void step(qreal& k, qreal& H, char& m, int& n);

    // Рисование осей и разметки
    virtual void draw(QPainter *painter, WorldToScreenConverter *coords_converter, qreal H) = 0;
};



// Класс абсцисс
class AbscissaAxis : public Axis
{
public:
    // Рисование осей и разметки оси абсцисс
    void draw(QPainter *painter, WorldToScreenConverter *coords_converter, qreal H);
};



// Класс ординат
class OrdinateAxis : public Axis
{
public:
    // Рисование осей и разметки оси ординат
    void draw(QPainter *painter, WorldToScreenConverter *coords_converter, qreal H);
};



// Класс для хранения информации о выводимой функции
class CurveData
{
    // Цвет кривой
    QColor curveColor;

    // Стиль пера
    QPen curvePen;
public:
    // Функция для рисования
    virtual double func(qreal x) = 0;

    QColor getCurveColor();
    void setCurveColor(QColor color);

    QPen getCurvePen();
    void setCurvePen(QPen pen);
};



// Класс для рисования синуса
class SinCurveData : public CurveData
{
public:
    qreal func(qreal x);
};



// Класс для рисования косинуса
class CosCurveData : public CurveData
{
public:
    qreal func(qreal x);
};



// Класс для рисования тангенса
class TanCurveData : public CurveData
{
public:
    qreal func(qreal x);
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
    WorldToScreenConverter coords_converter;
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // CHART_H
