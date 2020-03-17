#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Animate();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* event);//Обработчик события перерисовки окна
};

#endif // MAINWINDOW_H
