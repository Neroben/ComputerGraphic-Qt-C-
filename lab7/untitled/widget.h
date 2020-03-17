#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtGui>
#include <QGLWidget>
#include <GL/glu.h>
#include <QTimer>

class Widget : public QGLWidget
{


public:
    Widget(QWidget *parent = 0);

    float angle = 0.0;
    float lx = 0.0f, lz = 1.0f, ly = 0.0f;
    float x = 0.0f, y = 0.0f, z = 0.0f;

    GLfloat qaLightPosition5[4];

    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

    GLuint textures[5];

    void drawRoom();
    void drawTree();
    void LoadTexture();

    QPointF previousPoint;
    qreal dw, dh;
    qreal step = 0.1;
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    int id_timer;
    QTimer *timer;
    qreal light_y;
    int type;

private slots:
    void change(); // слот выполняет обновление изображения
protected:
      // виртуальная функция - динамический полиморфизм:
    void timerEvent(QTimerEvent *event); // обработка события таймера
};

#endif // WIDGET_H
