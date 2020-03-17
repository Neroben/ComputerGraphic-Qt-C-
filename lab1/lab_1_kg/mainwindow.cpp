#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

qint32 n = 100;//количество лопастей
double angle = 10;//поворот лопастей
qint32 scroll = 100;//процент открытия паруса
bool flag = true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    extern qint32 scroll;//поворот лопастей
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::Animate);
    timer->start(15);

    scroll -= 1;
}

void MainWindow::Animate(){
    extern double angle;//поворот лопастей
    extern qint32 scroll;//процент открытия паруса
    extern bool flag;
    if(scroll <= 20)
        flag = true;
    if(scroll > 100)
        flag = false;
    if(flag)
        scroll +=1;
    else
        scroll -=1;
    angle -= 16;
    repaint();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this); // Создаём объект-живописец

    QColor Clear(255,255,255);//Белый цвет
    QColor Brown(64, 35, 0); // Коричневый цвет

    qint32 a = 0;
    extern qint32 n;//количество лопастей
    extern double angle;//поворот лопастей
    extern qint32 scroll;//процент открытия паруса

    if((3*a + 20 < width()) && (2*a + 20 < height())){
        if(width() < 2*height()){
            a = (width() - 20) * 0.25;
        }
        else{
            a = (height() - 20)*0.5;
        }
    }

    QPoint pTriangleL1(0.5*width() - 1.5*a, 0.5*height()), pTriangleL2(0.5*width() - 0.5*a, 0.5*height()), pTriangleL3(0.5*width() - 0.5*a, 0.5*height() + a);
    QPoint pTriangleR1(0.5*width() + 1.5*a, height()/2), pTriangleR2(0.5*width() + 0.5*a, 0.5*height()), pTriangleR3(0.5*width() + 0.5*a, 0.5*height() + a);
    QPoint pMast1(width()/2, height()/2), pMast2(width()/2,height()/2 - a);
    QPoint pPaper(width()/2 + 0.5*a*(scroll*0.01), height()/2);
    QPoint pFlag1(0.5*width(), 0.5*height() - a*((scroll*0.01))), pFlag2(0.5*width(), height()/2 - a*((scroll*0.01)) + a*0.2), pFlag3(width()/2 - a*0.2, height()/2 - a*((scroll*0.01)) + a*0.1);
    QRect rect = QRect(width()*0.5 - 1.35*a, height()*0.5 + 0.15*a, a*0.7, a*0.7);


    //painter.setBrush(Brown);
    painter.setPen(Brown);
    painter.drawLine(pTriangleL1, pTriangleL2);
    painter.drawLine(pTriangleL1, pTriangleL3);
    painter.drawLine(pTriangleR1, pTriangleR2);
    painter.drawLine(pTriangleR1, pTriangleR3);
    painter.drawLine(pMast1, pMast2);
    painter.drawLine(pMast2, pPaper);
    painter.drawLine(pFlag3, pFlag1);
    painter.drawLine(pFlag3, pFlag2);
    painter.drawRect(width()/2 - 0.5*a, height()/2, a, a);
    int iColor = 1;
    for(qint8 i = 0 ; i < n ; i++){
        if(i < n/2)
            iColor += 255/n*2;
        else
            iColor -= 255/n*2;
        painter.setPen(QColor(0,255-iColor,iColor));
        painter.setBrush(QColor(0,255-iColor,iColor));
        painter.drawPie(rect, angle, 360.0/n*16);
        angle += 360.0/n*16;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
