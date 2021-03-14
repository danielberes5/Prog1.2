#include "../../../res/GUI/Simple_window.h"
#include "../../../res/GUI/Tools.h"

#include <string>
#include <iostream>

using namespace Graph_lib;

int main()
try {
    // Window
    const Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Chapter 13 Ex 2"};

    Box b1 {Point{200, 150}, 200, 100, 20};
    b1.set_color(Color::red);
    win.attach(b1);

    Box b2 {Point{100, 100}, 120, 80, 10};
    b2.set_style(Line_style{Line_style::solid,4});
    b2.set_color(Color::blue);
    win.attach(b2);

    Box b3 {Point{400, 300}, 50, 50, 25};
    win.attach(b3);

    win.wait_for_button();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "error\n";
    return 2;
}
/* Compile command
g++ -w -Wall -std=c++11 ../../../res/GUI/Graph.cpp ../../../res/GUI/Window.cpp ../../../res/GUI/GUI.cpp ../../../res/GUI/Simple_window.cpp ../../../res/GUI/Tools.cpp main.cpp `fltk-config --ldflags --use-images` -o a.out
*/
