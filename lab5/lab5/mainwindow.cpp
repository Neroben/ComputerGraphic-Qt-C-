#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>

QPointF *pointwin;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setMinimumWidth(320);
    numberProjection = 0;
    xAxisRotation = 0;
    yAxisRotation = 0;
    wheelCoeficient = 0;
    R1 = QMatrix4x4();
    for(int i = 0; i < 35; i++){
        flags.push_back(false);
    }
    reset();
    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen((QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap)));

    fg.draw(&painter);
}


void MainWindow::reset()
{
    double scale = 1;
    if (width()/2 < height())
        scale = width()/10.0;
    else
        scale = height()/10.0;

    fg = Figure();
    QMatrix4x4 matr;
    matr.translate(width() / 2, height() / 2, 0);
    matr = matr * Matrix::prj_c(scale*15);
    matr.translate(0, 0, wheelCoeficient);
    matr = matr * R1.transposed();
    matr.scale(scale, scale, scale);
    for (int i = 0; i < fg.polygones.size(); i++)
        for(int j = 0; j < fg.polygones[i].points.size(); j++){
            fg.polygones[i].points[j] = matr * fg.polygones[i].points[j];
        }



    fg.rewritePolygone();
    fg.sortPolygone();
    if(pointwin != NULL){
        int index = fg.selectionPolygon(*pointwin);
        if(index >= 0)
            flags[index] = !flags[index];
    }
    for(int i = 0; i < 31; i++){
        if(flags[i]){
            fg.polygones[i].pen = QPen(Qt::green, 6, Qt::SolidLine, Qt::RoundCap);
        }
        else
            fg.polygones[i].pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap);
    }
}


void MainWindow::newProection_pressed()
{
    repaint();
}

//Нажатие мыши
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    previousPoint = event->windowPos();
    if(event->buttons() == Qt::RightButton){
        pointwin = &previousPoint;
        reset();
        pointwin = NULL;
        repaint();
    }

}

//Смеще;ние мыши относительно нажатия
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        float dh = (event->y() - previousPoint.y());
        float dw = (event->x() - previousPoint.x());

        R1.rotate(-dw, QVector3D(0,1,0));
        R1.rotate(dh, QVector3D(1,0,0));

        //Обновление данных о предыдущей координате
        previousPoint = event->windowPos();
        reset();
        repaint();
    }

}

void MainWindow::wheelEvent(QWheelEvent *event){
    int wheelCoeficientPlus = event -> delta() / 4;
    wheelCoeficient += wheelCoeficientPlus;
    reset();
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

