#include "../../../res/GUI/Simple_window.h"
#include "../../../res/GUI/Graph.h"

double one(double x) { return 1; }
double slope(double x) { return x/2; }
double square(double x) { return x*x; }
double sloping_cos(double x) { return cos(x) + slope(x); }

int main()
try {


    Point tl(600,50);
    Simple_window win(tl,600,600,"Fct test");

    Axis x(Axis::x,Point(100,300),400,20,"1 == 20 pixels");
    x.set_color(Color::red);
    win.attach(x);
    Axis y(Axis::y,Point(300,500),400,20,"1 == 20 pixels");
    y.set_color(Color::red);
    win.attach(y);
    win.wait_for_button();

    Flex_function s(one,-10,11,Point(300,300),400,30,30);
    win.attach(s);
    win.wait_for_button();

    s.reset_xscale(20);
    s.reset_yscale(20);
    win.wait_for_button();

    s.reset_fct(sloping_cos);
    win.wait_for_button();

    s.reset_count(15);
    win.wait_for_button();

    s.reset_orig(Point(350,250));
    win.wait_for_button();

    s.reset_range(-8,8);
    win.wait_for_button();

    s.reset_precision(15);
    win.wait_for_button();

    s.reset_precision(1);
    win.wait_for_button();
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    keep_window_open();
}
catch (...) {
    cerr << "exception\n";
    keep_window_open();
}