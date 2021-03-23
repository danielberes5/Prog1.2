class Scale {
	int cbase;
	int vbase;
	double scale;
public:
	Scale(int b, int vb, double s);
	int operator()(int v) const {return cbase + (v - vbase)*scale;}
};