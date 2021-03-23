#include "../../res/GUI/Simple_window.h"
#include "../../res/GUI/Graph.h"
#include "Scale.h"
#include "Distribution.h"

#include <iostream>

using namespace Graph_lib;


int main()
try {

    constexpr int xmax = 600;
    constexpr int ymax = 400;

    constexpr int xoffset = 100;
    constexpr int yoffset = 60;

    constexpr int xspace = 40;
    constexpr int yspace = 40;

    constexpr int xlength = xmax - xoffset - xspace;
    constexpr int ylength = ymax - yoffset - yspace;

    constexpr int base_year = 1960;
    constexpr int end_year = 2040;

    constexpr double xscale = double(xlength)/(end_year - base_year);
    constexpr double yscale = double(ylength)/100;

    Scale xs {xoffset,base_year,xscale}; 
    Scale ys {ymax - yoffset,0, -yscale};

    Simple_window win {Point{100,100},xmax,ymax,"Aging Japan"};

    Axis x {Axis::x, Point{xoffset,ymax - yoffset}, xlength,(end_year - base_year)/10, "year   1960   1970   1980   1990   2000   2010   2020   2030   2040"};
    x.label.move(-100,0);

    Axis y {Axis::y,Point{xoffset, ymax - yoffset},ylength, 10, "o/o of population"};

    Line current_year {Point{xs(2008),ys(0)},Point{xs(2008),ys(100)}};
    current_year.set_style(Line_style::dash);

    Open_polyline children;
    Open_polyline adults;
    Open_polyline aged;

    ifstream ifs{"japanage.txt"};

    if(ifs)
    {
        for (Distribution d; ifs>>d;)
        {
            if(d.year < base_year || end_year < d.year) error("year out of range");
            if(d.young + d.middle + d.old !=100)
            {
                error("percentages don't add up");
            }
            const int x = xs(d.year);
            children.add(Point{x,ys(d.young)});
            adults.add(Point{x,ys(d.middle)});
            aged.add(Point{x,ys(d.old)});
        }
        ifs.close();
    }
    else{
        error("stream error");
    }
    

    Text children_label {Point{20,children.point(0).y},"age 0-14"};
    children.set_color(Color::red);
    children_label.set_color(Color::red);

    Text adults_label {Point{20,adults.point(0).y},"age 15-64"};
    adults.set_color(Color::blue);
    adults_label.set_color(Color::blue);

    Text aged_label {Point{20,aged.point(0).y},"age 65+"};
    aged.set_color(Color::dark_green);
    aged_label.set_color(Color::dark_green);

    win.attach(children);
    win.attach(adults);
    win.attach(aged);

    win.attach(children_label);
    win.attach(adults_label);
    win.attach(aged_label);

    win.attach(x);
    win.attach(y);
    win.attach(current_year);

    gui_main();
}
catch (exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    std::cerr << "Unknown exception\n";
    return 2;
}
/*
g++ -w -Wall -std=c++11 ../../res/GUI/Graph.cpp ../../res/GUI/Window.cpp ../../res/GUI/GUI.cpp ../../res/GUI/Simple_window.cpp Scale.cpp main.cpp `fltk-config --ldflags --use-images` -o a.out
*/