//
// Created by ivb on 19.03.17.
//

#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <cctype>

#include "Triangle.h"

#include "geometry.h"

void ObjLoader::load(const std::string _filename, Scene *_scene)
{
    scene = _scene;

    obj_filename = _filename;

    fin.open(obj_filename);

    std::string cmd = "";

    int line_number = 0;

    while(fin >> cmd) {
        // пропускаем комментарии
        if(cmd[0] == '#') {
            std::getline(fin, cmd, '\n');
        } else if(cmd == "mtllib") {
            std::getline(fin, mtl_filename, '\n');
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
    vt.push_back({u, v, w});
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
                                   {255, 255, 255}, n);
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