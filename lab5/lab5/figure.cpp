#include "figure.h"

int index = 0;

Figure::Figure()
{
    //сиденье
    index = 0;
    QVector3D a[4];
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(-2); a[1].setY(-0.25); a[1].setZ(-2);
    a[2].setX(2); a[2].setY(-0.25); a[2].setZ(-2);
    a[3].setX(2); a[3].setY(0.25); a[3].setZ(-2);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(-2); a[1].setY(-0.25); a[1].setZ(2);
    a[2].setX(2); a[2].setY(-0.25); a[2].setZ(2);
    a[3].setX(2); a[3].setY(0.25); a[3].setZ(2);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(-2); a[1].setY(-0.25); a[1].setZ(-2);
    a[3].setX(-2); a[3].setY(0.25); a[3].setZ(2);
    a[2].setX(-2); a[2].setY(-0.25); a[2].setZ(2);
    addPolygon(4, a, QColor(0,0,255,155));
    a[0].setX(2); a[0].setY(-0.25); a[0].setZ(-2);
    a[1].setX(2); a[1].setY(0.25); a[1].setZ(-2);
    a[3].setX(2); a[3].setY(-0.25); a[3].setZ(2);
    a[2].setX(2); a[2].setY(0.25); a[2].setZ(2);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-2); a[0].setY(-0.25); a[0].setZ(-2);
    a[1].setX(2); a[1].setY(-0.25); a[1].setZ(-2);
    a[2].setX(2); a[2].setY(-0.25); a[2].setZ(2);
    a[3].setX(-2); a[3].setY(-0.25); a[3].setZ(2);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(2); a[1].setY(0.25); a[1].setZ(-2);
    a[2].setX(2); a[2].setY(0.25); a[2].setZ(2);
    a[3].setX(-2); a[3].setY(0.25); a[3].setZ(2);
    addPolygon(4, a, QColor(0,0,255,155));

    //ножки
    //1
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(-2); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(-2); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(-2); a[3].setY(0.25); a[3].setZ(1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-1.5); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(-1.5); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(-1.5); a[3].setY(0.25); a[3].setZ(1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(-2); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(2);
    a[3].setX(-1.5); a[3].setY(0.25); a[3].setZ(2);
    addPolygon(4, a, QColor(0,0,255,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(1.5);
    a[1].setX(-2); a[1].setY(3.5); a[1].setZ(1.5);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(-1.5); a[3].setY(0.25); a[3].setZ(1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-2); a[0].setY(3.5); a[0].setZ(2);
    a[1].setX(-1.5); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(-2); a[3].setY(3.5); a[3].setZ(1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    //2
    a[0].setX(2); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(2); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(2); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(2); a[3].setY(0.25); a[3].setZ(1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(1.5); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(1.5); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(1.5); a[3].setY(0.25); a[3].setZ(1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(2); a[0].setY(0.25); a[0].setZ(2);
    a[1].setX(2); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(2);
    a[3].setX(1.5); a[3].setY(0.25); a[3].setZ(2);
    addPolygon(4, a, QColor(0,0,255,155));
    a[0].setX(2); a[0].setY(0.25); a[0].setZ(1.5);
    a[1].setX(2); a[1].setY(3.5); a[1].setZ(1.5);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(1.5); a[3].setY(0.25); a[3].setZ(1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(2); a[0].setY(3.5); a[0].setZ(2);
    a[1].setX(1.5); a[1].setY(3.5); a[1].setZ(2);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(1.5);
    a[3].setX(2); a[3].setY(3.5); a[3].setZ(1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    //3
    a[0].setX(2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(2); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(2); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(2); a[3].setY(0.25); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(1.5); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(1.5); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(1.5); a[3].setY(0.25); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(2); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(-2);
    a[3].setX(1.5); a[3].setY(0.25); a[3].setZ(-2);
    addPolygon(4, a, QColor(0,0,255,155));
    a[0].setX(2); a[0].setY(0.25); a[0].setZ(-1.5);
    a[1].setX(2); a[1].setY(3.5); a[1].setZ(-1.5);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(1.5); a[3].setY(0.25); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(2); a[0].setY(3.5); a[0].setZ(-2);
    a[1].setX(1.5); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(1.5); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(2); a[3].setY(3.5); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    //4
    //1
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(-2); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(-2); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(-2); a[3].setY(0.25); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-1.5); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(-1.5); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(-1.5); a[3].setY(0.25); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(-2);
    a[1].setX(-2); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(-2);
    a[3].setX(-1.5); a[3].setY(0.25); a[3].setZ(-2);
    addPolygon(4, a, QColor(0,0,255,155));
    a[0].setX(-2); a[0].setY(0.25); a[0].setZ(-1.5);
    a[1].setX(-2); a[1].setY(3.5); a[1].setZ(-1.5);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(-1.5); a[3].setY(0.25); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-2); a[0].setY(3.5); a[0].setZ(-2);
    a[1].setX(-1.5); a[1].setY(3.5); a[1].setZ(-2);
    a[2].setX(-1.5); a[2].setY(3.5); a[2].setZ(-1.5);
    a[3].setX(-2); a[3].setY(3.5); a[3].setZ(-1.5);
    addPolygon(4, a, QColor(0,255,0,155));

    //спинка
    a[0].setX(-2); a[0].setY(-0.25); a[0].setZ(-2);
    a[1].setX(-2); a[1].setY(-3.5); a[1].setZ(-2);
    a[2].setX(2); a[2].setY(-3.5); a[2].setZ(-2);
    a[3].setX(2); a[3].setY(-0.25); a[3].setZ(-2);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(-2); a[0].setY(-0.25); a[0].setZ(-1.75);
    a[1].setX(-2); a[1].setY(-3.5); a[1].setZ(-1.75);
    a[2].setX(2); a[2].setY(-3.5); a[2].setZ(-1.75);
    a[3].setX(2); a[3].setY(-0.25); a[3].setZ(-1.75);
    addPolygon(4, a, QColor(0,255,0,155));
    a[0].setX(-2); a[0].setY(-0.25); a[0].setZ(-1.75);
    a[1].setX(-2); a[1].setY(-3.5); a[1].setZ(-1.75);
    a[2].setX(-2); a[2].setY(-3.5); a[2].setZ(-2);
    a[3].setX(-2); a[3].setY(-0.25); a[3].setZ(-2);
    addPolygon(4, a, QColor(0,0,255,155));
    a[0].setX(2); a[0].setY(-0.25); a[0].setZ(-1.75);
    a[1].setX(2); a[1].setY(-3.5); a[1].setZ(-1.75);
    a[2].setX(2); a[2].setY(-3.5); a[2].setZ(-2);
    a[3].setX(2); a[3].setY(-0.25); a[3].setZ(-2);
    addPolygon(4, a, QColor(255,0,0,155));
    a[0].setX(2); a[0].setY(-3.5); a[0].setZ(-2);
    a[1].setX(2); a[1].setY(-3.5); a[1].setZ(-1.75);
    a[2].setX(-2); a[2].setY(-3.5); a[2].setZ(-1.75);
    a[3].setX(-2); a[3].setY(-3.5); a[3].setZ(-2);
    addPolygon(4, a, QColor(0,255,0,155));
}

void Figure::addPolygon(int n, QVector3D *arr, QColor color){
    MyPoligon mypolygon;
    mypolygon.z = 0;
    for(int i = 0; i < n; i++){
        mypolygon.points.push_back(arr[i]);
        mypolygon.polygon << QPointF(arr[i].x(), arr[i].y());
        mypolygon.z += arr[i].z();
    }
    mypolygon.brush = color;
    mypolygon.index = index++;
    polygones.push_back(mypolygon);
}

void Figure::rewritePolygone(){
    for(int i = 0; i < polygones.size(); i++){
        QPolygonF a;
        polygones[i].z = 0;
        for(int j = 0; j < polygones[i].points.size(); j++){
            polygones[i].z += polygones[i].points[j].z();
            a << QPointF(polygones[i].points[j].x(),polygones[i].points[j].y());
        }
        polygones[i].polygon = a;
    }
}

bool Figure::testPoint(MyPoligon a, QPointF p){
    //QVector<bool> flags;
    QVector<QPointF> vectors;

    for(int i = 0; i < a.points.size(); i++){
        vectors.push_back(QPointF(p.x() - a.points[i].x(), p.y() - a.points[i].y()));
    }

    int n = vectors.size();
    bool f1 = vectors[n-1].x()*vectors[0].y() - (vectors[n-1].y() * vectors[0].x()) > 0;
    for(int i = 0; i < vectors.size()-1; i++)
        if(((vectors[i].x()*vectors[i+1].y()) - (vectors[i].y() * vectors[i+1].x()) > 0) != f1)
            return false;
    return true;
}

int Figure::selectionPolygon(QPointF prevPos){
    multimap<double,MyPoligon*>::iterator it;
    it = sortpolygones.end();
    it--;
    while(it != sortpolygones.begin()){
        if(testPoint(*(it->second), prevPos)){
            if(it->second->pen == QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap))
                it->second->pen = QPen(Qt::green, 4, Qt::SolidLine, Qt::RoundCap);
            else
                it->second->pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap);
            return it->second->index;
        }
        it--;
    }
    if(testPoint(*(it->second), prevPos)){
        if(it->second->pen == QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap))
            it->second->pen = QPen(Qt::green, 4, Qt::SolidLine, Qt::RoundCap);
        else
            it->second->pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap);
        return it->second->index;
    }
    return -1;
}


void Figure::sortPolygone(){
    sortpolygones.clear();
    for(int i = 0; i < polygones.size(); i++){
        sortpolygones.insert(make_pair(polygones[i].z, &(polygones[i])));
    }
}

void Figure::draw(QPainter *painter)
{
    multimap<double,MyPoligon*>::iterator it;
    it = sortpolygones.begin();
    while(it != sortpolygones.end()){
        painter->setPen(it->second->pen);
        painter->setBrush(it->second->brush);
        painter->drawPolygon(it->second->polygon);
        it++;
    }
}
