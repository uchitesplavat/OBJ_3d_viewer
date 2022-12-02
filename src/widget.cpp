#include "widget.h"


Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("The model");
}

Widget::~Widget()
{
}

double arr[10000000];
int countVertex = 0;
void Widget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
}

void Widget::resizeGL(int w, int h) {
    float aspect = w / (float)h;
    makeCurrent();
//    m_projectionMatrix.setToIdentity();
//    m_projectionMatrix.perspective(45, aspect, 0.1, 10.0);
    glViewport(0,0,w,h);
//    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-10,10,-20,1,2,200);

}

void Widget::paintGL() {
    glClearColor(0.0, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    gluOrtho2D(0, 800, 600,0);


//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    glFrustum(1.2,1.2,1,1,10,20);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glRotatef(90,0,0,1);
//    double arr1[] = {0,0,0,1,1,1,0,1,0};
    glVertexPointer(3, GL_DOUBLE, 0, &arr);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 1.0, 1.0);
    glDrawArrays(GL_LINES, 0, countVertex-1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glRotatef(xRot, 1,0,0);
    glRotatef(yRot, 0,1,0);
//        gluPerspective(60, 800.0/600.0, 2, 256);

}

void Widget::mousePressEvent(QMouseEvent *apEvent) {
    mPos = apEvent->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *apEvent) {
    xRot = 1/5.14*(apEvent->pos().y() - mPos.y());
    yRot = 1/5.14*(apEvent->pos().x() - mPos.x());
    update();
}

void Widget::initialPoints() {
    database matrix_of_vertex = {0};
    char str[] = "models/Cube.obj";
    matrix_of_vertex = parser(str);
    array_of_coord(arr, matrix_of_vertex);
    countVertex = matrix_of_vertex.count_polygons*3;

//    printf("%lf\n", matrix_of_vertex.matrix_3d.matrix[1][1]);
          s21_remove_matrix(&matrix_of_vertex.matrix_3d);

    free_polygons(matrix_of_vertex);

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




//          for (int i = 0; i < countVertex; i++) {
//              arr[i] /=10;
//          }
//          for (int i = 0; i < matrix_of_vertex.count_polygons*3; i++) {
//                  printf("%lf\n", arr[i]);
//          }
//          printf("COUNT%d\n", countVertex);
}

