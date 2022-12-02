#ifndef WIDGET_H
#define WIDGET_H

#include <GL/glut.h>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QMouseEvent>


extern "C" {
#include "parser.h"
}


namespace Ui {
class Widget;
}

class Widget : public QOpenGLWidget
{
    Q_OBJECT


public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initialPoints();

    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

private:
    QMatrix4x4 m_projectionMatrix;
    QPoint mPos;
    float xRot, yRot, zRot;
};

#endif // WIDGET_H
