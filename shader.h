#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QRgb>
#include <qimage.h>
#include <QPainter>
#include <Base/tgaimage.h>
#include <Base/geometry.h>
#include "Base/camera.h"
#include "Base/light.h"
#include "Base/model.h"
#include "Base/Texture.h"

class Shader : public QObject
{
    Q_OBJECT
public:
    explicit Shader(QObject *parent = nullptr);
    Shader(int height, int width) : height(height), width(width) {

    }
    //放大倍数
    int magnification = 50;
    int height;
    int width;
    bool isproject = false;
    bool issoomth = false;
    bool ismove = true;
    bool iscalculate = false;
    bool isTexture = false;
    //深度
    std::vector<std::vector<int>> depth;

private:
    //放大比例
    std::vector<vec3> enlarge(std::vector<vec3> v, int num);
    //判断是否在三角形范围内
    bool inside(std::vector<vec3> vectors, double x, double y);
    //以下全是各种渲染方式
    double flat_shading(vec3 normal, Light light);
    TGAColor gouraud_shading(vec3 normal);
    TGAColor phong_shading(vec3 normal, vec3 color, Light light);
    TGAColor normal_fragment_shader(vec3 normal);
    TGAColor phong_fragment_shader(vec3 normal, vec3 view_pos, vec3 color);
    TGAColor bump_fragment_shader(vec3 normal, vec3 view_pos, double v, double u, Texture texture);



public slots:
    void draw(Model *model, Camera *camera, Light *light);

signals:
    void resultReady(const QImage &image);  // 线程完成工作时发送的信号
};

#endif // SHADER_H
