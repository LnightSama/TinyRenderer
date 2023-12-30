#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QPainter>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include "Base/tgaimage.h"
#include "Base/camera.h"
#include "Base/light.h"
#include "shader.h"

namespace Ui {
class ViewPort;
}

class ViewPort : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPort(QWidget *parent = nullptr);
    ~ViewPort();
    void load_model(QString file);
    void load_texture(const std::string filename, const std::string suffix, TGAImage &img);

public:
    //相机
    Camera camera;
    //3d模型文件
    Model* model;
    //线性光源
    Light light;
    //子线程
    QThread renderer_thread;
    //线程执行者
    Shader *shader;
    int count = 0;
    QString fps = 0;

private:
    //控件本体
    Ui::ViewPort *ui;
    //图片
    QImage image;
    QPointF temppos;

    // QWidget interface
protected:
    //控件的绘制事件，每当切换应用程序时就会触发
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void handleResults(const QImage &image);  // 处理子线程执行的结果

signals:
    void operate(Model *model, Camera *camera, Light *light);  // 发送信号，触发线程
    void mouseMoveYaw(int value);
    void mouseMovePitch(int value);
    void mouseWheelEvent();

};

#endif // VIEWPORT_H
