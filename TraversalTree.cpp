//
// Created by ivb on 30.03.17.
//

#include "Shape.h"
#include "TraversalTree.h"
#include "geometry.h"

#include <vector>
#include <algorithm>

TraversalTree::TraversalTree()
{
    root = nullptr;
}

void TraversalTree::build_from_shapes(const std::vector<Shape*> &shapes)
{
    // создаем корневой узел
    root = new Node;

    // сохраняем копию указателей на объекты
    root->shapes = shapes;

    // устанавливаем ограничивающий объем корневого узла
    set_limiting_box(root);
    
    // начинаем построение с корня
    build_node(root, BY_X);
}

bool TraversalTree::traverse(Point3D p, Point3D v,
                             Point3D *nearest_intersection,
                             Shape **object)
{
    return traverse_routine(root, p, v, nearest_intersection, object);
}

bool TraversalTree::traverse_routine(TraversalTree::Node *node, Point3D p, Point3D v,
                              Point3D *nearest_intersection, Shape **object)
{
    if(node == nullptr) {
        return false;
    }

    if(!box_intersection(p, v, node->A, node->B)) {
        return false;
    }

    // если листовой
    if(node->leaf) {
        // то просто просматриваем все объекты
        return traverse_scan(node, p, v, nearest_intersection, object);
    } else {
        // иначе опускаемся ниже по дереву рекурсивно

        // данные о пересечении в левом поддереве
        Point3D left_int;
        Shape *left_obj;
        bool in_left = traverse_routine(node->left, p, v, &left_int, &left_obj);

        // данные о пересечении в правом поддереве
        Point3D right_int;
        Shape *right_obj;
        bool in_right = traverse_routine(node->right, p, v, &right_int, &right_obj);

        // выбираем из них ближайшее
        if (in_left && in_right) {
            // если пересечение в обоих узлах, то выбираем из них ближайшее
            if (isLessThan((p - left_int).len2(), (p - right_int).len2())) {
                *nearest_intersection = left_int;
                *object = left_obj;
            } else {
                *nearest_intersection = right_int;
                *object = right_obj;
            }
            return true;
        } else if (in_left) {
            // если только в левом
            *nearest_intersection = left_int;
            *object = left_obj;
            return true;
        } else if (in_right) {
            // иначе только в правом
            *nearest_intersection = right_int;
            *object = right_obj;
            return true;
        } else {
            return false;
        }
    }
}

bool TraversalTree::traverse_scan(TraversalTree::Node *node, Point3D p, Point3D v,
                                  Point3D *nearest_intersection, Shape **object)
{
    // расстояние до ближайшей точки пересечения
    ld cur_min_len2 = 1e50;

    // флаг существования пересечения
    bool F = false;

    // перебираем объекты сцены
    for(Shape *obj: node->shapes) {
        // точка пересечения луча и объекта
        Point3D intersection;

        // есть ли пересечение объекта с лучом?
        if(obj->ray_intersection(p, v, &intersection)) {
            // выбираем самое близкое пересечение
            ld len2 = (p - intersection).len2();
            if(isLessThan(len2, cur_min_len2)) {
                // обновляем данные
                cur_min_len2 = len2;
                *nearest_intersection = intersection;
                *object = obj;

                // пересечение уже точно есть
                F = true;
            }
        }
    }
    return F;
}

void TraversalTree::build_node(TraversalTree::Node *node, SPLIT_TYPE stp)
{
    if(node == nullptr) {
        return;
    }
    // разбиваем узел
    split_node(node, stp);

    // продолжаем построение рекурсивно
    build_node(node->left, SPLIT_TYPE((stp + 1) % 3));
    build_node(node->right, SPLIT_TYPE((stp + 1) % 3));
}

bool TraversalTree::split_node(TraversalTree::Node *node, SPLIT_TYPE stp)
{
    // массив событий
    std::vector<Event> events;

    // строим этот массив по примитивам в узле
    build_event_array(node, &events, stp);

    // координаты краев
    ld xmin = 0;
    ld xmax = 0;
    get_limits(node, &xmin, &xmax, stp);

    // разбиваем наилучшим образом
    ld best = 0;
    if(!best_split(events, xmin, xmax, &best)) {
        // если нет, то делаем узел листом
        node->leaf = true;
        return false;
    } else {
        // если да, то заполняем поля
        node->leaf = false;

        node->left = new Node;
        node->right = new Node;

        // заполняем ограничивающий объем в потомках
        fill_boxes(node, best, stp);

        // заполняем список примитивов в левом узле
        fill_node_shapes(node->left, events.cbegin(), events.cend(), best);

        // заполняем список примитивов в правом узле
        fill_node_shapes(node->right, events.crbegin(), events.crend(), best);

        // очищаем список примитивов текущего узла
        node->shapes.clear();
        return true;
    }
}

template<typename Iterator>
void TraversalTree::fill_node_shapes(Node *node, Iterator beg, Iterator end, ld best)
{
    // записываем в узел все примитивы, начавшиеся до линии разбиения
    for(Iterator it = beg; it != end && (best - beg->x) * (best - it->x) > 0; ++it) {
        if(it->type == beg->type) {
            node->shapes.push_back(it->obj);
        }
    }
}

void TraversalTree::build_event_array(TraversalTree::Node *node, std::vector<Event> *events, SPLIT_TYPE stp)
{
    // создаем список событий
    for(Shape *obj : node->shapes) {
        auto p = make_events(obj, stp);
        events->push_back(p.first);
        events->push_back(p.second);
    }

    // сортируем его
    std::sort(events->begin(), events->end(),
              [](const Event &e1, const Event &e2){ return e1.x < e2.x; });
}

bool TraversalTree::best_split(const std::vector<Event> &events, ld xmin, ld xmax, ld *xbest)
{
    // количество примитивов слева и справа от сканирующей прямой
    int left = 0;
    int right = events.size() / 2;

    // флаг предпоследнего события начала
    bool prev_beg = false;

    // свободный член в оптимизируемой функции
    // отражает стоимость спуска на один уровень ниже в дереве
    const ld bias = 10;

    // количество примитивов, дальше которого можно не разбивать
    const int min_child = 8;

    // текущая стоимость прослеживания в разбиваемом узле,
    // если не производить его разбиение
    ld curr_cost = (right - min_child) * (xmax - xmin);

    // текущий минимум и координата, на которой он достигается
    ld min = 1e50;

    // координата предыдущего события
    ld xprev = 1e50;

    for(Event e : events) {
        // пересчитываем количества примитивов
        if(prev_beg) {
            ++left;
        }
        if(e.type) {
            prev_beg = true;
        } else {
            --right;
        }
        // обновляем минимум
        if(!areEqual(xprev, e.x) && // все события с одной координатой обрабатываем вместе
           isLessEqual(xmin, e.x) && isLessEqual(e.x, xmax)) // оптимизируем на отрезке
        {
            ld val = bias + left * (e.x - xmin) + right * (xmax - e.x);
            if(isMoreThan(min, val)) {
                min = val;
                *xbest = e.x;
            }
        }
        xprev = e.x;
    }
    if(isLessThan(min, curr_cost)) {
        return true;
    } else {
        return false;
    }
}

void TraversalTree::fill_boxes(Node *node, ld x, SPLIT_TYPE stp)
{
    Point3D A = node->A;
    Point3D B = node->B;
    switch(stp) {
        case BY_X:
            node->left->A = A;
            node->left->B = {x, B.y, B.z};
            node->right->A = {x, A.y, A.z};
            node->right->B = B;
            break;

        case BY_Y:
            node->left->A = A;
            node->left->B = {B.x, x, B.z};
            node->right->A = {A.x, x, A.z};
            node->right->B = B;
            break;

        case BY_Z:
            node->left->A = A;
            node->left->B = {B.x, B.y, x};
            node->right->A = {A.x, A.y, x};
            node->right->B = B;
            break;
    }
}

std::pair<TraversalTree::Event, TraversalTree::Event>
    TraversalTree::make_events(Shape *obj, SPLIT_TYPE stp)
{
    // возвращаемое значение
    std::pair<Event, Event> events;
    events.first.type = true;
    events.second.type = false;
    events.first.obj = obj;
    events.second.obj = obj;

    // ограничивающий объем
    Point3D A, B;
    obj->limiting_box(&A, &B);

    // определяем координату события
    switch(stp) {
        case BY_X:
            events.first.x = A.x;
            events.second.x = B.x;
            break;

        case BY_Y:
            events.first.x = A.y;
            events.second.x = B.y;
            break;

        case BY_Z:
            events.first.x = A.z;
            events.second.x = B.z;
            break;
    }
    return events;
}

void TraversalTree::get_limits(TraversalTree::Node *node, ld *xmin, ld *xmax,
                               TraversalTree::SPLIT_TYPE stp)
{
    if(stp == BY_X) {
        *xmin = node->A.x;
        *xmax = node->B.x;
    } else if(stp == BY_Y) {
        *xmin = node->A.y;
        *xmax = node->B.y;
    } else if(stp == BY_Z) {
        *xmin = node->A.z;
        *xmax = node->B.z;
    }
}

void TraversalTree::set_limiting_box(TraversalTree::Node *node) 
{
    node->A = {1e50, 1e50, 1e50};
    node->B = {-1e50, -1e50, -1e50};
    for(Shape *obj : node->shapes) {
        Point3D A, B;
        obj->limiting_box(&A, &B);
        node->A.x = std::min(node->A.x, A.x);
        node->A.y = std::min(node->A.y, A.y);
        node->A.z = std::min(node->A.z, A.z);
        node->B.x = std::max(node->B.x, B.x);
        node->B.y = std::max(node->B.y, B.y);
        node->B.z = std::max(node->B.z, B.z);
    }
}
