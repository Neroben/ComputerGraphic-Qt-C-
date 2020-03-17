#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include "figure.h"
#include "matr_pr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void newProection_pressed();

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    Figure fg;
    QMatrix4x4 R1;

    QVector<bool>flags;

    int wheelCoeficient;
    void wheelEvent(QWheelEvent* events);

    ~MainWindow();

private:
    void reset();
    Ui::MainWindow *ui;
    //Повороты по осям
    float xAxisRotation;
    float yAxisRotation;
    int numberProjection;

    //Координаты предыдущей точки курсора мыши
    QPointF previousPoint;


};
#endif // MAINWINDOW_H
