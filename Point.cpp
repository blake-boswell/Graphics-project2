//
// Created by Blake on 1/26/2018.
//
#include "Point.h"

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point() {
	this->x = 0;
	this->y = 0;
	this->z = 1;
}

Point::~Point() {
}

float Point::getX() {
	return this->x;
}

void Point::setX(float x) {
	this->x = x;
}

float Point::getY() {
	return this->y;
}

void Point::setY(float y) {
	this->y = y;
}

float Point::getZ() {
	return this->z;
}

void Point::setZ(float z) {
	this->z = z;
}
