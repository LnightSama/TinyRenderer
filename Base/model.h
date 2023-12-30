#include <vector>
#include <string>
#include "geometry.h"
#include "tgaimage.h"

class Model {
    std::vector<vec3> verts{};     // 顶点数组 array of vertices 
    std::vector<vec2> tex_coord{}; // tex 坐标的逐顶点数组 per-vertex array of tex coords
    std::vector<vec3> norms{};     // 法向量 per-vertex array of normal vectors
    std::vector<int> facet_vrt{};
    std::vector<int> facet_tex{};  // 以上数组中的每三角形索引 per-triangle indices in the above arrays
    std::vector<int> facet_nrm{};

public:
    Model(const std::string filename);
    int nverts() const;
    int nfaces() const;
    std::vector<int> face(const int i) const;
    vec3 normal(const int iface, const int nthvert) const; // 每个三角形角法线顶点 per triangle corner normal vertex
    vec3 normal(const vec2 &uv) const;                     // 每个三角形角法线顶点从法线贴图纹理获取法线向量 fetch the normal vector from the normal map texture
    vec3 vert(const int i) const;
    vec3 vert(const int iface, const int nthvert) const;
    vec2 uv(const int iface, const int nthvert) const;
    const TGAImage& diffuse()  const { return diffusemap;  }
    const TGAImage& specular() const { return specularmap; }
    void load_texture(const std::string filename, const std::string suffix, TGAImage &img);
    TGAImage diffusemap{};         // 漫反射颜色纹理 diffuse color texture
    TGAImage normalmap{};          // 法线贴图纹理 normal map texture
    TGAImage specularmap{};        // 镜面反射贴图纹理 specular map texture
    vec3 rotation_formula(vec3 k, vec3 v, float deg);
};

