#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->viewport, SIGNAL(mouseMovePitch(int)), this, SLOT(set_horizontalSlider_4_value(int)));
    connect(ui->viewport, SIGNAL(mouseMoveYaw(int)), this, SLOT(set_horizontalSlider_5_value(int)));
    connect(ui->viewport, SIGNAL(mouseWheelEvent()), this, SLOT(set_horizontalSlider_3_value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Selectfile_clicked()
{
    // 选择文件
    QString file  = QFileDialog::getOpenFileName(this, tr("选择模型文件"), "./", tr("File(*.obj*)"));
    ui->filelabel->setText(file);
    ui->viewport->load_model(file);
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    ui->viewport->camera.sight_distance = value;
    ui->viewport->shader->ismove = true;
}

void MainWindow::set_horizontalSlider_3_value()
{
    ui->horizontalSlider_3->setValue(ui->viewport->camera.sight_distance);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->viewport->light.revolve_pitch(value);
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_checkBox_3_clicked()
{
    ui->viewport->shader->isproject = ui->checkBox_3->isChecked();
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    ui->viewport->camera.revolve_pitch(value);
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    ui->viewport->camera.revolve_yaw(value);
    ui->viewport->shader->ismove = true;
}

void MainWindow::set_horizontalSlider_4_value(int value)
{
    ui->horizontalSlider_4->setValue(value);
}

void MainWindow::set_horizontalSlider_5_value(int value)
{
    ui->horizontalSlider_5->setValue(value);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->viewport->light.revolve_yaw(value);
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_checkBox_clicked()
{
    ui->viewport->shader->issoomth = ui->checkBox->isChecked();
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->viewport->shader->magnification = arg1;
    ui->viewport->shader->ismove = true;
}


void MainWindow::on_TextureSelet_clicked()
{
    QString file  = QFileDialog::getOpenFileName(this, tr("选择纹理文件"), "./", tr("File(*.tga* *.jpg*)"));
    if(file != "") {
        qDebug() << file;
        ui->viewport->model->load_texture(file.toStdString(), ".tga",    ui->viewport->model->diffusemap ); // 漫反射颜色纹理 diffuse color texture
        ui->viewport->shader->isTexture = true;
    } else ui->viewport->shader->isTexture = false;
    ui->viewport->shader->ismove = true;
}

