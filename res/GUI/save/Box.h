#include "Graph.h"
#include "Arc.h"
#include <string>
#include <cmath>

using namespace Graph_lib;

// Ex 2 - Box

struct Box : Shape {
    Box(Point p, int w, int h, int r);

    void draw_lines() const;

private:
    Vector_ref<Arc> corners;
    Lines sides;
};