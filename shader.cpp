#include "shader.h"

Shader::Shader(QObject *parent)
    : QObject{parent}
{}

void Shader::draw(Model *model, Camera *camera, Light *light)
{
    QImage image(width, height, QImage::Format_RGB32);
    image.fill(Qt::black);

    QPainter painter(&image);
    if(ismove) {
        ismove = false;
        iscalculate = true;
        depth = std::vector<std::vector<int>>(width, std::vector<int>(height, INT_MAX));

        for (int i = 0; i < model->nfaces(); i++) {

            vec normal = model->normal(i, 0) + model->normal(i, 1) + model->normal(i, 2);
            normal = vec3(0,0,0) - normal.normalize();
            //简单的背面剔除
            if (normal * camera->forward <= 0) continue;
            //从归一化转换
            std::vector<vec3> vectors = {
                model->vert(i, 0) * magnification - camera->position,
                model->vert(i, 1) * magnification - camera->position,
                model->vert(i, 2) * magnification - camera->position,
            };

            TGAColor color = TGAColor(255, 255, 255, 255);

            //                                          Top,Bottom,        Right,left
            std::vector<double> area = { 0, (double)height, 0, (double)width };
            //投射到屏幕，从三维坐标，转换为左上角为原点的二维坐标
            std::vector<vec3> projections = {
                camera->get_projection(vectors[0], isproject) + vec3(width / 2, height / 2, 0),
                camera->get_projection(vectors[1], isproject) + vec3(width / 2, height / 2, 0),
                camera->get_projection(vectors[2], isproject) + vec3(width / 2, height / 2, 0)
            };
            //三角形的包围盒
            area[0] = std::max({projections[0].y, projections[1].y, projections[2].y, area[0]});
            area[1] = std::min({projections[0].y, projections[1].y, projections[2].y, area[1]});
            area[2] = std::max({projections[0].x, projections[1].x, projections[2].x, area[2]});
            area[3] = std::min({projections[0].x, projections[1].x, projections[2].x, area[3]});

            for(int y = std::max(area[1], 0.0); y < area[0] && y < height; y++) {
                QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(height - y - 1));
                for(int x = std::max(area[3], 0.0); x < area[2] && x < width; x++) {
                    if (inside(projections, x + 0.5, y + 0.5))
                    {
                        double a = cross(vec2(projections[2].x - x, projections[2].y - y), vec2(projections[1].x - x, projections[1].y - y)) / 2;
                        double b = cross(vec2(projections[0].x - x, projections[0].y - y), vec2(projections[2].x - x, projections[2].y - y)) / 2;
                        double c = cross(vec2(projections[1].x - x, projections[1].y - y), vec2(projections[0].x - x, projections[0].y - y)) / 2;
                        double alpha = a / (a + b + c);
                        double beta = b / (a + b + c);
                        double gamma = 1 - alpha - beta;
                        vec3 n = - alpha * model->normal(i, 0) - beta * model->normal(i, 1) - gamma * model->normal(i, 2);
                        n = n.normalize();
                        if (n * camera->forward <= 0) continue;
                        double z = alpha * projections[0].z + beta * projections[1].z + gamma * projections[2].z;
                        if (depth[x][y] > z && (z > 0 || isproject))
                        {
                            depth[x][y] = z;
                            if(isTexture) {
                                vec2 bump_vec = alpha * model->uv(i, 0) + beta * model->uv(i, 1) + gamma * model->uv(i, 2);
                                color = model->diffuse().get(bump_vec.x * model->diffuse().width(), bump_vec.y * model->diffuse().height());
                            }
                            TGAColor result_color = color * flat_shading(issoomth ? normal : n, *light);
                            line[x] = qRgb(result_color[2], result_color[1], result_color[0]);
                        }
                    }

                }
            }
        }
    }
    //执行结束就发送resultReady方法作为通知
    emit resultReady(image);
}

double Shader::flat_shading(vec3 normal, Light light)
{
    double n_l = normal * light.direction;
    double a = std::max(0., n_l);
    return a;
}

TGAColor Shader::gouraud_shading(vec3 normal)
{
    normal = (normal.normalize() + vec3(1.0f, 1.0f, 1.0f)) / 2.f;
    return TGAColor(normal.x * 255, normal.y * 255, normal.z * 255);
}

TGAColor Shader::phong_shading(vec3 normal, vec3 color, Light light)
{
    vec3 l2 = vec3(-20, 20, 0).normalize();

    normal = normal.normalize();
    double n_l = std::max(0., -1 * normal * light.direction);
    double n_h = std::max(0., normal * l2);

    vec3 ka = vec3(0.005, 0.005, 0.005);
    vec3 kd = color;
    vec3 ks = vec3(0.7937, 0.7937, 0.7937);

    double r1 = vec3(20, 20, 20).norm2();
    double r2 = vec3(-20, 20, 0).norm2();
    vec3 r = ka * 10.0;
    r = r + kd * 500.0 / r1 * n_l + ks * 500.0 / r1 * pow(n_l, 32);
    r = r + kd * 500.0 / r2 * n_h + ks * 500.0 / r2 * pow(n_h, 32);

    for (int i = 0;i < 3;i++) {
        if (r[i] > 1)
        {
            r[i] = 1;
        } else if (r[i] < 0)
        {
            r[i] = 0;
        }
    }
    r = r * 255.0;
    //std::cout << vec3(static_cast<unsigned int>(color[2]), static_cast<unsigned int>(color[1]), static_cast<unsigned int>(color[0])) << "==" << r << std::endl;
    return TGAColor(r[0], r[1], r[2]);
}

bool Shader::inside(std::vector<vec3> vectors, double x, double y)
{

    double direction[3] = { 0., 0. ,0. };
    for (int i = 0; i < 3; i++) {
        vec3 v0 = vectors[i];
        vec3 v1 = vectors[(i + 1) % 3];
        direction[i] = (y - v0.y) * (v1.x - v0.x) - (x - v0.x) * (v1.y - v0.y);
    }

    double i = std::abs(direction[0]) + std::abs(direction[1]) + std::abs(direction[2]);
    double j = std::abs(direction[0] + direction[1] + direction[2]);

    //cout << i << " " << j << endl;
    return i == j;
}
