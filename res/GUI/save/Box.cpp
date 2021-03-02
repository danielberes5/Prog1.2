#include "Box.h"
#include <iostream>

using namespace Graph_lib;

Box::Box(Point p, int w, int h, int r)
{
    sides.add(Point{p.x + r, p.y}, Point{p.x+w-r, p.y});    // top
    sides.add(Point{p.x+w, p.y+r}, Point{p.x+w, p.y+h-r});  // right
    sides.add(Point{p.x+w-r, p.y+h}, Point{p.x+r, p.y+h});  // bottom
    sides.add(Point{p.x, p.y+h-r}, Point{p.x, p.y+r});      // left

    corners.push_back(new Arc{Point{p.x+w-r, p.y+r}, r, 0, 90});        // tr
    corners.push_back(new Arc{Point{p.x+r, p.y+r}, r, 90, 180});        // tl
    corners.push_back(new Arc{Point{p.x+r, p.y+h-r}, r, 180, 270});     // bl
    corners.push_back(new Arc{Point{p.x+w-r, p.y+h-r}, r, 270, 360});   // br
}

void Box::draw_lines() const
{
    for (int i = 0; i < 4; ++i)
        corners[i].draw_lines();

    sides.draw_lines();
}