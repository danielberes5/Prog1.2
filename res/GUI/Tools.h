#include "Graph.h"
#include <string>
#include <cmath>

using namespace Graph_lib;

constexpr double PI = 3.14159265;

// Ex 1 - Arc

struct Arc : Shape {
    Arc(Point p, int rr, double start, double end);

    void draw_lines() const;

    int radius() const { return r; }

private:
    int r;
    double start;
    double end;
};

// Ex 2 - Box

struct Box : Shape {
    Box(Point p, int w, int h, int r);

    void draw_lines() const;

private:
    Vector_ref<Arc> corners;
    Lines sides;
};

// Ex 3 - Arrow

struct Arrow : Shape {
    Arrow(Point p1, Point p2);

    void draw_lines() const;
    
    void set_size(int s) { size = s; }

private:
    int size = 12;
    int iso = 20;
};

// Ex 6 - Text_box

Point n (Rectangle& r);
Point s (Rectangle& r);
Point e (Rectangle& r);
Point w (Rectangle& r);
Point nw (Rectangle& r);
Point ne (Rectangle& r);
Point sw (Rectangle& r);
Point se (Rectangle& r);
Point center (Rectangle& r);

struct Text_box : Rectangle {
    Text_box(Point pp, int ww, int hh, string ss);

    void draw_lines() const;

private:
    Text label;
};

