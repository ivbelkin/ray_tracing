//
// Created by ivb on 19.03.17.
//

#ifndef RAY_TRACING_OBJREADER_H
#define RAY_TRACING_OBJREADER_H

#include "Scene.h"
#include "geometry.h"
#include <string>
#include <vector>
#include <fstream>

// импортирует 3D модель из фаила .obj
class ObjLoader {
public:
    // считать модель из .obj фаила и создать сцену
    void load(const std::string _filename, Scene *_scene);

private:
    // сцена для сохранения модели
    Scene *scene;

    Appearance *cur_ap;

    // .obj фаил с геометрией
    // std::string obj_filename;

    // .mtl фаил с метериалами
    // std::string mtl_filename;

    // ассоциированный поток
    std::ifstream fin;

    // вершины
    std::vector<Point3D> v;

    // текстурные координаты
    std::vector<Point2D> vt;

    // нормали
    std::vector<Point3D> vn;

    // вызавается для строк: v ...
    void read_v();

    // вызавается для строк: vt ...
    void read_vt();

    // вызавается для строк: vn ...
    void read_vn();

    // вызавается для строк: g ...
    void read_g();

    // вызавается для строк: s ...
    void read_s();

    // вызавается для строк: f ...
    void read_f();

    // разбор одного f выражения: v[/[vt][/vn]]
    void parse_face_element(std::string s, int *vertex,
                            int *texture, int *normal);

    // подготовить библиотеку материалов
    void read_mtl(const std::string &filename);

    // установить текстуру
    void load_texture(const std::string &filename);
};

#endif //RAY_TRACING_OBJREADER_H
