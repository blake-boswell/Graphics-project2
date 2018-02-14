//
// Created by blake on 1/30/2018.
//

#include "Letter.h"

Letter::Letter() {
	numLetters++;
	char letter = '-';
	float originalHeight = -1;
	float originalWidth = -1;
	float originalDepth = 1;
	int numVertices = -1;
	cout << "Letter Constructor called." << endl;

}
Letter::~Letter() {
	numLetters--;
	cout << "Letter Destructor called." << endl;
}

int Letter::numLetters = 0;

char Letter::getLetter() {
	return Letter::letter;
}

void Letter::setLetter(char letter) {
	Letter::letter = letter;
}

Point* Letter::getOriginalPoints() {
	return this->originalPoints;
}

void Letter::setOriginalPoints(Point points[], int length) {
	float xMax = 0.0;
	float yMax = 0.0;
	float zMax = 0.0;
	for (int i = 0; i < length; i++) {
		this->originalPoints[i] = points[i];
		if (points[i].getX() > xMax)
			xMax = points[i].getX();
		if (points[i].getY() > yMax)
			yMax = points[i].getY();
		if (points[i].getZ() > zMax)
			zMax = points[i].getZ();
	}
	this->originalWidth = xMax;
	this->originalHeight = yMax;
	this->originalDepth = zMax;
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

float Letter::getOriginalDepth() {
	return this->originalDepth;
}

void Letter::setOriginalDepth(float depth) {
	this->originalDepth = depth;
}

int Letter::getNumVertices() {
	return this->numVertices;
}

void Letter::setNumVertices(int numVertices) {
	Letter::numVertices = numVertices;
}

Point *Letter::transform(float x, float y, float z) {
	Point * newPoints = new Point[numVertices];
	for (int i = 0; i < numVertices; i++) {
		// Prevention from division by 0
		if(originalWidth != 0)
			(newPoints + i)->setX(originalPoints[i].getX() * (x / originalWidth));
		else {
			cout << "Prevented attempt to divide by 0 transforming the x coordinate." << endl;
			(newPoints + i)->setX(0);
		}
			
		// Prevention from division by 0
		if(originalHeight != 0)
			(newPoints + i)->setY(originalPoints[i].getY() * (y / originalHeight));
		else {
			cout << "Prevented attempt to divide by 0 transforming the y coordinate." << endl;
			(newPoints + i)->setY(0);
		}

		// Prevention from division by 0
		if(originalDepth != 0) 
			(newPoints + i)->setZ(originalPoints[i].getZ() * (z / originalDepth));
		else {
			cout << "Prevented attempt to divide by 0 transforming the z coordinate." << endl;
			(newPoints + i)->setZ(0);
		 }
	}
	return newPoints;
}

void Letter::print() {
	cout << "Total number of letters: " << numLetters << endl;
	cout << "Letter: " << letter << endl;
	cout << "Original Height: " << originalHeight << endl;
	cout << "Original Width: " << originalWidth << endl;
	cout << "Original Depth: " << originalDepth << endl;
	cout << "Number of vertices: " << numVertices << endl;
	cout << "Points:\t";
	for(int i = 0; i < numVertices; i++) {
		cout << "(" << originalPoints[i].getX() << ", " << originalPoints[i].getY() << ", " << originalPoints[i].getZ() << ")\t";
	}
}

