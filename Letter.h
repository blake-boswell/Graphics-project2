//
// Created by blake on 1/30/2018.
//

#ifndef GRAPHICS_LETTER_H
#define GRAPHICS_LETTER_H


#include "Point.h"

class Letter {
private:
    char letter;
    static const int MAX_POINTS = 75;
    Point originalPoints[MAX_POINTS];
    float originalHeight;
    float originalWidth;
    int numVertices;


public:
    static int numLetters;
    Letter();
    ~Letter();
    char getLetter();
    void setLetter(char letter);
    Point* getOriginalPoints();
    void setOriginalPoints(Point points[], int length);
    float getOriginalHeight();
    void setOriginalHeight(float height);
    float getOriginalWidth();
    void setOriginalWidth(float width);
    int getNumVertices();
    void setNumVertices(int numVertices);
    Point* transform(float x, float y);
};


#endif //GRAPHICS_LETTER_H
