#pragma once
#include "Line.h"
#include "Point.h"
#include <vector>
#include <fstream>

using namespace std;

class Polygon {
private:
	/* Lines are in order of which are connected in the polygon.
	 *	Last is connected to First	*/
	vector<Line> lines;
	int dir;
	bool convex = true;

	/*	Identifies if the vectors <p1, p2> to <p2,p3> turns clockwise
	 *	or counterclockwise, returns + if counterclockwise and - if clockwise	 */
	int direction(Point p1, Point p2, Point p3);

	/*	Logic taken from textbook and slides. Returns true if there is
	 *	an intersection detected between two given lines	*/
	bool lineInersectionAlgorithm(Line a, Line b);

public:
	/* Empty constructor which defaults direction to -1 */
	Polygon();

	/* Creates 1 polygon from information in the file */
	Polygon(ifstream &fin);

	/* Returns number of lines in polygon */
	int numLines();

	/*	Returns true if the polygon is convex, false otherwise	*/
	bool checkForConvex();

	/*	Returns true if polygon is oriented in the Clockwise
	 *		direction, and false otherwise	*/
	bool checkForClockwise();

	/* Adds a line to the polygon */
	void addLine(Line line);

	/*	Returns true if the polygon is contains an intersection, false otherwise	*/
	bool checkForIntersection();
};
