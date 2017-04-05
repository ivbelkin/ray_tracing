//
// Created by ivb on 30.03.17.
//

#ifndef RAY_TRACING_KDTREE_H
#define RAY_TRACING_KDTREE_H

#include "Shape.h"

class TraversalTree {
public:
    TraversalTree();

    // построить дерево по списку объектов
    void build_from_shapes(const std::vector<Shape*> &_shapes);

    // наити ближайшее пересечение луча с объектом
    bool traverse(Point3D p, Point3D v, Point3D *nearest_intersection, Shape **object);

private:
    // узел дерева
    struct Node;

    // событие начала или конца границы примитива
    // используется при поиске наилучшего разбиения узла
    struct Event;

    // ось, перпендикулярно поторой проводится разбиение
    enum SPLIT_TYPE {BY_X = 0, BY_Y, BY_Z};

    // корень дерева
    Node *root;

    // поиск первого пересечения луча с объектом сцены
    bool traverse_routine(Node *node, Point3D p, Point3D v,
                          Point3D *nearest_intersection, Shape **object);

    // перебор объектов в узле в поисках первого пересечения
    bool traverse_scan(Node *node, Point3D p, Point3D v,
                       Point3D *nearest_intersection, Shape **object);;

    // строит поддерево с корнем в node
    void build_node(Node *node, SPLIT_TYPE stp);

    // производит разбиение узла на два дочерних
    // возвращает true, если разбиение было произведено
    // устанавливает значения left->A, left->B, right->A, right->B
    bool split_node(Node *node, SPLIT_TYPE stp);

    // записывает в поле node->shapes все объекты, ограничивающий
    // параллелепипед которых пересекается с таковым узла
    template<typename Iterator>
    void fill_node_shapes(Node *node, Iterator beg, Iterator end, ld best);

    // построить массив событий
    void build_event_array(Node *node, std::vector<Event> *events, SPLIT_TYPE stp);

    // наити наилучшее разбиение соответствующее некоторому событию
    // вернуть итератор этого события в массиве событий
    // возвращает false, если разбиение не нужно производить
    bool best_split(const std::vector<Event> &events, ld xmin, ld xmax, ld *min);

    // заполнить поля, соответствующие ограничивающим объемам в потомках узла
    // в соответствии с лучшим разбиением
    void fill_boxes(Node *node, ld x, SPLIT_TYPE stp);

    // создать объект события для объекта соответствующего типа
    std::pair<Event, Event> make_events(Shape *obj, SPLIT_TYPE stp);

    // граници ограничивающей области
    void get_limits(Node *node, ld *xmin, ld *xmax, SPLIT_TYPE stp);

    // задает границы узла в соответствии со списком его примитивов
    void set_limiting_box(Node *node);

    // упорядочивает узлы по расстоянию до точки p
    void sort_nodes(Point3D p, Node* &first, Node* &second);
};

struct TraversalTree::Node {
    Node() :
            left(nullptr),
            right(nullptr),
            leaf(true)
    {
        A = {0, 0, 0};
        B = {0, 0, 0};
    }

    // левый дочерний узел
    Node *left;

    // правый дочерний узел
    Node *right;

    // противоположные по диагонали вершины
    Point3D A;
    Point3D B;

    // true если узел является листом
    bool leaf;

    // объекты узла
    // не пуст если и только если leaf == true
    std::vector<Shape*> shapes;
};

struct TraversalTree::Event {
    // координата события
    ld x;

    // примитив, событие для которого отслеживается
    Shape *obj;

    // тип события
    // первое событие в массиве событий всегда начало примитива
    bool type;
};
#endif //RAY_TRACING_KDTREE_H
