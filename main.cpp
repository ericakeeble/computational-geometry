//Erica Keeble

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Point.h"
#include "Line.h"
#include "Polygon.h"

/*		Notes
 *	-Large storage, most of the points are stored twice, because a line will 
 *		share a point with another line. Could convert to pointers to conserve space.
 *	-It takes O(n^2/2) time to determine if there is an intersection within an 
 *		entire polygon. But, there is a maximum n = 30, so it might be more inefficient 
 *		to change to O(nlgn) algorithm since n is so small.
 *	-I could shorten/eliminate some objects and logic statements, but it would make the 
 *	code harder to read.
 */

using namespace std;


int main(int argc, char *argv[]) {
	//open file
	ifstream fin(argv[1]);
	if (!fin.is_open()) {
		cout << "File did not open :(" << endl;
		return 0;
	}

	Polygon shape = Polygon(fin);
	int i = 1;
	
	while (shape.numLines() != 0) {
		cout << "Polygon " << i << endl;
		if (!shape.checkForIntersection()) {
			cout << "   Simple" << endl;

			if (shape.checkForConvex()) {
				cout << "   Convex" << endl;

				if (shape.checkForClockwise()) {
					cout << "   Clockwise" << endl;
				}
				else {
					cout << "   CounterClockwise" << endl;
				}
			}
			else {
				cout << "   Not Convex" << endl;
			}
		}
		else {
			cout << "   Not Simple" << endl;
		}

		//get next shape
		shape = Polygon(fin);
		i++;
	}

	fin.close();
}
