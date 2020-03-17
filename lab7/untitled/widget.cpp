#include "widget.h"


Widget::Widget(QWidget *parent)
    : QGLWidget(parent)
{
    resize(600, 600);
    id_timer=startTimer(20); // устанавливаем таймер id_timer
                             // и запускаем его с интервалом 10 миллисекунд
    qaLightPosition5[0] = 0;
    qaLightPosition5[1] = 0;
    qaLightPosition5[2] = 2.5;
    qaLightPosition5[3] = 1.0;
}

void Widget::initializeGL()
{
    glClearColor(1, 1, 1, 1); // заполняем экран белым цветом

    LoadTexture();

    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_SMOOTH); // убираем режим сглаживания цветов
    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон

    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_NORMALIZE);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
    gluPerspective( GLfloat(90.0f), GLfloat(nWidth)/nHeight, GLfloat(0.001), 1000.0f );
}

void Widget::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана

/************************************************************************/
/*
    if (type % 3 == 0)
    {
        GLfloat qaAmbientLight[] = {0.0, GLfloat(0.2), GLfloat(0.2), GLfloat(0.2)};
        GLfloat qaDiffuseLight[] = {1.0, GLfloat(0.4), GLfloat(0.4), 1.0};
        GLfloat qaSpecularLight[] = {1, 1, 1, 1};


        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    }
    else if (type % 3 == 1)
    {
        GLfloat qaAmbientLight[] = {GLfloat(0.2), 0.0, GLfloat(0.2), GLfloat(0.2)};
        GLfloat qaDiffuseLight[] = {0.4, 1, 0.4, 1.0};
        GLfloat qaSpecularLight[] = {1, 1, 1, 1};


        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    }
    else
    {
        GLfloat qaAmbientLight[] = {0.2, 0.2, 0.0, 0.2};
        GLfloat qaDiffuseLight[] = {0.4, 0.4, 1, 1.0};
        GLfloat qaSpecularLight[] = {1, 1, 1, 1};


        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    }
    if (light_y >= 50)
    {
        light_y = 0;
        type++;
    }
    else light_y+= 1;

    GLfloat qaLightPosition[] = {0, (GLfloat)light_y, -2.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);



    GLfloat qaAmbientLight1[] = {0.5, 0.5, 0.6, 0.0};
    GLfloat qaDiffuseLight1[] = {0.5, 0.5, 0.4, 1.0};
    GLfloat qaSpecularLight1[] = {0, 0, 0, 1};

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);

    GLfloat qaLightPosition1[] = {x, y, z +1 , 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);



    GLfloat qaAmbientLight2[] = {0, 0, 0, 0.0};
    GLfloat qaDiffuseLight2[] = {0.1, 10, 0.1, 1.0};
    GLfloat qaSpecularLight2[] = {5, 0, 0, 1};

    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, qaAmbientLight2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, qaDiffuseLight2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, qaSpecularLight2);

    GLfloat qaLightPosition2[] = {0, 0.49, 2.6, 1.0};
    GLfloat qaLightDirection[] = {0, -1, 0};
    glLightfv(GL_LIGHT2, GL_POSITION, qaLightPosition2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, qaLightDirection);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60);


    GLfloat qaAmbientLight3[] = {0, 0, 0, 0.0};
    GLfloat qaDiffuseLight3[] = {0.1, 10, 0.1, 1.0};
    GLfloat qaSpecularLight3[] = {5, 0, 0, 1};

    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, qaAmbientLight3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, qaDiffuseLight3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, qaSpecularLight3);

    GLfloat qaLightPosition3[] = {0, GLfloat(0.49), 2.4, 1.0};
    GLfloat qaLightDirection1[] = {0, -1, 0};
    glLightfv(GL_LIGHT3, GL_POSITION, qaLightPosition3);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, qaLightDirection1);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60);



    GLfloat qaAmbientLight4[] = {0, 0, 0, 0.0};
    GLfloat qaDiffuseLight4[] = {1, 1, 1, 1.0};
    GLfloat qaSpecularLight4[] = {5, 0, 0, 1};

    glEnable(GL_LIGHT4);
    glLightfv(GL_LIGHT4, GL_AMBIENT, qaAmbientLight4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, qaDiffuseLight4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, qaSpecularLight4);

    GLfloat qaLightPosition4[] = {-0.16, 0.4, 2.8, 1.0};
    GLfloat qaLightDirection2[] = {0, -1, 0.5};
    glLightfv(GL_LIGHT4, GL_POSITION, qaLightPosition4);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, qaLightDirection2);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 60);
*/
    //----------------------------------------------------------
    GLfloat qaAmbientLight5[] = {1, 1, 1, 1.0};
    GLfloat qaDiffuseLight5[] = {1, 1, 1, 1.0};
    GLfloat qaSpecularLight5[] = {1, 1, 1, 1};

    glEnable(GL_LIGHT5);
    glLightfv(GL_LIGHT5, GL_AMBIENT, qaAmbientLight5);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, qaDiffuseLight5);
    glLightfv(GL_LIGHT5, GL_SPECULAR, qaSpecularLight5);

    glLightfv(GL_LIGHT5, GL_POSITION, qaLightPosition5);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 360);
    //------------------------------------------------------------w
/*************************************************************************/

    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    glLoadIdentity();           // загрузка единичную матрицу

    //glRotatef(dw, 0, 1, 0);



    /*float ambient[4] = {1, 1, 1, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);*/

    if (x >= 1)
        x = 0.8;
    else if (x <= -1)
        x = -0.8;

    if (z >= 2)
        z = 1.8;
    else if (z <= -1)
        z = -0.8;

    gluLookAt(x, y, z,
              x+lx, y+ly,  z+lz,
              0.0f, 1.0f,  0.0f );


    drawRoom();
    drawTree();
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
}

void Widget::drawRoom()
{
    glTranslatef(0.0f,0.0f,-1.0f);

    glColor3f(0, 0, 0);
    // Плато
    glBegin(GL_QUADS);
        glVertex3f(-10, -0.51, -10);
        glVertex3f(-10, -0.51, 10);
        glVertex3f(10, -0.51, 10);
        glVertex3f(10, -0.51, -10);
    glEnd();

    glColor3f(0, 0, 0); // задаем цвет

    // Стены без окна
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(-1, 0.5, 0.0);
        glTexCoord2d(0, 1); glVertex3f(-1, 0.5, 3);
        glTexCoord2d(1, 1); glVertex3f(-1, -0.5, 3);
        glTexCoord2d(1, 0); glVertex3f(-1, -0.5, 0.0);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(1, 0.5, 3);
        glTexCoord2d(0, 1); glVertex3f(1, 0.5, 0);
        glTexCoord2d(1, 1); glVertex3f(1, -0.5, 0);
        glTexCoord2d(1, 0); glVertex3f(1, -0.5, 3);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(1, 0.5, 3);
        glTexCoord2d(0, 1); glVertex3f(1, -0.5, 3);
        glTexCoord2d(1, 1); glVertex3f(-1, -0.5, 3);
        glTexCoord2d(1, 0); glVertex3f(-1, 0.5, 3);
    glEnd();

    // Стена с окном
    glBegin(GL_QUADS);
        glTexCoord2d(1, 1); glVertex3f(1, 0.5, 0);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.3, 0);
        glTexCoord2d(0, 0); glVertex3f(0.5, -0.3, 0);
        glTexCoord2d(1, 0); glVertex3f(1, -0.5, 0);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord2d(1, 1); glVertex3f(-1, 0.5, 0);
        glTexCoord2d(0, 1); glVertex3f(-1, -0.5, 0);
        glTexCoord2d(0, 0); glVertex3f(-0.5, -0.3, 0);
        glTexCoord2d(1, 0); glVertex3f(-0.5, 0.3, 0);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord2d(1, 1); glVertex3f(-1, 0.5, 0);
        glTexCoord2d(0, 1); glVertex3f(-0.5, 0.3, 0);
        glTexCoord2d(0, 0); glVertex3f(0.5, 0.3, 0);
        glTexCoord2d(1, 0); glVertex3f(1, 0.5, 0);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord2d(1, 1); glVertex3f(-1, -0.5, 0);
        glTexCoord2d(0, 1); glVertex3f(1, -0.5, 0);
        glTexCoord2d(0, 0); glVertex3f(0.5, -0.3, 0);
        glTexCoord2d(1, 0); glVertex3f(-0.5, -0.3, 0);
    glEnd();

    // Пол
    glColor3f(0, 0, 0); // задаем цвет
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(-1, -0.5, 0);
        glTexCoord2d(0, 1); glVertex3f(-1, -0.5, 3);
        glTexCoord2d(1, 1); glVertex3f(1, -0.5, 3);
        glTexCoord2d(1, 0); glVertex3f(1, -0.5, 0);
    glEnd();

    // Потолок
    glColor3f(0, 0, 0); // задаем цвет
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(-1, 0.5, 0);
        glTexCoord2d(0, 1); glVertex3f(1, 0.5, 0);
        glTexCoord2d(1, 1); glVertex3f(1, 0.5, 3);
        glTexCoord2d(1, 0); glVertex3f(-1, 0.5, 3);
    glEnd();

    // Картина
    glColor3f(0, 0, 0); // задаем цвет

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
        glTexCoord2d(1, 1); glVertex3f(0, 0.4, 2.99);
        glTexCoord2d(1, 0); glVertex3f(0, 0, 2.99);
        glTexCoord2d(0, 0); glVertex3f(-0.32, 0, 2.99);
        glTexCoord2d(0, 1); glVertex3f(-0.32, 0.4, 2.99);
    glEnd();

    //---------------------------------------------------

    glBegin(GL_QUADS);
        //glTexCoord2d(1, 1);
        glVertex3f(qaLightPosition5[0]+0.05, qaLightPosition5[1]+0.05, qaLightPosition5[2] - 2);
        //glTexCoord2d(1, 0);
        glVertex3f(qaLightPosition5[0]+0.05, qaLightPosition5[1]-0.05, qaLightPosition5[2] - 2);
        //glTexCoord2d(0, 0);
        glVertex3f(qaLightPosition5[0]-0.05, qaLightPosition5[1]-0.05, qaLightPosition5[2] - 2);
        //glTexCoord2d(0, 1);
        glVertex3f(qaLightPosition5[0]-0.05, qaLightPosition5[1]+0.05, qaLightPosition5[2] - 2);
    glEnd();

    glBegin(GL_QUADS);
        //glTexCoord2d(1, 1);
        glVertex3f(qaLightPosition5[0]+0.05, qaLightPosition5[1]+0.05, qaLightPosition5[2] - 2);
        //glTexCoord2d(1, 0);
        glVertex3f(qaLightPosition5[0]-0.05, qaLightPosition5[1]+0.05, qaLightPosition5[2] - 2);
        //glTexCoord2d(0, 0);
        glVertex3f(qaLightPosition5[0]-0.05, qaLightPosition5[1]-0.05, qaLightPosition5[2] - 2);
        //glTexCoord2d(0, 1);
        glVertex3f(qaLightPosition5[0]+0.05, qaLightPosition5[1]-0.05, qaLightPosition5[2] - 2);
    glEnd();
    //---------------------------------------------------
}

void Widget::drawTree()
{
    // Верхий уровень
    glColor3f(0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45*0.5, -0.5, 2.5 + 0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45, -0.5, 2.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45*0.5, -0.5, 2.5 - 0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();

    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45*0.5, -0.5, 2.5 + 0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45, -0.5, 2.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45*0.5, -0.5, 2.5 - 0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();

    // Средний уровень
    glColor3f(0.32, 0.54, 0.39);
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45*sqrt(3)*0.5, -0.5, 2.5 + 0.45*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45*sqrt(3)*0.5, -0.5, 2.5 + 0.45*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5, -0.5, 2.5 - 0.45);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();


    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45*sqrt(3)*0.5, -0.5, 2.5 + 0.45*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45*sqrt(3)*0.5, -0.5, 2.5 + 0.45*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5, -0.5, 2.5 - 0.45);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();

    // Нижний уровень
    glColor3f(0.24, 0.4, 0.29);
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45, -0.5, 2.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45*0.5, -0.5, 2.5 + 0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45*0.5, -0.5, 2.5 -  0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();


    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5+0.45, -0.5, 2.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, 0.45, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, -0.5, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45*0.5, -0.5, 2.5 + 0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glTexCoord2d(0, 0); glVertex3f(0.5-0.45*0.5, -0.5, 2.5 -  0.45*sqrt(3)*0.5);
        glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 2.5);
        glTexCoord2d(0.5, 1); glVertex3f(0.5, 0.45, 2.5);
    glEnd();
}

void Widget::LoadTexture()
{
    /*glGenTextures(5, textures);

    QImage walls;
    walls.load("C:\\RGZ\\walls.jpg");
    walls = QGLWidget::convertToGLFormat(walls);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)walls.width(), (GLsizei)walls.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, walls.bits());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage el;
    el.load("C:\\RGZ\\el.jpg");
    el = QGLWidget::convertToGLFormat(el);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)el.width(), (GLsizei)el.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, el.bits());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage pol;
    pol.load("C:\\RGZ\\pol.jpg");
    pol = QGLWidget::convertToGLFormat(pol);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)pol.width(), (GLsizei)pol.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pol.bits());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage pot;
    pot.load("C:\\RGZ\\potolok.jpg");
    pot = QGLWidget::convertToGLFormat(pot);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)pot.width(), (GLsizei)pot.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pot.bits());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage pic;
    pic.load("C:\\RGZ\\new_year.jpg");
    pic = QGLWidget::convertToGLFormat(pic);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)pic.width(), (GLsizei)pic.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pic.bits());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    */
}

void Widget::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_W:
        x += lx * step;
        z += lz * step;
        break;
    case Qt::Key_S:
        x -= lx * step;
        z -= lz * step;
        break;
     case Qt::Key_Up:
        qaLightPosition5[1] += step;
        break;
    case Qt::Key_Down:
        qaLightPosition5[1] -= step;
        break;
    case Qt::Key_Left:
        qaLightPosition5[0] += step;
        break;
    case Qt::Key_Right:
        qaLightPosition5[0] -= step;
        break;


    case Qt::Key_Equal:
        qaLightPosition5[2] += step;
        break;
    case Qt::Key_Minus:
        qaLightPosition5[2] -= step;
        break;


    }

    //updateGL(); // обновление изображения
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    previousPoint = event->windowPos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    dh += (event->y() - previousPoint.y()) / 1000;
    dw += (event->x() - previousPoint.x()) / 1000;


    lx = -sin(dw);
    ly = -tan(dh);
    lz = +cos(dw);


    //Обновление данных о предыдущей координате
    previousPoint = event->windowPos();

    //updateGL(); // обновление изображения
}

void Widget::timerEvent(QTimerEvent *event) // событие таймера
{
   // изменения

   updateGL(); // обновление изображения
}
