//
// Created by ivb on 19.03.17.
//

#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <cctype>
#include <string>

#include "Triangle.h"

#include "geometry.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void ObjLoader::load(const std::string obj_filename, Scene *_scene)
{
    scene = _scene;

    fin.open(obj_filename);

    std::string cmd = "";

    int line_number = 0;

    cur_ap = nullptr;

    while(fin >> cmd) {
        // пропускаем комментарии
        if(cmd[0] == '#') {
            std::getline(fin, cmd, '\n');
        } else if(cmd == "mtllib") {
            std::string mtl_filename;
            fin >> mtl_filename;
            read_mtl(mtl_filename);
        } else if(cmd == "v") {
            read_v();
        } else if(cmd == "vt") {
            read_vt();
        } else if(cmd == "vn") {
            read_vn();
        } else if(cmd == "g") {
            read_g();
        } else if(cmd == "s") {
            read_s();
        } else if(cmd == "f") {
            read_f();
        } else if(cmd == "usemtl") {
            std::string name;
            fin >> name;
            cur_ap = scene->materials[name];
        }
        ++line_number;
    }
    if(fin.fail() || fin.bad()) {
        std::cerr << "An error occure while reading the file\n";
        fin.clear();
    }
}

void ObjLoader::read_v()
{
    ld x, y, z;
    ld w = 1.0;
    fin >> x >> y >> z;
    if(fin.peek() == ' ') {
        fin >> w;
    }
    v.push_back({x, y, z});
}

void ObjLoader::read_vt()
{
    ld u = 0.0;
    ld v = 0.0;
    ld w = 0.0;
    fin >> u;
    if(fin.peek() == ' ') {
        fin >> v;
    }
    if(fin.peek() == ' ') {
        fin >> w;
    }
    u = std::min(u, 1.0l);
    v = std::min(v, 1.0l);
    w = std::min(w, 1.0l);
    vt.push_back({u, 1.0-v});
}

void ObjLoader::read_vn()
{
    ld i, j, k;
    fin >> i >> j >> k;
    vn.push_back({i, j, k});
}

void ObjLoader::read_g()
{
    std::string group_name;
    fin >> group_name;
}

void ObjLoader::read_s()
{
    std::string shading_group;
    fin >> shading_group;
}

void ObjLoader::read_f()
{
    // общая вершина треугольников
    int cvertex = -1;
    int ctexture = -1;
    int cnormal = -1;

    std::string face;
    fin >> face;

    parse_face_element(face, &cvertex, &ctexture, &cnormal);

    int pvertex = -1;
    int ptexture = -1;
    int pnormal = -1;

    fin >> face;
    parse_face_element(face, &pvertex, &ptexture, &pnormal);

    while(fin.peek() != '\n') {
        int vertex = -1;
        int texture = -1;
        int normal = -1;
        fin >> face;
        parse_face_element(face, &vertex, &texture, &normal);
        Point3D n = (vn[normal - 1] + vn[pnormal - 1] + vn[cnormal - 1]);
        Triangle *t = new Triangle(v[cvertex - 1], v[pvertex - 1], v[vertex - 1],
                                   vt[ctexture - 1], vt[ptexture - 1], vt[texture - 1], n);
        t->reset_material(cur_ap);
        scene->add_shape(t);
        pvertex = vertex;
        ptexture = texture;
        pnormal = normal;
        while(!isalnum(fin.peek()) && fin.peek() != '\n') {
            fin.get();
        }
    }
}

void ObjLoader::parse_face_element(std::string s, int *vertex, int *texture, int *normal)
{
    std::regex pattern("([\\d]+)(/([\\d]+)?(/([\\d]+))?)?");
    std::smatch result;
    std::regex_match(s, result, pattern);
    s.assign(result[1].first, result[1].second);
    *vertex = atoi(s.c_str());
    if(result[3].matched) {
        s.assign(result[3].first, result[3].second);
        *texture = atoi(s.c_str());
    }
    if(result[5].matched) {
        s.assign(result[5].first, result[5].second);
        *normal = atoi(s.c_str());
    }
}

void ObjLoader::read_mtl(const std::string &filename)
{
    IMG_Init(IMG_INIT_JPG);
    std::ifstream mtlin(filename);
    std::string cmd;
    cur_ap = nullptr;
    ld r, g, b;
    while(mtlin >> cmd) {
        if(cmd[0] == '#') {
            continue;
        } else if(cmd == "newmtl"){
            std::string name;
            mtlin >> name;
            auto p = scene->materials.insert(std::make_pair(name, new Appearance));
            assert(p.second);
            cur_ap = p.first->second;
            cur_ap->base = new Material;
            cur_ap->map_Kd = nullptr;
        } else if(cmd == "Ka") {
            mtlin >> r >> g >> b;
            cur_ap->base->Ka = Color(r, g, b);
        } else if(cmd == "Kd") {
            mtlin >> r >> g >> b;
            cur_ap->base->Kd = Color(r, g, b);
        } else if(cmd == "Ks") {
            mtlin >> r >> g >> b;
            cur_ap->base->Ks = Color(r, g, b);
        } else if(cmd == "d") {
            mtlin >> cur_ap->base->d;
        } else if(cmd == "Ns") {
            mtlin >> cur_ap->base->Ns;
        } else if(cmd == "Ni") {
            mtlin >> cur_ap->Ni;
        } else if(cmd == "Tf") {
            mtlin >> r >> g >> b;
            cur_ap->base->Tf = Color(r, g, b);
        } else if(cmd == "illum") {
            mtlin >> cur_ap->illum;
        } else if(cmd == "map_Kd") {
            std::string name;
            mtlin >> name;
            load_texture(name);
        }
    }
}

void ObjLoader::load_texture(const std::string &filename)
{
    SDL_Surface *sfr = IMG_Load(filename.c_str());
    if(sfr == nullptr) {
        std::cerr << "Error " << IMG_GetError() << std::endl;
    }
    cur_ap->map_Kd = sfr;
}
