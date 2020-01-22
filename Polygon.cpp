#include "Polygon.h"

Polygon::Polygon() {
	dir = -1;
}


Polygon::Polygon(ifstream& fin) {
	dir = -1;

	vector<Point> points;
	int numPoints;
	fin >> numPoints;

	//return empty polygon if end of file
	if (numPoints < 3) {
		return;
	}

	//get all points
	double x, y;
	for (int i = 0; i < numPoints; i++) {
		fin >> x >> y;
		Point p(x, y);
		points.push_back(p);
	}

	//create all lines
	for (int i = 0; i < numPoints - 1; i++) {
		Line l(points[i], points[i + 1]);
		addLine(l);
	}

	//create line between last and first point
	Line l(points[points.size() - 1], points[0]);
	addLine(l);

	return;

}


/*	Identifies if the vectors <p1, p2> to <p2,p3> turns clockwise
 *	or counterclockwise, returns + if counterclockwise and - if clockwise	 */
int Polygon::direction(Point p1, Point p2, Point p3) {
	double result = p1.crossProd(p1, p2, p3);
	if (result > 0) { return 1; }
	else if (result < 0) { return -1; }
	else if (result == 0) { return 0; }
}

/*	Logic taken from textbook and slides. Returns true if there is
 *	an intersection detected between two given lines	*/
bool Polygon::lineInersectionAlgorithm(Line a, Line b) {
	Point p1 = a.p1;
	Point p2 = a.p2;
	Point p3 = b.p1;
	Point p4 = b.p2;

	int d1 = direction(p3, p4, p1);
	int d2 = direction(p3, p4, p2);
	int d3 = direction(p1, p2, p3);
	int d4 = direction(p1, p2, p4);

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
		return true;
	}
	else if (d1 == 0 && p1.onSegment(p3, p4, p1)) {
		return true;
	}
	else if (d2 == 0 && p1.onSegment(p3, p4, p1)) {
		return true;
	}
	else if (d3 == 0 && p1.onSegment(p1, p2, p3)) {
		return true;
	}
	else if (d4 == 0 && p1.onSegment(p1, p2, p4)) {
		return true;
	}
	else {
		return false;
	}
}

int Polygon::numLines() {
	return lines.size();
}

/*	Returns true if the polygon is convex, false otherwise	*/
bool Polygon::checkForConvex() {
	//for all lines in the polygon, find direction of turn to next line
	for (int i = 0; i < lines.size() - 1; i++) {
		Point p1 = lines[i].p1;
		Point p2 = lines[i].p2;
		Point p3 = lines[i + 1].p2;

		if (i == 0) {
			dir = direction(p1, p2, p3);
			if (dir == 0) {
				convex = false;
				return false;
			}
		}
		else if (direction(p1, p2, p3) != dir) {
			convex = false;
			return false;
		}
	}
	return true;
}

/*	Returns true of polygon is oriented in the Clockwise
 *		direction, and false otherwise	*/
bool Polygon::checkForClockwise() {
	if (convex == true) {
		if (dir > 0) {
			return false;
		}
		else if (dir < 0) {
			return true;
		}
	}
}


void Polygon::addLine(Line line) {
	lines.push_back(line);
}

/*	Returns true if the polygon is contains an intersection, false otherwise	*/
bool Polygon::checkForIntersection() {
	//if there are only 3 lines, there is no intersections possible
	if (lines.size() == 3) {
		return false;
	}

	//check all lines compared to all other lines for intersection
	for (int i = 0; i < lines.size() - 2; i++) {
		for (int j = i + 2; j < lines.size(); j++) {
			//if line intersection is true, return true
			if (this->lineInersectionAlgorithm(lines[i], lines[j]) && (i + j != lines.size() - 1)) {
				return true;
			}
		}
	}

	return false;
}

