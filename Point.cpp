//
// Created by Blake on 1/26/2018.
//
#include "Point.h"

Point::Point(int x, int y) {
    Point::x = x;
    Point::y = y;
}

Point::Point() {
    Point::x = 0;
    Point::y = 0;
}

Point::~Point() {
}

float Point::getX() {
    return x;
}

void Point::setX(float x) {
    Point::x = x;
}

float Point::getY() {
    return y;
}

void Point::setY(float y) {
    Point::y = y;
}
