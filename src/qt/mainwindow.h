#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include <QSurfaceFormat>
#include <QFileDialog>
#include <QString>
#include "gif/qgifimage_p.h"
#include <QTimer>
//#include <qgifimage.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QImage mp[100];
    int check;
    QTimer *timer_gif;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGifImage gif;


private slots:
    void on_scaleButton_clicked();

    void on_translateButton_clicked();

    void on_refreshButton_clicked();

    void on_rotateButton_clicked();

    void on_openButton_clicked();

    void initial_position_widgets();

    void on_pTypeComboBox_currentIndexChanged(int index);

    void on_BackColorRHorizontalSlider_valueChanged(int value);

    void on_BackColorGHorizontalSlider_valueChanged(int value);

    void on_BackColorBHorizontalSlider_valueChanged(int value);

    void on_lineColorRHorizontalSlider_valueChanged(int value);

    void on_lineColorGHorizontalSlider_valueChanged(int value);

    void on_lineColorBHorizontalSlider_valueChanged(int value);

    void on_lineWidthHorizontalSlider_valueChanged(int value);

    void on_lTypeComboBox_currentIndexChanged(int index);

    void on_vertexSizeHorizontalSlider_valueChanged(int value);

    void on_displayWayComboBox_currentIndexChanged(int index);

    void on_vColorRHorizontalSlider_valueChanged(int value);

    void on_vColorGHorizontalSlider_valueChanged(int value);

    void on_vColorBHorizontalSlider_10_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void timer_grab();

    void print_grab();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
