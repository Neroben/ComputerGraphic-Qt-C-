#include "torcher.h"
#include "matrix.h"

Torcher::Torcher(int N)
{
    //Количество линий в торшере
    //Сделаем сначала для куба (ПОГ)
    Dots.resize(1000);
    polygones = {};

    Dots[0] = QVector3D(0, 1-2, -1);
    Dots[1] = QVector3D(1, -1-2, -1);
    Dots[2] = QVector3D(-1, -1-2, -1);
    Dots[3] = QVector3D(-1, 1-2, -1);
    Dots[4] = QVector3D(1, 1-2, 1);
    Dots[5] = QVector3D(1, -1-2, 1);
    Dots[6] = QVector3D(-1, -1-2, 1);
    Dots[7] = QVector3D(-1, 1-2, 1);
    Dots[8] = QVector3D(0.5, 2+0.5-2, -0.5);
    Dots[9] = QVector3D(0.5, +1-2, -0.5);
    Dots[10] = QVector3D(-0.5, +1-2, -0.5);
    Dots[11] = QVector3D(-0.5, +2+0.5-2, -0.5);
    Dots[12] = QVector3D(0.5, 2+0.5-2, 0.5);
    Dots[13] = QVector3D(0.5, 1-2, 0.5);
    Dots[14] = QVector3D(-0.5, 1-2, 0.5);
    Dots[15] = QVector3D(-0.5, 2+0.5-2, 0.5);


    //Получим число n угольников
    //В основании n-угольник и сверху n-угольник
    double stepAngle = 360/N;
    int Angle = 0;
    int i_lines = 0;
    int j = 0;
    for (int i = 18; i < 18+N; i++, i_lines+=1, Angle += stepAngle, j++)
    {
        QVector3D VectorBig;
        QVector3D VectorSmall;
        QMatrix4x4 Matrix;
        VectorBig = {0,2-2,1.75};
        VectorSmall = {0,5-2,0.7};

        //Вращение вокруг Y
        Matrix.rotate(Angle, 0,1,0);
        VectorBig = Matrix * VectorBig;
        VectorSmall = Matrix * VectorSmall;

        //Сначала в массиве точек с маленьким "кругом" в основании
        //Затем с большим
        Dots[18+N+j] = QVector3D(VectorBig.x(), VectorBig.y(), VectorBig.z());
        Dots[i] = QVector3D(VectorSmall.x(), VectorSmall.y(), VectorSmall.z());
    }

    //Большой круг на плоскости большого, маленький круг на плоскости маленького
    //сейчас всего Точек: 18+2*N (по 10 с каждой стороны)
    //Всего Линий: 24+3*N (по 10 с каждой стороны и 10 между верхом и низом)
    Angle = 0;
    i_lines = 0;
    j = 0;
    for (int i = 18+2*N; i<(18+3*N); i++, j++, i_lines++, Angle += stepAngle){
        QVector3D VectorBigSmall;
        QVector3D VectorSmallSmall;
        QMatrix4x4 Matrix;
        VectorBigSmall = {0,2-2,1.5};
        VectorSmallSmall = {0,5-2,0.4};

        Matrix.rotate(Angle, 0, 1, 0);
        VectorBigSmall = Matrix * VectorBigSmall;
        VectorSmallSmall = Matrix * VectorSmallSmall;

        //Сначала в массиве точек с маленьким "кругом" в основании
        //Затем с большим
        Dots[i] = QVector3D(VectorSmallSmall.x(), VectorSmallSmall.y(), VectorSmallSmall.z());
        Dots[18+3*N+j] = QVector3D(VectorBigSmall.x(), VectorBigSmall.y(), VectorBigSmall.z());
    }
}

//Получение полигонов
void Torcher::getPolygones(int N){
    vector<QColor> colors = {Qt::black, Qt::blue, Qt::gray, Qt::red, Qt::cyan, Qt::yellow};


    for (int coef = 0; coef<2; coef++){
        QPolygon *poly = new QPolygon();
        *poly << QPoint(Dots[0+8*coef].x(), Dots[0+8*coef].y())
              << QPoint(Dots[1+8*coef].x(), Dots[1+8*coef].y())
              << QPoint(Dots[2+8*coef].x(), Dots[2+8*coef].y())
              << QPoint(Dots[3+8*coef].x(), Dots[3+8*coef].y());
        polygones.push_back(*poly);
        zpVector.push_back((Dots[0+8*coef].z()+Dots[1+8*coef].z()+Dots[2+8*coef].z()+Dots[3+8*coef].z())/4);
        vector<int> temp;
        temp.push_back(0+8*coef);
        temp.push_back(1+8*coef);
        temp.push_back(2+8*coef);
        temp.push_back(3+8*coef);
        dotsPolygones.push_back(temp);
        vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);

        poly = new QPolygon();
        *poly << QPoint(Dots[0+8*coef].x(), Dots[0+8*coef].y())
              << QPoint(Dots[1+8*coef].x(), Dots[1+8*coef].y())
              << QPoint(Dots[5+8*coef].x(), Dots[5+8*coef].y())
              << QPoint(Dots[4+8*coef].x(), Dots[4+8*coef].y());
        zpVector.push_back((Dots[0+8*coef].z()+Dots[1+8*coef].z()+Dots[5+8*coef].z()+Dots[4+8*coef].z())/4);
        polygones.push_back(*poly);
        temp = {};
        temp.push_back(0+8*coef);
        temp.push_back(1+8*coef);
        temp.push_back(5+8*coef);
        temp.push_back(4+8*coef);
        dotsPolygones.push_back(temp);
        vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);

        poly = new QPolygon();
        *poly << QPoint(Dots[5+8*coef].x(), Dots[5+8*coef].y())
              << QPoint(Dots[6+8*coef].x(), Dots[6+8*coef].y())
              << QPoint(Dots[7+8*coef].x(), Dots[7+8*coef].y())
              << QPoint(Dots[4+8*coef].x(), Dots[4+8*coef].y());
        zpVector.push_back((Dots[5+8*coef].z()+Dots[6+8*coef].z()+Dots[7+8*coef].z()+Dots[4+8*coef].z())/4);
        polygones.push_back(*poly);
        temp = {};
        temp.push_back(5+8*coef);
        temp.push_back(6+8*coef);
        temp.push_back(7+8*coef);
        temp.push_back(4+8*coef);
        dotsPolygones.push_back(temp);
        vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);

       poly = new QPolygon();
        *poly << QPoint(Dots[6+8*coef].x(), Dots[6+8*coef].y())
              << QPoint(Dots[7+8*coef].x(), Dots[7+8*coef].y())
              << QPoint(Dots[3+8*coef].x(), Dots[3+8*coef].y())
              << QPoint(Dots[2+8*coef].x(), Dots[2+8*coef].y());
       zpVector.push_back((Dots[6+8*coef].z()+Dots[7+8*coef].z()+Dots[3+8*coef].z()+Dots[2+8*coef].z())/4);
       polygones.push_back(*poly);
       temp = {};
       temp.push_back(6+8*coef);
       temp.push_back(7+8*coef);
       temp.push_back(3+8*coef);
       temp.push_back(2+8*coef);
       dotsPolygones.push_back(temp);
       vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);

       poly = new QPolygon();
        *poly << QPoint(Dots[1+8*coef].x(), Dots[1+8*coef].y())
              << QPoint(Dots[5+8*coef].x(), Dots[5+8*coef].y())
              << QPoint(Dots[6+8*coef].x(), Dots[6+8*coef].y())
              << QPoint(Dots[2+8*coef].x(), Dots[2+8*coef].y());
       zpVector.push_back((Dots[1+8*coef].z()+Dots[5+8*coef].z()+Dots[6+8*coef].z()+Dots[2+8*coef].z())/4);
       polygones.push_back(*poly);
       temp = {};
       temp.push_back(1+8*coef);
       temp.push_back(5+8*coef);
       temp.push_back(6+8*coef);
       temp.push_back(2+8*coef);
       dotsPolygones.push_back(temp);
       vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);

       poly = new QPolygon();
        *poly << QPoint(Dots[0+8*coef].x(), Dots[0+8*coef].y())
              << QPoint(Dots[4+8*coef].x(), Dots[4+8*coef].y())
              << QPoint(Dots[7+8*coef].x(), Dots[7+8*coef].y())
              << QPoint(Dots[3+8*coef].x(), Dots[3+8*coef].y());
       zpVector.push_back((Dots[0+8*coef].z()+Dots[4+8*coef].z()+Dots[7+8*coef].z()+Dots[3+8*coef].z())/4);
       polygones.push_back(*poly);
       temp = {};
       temp.push_back(0+8*coef);
       temp.push_back(4+8*coef);
       temp.push_back(7+8*coef);
       temp.push_back(3+8*coef);
       dotsPolygones.push_back(temp);
       vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);
    }

    //Полигоны верхушки(низа при 2 проходе)
    for (int coef = 0 ; coef < 2; coef++){
    for (int i = 0; i < N-1; i++){
      QPolygon *poly = new QPolygon();
      *poly << QPoint(Dots[18+N*coef+i].x(), Dots[18+N*coef+i].y())
           << QPoint(Dots[18+N*coef+i+2*N].x(), Dots[18+N*coef+i+2*N].y())
           << QPoint(Dots[18+N*coef+i+2*N+1].x(), Dots[18+N*coef+i+2*N+1].y())
           << QPoint(Dots[18+N*coef+i+1].x(), Dots[18+N*coef+i+1].y());
        polygones.push_back(*poly);
        zpVector.push_back((Dots[18+N*coef+i].z()+Dots[18+N*coef+i+2*N].z()+Dots[18+N*coef+i+2*N+1].z()+Dots[18+N*coef+i+1].z())/4);
        vector<int> temp = {};
        temp.push_back(18+N*coef+i);
        temp.push_back(18+N*coef+i+2*N);
        temp.push_back(18+N*coef+i+2*N+1);
        temp.push_back(18+N*coef+i+1);
        dotsPolygones.push_back(temp);
        vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);
        }
    QPolygon *poly = new QPolygon();
    *poly << QPoint(Dots[18+N*coef+N-1].x(), Dots[18+N*coef+N-1].y())
         << QPoint(Dots[18+N*coef].x(), Dots[18+N*coef].y())
         << QPoint(Dots[18+N*coef+2*N].x(), Dots[18+N*coef+2*N].y())
         << QPoint(Dots[18+N*coef+3*N-1].x(), Dots[18+N*coef+3*N-1].y());
      zpVector.push_back((Dots[18+N*coef+N-1].z()+Dots[18+N*coef].z()+Dots[18+N*coef+2*N].z()+Dots[18+N*coef+3*N-1].z())/4);
      polygones.push_back(*poly);
      vector<int> temp = {};
      temp.push_back(18+N*coef+N-1);
      temp.push_back(18+N*coef);
      temp.push_back(18+N*coef+2*N);
      temp.push_back(18+N*coef+3*N-1);
      dotsPolygones.push_back(temp);
      vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);
    }

    //Боковые полигоны
    for (int i = 0; i < N-1; i++){
        QPolygon *poly = new QPolygon();
        *poly << QPoint(Dots[18+i].x(), Dots[18+i].y())
             << QPoint(Dots[18+N+i].x(), Dots[18+N+i].y())
             << QPoint(Dots[18+N+i+1].x(), Dots[18+N+i+1].y())
             << QPoint(Dots[18+i+1].x(), Dots[18+i+1].y());
          zpVector.push_back((Dots[18+i].z()+Dots[18+N+i].z()+Dots[18+N+i+1].z()+Dots[18+i+1].z())/4);
          polygones.push_back(*poly);
          vector<int> temp = {};
          temp.push_back(18+i);
          temp.push_back(18+N+i);
          temp.push_back(18+N+i+1);
          temp.push_back(18+i+1);
          dotsPolygones.push_back(temp);
          vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);
    }
    QPolygon *poly = new QPolygon();
    *poly << QPoint(Dots[18+2*N-1].x(), Dots[18+2*N-1].y())
         << QPoint(Dots[18+N].x(), Dots[18+N].y())
         << QPoint(Dots[18].x(), Dots[18].y())
         << QPoint(Dots[18+N-1].x(), Dots[18+N-1].y());
      zpVector.push_back((Dots[18+2*N-1].z()+Dots[18+N].z()+Dots[18].z()+Dots[18+N-1].z())/4);
      polygones.push_back(*poly);
      vector<int> temp = {};
      temp.push_back(18+2*N-1);
      temp.push_back(18+N);
      temp.push_back(18);
      temp.push_back(18+N-1);
      dotsPolygones.push_back(temp);
      vectorColor.push_back(colors[((temp[0]+temp[1]+temp[2]+temp[3])/4) % colors.size()]);
}

//Рисование торшера
void Torcher::drawTorcher(QPainter *painter, vector<QPolygon> newPolygones, int indexPressedPolygon, int N){
    painter->setBrush(Qt::NoBrush);
    //painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));

    for (unsigned int i = 0; i < polygones.size(); i++){
        //Выбрать выделение согласно индексу выбранного полигона
        //if (i == indexPressedPolygon){
        if (this->isPressedVector[i])
            painter->setPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap));
        else
            painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
        painter->setBrush(this->vectorColor[i]);
        painter->drawPolygon(newPolygones[i]);
    }
}
