
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

struct point {
	float x;
	float y;
};

struct bezier {
	float x0;
	float y0;
	float ax;
	float bx;
	float cx;
	float ay;
	float by;
	float cy;
	void setup(point p0, point p1, point p2, point p3);
	point calc(float t);
};

void bezier::setup(point p0, point p1, point p2, point p3) {
	x0 = p0.x;
	y0 = p0.y;
	cx = 3.0*(p1.x - p0.x);
	bx = 3.0*(p2.x - p1.x) - cx;
	ax = p3.x - p0.x - cx - bx;
	cy = 3.0*(p1.y - p0.y);
	by = 3.0*(p2.y - p1.y) - cy;
	ay = p3.y - p0.y - cy - by;
}

point bezier::calc(float t) {
	point p;
	float t2 = t*t;
	float t3 = t2*t;
	p.x = ax*t3 + bx*t2 + cx*t + x0;
	p.y = ay*t3 + by*t2 + cy*t + y0;
	return p;
}

int main() {
	point p0, p1, p2, p3;

	p0.x = 10;
	p0.y = 15;

	p1.x = 20;
	p1.y = 25;

	p2.x = 25;
	p2.y = 30;

	p3.x = 30;
	p3.y = 15;

	bezier b;

	b.setup(p0, p1, p2, p3);

	for (float t = 0.0; t <= 1.0; t += 0.02) {
		point p = b.calc(t);
		cout << p.x << "," << p.y << endl;
	}

	return 0;
}