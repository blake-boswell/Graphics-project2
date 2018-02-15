#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Point.h"
#include "Letter.h"

using namespace std;

// Global variables 
int xAngle = 0;
int yAngle = 0;
int zAngle = 0;
Letter letter;
// GLenum mode = GL_POLYGON;
GLenum mode = GL_LINE_LOOP;

// Functions for creating letter models
// <begin>

// <end>

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	// User Input Menu
	Letter::generateLetters();

	letter = Letter::read3DLetter("output.txt");

	// Debugging
	cout << "Receiving letter variable" << endl;
	cout << Letter::numLetters << endl;
	letter.print();
	
}

//---------------------------------------
// Function to draw a letter
//---------------------------------------
void drawLetter(Letter letter) {
	Point* points = letter.getOriginalPoints();
	float x, y, z;

	// Draw the foreground letter
	glBegin(mode);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < letter.getNumVertices(); i++) {
		// Center all the coordinates
		x = points[i].getX() - (letter.getOriginalWidth() / 2);
		y = points[i].getY() - (letter.getOriginalHeight() / 2);
		z = points[i].getZ() / 2;
		glVertex3f(x, y, z);
	}
	x = points[0].getX() - (letter.getOriginalWidth() / 2);
	y = points[0].getY() - (letter.getOriginalHeight() / 2);
	z = points[0].getZ() / 2;

	// Connect the first and last vertex
	glVertex3f(x, y, z);
	glEnd();

	// Draw the background letter
	glBegin(mode);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < letter.getNumVertices(); i++) {
		// Center all the coordinates
		x = points[i].getX() - (letter.getOriginalWidth() / 2);
		y = points[i].getY() - (letter.getOriginalHeight() / 2);
		z = -.5 * points[i].getZ();
		glVertex3f(x, y, z);
	}
	x = points[0].getX() - (letter.getOriginalWidth() / 2);
	y = points[0].getY() - (letter.getOriginalHeight() / 2);
	z = -.5 * points[0].getZ();

	// Connect the first and last vertex
	glVertex3f(x, y, z);
	glEnd();

	// Connect the letters
	for (int i = 0; i < letter.getNumVertices(); i++) {
		glBegin(mode);
		glColor3f(0.0, 1.0, 0.0);
		x = points[i].getX() - (letter.getOriginalWidth() / 2);
		y = points[i].getY() - (letter.getOriginalHeight() / 2);
		z = points[i].getZ() / 2;
		glVertex3f(x, y, z);
		glVertex3f(x, y, -z);
		glEnd();
	}
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	// Update angles
	if(key == 'x')
		xAngle -= 5;
	else if(key == 'y')
		yAngle -= 5;
	else if (key == 'z')
		zAngle -= 5;
	else if(key == 'X')
		xAngle += 5;
	else if(key == 'Y')
		yAngle += 5;
	else if(key == 'Z')
		zAngle += 5;

	// Redraw objects
	glutPostRedisplay();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
	// Incrementally rotate objects
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);

	// Read File for letter points
	// Draw tables and book cases
	drawLetter(letter);
	glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Project 2");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}