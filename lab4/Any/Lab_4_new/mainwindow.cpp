#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>

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

    ui->setupUi(this);
    ui->ProectionBox->addItem("Центральная");
    ui->ProectionBox->addItem("Ортографическая");
    ui->ProectionBox->addItem("Кабинетная");
    ui->ProectionBox->addItem("Свободная");
    ui->ProectionBox->addItem("Триметрическая");
    connect(ui->ProectionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(newProection_pressed()));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen((QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap)));

    painter.drawLine(width()/2, 0, width()/2, height());
    painter.drawLine(0, height()/2, width(), height()/2);

    double scale = 1;
    if (width()/2 < height())
        scale = width()/20.0;
    else
        scale = height()/10.0;


    //вид сверху
    Figure fg;
    QMatrix4x4 matr;

    matr.translate(width() / 4, 3 * height() / 4, 0);
    matr.scale(scale, scale, scale);

    for (int i = 0; i < fg.Points.size(); i++)
    {
        QVector3D V = {fg.Points[i].x(), fg.Points[i].y(), fg.Points[i].z()};
        V = matr * V;
        fg.Points[i] = QVector3D(V.x(), V.y(), V.z());
    }
    fg.draw(&painter);


    //вид спереди
    fg = Figure();
    matr = QMatrix4x4();

    matr.translate(width() / 4, 1.2 * height() / 4, 0);
    matr.scale(scale, scale, scale);
    matr.rotate(90, QVector3D(1, 0, 0));

    for (int i = 0; i < fg.Points.size(); i++)
    {
        QVector3D V = {fg.Points[i].x(), fg.Points[i].y(), fg.Points[i].z()};
        V = matr * V;
        fg.Points[i] = QVector3D(V.x(), V.y(), V.z());
    }
    fg.draw(&painter);


    //вид сбоку
    fg = Figure();
    matr = QMatrix4x4();

    matr.translate(3*width()/4, 1.2 * height() / 4, 0);
    matr.scale(scale, scale, scale);
    matr.rotate(90, QVector3D(1, 0, 0));
    matr.rotate(90, QVector3D(0, 0, 1));

    for (int i = 0; i < fg.Points.size(); i++)
    {
        QVector3D V = {fg.Points[i].x(), fg.Points[i].y(), fg.Points[i].z()};
        V = matr * V;
        fg.Points[i] = QVector3D(V.x(), V.y(), V.z());
    }
    fg.draw(&painter);


    //проекции
    fg = Figure();

    //центральная проекция
    if (numberProjection == 0)
    {
        QMatrix4x4 matr;

        matr.translate(3 * width() / 4, 3 * height() / 4, 0);
        matr = matr * Matrix::prj_c(scale*15);
        matr.translate(0, 0, wheelCoeficient);
        matr = matr * R1.transposed();
        matr.scale(scale, scale, scale);

        for (int i = 0; i < fg.Points.size(); i++)
        {

            QVector3D V(fg.Points[i].x(), fg.Points[i].y(), fg.Points[i].z());
            V = matr * V;
            fg.Points[i] = QVector3D(V.x(), V.y(), V.z());
        }
    }
    else
    //параллельная проекция
    {
        QMatrix4x4 matr;
        matr.translate(3 * width() / 4, 3 * height() / 4, 0);
        matr = matr * Matrix::prj(numberProjection);
        matr.rotate(yAxisRotation, QVector3D(0,1,0));
        matr.rotate(xAxisRotation, QVector3D(1,0,0));
        matr.scale(scale,scale,scale);

        for (int i = 0; i < fg.Points.size(); i++)
        {
            QVector3D V(fg.Points[i].x(), fg.Points[i].y(), fg.Points[i].z());
            V = matr * V;
            fg.Points[i] = QVector3D(V.x(), V.y(), V.z());
        }
    }
    fg.draw(&painter);
}

void MainWindow::newProection_pressed()
{
    numberProjection = ui->ProectionBox->currentIndex();
    repaint();
}

//Нажатие мыши
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    previousPoint = event->windowPos();
}

//Смещение мыши относительно нажатия
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    float dh = (event->y() - previousPoint.y());
    float dw = (event->x() - previousPoint.x());

    R1.rotate(-dw, QVector3D(0,1,0));
    R1.rotate(dh, QVector3D(1,0,0));

    //Обновление данных о предыдущей координате
    previousPoint = event->windowPos();
    repaint();
}


void MainWindow::wheelEvent(QWheelEvent *event){
    int wheelCoeficientPlus = event -> delta() / 4;
    wheelCoeficient += wheelCoeficientPlus;

    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

