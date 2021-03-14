#include "../../../res/GUI/Simple_window.h"
#include "../../../res/GUI/Graph.h"
#include "../../../res/GUI/Tools.h"

#include <iostream>

int main()
try {
    const Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Chapter 14 Ex 1"};

    Smiley_hat sm {Point{150, 200}, 100};
    win.attach(sm);

    Frowny_hat fr {Point{450, 200}, 100};
    win.attach(fr);

    win.wait_for_button();
}
catch (exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    std::cerr << "Unknown error!\n";
    return 2;
}
/* Compile command
g++ -w -Wall -std=c++11 ../../../res/GUI/Graph.cpp ../../../res/GUI/Window.cpp ../../../res/GUI/GUI.cpp ../../../res/GUI/Simple_window.cpp ../../../res/GUI/Tools.cpp main.cpp `fltk-config --ldflags --use-images` -o a.out
*/