#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
        ui->model_window->initialPoints();
        ui->model_window->makeCurrent();
        ui->model_window->initializeGL();
        ui->model_window->resize(800, 600);
        ui->model_window->paintGL();
}

MainWindow::~MainWindow() {
    delete ui;

}

