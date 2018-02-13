//
// Created by blake on 1/30/2018.
//

#include "Letter.h"

Letter::Letter() {
    numLetters++;
}
Letter::~Letter() {
    numLetters--;
}

int Letter::numLetters = 0;

char Letter::getLetter() {
    return Letter::letter;
}

void Letter::setLetter(char letter) {
    Letter::letter = letter;
}

Point* Letter::getOriginalPoints() {
    return Letter::originalPoints;
}

void Letter::setOriginalPoints(Point points[], int length) {
    int xMax = 0;
    int yMax = 0;
    for(int i = 0; i < length; i++) {
        Letter::originalPoints[i] = points[i];
        if(points[i].getX() > xMax)
            xMax = points[i].getX();
        if(points[i].getY() > yMax)
            yMax = points[i].getY();
    }
    Letter::originalWidth = xMax;
    Letter::originalHeight = yMax;
}

float Letter::getOriginalHeight() {
    return Letter::originalHeight;
}

void Letter::setOriginalHeight(float height) {
    Letter::originalHeight = height;
}

float Letter::getOriginalWidth() {
    return Letter::originalWidth;
}

void Letter::setOriginalWidth(float width) {
    Letter::originalWidth = width;
}

int Letter::getNumVertices() {
    return Letter::numVertices;
}

void Letter::setNumVertices(int numVertices) {
    Letter::numVertices = numVertices;
}

Point *Letter::transform(float x, float y) {
    Point * newPoints = new Point[numVertices];
    for(int i = 0; i < numVertices; i++) {
        (newPoints+i)->setX(originalPoints[i].getX() * (x/originalWidth));
        (newPoints+i)->setY(originalPoints[i].getY() * (y/originalHeight));
    }
    return newPoints;
}

