#include "figure.h"

Figure::Figure()
{
    set_part(-1.25,-2,0, 2.5,3,0.5, 0);
    set_part(-1.25,-1.25,0, 0.5,0.5,0.5, 45);
    set_part(-1.25,1,0, 2.5,0.5,2.5, 0);

    set_part(-1.25,1,0, 0.5,2,0.5,  0);
    set_part(0.75,1,0, 0.5,2,0.5, 0);
    set_part(-1.25,1,2, 0.5,2,0.5, 0);
    set_part(0.75,1,2, 0.5,2,0.5, 0);
}

void Figure::set_part(double centerX, double centerY, double centerZ, double x, double y, double z, int angle)  //задать часть фигуры
{
    QMatrix4x4 m;
    m.rotate(angle, QVector3D(0,0,1));
    Points.push_back(m*QVector3D(centerX + x,centerY + y,centerZ));//x,y,0
    Points.push_back(m*QVector3D(centerX + x,centerY,centerZ));//x,0,0
    Points.push_back(m*QVector3D(centerX,centerY,centerZ));//0,0,0
    Points.push_back(m*QVector3D(centerX,centerY + y,centerZ));//0,y,0

    Points.push_back(m*QVector3D(centerX + x,centerY + y,centerZ + z));//x,y,0
    Points.push_back(m*QVector3D(centerX + x,centerY,centerZ + z));//x,0,0
    Points.push_back(m*QVector3D(centerX,centerY,centerZ + z));//0,0,0
    Points.push_back(m*QVector3D(centerX,centerY + y,centerZ + z));//0,y,0
}

void Figure::draw(QPainter *painter)
{

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));

    QVector<QPolygon> vect;

    for(int i = 0, p = 0; i < 50; i += 4, p += 1)
    {
        QPolygon t;
        for(int j = 0; j < 4; j++)
            t << QPoint(Points[i + j].x(), Points[i + j].y());
        vect.push_back(t);

        //соединительные грани
        if (p % 2 == 0)
        {
            vect.push_back(QPolygon() << QPoint(Points[i + 5].x(), Points[i + 5].y()) << QPoint(Points[i + 1].x(), Points[i + 1].y()) << QPoint(Points[i + 2].x(), Points[i + 2].y()) << QPoint(Points[i + 6].x(), Points[i + 6].y()));
            vect.push_back(QPolygon() << QPoint(Points[i + 4].x(), Points[i + 4].y()) << QPoint(Points[i].x(), Points[i].y()) << QPoint(Points[i + 3].x(), Points[i + 3].y()) << QPoint(Points[i + 7].x(), Points[i + 7].y()));
            vect.push_back(QPolygon() << QPoint(Points[i + 5].x(), Points[i + 5].y()) << QPoint(Points[i + 1].x(), Points[i + 1].y()) << QPoint(Points[i].x(), Points[i].y()) << QPoint(Points[i + 4].x(), Points[i + 4].y()));
            vect.push_back(QPolygon() << QPoint(Points[i + 6].x(), Points[i + 6].y()) << QPoint(Points[i + 2].x(), Points[i + 2].y()) << QPoint(Points[i + 3].x(), Points[i + 3].y()) << QPoint(Points[i + 7].x(), Points[i + 7].y()));
        }
    }

    for(int i = 0; i < vect.size(); i++) {
        painter->drawPolygon(vect[i]);
    }

}
