#include <vector>
#include "BezierCurve.h"

using namespace std;

class Animation {
	public:
		vector<BezierCurve> curves;

		Animation() {}

		void addCurve(BezierCurve b) {
			curves.push_back(b);
		}

};
