#ifndef _POINT_H_
#define _POINT_H_

struct Point {
	float x;
	float y;

	Point() : x(0.0f), y(0.0f) {}

	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}
};
#endif