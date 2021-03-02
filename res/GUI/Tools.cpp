#include "Tools.h"
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

// Ex 2 - Box

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

// Ex 3 - Arrow

Arrow::Arrow(Point tail, Point tip)
{
    add(tail);
    add(tip);
}

void Arrow::draw_lines() const
{
    constexpr double PI = 3.14159265;

    int diff_x = point(1).x - point(0).x;
    int diff_y = point(1).y - point(0).y;
    double angle = atan2(diff_y, diff_x)*180/PI;

    double x1 = point(1).x - cos((angle-iso)*PI/180) * size;
    double y1 = point(1).y - sin((angle-iso)*PI/180) * size;

    double x2 = point(1).x - cos((angle+iso)*PI/180) * size;
    double y2 = point(1).y - sin((angle+iso)*PI/180) * size;

    Polygon head;
    head.add(point(1));
    head.add(Point{int(x1), int(y1)});
    head.add(Point{int(x2), int(y2)});
    head.set_fill_color(color());

    head.draw_lines();          // draw arrow head
    Shape::draw_lines();        // draw line
}


// Ex 6 - Text_box

Point n (Rectangle& r)
{
    int x = r.point(0).x + r.width() / 2;
    int y = r.point(0).y;

    return Point{x, y};
}

Point s (Rectangle& r)
{
    int x = r.point(0).x + r.width() / 2;
    int y = r.point(0).y + r.height();
    return Point{x, y};
}

Point e (Rectangle& r)
{
    int x = r.point(0).x + r.width();
    int y = r.point(0).y + r.height() / 2;
    return Point{x, y};
}

Point w (Rectangle& r)
{
    int x = r.point(0).x;
    int y = r.point(0).y + r.height() / 2;
    return Point{x, y};
}

Point nw (Rectangle& r)
{
    int x = r.point(0).x;
    int y = r.point(0).y;
    return Point{x, y};
}

Point ne (Rectangle& r)
{
    int x = r.point(0).x + r.width();
    int y = r.point(0).y;
    return Point{x, y};
}

Point sw (Rectangle& r)
{
    int x = r.point(0).x;
    int y = r.point(0).y + r.height();
    return Point{x, y};
}

Point se (Rectangle& r)
{
    int x = r.point(0).x + r.width();
    int y = r.point(0).y + r.height();
    return Point{x, y};
}

Point center (Rectangle& r)
{
    int x = r.point(0).x + r.width() / 2;
    int y = r.point(0).y + r.height() / 2;
    return Point{x, y};
}


Text_box::Text_box(Point p, int ww, int hh, string ss)
    : Rectangle(p, ww, hh), label (Point{p.x+5,p.y+16}, ss)
{
    add(p);
}

void Text_box::draw_lines() const
{
    Rectangle::draw_lines();
    label.draw_lines();
}


