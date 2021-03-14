#include "Tools.h"
#include <iostream>

using namespace Graph_lib;

// Ex 13 1 - Arc

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

// Ex 13 2 - Box

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

// Ex 13 3 - Arrow

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


// Ex 13 6 - Text_box

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

// Ex 14 1 - Smiley, Frowny

Smiley::Smiley (Point p, int r) :
    Circle  {p, r},
    left    {Point{p.x-r/3, p.y-r/3}, r / 4},
    right   {Point{p.x+r/3, p.y-r/3}, r / 4},
    mouth   {p, r*2/3, 200, 340} { }

void Smiley::draw_lines () const
{
    Circle::draw_lines();
    left.draw_lines();
    right.draw_lines();
    mouth.draw_lines();
}

Frowny::Frowny (Point p, int r) :
    Circle  {p, r},
    left    {Point{p.x-r/3, p.y-r/3}, r / 4},
    right   {Point{p.x+r/3, p.y-r/3}, r / 4},
    mouth   {Point{p.x, p.y+r*3/4}, r*2/3, 22, 157} { }

void Frowny::draw_lines () const
{
    Circle::draw_lines();
    left.draw_lines();
    right.draw_lines();
    mouth.draw_lines();
}

Smiley_hat::Smiley_hat (Point p, int r) :
    Smiley  {p, r},
    hat     {Point{p.x-r*3/4, p.y-r*5/4}, r*3/2, r/2}
{
    hat.set_fill_color(Color::black);
}

void Smiley_hat::draw_lines () const
{
    Smiley::draw_lines();
    hat.draw_lines();
}

Frowny_hat::Frowny_hat (Point p, int r)
    : Frowny  {p, r}
{
    hat.add(Point{p.x-r*3/4, p.y-r*3/4});
    hat.add(Point{p.x+r*3/4, p.y-r*3/4});
    hat.add(Point{p.x, p.y-r*3/2});

    hat.set_fill_color(Color::yellow);
}

void Frowny_hat::draw_lines () const
{
    Frowny::draw_lines();
    hat.draw_lines();
}

// Ex 14 11 - Binary_tree

Binary_tree::Binary_tree(Point p, int levels, string edge_style)
    : l{levels}
{
    if (levels<0) error("Binary_tree: levels must be at least zero");
    if (levels==0) return;  // tree ist empty
    nodes.push_back(p);    // if levels==1, only root is added
    for (int i = 2; i<=levels; ++i) {
        for (int j = 0; j<pow(2,i-1); ++j) {
            int x = p.x - ((pow(2,i-1)-1)/2-j) * pow(2,(levels-i)+1) * r;
            int y = p.y + (i-1)*r*3;
            nodes.push_back(Point{x,y});
        }
    }

    if (edge_style=="up")
    {
        for (int i = 0; i < nodes.size()/2; ++i)
        {
            edges.push_back(new Arrow(Point(nodes[2*i+1].x, nodes[2*i+1].y - r), Point(nodes[i].x, nodes[i].y + r)));
            edges.push_back(new Arrow(Point(nodes[2*i+2].x, nodes[2*i+2].y - r), Point(nodes[i].x, nodes[i].y + r)));
        }
    }
    else if (edge_style=="down")
    {
        for (int i = 0; i < nodes.size()/2; ++i)
        {
            edges.push_back(new Arrow(Point(nodes[i].x, nodes[i].y + r), Point(nodes[2*i+1].x, nodes[2*i+1].y - r)));
            edges.push_back(new Arrow(Point(nodes[i].x, nodes[i].y + r), Point(nodes[2*i+2].x, nodes[2*i+2].y - r)));
        }
    }
    else {
        for (int i = 0; i < nodes.size()/2; ++i)
        {
            edges.push_back(new Line(Point(nodes[i].x, nodes[i].y + r), Point(nodes[2*i+1].x, nodes[2*i+1].y - r)));
            edges.push_back(new Line(Point(nodes[i].x, nodes[i].y + r), Point(nodes[2*i+2].x, nodes[2*i+2].y - r)));
        }
    }
    for (int i = 0; i < nodes.size(); ++i){
        labels.push_back(new Text(nodes[i],""));
    }
}

void Binary_tree::set_node_label(string n, string lbl)
{
    if (n.size()<1 || n.size()>l) error("set_node_label: illegal node string ",n);
    istringstream iss(n);
    char ch;
    iss.get(ch);    // look at first character
    if (n.size()==1) {
        switch (ch) {
        case 'l':
        case 'r':
            labels[0].set_label(lbl);
            return;
        default:
            error("set_node_label: illegal character in node string: ",string(1,ch));
        }
    }
    int n_idx = 0;  // node index in point list
    while (iss.get(ch)) {
        switch (ch) {
        case 'l':
            n_idx = 2*n_idx + 1;
            break;
        case 'r':
            n_idx = 2*n_idx + 2;
            break;
        default:
            error("set_node_label: illegal character in node string: ",string(1,ch));
        }
    }
    labels[n_idx].set_label(lbl);
}

void Binary_tree::draw_lines() const
{
    if (color().visibility()) {
        for (int i = 0; i< nodes.size()-1; ++i)
            edges[i].draw();

        // draw labels
        for (int i = 0; i< nodes.size(); ++i)
            labels[i].draw();

        // draw circles
        fl_color(fl_rgb_color(192,192,192));
        for (int i = 0; i< nodes.size(); ++i)
            fl_pie(nodes[i].x-r,nodes[i].y-r,r+r-1,r+r-1,0,360);
        fl_color(color().as_int()); // reset color
        for (int i = 0; i< nodes.size(); ++i)
            fl_arc(nodes[i].x-r,nodes[i].y-r,r+r,r+r,0,360);
    }
}

void Binary_tree_squares::draw_lines() const
{
    if (color().visibility()) {
        for (int i = 0; i<nodes.size()-1; ++i)
            edges[i].draw();

        // draw labels
        for (int i = 0; i<nodes.size(); ++i)
            labels[i].draw();

        // draw squares
        fl_color(fl_rgb_color(192,192,192));
        for (int i = 0; i<nodes.size(); ++i)
            fl_rectf(nodes[i].x-r,nodes[i].y-r,2*r,2*r);
        fl_color(color().as_int()); // reset color
        for (int i = 0; i<nodes.size(); ++i)
            fl_rect(nodes[i].x-r,nodes[i].y-r,2*r,2*r);
    }
}

