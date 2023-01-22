#include "qt/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    const QSurfaceFormat *format = new const QSurfaceFormat;
    QSurfaceFormat::setDefaultFormat(format->defaultFormat());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
