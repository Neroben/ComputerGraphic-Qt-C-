#include "chart.h"
#include <qmath.h>
#include <algorithm>
#include <vector>
#include <limits>

Chart::Chart(QWidget *parent) : QWidget(parent), converter(WorldToScreenConverter(-4,4,-2,2))
{

}

void Axis::step(double& k, double& h, int& m, int& n){
    double p = h/k;

    double n1 = log10(p);
    double n2 = log10(p/2);
    double n5 = log10(p/5);

    double tmp1 =  qPow(10, ceil(n1)) - p;
    double tmp2 = p - qPow(10, floor(n1));

    m = 1;
    n = floor(n1);
    if(tmp1 < tmp2)
    {
        m = 1;
        n = ceil(n1);
        tmp2 = tmp1;
    }

    tmp1 = p - 2 * qPow(10, floor(n2));
    if(tmp1 < tmp2)
    {
        m = 2;
        n = floor(n2);
        tmp2 = tmp1;
    }

    tmp1 = 2 * qPow(10, ceil(n2)) - p;
    if(tmp1 < tmp2)
    {
        m = 2;
        n = ceil(n2);
        tmp2 = tmp1;
    }

    tmp1 = p - 5 * qPow(10, floor(n5));
    if(tmp1 < tmp2)
    {
        m = 5;
        n = floor(n5);
        tmp2 = tmp1;
    }

    tmp1 = 5 * qPow(10, ceil(n5)) - p;
    if(tmp1 < tmp2)
    {
        m = 5;
        n = ceil(n5);
    }

    h = k;

    // k = m * qPow(10, n) - действительный шаг разметки в мировой системе координат
    k = m * qPow(10, n);

    h *= k;
}

QPoint WorldToScreenConverter::convert(double x, double y){
    return QPoint(kx*(x - x1) + screen.left(), screen.bottom() - ky*(y - y1));
}

WorldToScreenConverter::WorldToScreenConverter(double x1, double x2, double y1, double y2):x1(x1), x2(x2), y1(y1), y2(y2){
    kx = (screen.right() - screen.left())/(x2 - x1);
    ky = (screen.bottom()-screen.top())/(y2-y1);
}

double WorldToScreenConverter::x(int X){
    return ((X - screen.left()) / kx + x1);
}

double WorldToScreenConverter::y(int Y){
    return ((screen.bottom() - Y) / ky + y1);
}

void AbscissaAxis::draw(QPainter *painter, WorldToScreenConverter *converter, double H){
    double k = converter->screen.width() / (converter->x2 - converter->x1);


    int m = 0;
    int  n = 0;

    step(k, H, m, n);

    // Координаты первой разметки
    qreal start = floor(converter->x1 / k + 1) * k;
    int j = 0;

    // Ручка для рисование оси Ox
    QPen penOx;
    penOx.setWidth(2);
    penOx.setColor(Qt::black);

    // Рисование Ox
    painter->setPen(penOx);

    // Координаты левого края Ox
    QPointF p1 = converter->convert(converter->x1, converter->y1);
    p1.setX(p1.x() + penOx.width() + 40);
    p1.setY(p1.y() - penOx.width() - 40);

    // Координаты правого края Ox
    QPointF p2 = converter->convert(converter->x2, converter->y1);
    p2.setX(p2.x() + penOx.width() + 40);
    p2.setY(p2.y() - penOx.width() - 40);

    // Рисования Ox
    painter->drawLine(p1, p2);

    // Рисование разметки и значений разметок
    for (auto i = p1.x() + H; i < p2.x() - 0.5 * H; i += H)
    {
        painter->drawLine(i, p1.y() - 4, i, p1.y() + 4);
        painter->drawText(QRectF(QPointF(i - 30, p1.y() + 5), QPointF(i + 30, p1.y() + 25)), Qt::AlignCenter, QString::number(start + (j++) * k));
    }
}

void OrdinateAxis::draw(QPainter *painter, WorldToScreenConverter *converter, double H){
    // k - количество пикселей на одну единицу в мировой системе координат
        qreal k = converter->screen.height() / (converter->y2 - converter->y1);

        // k = m * qPow(10, n) - действительный шаг разметки в мировой системе координат
        int m = 0;
        int  n = 0;

        // Вычисление шага разметки в экранной H и мировой k = m * qPow(10, n) системах координат
        step(k, H, m, n);

        // Координаты первой разметки
        qreal start = floor(converter->y1 / k + 1) * k;
        int j = 0;

        // Ручка для рисование оси Oy
        QPen penOy;
        penOy.setWidth(2);
        penOy.setColor(Qt::black);

        // Рисование Oy
        painter->setPen(penOy);

        // Координаты нижнего края Oy
        QPointF p1 = converter->convert(converter->x1, converter->y1);
        p1.setX(p1.x() + penOy.width() + 40);
        p1.setY(p1.y() - penOy.width() - 40);

        // Координаты верхнего края Oy
        QPointF p2 = converter->convert(converter->x1, converter->y2);
        p2.setX(p2.x() + penOy.width() + 40);
        p2.setY(p2.y() - penOy.width() - 40);

        // Рисования Ox
        painter->drawLine(p1, p2);

        // Рисование разметки и значений разметок
        for (auto i = p1.y() - H; i > p2.y() + 0.5 * H; i -= H)
        {
            painter->drawLine(p1.x() - 4, i, p1.x() + 4, i);
            painter->drawText(QRectF(QPointF(p1.x() - 45, i - 10), QPointF(p1.x() - 5, i + 10)), Qt::AlignCenter, QString::number(start + (j++) * k));
        }
}

QColor CurveData::getCurveColor()
{
    return curveColor;
}

void CurveData::setCurveColor(QColor color)
{
    curveColor = color;
}

QPen CurveData::getCurvePen()
{
    return curvePen;
}

void CurveData::setCurvePen(QPen pen)
{
    curvePen = pen;
}



qreal SinCurveData::func(double x)
{
    return qSin(x);
}



qreal CosCurveData::func(double x)
{
    return qCos(x);
}

qreal TanCurveData::func(double x)
{
    return qTan(x);
}

void Chart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Рисование всего, что связано с Ox
    {
        AbscissaAxis __X;
        qreal H = 100;
        __X.draw(&painter, &converter, H);
    }

    // Рисование всего, что связано с Oy
    {
        OrdinateAxis __Y;
        qreal H = 100;
        __Y.draw(&painter, &converter, H);
    }

    // Рисование графиков функций
    {
        QVector<CurveData*> funcs;
        funcs.push_back(new SinCurveData);
        funcs.push_back(new CosCurveData);
        funcs.push_back(new TanCurveData);

        for (int i = 0; i < funcs.size(); ++i)
        {
            funcs[i]->setCurveColor(QColor(0, ((i + 1) * 255 / funcs.size()) & 255, ((funcs.size() - i) * 255 / funcs.size()) & 255, 255));

            QPen pen;
            pen.setWidth(2);
            pen.setColor(funcs[i]->getCurveColor());

            painter.setPen(pen);

            QPoint tmp1 = converter.convert(converter.x1, funcs[i]->func(converter.x1));
            tmp1.setX(tmp1.x() + pen.width() + 40);
            tmp1.setY(tmp1.y() - pen.width() - 40);
            QPoint tmp2;
            for (auto j = converter.x1; j <= converter.x2; j += 0.01)
            {
                tmp2 = converter.convert(j, funcs[i]->func(j));
                tmp2.setX(tmp2.x() + pen.width() + 40);
                tmp2.setY(tmp2.y() - pen.width() - 40);
                if ((tmp1.y() < converter.convert(converter.x1, converter.y1).y() - 40) &&
                        (tmp2.y() < converter.convert(converter.x1, converter.y1).y() - 40))
                    painter.drawLine(tmp1, tmp2);
                tmp1 = tmp2;
            }
        }
    }

    if (QWidget::width() > QWidget::parentWidget()->width() - 60){
        QWidget::resize(QWidget::parentWidget()->width() - 50, QWidget::height());
    }
    else if (QWidget::width() < QWidget::parentWidget()->width() - 90)
        QWidget::resize(QWidget::parentWidget()->width() - 50, QWidget::height());

    if (QWidget::height() > QWidget::parentWidget()->height())
        QWidget::resize(QWidget::width(), QWidget::parentWidget()->height());
    else if (QWidget::height() < QWidget::parentWidget()->height() + 1)
        QWidget::resize(QWidget::width(), QWidget::parentWidget()->height());

}

void Chart::resizeEvent(QResizeEvent *) {
    converter.screen = QWidget::geometry();

    // Установка точек в мировой системе координат
    converter.x1 = -3.777;
    converter.x2 = -3.5;

    converter.y1 =-2;
    converter.y2 =2;



    converter.kx = (converter.screen.right() - converter.screen.left()) / (converter.x2 - converter.x1);
    converter.ky = (converter.screen.bottom() - converter.screen.top()) / (converter.y2 - converter.y1);
}
