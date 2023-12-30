#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "viewport.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
//主窗口
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_Selectfile_clicked();

    void on_horizontalSlider_3_valueChanged(int value);

    void set_horizontalSlider_3_value();

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_3_clicked();

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void set_horizontalSlider_4_value(int value);

    void set_horizontalSlider_5_value(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_checkBox_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_TextureSelet_clicked();



private:
    Ui::MainWindow *ui;
    //用于显示3维世界的视口
    ViewPort *viewport;

};
#endif // MAINWINDOW_H
