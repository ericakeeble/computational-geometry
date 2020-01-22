#pragma once

class Point {
	double x, y;

public:
	Point();
	Point(double _x, double _y);

	/*	returns cross product value of vectors <p1,p2> and <p1,p3>	*/
	static double crossProd(Point p1, Point p2, Point p3);

	/*	checks if point p3 is on the segment (p1,p2)	*/
	static bool onSegment(Point p1, Point p2, Point p3);
};

