#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("The model");
}

Widget::~Widget() {}

void Widget::initializeGL() { initialParam(); }

void Widget::resizeGL(int w, int h) {
  makeCurrent();
  glViewport(0, 0, w, h);
}

void Widget::paintGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(data1.xbc, data1.ybc, data1.zbc, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (countVertex) {
    if (data1.camMark == 0) {
      glFrustum(-10, 10, -20, 20, -10, 10);
    } else if (data1.camMark == 1) {
      glOrtho(-1, 1, -1, 1, -2, 10);
    }
    glLineWidth(data1.lWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(data1.xl, data1.yl, data1.zl);
    glVertexPointer(3, GL_DOUBLE, 0, &arr);
    if (data1.lineMark == 0) {
      glDrawArrays(GL_LINES, 0, countVertex / 3);
    } else if (data1.lineMark == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0X00FF);
      glDrawArrays(GL_LINES, 0, countVertex / 3);
      glDisable(GL_LINE_STIPPLE);
    }
    if (data1.pointMark == 2) {
      glColor3f(data1.xv, data1.yv, data1.zv);
      glPointSize(data1.pointSize);
      glDrawArrays(GL_POINTS, 0, countVertex / 3);
    } else if (data1.pointMark == 1) {
      glColor3f(data1.xv, data1.yv, data1.zv);
      glEnable(GL_POINT_SMOOTH);
      glPointSize(data1.pointSize);
      glDrawArrays(GL_POINTS, 0, countVertex / 3);
      glDisable(GL_POINT_SMOOTH);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    initialParam();
    save_data(data1);
  }
  //    update();
}

void Widget::initialParam() {
  angleRot = 1.0;
  xRot = 0;
  yRot = 0;
  zRot = 0;
  xTrans = 0;
  yTrans = 0;
  zTrans = 0;
}

void Widget::mousePressEvent(QMouseEvent *apEvent) { mPos = apEvent->pos(); }

void Widget::mouseMoveEvent(QMouseEvent *apEvent) {
  xRot = -0.01 * (apEvent->pos().y() - mPos.y());
  yRot = 0.01 * (apEvent->pos().x() - mPos.x());
  model_rotation(arr, xRot, 0, countVertex);
  model_rotation(arr, yRot, 1, countVertex);
  update();
}

void Widget::wheelEvent(QWheelEvent *apEvent) {
  initialParam();
  numPix = apEvent->angleDelta();
  angleRot = numPix.y() / 60;
  if (angleRot > 0) {
    angleRot = 1.1;
  } else {
    angleRot = 0.9;
  }
  model_scale(arr, angleRot, countVertex);
  update();
}

void Widget::initialPoints() {
  database matrix_of_vertex = {0};
  //    strcpy(nameOfFile, "models/cube.obj");
  matrix_of_vertex = parser(nameOfFile);
  array_of_coord(arr, matrix_of_vertex);
  countVertex = matrix_of_vertex.count_polygons * 18;
  numOfPoints = matrix_of_vertex.count_of_vert;
  s21_remove_matrix(&matrix_of_vertex.matrix_3d);

  for (int k = 1; k < matrix_of_vertex.count_polygons + 1; k++) {
    memory_dealloc_int(matrix_of_vertex.polygons[k].vertexes);
    memory_dealloc_int(matrix_of_vertex.polygons[k].tex);
    memory_dealloc_int(matrix_of_vertex.polygons[k].normals);
  }

  memory_dealloc_polygon_t(matrix_of_vertex.polygons);
  double max = 1;

  for (int i = 0; i < countVertex; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  if (max > 1) {
    while (max >= 1) {
      for (int i = 0; i < countVertex; i++) {
        arr[i] /= 2;
      }
      max /= 2;
    }
  }
  for (int i = 0; i < countVertex; i++) {
    arr1[i] = arr[i];
  }
}