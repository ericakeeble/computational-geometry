#include "Point.h"
#include <algorithm>

using namespace std;


Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(double _x, double _y) {
	x = _x;
	y = _y;
}

/*	returns cross product value of vectors <p1,p2> and <p1,p3>	*/
double Point::crossProd(Point p1, Point p2, Point p3) {
	return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

/*	checks if point p3 is on the segment (p1,p2)	*/
bool Point::onSegment(Point p1, Point p2, Point p3) {
	if ((min(p1.x, p2.x) <= p3.x <= max(p1.x, p2.x)) &&
		(min(p1.y, p2.y) <= p3.y <= max(p1.y, p2.y))) {
		return true;
	}
	else {
		return false;
	}
}
