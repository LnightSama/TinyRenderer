#include <vector>
#include <string>
#include "geometry.h"
#include "tgaimage.h"

class Model {
    std::vector<vec3> verts{};     // �������� array of vertices 
    std::vector<vec2> tex_coord{}; // tex ������𶥵����� per-vertex array of tex coords
    std::vector<vec3> norms{};     // ������ per-vertex array of normal vectors
    std::vector<int> facet_vrt{};
    std::vector<int> facet_tex{};  // ���������е�ÿ���������� per-triangle indices in the above arrays
    std::vector<int> facet_nrm{};

public:
    Model(const std::string filename);
    int nverts() const;
    int nfaces() const;
    std::vector<int> face(const int i) const;
    vec3 normal(const int iface, const int nthvert) const; // ÿ�������νǷ��߶��� per triangle corner normal vertex
    vec3 normal(const vec2 &uv) const;                     // ÿ�������νǷ��߶���ӷ�����ͼ�����ȡ�������� fetch the normal vector from the normal map texture
    vec3 vert(const int i) const;
    vec3 vert(const int iface, const int nthvert) const;
    vec2 uv(const int iface, const int nthvert) const;
    const TGAImage& diffuse()  const { return diffusemap;  }
    const TGAImage& specular() const { return specularmap; }
    void load_texture(const std::string filename, const std::string suffix, TGAImage &img);
    TGAImage diffusemap{};         // ��������ɫ���� diffuse color texture
    TGAImage normalmap{};          // ������ͼ���� normal map texture
    TGAImage specularmap{};        // ���淴����ͼ���� specular map texture
    vec3 rotation_formula(vec3 k, vec3 v, float deg);
};

