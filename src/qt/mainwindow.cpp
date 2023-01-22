#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMovie>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initial_position_widgets();
    ui->model_window->makeCurrent();
    ui->model_window->initializeGL();
    ui->model_window->resize(800, 681);
    ui->model_window->paintGL();
}

void MainWindow::initial_position_widgets() {
    open_data(&ui->model_window->data1);
    ui->BackColorRHorizontalSlider->setSliderPosition(ui->model_window->data1.xbc*100);
    ui->BackColorGHorizontalSlider->setSliderPosition(ui->model_window->data1.ybc*100);
    ui->BackColorBHorizontalSlider->setSliderPosition(ui->model_window->data1.zbc*100);
    ui->lineColorRHorizontalSlider->setSliderPosition(ui->model_window->data1.xl*100);
    ui->lineColorGHorizontalSlider->setSliderPosition(ui->model_window->data1.yl*100);
    ui->lineColorBHorizontalSlider->setSliderPosition(ui->model_window->data1.zl*100);
    ui->vColorRHorizontalSlider->setSliderPosition(ui->model_window->data1.xv*100);
    ui->vColorGHorizontalSlider->setSliderPosition(ui->model_window->data1.yv*100);
    ui->vColorBHorizontalSlider_10->setSliderPosition(ui->model_window->data1.zv*100);
    ui->lineWidthHorizontalSlider->setSliderPosition((ui->model_window->data1.lWidth-1)*10);
    ui->lTypeComboBox->setCurrentIndex(ui->model_window->data1.lineMark);
    ui->displayWayComboBox->setCurrentIndex(ui->model_window->data1.pointMark);
    ui->pTypeComboBox->setCurrentIndex(ui->model_window->data1.camMark);
    ui->vertexSizeHorizontalSlider->setSliderPosition(ui->model_window->data1.pointSize-1);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_scaleButton_clicked() {
    ui->model_window->initialParam();
    int error_mark = 0;
    double scale = 0;
    std::string scaleText = ui->scaleLine->text().toUtf8().constData();
    error_mark = check_amount((char*)scaleText.c_str());
    if (!error_mark) {
        model_scale(ui->model_window->arr, ui->scaleLine->text().toDouble(), ui->model_window->countVertex);
        ui->model_window->initialParam();
        ui->model_window->update();

    } else {
        ui->scaleLine->setText("ERROR");
    }
}


void MainWindow::on_translateButton_clicked() {
    ui->model_window->initialParam();
    int error_mark = 0;
    std::string translateText = ui->translateLine->text().toUtf8().constData();
    error_mark = check_amount((char*)translateText.c_str());
    if (!error_mark) {
        model_trans(ui->model_window->arr, ui->translateLine->text().toDouble(),
        ui->transComboBox->currentIndex(), ui->model_window->countVertex);
        ui->model_window->initialParam();
        ui->model_window->update();
    } else {
        ui->translateLine->setText("ERROR");
    }
}


void MainWindow::on_refreshButton_clicked()
{
    for (int i = 0; i < ui->model_window->countVertex; i++) {
        ui->model_window->arr[i] = ui->model_window->arr1[i];
    }
    ui->model_window->update();

}


void MainWindow::on_rotateButton_clicked() {
    ui->model_window->initialParam();
    int error_mark = 0;
    double rotate = 0;
    std::string rotateText = ui->rotateLine->text().toUtf8().constData();
    error_mark = check_amount((char*)rotateText.c_str()); 
    if (!error_mark) {
        model_rotation(ui->model_window->arr, ui->rotateLine->text().toDouble(),
                       ui->rotateComboBox->currentIndex(), ui->model_window->countVertex);
        ui->model_window->initialParam();
        ui->model_window->update();
    } else {
        ui->rotateLine->setText("ERROR");
    }
}


void MainWindow::on_openButton_clicked() {
   QString fileName = QFileDialog::getOpenFileName(this, "Open", "  ", "*.obj");
   QByteArray ba = fileName.toLocal8Bit();
   const char* str = ba.data();
   snprintf(ui->model_window->nameOfFile, 256, "%s", str);
   ui->model_window->initialPoints();
   ui->countVertexL->setText(QString::number(ui->model_window->numOfPoints, 'g', 9));
   ui->countRibsL->setText(QString::number(ui->model_window->countVertex/10, 'g', 9));
   ui->nameLabel->setText(ui->model_window->nameOfFile);
   ui->model_window->update();
}



void MainWindow::on_pTypeComboBox_currentIndexChanged(int index) {
    if (ui->pTypeComboBox->currentIndex() == 0) {
        ui->model_window->data1.camMark = 0;
    } else if (ui->pTypeComboBox->currentIndex() == 1) {
        ui->model_window->data1.camMark = 1;
    }    
    ui->model_window->update();
}


void MainWindow::on_BackColorRHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.xbc = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_BackColorGHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.ybc = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_BackColorBHorizontalSlider_valueChanged(int value){
    ui->model_window->data1.zbc = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_lineColorRHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.xl = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_lineColorGHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.yl = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_lineColorBHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.zl = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_lineWidthHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.lWidth = (double)value/10+1;
    ui->model_window->update();
}


void MainWindow::on_lTypeComboBox_currentIndexChanged(int index) {
    ui->model_window->data1.lineMark = ui->lTypeComboBox->currentIndex();
    ui->model_window->update();
}


void MainWindow::on_vertexSizeHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.pointSize = (double)value+1;
    ui->model_window->update();
}


void MainWindow::on_displayWayComboBox_currentIndexChanged(int index) {
    ui->model_window->data1.pointMark = index;
    ui->model_window->update();
}


void MainWindow::on_vColorRHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.xv = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_vColorGHorizontalSlider_valueChanged(int value) {
    ui->model_window->data1.yv = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_vColorBHorizontalSlider_10_valueChanged(int value) {
    ui->model_window->data1.zv = (double)value/100;
    ui->model_window->update();
}


void MainWindow::on_pushButton_clicked() {
    QString filters("Image files *.bmp(*.bmp);;Image files *.jpg(*.jpg)");
    QString defaultFilter("Image files (*.bmp)");
    QString name = QFileDialog::getSaveFileName(0, "Save screen", QDir::currentPath(), filters, &defaultFilter);
    const QRect rect(0,0, 800, 681);
    QPixmap pixmap = ui->model_window->grab(rect);

    std::string xtext = defaultFilter.toUtf8().constData();
    const char *str = xtext.c_str();
    if (!strcmp(str, "Image files *.bmp(*.bmp)")) {
        pixmap.save(name, "BMP", -1);
    } else if (!strcmp(str, "Image files *.jpg(*.jpg)")) {
        pixmap.save(name, "JPG", -1);
    }
}


void MainWindow::on_pushButton_2_clicked() {
    check = 0;
    timer_gif = new QTimer();
    connect(timer_gif, &QTimer::timeout, this, &MainWindow::timer_grab);
    timer_gif->start(100);
    ui->pushButton_2->setEnabled(0);
}

void MainWindow::timer_grab() {
  if (check > 99) {
    timer_gif->stop();
    disconnect(timer_gif);
    check = 0;
    for (int i = 0; i < 100; gif.addFrame(mp[i++], 200)) {
    }
    QString str =
        QFileDialog::getSaveFileName(0, "Save as", "", "*.gif");
    gif.save(str);
    ui->pushButton_2->setText("Make GIF");
    ui->pushButton_2->setEnabled(1);
  } else {
    mp[check] = ui->model_window->grab().toImage();
    check += 1;
    ui->pushButton_2->setText(QString::number(check / 10));
  }
}

void MainWindow::print_grab() {
  if (check > 99) {
    timer_gif->stop();
    disconnect(timer_gif);
  } else {
    gif.addFrame(mp[check]);
    check += 1;
  }
}



