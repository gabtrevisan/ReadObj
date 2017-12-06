class BezierCurve
{
public:
		float x0;
		float y0;
		float ax;
		float bx;
		float cx;
		float ay;
		float by;
		float cy;

		BezierCurve() {

		}

		BezierCurve(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3) {
			x0 = p0.x;
			y0 = p0.y;
			cx = 3.0*(p1.x - p0.x);
			bx = 3.0*(p2.x - p1.x) - cx;
			ax = p3.x - p0.x - cx - bx;
			cy = 3.0*(p1.y - p0.y);
			by = 3.0*(p2.y - p1.y) - cy;
			ay = p3.y - p0.y - cy - by;
		}

		glm::vec2 calc(float t) {
			glm::vec2 p;
			float t2 = t*t;
			float t3 = t2*t;
			p.x = ax*t3 + bx*t2 + cx*t + x0;
			p.y = ay*t3 + by*t2 + cy*t + y0;
			return p;
		}
};

