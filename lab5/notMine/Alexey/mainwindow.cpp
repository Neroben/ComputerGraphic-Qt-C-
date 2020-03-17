#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setMinimumWidth(320);
    NewEdge();
    //CallingNewEdge();
    xAxisRotation = 0;
    yAxisRotation = 0;
    wheelCoeficient = 0;
    indexPressedPolygon = -1;
    currentIndexPressedPolygon = -1;
    newZpCoordinats = {};

    ui->setupUi(this);
}

//Функция-компаратор для сравнения точек Zp
static bool compare(const pair<pair<vector<int>, QColor>, pair<bool,double>>& polygon1, const pair<pair<vector<int>, QColor>, pair<bool,double>>& polygon2)
{
    return (polygon1.second.second < polygon2.second.second)?true:false;
}


//Открыть меню выбора нового числа граней
int MainWindow::NewEdge() {
    bool flag = false;
    QString function = QInputDialog::getText(0, "Введите N", "N = ", QLineEdit::Normal, "", &flag);
    N = function.toInt();
    return true;
}



void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen((QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap)));
    vector<QColor> colors = {Qt::black, Qt::blue, Qt::gray, Qt::red, Qt::cyan, Qt::yellow};

    //Выбор коэфициента масштабирования в зависимости от размера экрана
    double scale = 1;
    if (width()/2 < height())
        scale = width()/17.0;
    else
        scale = height()/10.0;


       //Для нижнего-правого прямоугольника (3D-модель)
       Torcher model(N);

      //Сортировка значений Zp (Zp заполняется внутри функции получения полигонов)
       model.getPolygones(N);
       vector<pair<pair<vector<int>, QColor>, pair<bool,double>>> pairPolygonZp;
      //Если фигура уже была раз нарисована
       if (newZpCoordinats.size() != 0){
           model.zpVector = newZpCoordinats;
           model.dotsPolygones = newDotsPolygones;
           model.isPressedVector = newIsPressedVector;
       }


       //Флаг для перерисовки
       bool flagPressed = false;
       bool noFirstPaintOfPressed = currentIndexPressedPolygon == indexPressedPolygon;
       for (int i = 0; i < model.dotsPolygones.size(); i++){
           int indexColor = (model.dotsPolygones[i][0]+model.dotsPolygones[i][1]+model.dotsPolygones[i][2]+model.dotsPolygones[i][3]) / 4;
           if ((indexPressedPolygon == i and !noFirstPaintOfPressed) or (model.isPressedVector.size() and model.isPressedVector[i]))
               flagPressed = true;
           else
               flagPressed = false;
           //Для того, чтобы убрать нажатые
           if ((model.isPressedVector.size() and model.isPressedVector[i]) and currentIndexPressedPolygon != indexPressedPolygon)
               flagPressed = false;
           pairPolygonZp.push_back(pair<pair<vector<int>, QColor>, pair<bool,double>>
                                   (std::pair<vector<int>, QColor> (model.dotsPolygones[i], colors[indexColor % colors.size()]),
                                   (std::pair<bool, double> (flagPressed, model.zpVector[i]))));
       }
       currentIndexPressedPolygon = indexPressedPolygon;

       std::sort(pairPolygonZp.begin(), pairPolygonZp.end(), compare);
       model.vectorColor = {};
       model.isPressedVector = {};
       for (int i = 0; i < pairPolygonZp.size(); i++){
           model.dotsPolygones[i] = pairPolygonZp[i].first.first;
           model.vectorColor.push_back(pairPolygonZp[i].first.second);
           model.zpVector[i] = pairPolygonZp[i].second.second;
           model.isPressedVector.push_back(pairPolygonZp[i].second.first);
       }


       //Центральное проектирование
        // Коэфициент влияет на точку исхода, если выбрать маленьким, то изображение верно не построится
        Matrix M = Matrix::translate(width()/2, height()/2, 0)
                  * Matrix::projectionCentral(scale*15)
                  * Matrix::translate(0, 0, wheelCoeficient)
                  * Matrix::rotateY(yAxisRotation)
                  * Matrix::rotateX(xAxisRotation)
                  * Matrix::scale(scale, scale, scale);

        Matrix ZM = Matrix::translate(width()/2, height()/2, 0)
                  * Matrix::translate(0, 0, wheelCoeficient)
                  * Matrix::rotateY(yAxisRotation)
                  * Matrix::rotateX(xAxisRotation)
                  * Matrix::scale(scale, scale, scale);

        newPolygones = {};
        newZpCoordinats = {};
        newIsPressedVector = {};
        for (int i = 0; i < model.polygones.size(); i++){
                    QPolygon *tempPolygon = new QPolygon();
                    double tempZp = 0;
                    for (int j=0; j < model.dotsPolygones[i].size(); j++){
                      Vector ZVector(model.Dots[model.dotsPolygones[i][j]].x(), model.Dots[model.dotsPolygones[i][j]].y(), model.Dots[model.dotsPolygones[i][j]].z(), 1);
                      ZVector = ZM * ZVector;
                      tempZp += ZVector.z;

                      Vector FVector(model.Dots[model.dotsPolygones[i][j]].x(), model.Dots[model.dotsPolygones[i][j]].y(), model.Dots[model.dotsPolygones[i][j]].z(), 1);
                      FVector = M * FVector;
                      *tempPolygon << QPoint(FVector.x / FVector.h, FVector.y / FVector.h);
                    }
                    newPolygones.push_back(*tempPolygon);
                    newZpCoordinats.push_back(tempZp/model.dotsPolygones[i].size());
                    newIsPressedVector.push_back(model.isPressedVector[i]);
        }
      newDotsPolygones = model.dotsPolygones;
      model.drawTorcher(&painter, newPolygones, indexPressedPolygon, N);
}


//Нажатие на правую кнопку мыши
void MainWindow::rightClick(QMouseEvent *event){
        QPointF prevPos = event->windowPos();
        for (int i = newPolygones.size()-1; i >= 0; i--){
            vector<bool> vectorFlagLess = {};
            vector<bool> vectorFlagBigger = {};
            vector<QPointF> vectors = {};
            for (int j = 0; j<newPolygones[i].size(); j++){
                vectors.push_back(QPointF(newPolygones[i].point(j).x() - prevPos.x(), newPolygones[i].point(j).y() - prevPos.y()));
            }

            for (int j = 0; j<newPolygones[i].size(); j++){
                vectorFlagLess.push_back(vectors[j % 4].x() * vectors[(j+1) % 4].y() - vectors[(j+1) % 4].x() * vectors[j % 4].y() < 0);
                vectorFlagBigger.push_back(vectors[j % 4].x() * vectors[(j+1) % 4].y() - vectors[(j+1) % 4].x() * vectors[j % 4].y() > 0);
            }
            //Уникальные элементы в списках флагов (надо чтобы был только 1 True)
            std::vector<bool>::iterator it;
            it = std::unique (vectorFlagBigger.begin(), vectorFlagBigger.end());
            vectorFlagBigger.resize( std::distance(vectorFlagBigger.begin(),it));
            std::vector<bool>::iterator itLess;
            itLess = std::unique (vectorFlagLess.begin(), vectorFlagLess.end());
            vectorFlagLess.resize( std::distance(vectorFlagLess.begin(),itLess));

            //(Этот точка внутри этого полигона пересекает да)
            if (vectorFlagBigger.size() == 1 and vectorFlagBigger[0]){
                indexPressedPolygon = i;
                repaint();
                return;
            }

            //(Этот точка внутри этого полигона пересекает да)
            if (vectorFlagLess.size() == 1 and vectorFlagLess[0]){
                indexPressedPolygon = i;
                repaint();
                return;
            }
        }
}


//Нажатие мыши
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    previousPoint = event->windowPos();
    //Если нажата правая кнопка, то открыть функцию выделения полигона
    if (event->buttons() == Qt::RightButton)
       rightClick(event);
}

//Смещение мыши относительно нажатия
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){
    //dw/dh - расстояние, на которое мы переместили курсор
    //w - длина окна
    //h - ширина окна
    float w = width();
    float h = height();
    float dh = 180 * (event->y() - previousPoint.y());
    float dw = 180 * (event->x() - previousPoint.x());

    xAxisRotation += (dh / h);
    yAxisRotation -= (dw / w);

    //Обновление данных о предыдущей координате
    previousPoint = event->windowPos();
    repaint();
    }
}


void MainWindow::wheelEvent(QWheelEvent *event){
    int wheelCoeficientPlus = event -> delta()/4;
    wheelCoeficient += wheelCoeficientPlus;

    repaint();
}



MainWindow::~MainWindow()
{
    delete ui;
}

