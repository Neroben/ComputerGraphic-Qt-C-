#include "Chart.h"

QPoint WorldToScreenConverter::convert(QPointF p)
{
    return QPoint(screen.left() + k_x * (p.x() - point1.x()), screen.bottom() - k_y * (p.y() - point1.y()));
}

qreal WorldToScreenConverter::x(int X)
{
    return ((X - screen.left()) / k_x + point1.x());
}

qreal WorldToScreenConverter::y(int Y)
{
    return ((screen.bottom() - Y) / k_y + point1.y());
}

void WorldToScreenConverter::setIntervalX(qreal x1, qreal x2)
{
    point1.setX(x1);
    point2.setX(x2);
}

void WorldToScreenConverter::setIntervalY(qreal y1, qreal y2)
{
    point1.setY(y1);
    point2.setY(y2);
}



void Axis::step(qreal &k, qreal &H, char &m, int &n)
{
    //k = W / (b - a)
    qreal p = H / k;

    // Поиск степени
    qreal n1 = log10(p),
            n2 = log10(p / 2),
            n5 = log10(p / 5);

    // H = h * k
    {
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

        H = k;

        // k = m * qPow(10, n) - действительный шаг разметки в мировой системе координат
        k = m * qPow(10, n);

        H *= k;
    }
}



void AbscissaAxis::draw(QPainter *painter, WorldToScreenConverter *coords_converter, qreal H)
{
    // k - количество пикселей на одну единицу в мировой системе координат
    qreal k = coords_converter->screen.width() / (coords_converter->point2.x() - coords_converter->point1.x());

    // k = m * qPow(10, n) - действительный шаг разметки в мировой системе координат
    char m = 0;
    int  n = 0;

    // Вычисление шага разметки в экранной H и мировой k = m * qPow(10, n) системах координат
    this->step(k, H, m, n);

    // Координаты первой разметки
    qreal start = floor(coords_converter->point1.x() / k + 1) * k;
    int j = 0;

    // Ручка для рисование оси Ox
    QPen penOx;
    penOx.setWidth(2);
    penOx.setColor(Qt::black);

    // Рисование Ox
    painter->setPen(penOx);

    // Координаты левого края Ox
    QPointF p1 = coords_converter->convert(coords_converter->point1);
    p1.setX(p1.x() + penOx.width() + 40);
    p1.setY(p1.y() - penOx.width() - 40);

    // Координаты правого края Ox
    QPointF p2 = coords_converter->convert(QPointF(coords_converter->point2.x(), coords_converter->point1.y()));
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



void OrdinateAxis::draw(QPainter *painter, WorldToScreenConverter *coords_converter, qreal H)
{
    // k - количество пикселей на одну единицу в мировой системе координат
    qreal k = coords_converter->screen.height() / (coords_converter->point2.y() - coords_converter->point1.y());

    // k = m * qPow(10, n) - действительный шаг разметки в мировой системе координат
    char m = 0;
    int  n = 0;

    // Вычисление шага разметки в экранной H и мировой k = m * qPow(10, n) системах координат
    this->step(k, H, m, n);

    // Координаты первой разметки
    qreal start = floor(coords_converter->point1.y() / k + 1) * k;
    int j = 0;

    // Ручка для рисование оси Oy
    QPen penOy;
    penOy.setWidth(2);
    penOy.setColor(Qt::black);

    // Рисование Oy
    painter->setPen(penOy);

    // Координаты нижнего края Oy
    QPointF p1 = coords_converter->convert(coords_converter->point1);
    p1.setX(p1.x() + penOy.width() + 40);
    p1.setY(p1.y() - penOy.width() - 40);

    // Координаты верхнего края Oy
    QPointF p2 = coords_converter->convert(QPointF(coords_converter->point1.x(), coords_converter->point2.y()));
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



qreal SinCurveData::func(qreal x)
{
    return qSin(x);
}



qreal CosCurveData::func(qreal x)
{
    return qCos(x);
}



qreal TanCurveData::func(qreal x)
{
    return qTan(x);
}



Chart::Chart(QWidget *parent) : QWidget(parent)
{

}

void Chart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Рисование всего, что связано с Ox
    {
        AbscissaAxis __X;
        qreal H = 100;
        __X.draw(&painter, &coords_converter, H);
    }

    // Рисование всего, что связано с Oy
    {
        OrdinateAxis __Y;
        qreal H = 100;
        __Y.draw(&painter, &coords_converter, H);
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

            QPoint tmp1 = coords_converter.convert(QPointF(coords_converter.point1.x(), funcs[i]->func(coords_converter.point1.x())));
            tmp1.setX(tmp1.x() + pen.width() + 40);
            tmp1.setY(tmp1.y() - pen.width() - 40);
            QPoint tmp2;
            for (auto j = coords_converter.point1.x(); j <= coords_converter.point2.x(); j += 0.01)
            {
                tmp2 = coords_converter.convert(QPointF(j, funcs[i]->func(j)));
                tmp2.setX(tmp2.x() + pen.width() + 40);
                tmp2.setY(tmp2.y() - pen.width() - 40);
                if ((tmp1.y() < coords_converter.convert(coords_converter.point1).y() - 40) &&
                        (tmp2.y() < coords_converter.convert(coords_converter.point1).y() - 40))
                    painter.drawLine(tmp1, tmp2);
                tmp1 = tmp2;
            }
        }
    }

    if (QWidget::width() > QWidget::parentWidget()->width() - 60)
        QWidget::resize(QWidget::parentWidget()->width() - 50, QWidget::height());
    else if (QWidget::width() < QWidget::parentWidget()->width() - 90)
        QWidget::resize(QWidget::parentWidget()->width() - 50, QWidget::height());

    if (QWidget::height() > QWidget::parentWidget()->height())
        QWidget::resize(QWidget::width(), QWidget::parentWidget()->height());
    else if (QWidget::height() < QWidget::parentWidget()->height() + 1)
        QWidget::resize(QWidget::width(), QWidget::parentWidget()->height());

}


void Chart::resizeEvent(QResizeEvent *)
{
    coords_converter.screen = QWidget::geometry();

    // Установка точек в мировой системе координат
    coords_converter.setIntervalX(-4, 4);
    coords_converter.setIntervalY(-2, 2);

    coords_converter.k_x = (coords_converter.screen.right() - coords_converter.screen.left()) / (coords_converter.point2.x() - coords_converter.point1.x());
    coords_converter.k_y = (coords_converter.screen.bottom() - coords_converter.screen.top()) / (coords_converter.point2.y() - coords_converter.point1.y());
}

