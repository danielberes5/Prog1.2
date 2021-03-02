#include "Arc.h"
#include <iostream>

using namespace Graph_lib;

// Ex 1 - Arc

Arc::Arc(Point p, int rr, double s, double e)
    : r{rr}, start{s}, end{e}
{
    add(Point{p.x-r, p.y-r});
}

void Arc::draw_lines() const
{
    if (color().visibility())
        fl_arc(point(0).x, point(0).y, r+r, r+r, start, end);
}