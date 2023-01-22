#ifndef WIDGET_H
#define WIDGET_H

#include <GL/glut.h>

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWheelEvent>

extern "C" {
#include "../parser.h"
}

namespace Ui {
class Widget;
}

class Widget : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initialPoints();

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  void wheelEvent(QWheelEvent *) override;
  void initialParam();

  QPoint mPos, numPix;
  float xRot, yRot, zRot, angleRot, xTrans, yTrans, zTrans, xScale;
  float angleRot1 = 1;
  int countVertex = 0;
  int numOfPoints = 0;
  double arr[100000000], arr1[100000000];
  char nameOfFile[256];
  //    double xbc = 0;
  //    double ybc = 0;
  //    double zbc = 0;
  //    double xl = 1;
  //    double yl = 1;
  //    double zl = 1;
  //    double xv = 1;
  //    double yv = 1;
  //    double zv = 1;
  //    double lWidth = 1;
  //    int lineMark;
  //    double pointSize = 1;
  //    int pointMark = 0;
  //    int camMark = 0;
  view_data data1 = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0};

 private:
  QMatrix4x4 m_projectionMatrix;
};

#endif  // WIDGET_H
