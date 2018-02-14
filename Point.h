//
// Created by Blake on 1/26/2018.
//

#ifndef GRAPHICS_POINT_H
#define GRAPHICS_POINT_H

#include <iostream>
using namespace std;

class Point {
private:
	float x;
	float y;
	float z;
public:
	Point(float x, float y, float z);
	Point();
	~Point();
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getZ();
	void setZ(float z);
};
#endif //GRAPHICS_POINT_H