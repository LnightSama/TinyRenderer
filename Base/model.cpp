#include <iostream>
#include <sstream>
#include "model.h"

Model::Model(const std::string filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            //v 几何体顶点(Geometric vertices)
            iss >> trash;
            vec3 v;
            for (int i=0;i<3;i++) iss >> v[i];
            v = rotation_formula(vec3(1,0,0), v, 90);
            verts.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            //vn 顶点法线(Vertex normals)
            iss >> trash >> trash;
            vec3 n;
            for (int i=0;i<3;i++) iss >> n[i];
            n = rotation_formula(vec3(1,0,0), n, 90);
            norms.push_back(n.normalize());
        } else if (!line.compare(0, 3, "vt ")) {
            //vt 贴图坐标点(Texture vertices)
            iss >> trash >> trash;
            vec2 uv;
            for (int i=0;i<2;i++) iss >> uv[i];
            tex_coord.push_back({uv.x, 1-uv.y});
        }  else if (!line.compare(0, 2, "f ")) {
            //f 面(Face)
            int f,t,n;
            iss >> trash;
            int cnt = 0;
            while (iss >> f >> trash >> t >> trash >> n) {
                facet_vrt.push_back(--f);
                facet_tex.push_back(--t);
                facet_nrm.push_back(--n);
                cnt++;
            }
            if (3!=cnt) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                in.close();
                return;
            }
        }
    }
    in.close();
    std::cerr << "# v# " << nverts() << " f# "  << nfaces() << " vt# " << tex_coord.size() << " vn# " << norms.size() << std::endl;
    // load_texture(filename, "_diffuse.tga",    diffusemap ); // 漫反射颜色纹理 diffuse color texture
    // load_texture(filename, "_nm_tangent.tga", normalmap  ); // 法线贴图纹理 normal map texture
    // load_texture(filename, "_spec.tga",       specularmap); // 镜面反射贴图纹理 specular map texture
}

int Model::nverts() const {
    return verts.size();
}

int Model::nfaces() const {
    return facet_vrt.size()/3;
}

std::vector<int> Model::face(const int i) const {
    std::vector<int> iface{};
    iface.push_back(facet_vrt[i * 3 + 0]);
    iface.push_back(facet_vrt[i * 3 + 1]);
    iface.push_back(facet_vrt[i * 3 + 2]);
    return iface;
}


vec3 Model::vert(const int i) const {
    return verts[i];
}

vec3 Model::vert(const int iface, const int nthvert) const {
    return verts[facet_vrt[iface*3+nthvert]];
}

void Model::load_texture(std::string filename, const std::string suffix, TGAImage &img) {
    size_t dot = filename.find_last_of(".");
    if (dot==std::string::npos) return;
    std::string texfile = filename.substr(0,dot) + suffix;
    std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
}

vec3 Model::rotation_formula(vec3 k, vec3 v, float deg)
{
    k = k.normalize();
    vec3 vl = vec3() - cross(k, cross(k, v));
    vec3 vl_rot = vl * std::cos(deg / 180.0 * acos(-1)) + cross(k, v) * std::sin(deg / 180.0 * acos(-1));
    return vl_rot + k * v * k;
}

vec3 Model::normal(const vec2 &uvf) const {
    TGAColor c = normalmap.get(uvf[0]*normalmap.width(), uvf[1]*normalmap.height());
    return vec3{(double)c[2],(double)c[1],(double)c[0]}*2./255. - vec3{1,1,1};
}

vec2 Model::uv(const int iface, const int nthvert) const {
    return tex_coord[facet_tex[iface*3+nthvert]];
}

vec3 Model::normal(const int iface, const int nthvert) const {
    return norms[facet_nrm[iface*3+nthvert]];
}

