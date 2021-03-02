#include "Graph.h"
#include <string>
#include <cmath>

using namespace Graph_lib;

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