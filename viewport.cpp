#include "viewport.h"
#include "ui_viewport.h"

ViewPort::ViewPort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewPort), camera(), light()
{

    //setStyleSheet("background-color:black;");
    shader = new Shader(height(), width());
    shader->moveToThread(&renderer_thread);
    // operate 信号发射后启动线程工作
    connect(this, SIGNAL(operate(Model*,Camera*,Light*)), shader, SLOT(draw(Model*,Camera*,Light*)));
    // 该线程结束时销毁
    connect(&renderer_thread, &QThread::finished, shader, &QObject::deleteLater);
    // 线程结束后发送信号，对结果进行处理
    connect(shader, SIGNAL(resultReady(QImage)), this, SLOT(handleResults(QImage)));
    //线程启动
    renderer_thread.start();

    QTimer *time = new QTimer(this);
    connect(time,&QTimer::timeout,this,[=](){
        fps = QString::number(count);
        count = 0;
    });
    time->start(1000);  // 每秒触发一次fps刷新

    // 发射信号，开始执行
    qDebug() << "emit the signal to execute!" ;
    qDebug() << "\tCurrent thread ID:" << QThread::currentThreadId() << '\n' ;

    ui->setupUi(this);
}

ViewPort::~ViewPort()
{
    renderer_thread.quit();
    renderer_thread.wait();
    delete ui;
}

void ViewPort::load_model(QString file)
{
    model = new Model(file.toStdString());
    emit operate(model, &camera, &light);
}

void ViewPort::showEvent(QShowEvent *event)
{
    shader->height = height();
    shader->width = width();

    // 调用父类的 showEvent 以确保正常处理其他 showEvent 事件
    QWidget::showEvent(event);
}

void ViewPort::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) temppos = event->globalPosition();
}

void ViewPort::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        QPointF temp = event->globalPosition();
        if(temppos.y() - temp.y() > 0.1) camera.revolve_pitch(camera.pitch + camera.velocity);
        else if(temppos.y() - temp.y() < -0.1) camera.revolve_pitch(camera.pitch - camera.velocity);
        if(temppos.x() - temp.x() < -0.1) camera.revolve_yaw(camera.yaw + camera.velocity);
        else if(temppos.x() - temp.x() > 0.1) camera.revolve_yaw(camera.yaw - camera.velocity);
        temppos = temp;
        shader->ismove = true;
        emit mouseMoveYaw(camera.yaw);
        emit mouseMovePitch(camera.pitch);
    }
    QWidget::mouseMoveEvent(event);
}

void ViewPort::wheelEvent(QWheelEvent *event)
{
    int step = (event->angleDelta() / 8).y() / 15;
    if(camera.sight_distance > 0 && camera.sight_distance < 99) {
        if(step > 0){                    // 当滚轮远离使用者时
            camera.sight_distance = camera.sight_distance + 1;              // 进行放大
        }else{                                     // 当滚轮向使用者方向旋转时
            camera.sight_distance = camera.sight_distance - 1;              // 进行缩小
        }
        emit mouseWheelEvent();
    }
    shader->ismove = true;
}

void ViewPort::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(Qt::red));
    painter.drawImage(0, 0, image);
    painter.drawText(QPointF(20,30), fps);
    painter.drawText(QPointF(20,50), QString::number(camera.yaw));
    painter.drawText(QPointF(20,70), QString::number(camera.pitch));
    QWidget::paintEvent(event);
}

void ViewPort::handleResults(const QImage &image)
{
    //加载计算好的图像
    if(shader->iscalculate) {this->image = image;shader->iscalculate = false;}
    //累计一秒内重绘的次数
    count++ ;
    //更新画面
    update();
    //循环
    emit operate(model, &camera, &light);
}





