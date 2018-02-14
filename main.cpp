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
bool isFloatOrInt(std::string input) {
	std::string delimeter = ".";
	int splitIndex = input.find(delimeter);
	// No decimal, its an int
	if (splitIndex == -1 && (input[0] == '-' || isdigit(input[0]))) {
		for (int i = 1; i < input.size(); i++) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
		return true;
	}
	else if (input[0] == '-' || isdigit(input[0])) {
		for (int i = 1; i < splitIndex; i++) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
		for (int i = splitIndex + 1; i < input.size(); i++) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
		return true;
	}
	else if (splitIndex == 0) {
		for (int i = 1; i < input.size(); i++) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}

}

void writeLetterHeading(Letter letter, string filename) {
	ofstream writer;
	writer.open(filename, ios::app);
	writer << "1\n\n";
	writer << letter.getLetter() << "\n" << letter.getNumVertices() << "\n";
	writer.close();
}

void writePoint(float x, float y, float z, string filename) {
	ofstream writer;
	writer.open(filename, ios::app);
	writer << x << "," << y << "," << z << "\n";
	writer.close();
}

void resizePrompt(char letter, Letter letters[]) {
	cout << "Number of letters when we enter the resize prompt: " << Letter::numLetters << endl;
	for (int i = 0; i < Letter::numLetters; i++) {
		if (letters[i].getLetter() == letter) {
			cout << "You chose " << letter << endl;
			std::string xSize;
			std::string ySize;
			string zSize;

			cout << "Enter X size" << endl;
			std::cin >> xSize;
			// Error handling
			while (!isFloatOrInt(xSize)) {
				cout << "Please enter only numbers." << endl;
				cout << "Enter X size" << endl;
				std::cin >> xSize;
			}
			float x = std::stof(xSize);

			cout << "Enter Y size" << endl;
			std::cin >> ySize;
			// Error handling
			while (!isFloatOrInt(ySize)) {
				cout << "Please enter only numbers." << endl;
				cout << "Enter Y size" << endl;
				std::cin >> ySize;
			}
			float y = std::stof(ySize);

			cout << "Enter Z size" << endl;
			std::cin >> zSize;
			// Error handling
			while (!isFloatOrInt(zSize)) {
				cout << "Please enter only numbers." << endl;
				cout << "Enter Z size" << endl;
				std::cin >> zSize;
			}
			float z = std::stof(zSize);

			Point* newPoints = letters[i].transform(x, y, z);
			cout << "poly2d" << letters[i].getNumVertices() << endl;
			writeLetterHeading(letters[i], "output.txt");
			for (int j = 0; j < letters[i].getNumVertices(); j++) {
				cout << (newPoints + j)->getX() << " " << (newPoints + j)->getY() << endl;
				// Write point to file
				writePoint((newPoints + j)->getX(), (newPoints + j)->getY(), (newPoints + j)->getZ(), "output.txt");
			}
			// delete newPoints;
		}
	}
	// Free the unused memory
	cout << "Number of letters before deletion: " << Letter::numLetters << endl;
	delete[] letters;
	cout << "Number after: " << Letter::numLetters << endl;
}

void letterTransformationMenu(Letter letters[]) {
	bool loop = true;
	std::string response;
	char input;
	while (loop) {
		// prompt user for what letter they want to generate
		cout << "What letter do you want to generate? (L, N, T, E, F)" << endl;
		std::cin >> response;
		if (response.size() == 1) {
			input = response[0];
			if (isalpha(input)) {
				input = toupper(input);
				// prompt user for size of model in the X & Y dimensions
				switch (input) {
				case 'L':
					resizePrompt('L', letters);
					loop = false;
					break;
				case 'N':
					resizePrompt('N', letters);
					loop = false;
					break;
				case 'T':
					resizePrompt('T', letters);
					loop = false;
					break;
				case 'E':
					resizePrompt('E', letters);
					loop = false;
					break;
				case 'F':
					resizePrompt('F', letters);
					loop = false;
					break;
				default:
					cout << "Invalid input: please enter one of the available letters(L, N, T, E, F)" << endl;
					break;
				}
			}
		}
		else {
			cout << "Invalid input: please enter a letter" << endl;
		}

	}

}

Letter* readLetters(std::string fileName) {
	std::ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		cout << "Reading file..." << endl;
		std::string pair;
		std::string line;
		char letter;
		int numVertices;
		int index;
		int splitIndex;
		float x;
		float y;

		// Read numLetter line
		std::getline(file, line, '\n');
		int numLetters = std::stoi(line);
		Letter* letters = new Letter[numLetters];
		// Read blank line
		std::getline(file, line, '\n');
		// Read in letters and vertices
		for (int i = 0; i < numLetters; i++) {
			// Read letter line
			std::getline(file, line, '\n');
			letter = line[0];
			letters[i].setLetter(letter);
			// Read numVertices line
			std::getline(file, line, '\n');
			numVertices = std::stoi(line);
			letters[i].setNumVertices(numVertices);
			Point* points = new Point[numVertices];
			// Read original points
			std::getline(file, line);
			index = 0;
			while (line != "") {
				pair = line;
				// Extract the x and y
				std::string delimeter = ",";
				splitIndex = line.find(delimeter);
				x = std::stof(line.substr(0, splitIndex));
				y = std::stof(line.substr(splitIndex + 1, line.length()));
				// create a point object for each point
				points[index].setX(x);
				points[index].setY(y);
				index++;
				// Protection from seg. fault
				// Won't try to read in another line if we are at the end of file
				if (file.eof()) {
					line = "";
				}
				std::getline(file, line);
			}
			// Set the letter's points to the points array we just made
			letters[i].setOriginalPoints(points, numVertices);
			// delete points;
		}
		file.close();
		cout << "File read complete." << endl;
		return letters;
	}
	else {
		cout << "File wasn't opened! Please make sure you entered the correct file name" << endl;
		return NULL;
	}
}

std::string getFileName() {
	// default file
	std::string fileName = "letters.txt";
	// Prompt user for a file to read from
	std::string response;
	char input;
	cout << "Welcome!" << endl;
	cout << "Read data from default file? (y or n)" << endl;
	std::cin >> response;
	input = response[0];
	// Error handling
	while (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
		cout << "Please respond with y or n" << endl;
		// re-prompt
		cout << "Read data from default file? (y or n)" << endl;
		std::cin >> input;
	}
	if (input == 'n' || input == 'N') {
		cout << "Please enter the name of the file you wish to read from:" << endl;
		std::cin >> fileName;
	}
	return fileName;
}

Letter read3DLetter(string filename) {
	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		cout << "Reading file (3D)..." << endl;
		std::string point;
		std::string line;
		char letterChar;
		int numVertices;
		int index;
		int splitIndex;
		float x;
		float y;
		float z;

		// Read numLetter line
		std::getline(file, line, '\n');
		int numLetters = std::stoi(line);
		cout << "No. Letters before 3D read creation" << Letter::numLetters << endl;
		Letter letter;
		// Read blank line
		std::getline(file, line, '\n');
		// Read in letters and vertices
		cout << "Reading 3D. No. of letters " << Letter::numLetters << endl;
		
		// Read letter line
		std::getline(file, line, '\n');
		letterChar = line[0];
		letter.setLetter(letterChar);
		// Read numVertices line
		std::getline(file, line, '\n');
		numVertices = std::stoi(line);
		letter.setNumVertices(numVertices);
		Point* points = new Point[numVertices];
		// Read original points
		std::getline(file, line);
		index = 0;
		while (line != "") {
			point = line;
			// Extract the x, y, and z
			std::string delimeter = ",";
			splitIndex = line.find(delimeter);
			x = std::stof(line.substr(0, splitIndex));
			string yAndZ = line.substr(splitIndex + 1, line.length());
			splitIndex = yAndZ.find(delimeter);
			y = std::stof(yAndZ.substr(0, splitIndex));
			z = std::stof(yAndZ.substr(splitIndex + 1, yAndZ.length()));
				
			// create a point object for each point
			points[index].setX(x);
			points[index].setY(y);
			points[index].setZ(z);
			index++;
			// Protection from seg. fault
			// Won't try to read in another line if we are at the end of file
			if (file.eof()) {
				line = "";
			}
			std::getline(file, line);
		}
		// Set the letter's points to the points array we just made
		letter.setOriginalPoints(points, numVertices);
		// delete points;
		
		file.close();
		cout << "File read complete." << endl;
		cout << "Returning letter variable" << endl;
		return letter;
	}
	else {
		cout << "File wasn't opened! Please make sure you entered the correct file name" << endl;
	}
}
// <end>

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glEnable(GL_DEPTH_TEST);

	// Delete old output.txt file
	remove("output.txt");
	// Get user input for letter models
	bool loop = true;
	while (loop) {
		std::string fileName = getFileName();
		// Read file
		Letter* letters = readLetters(fileName);
		if (letters != NULL) {
			// Success
			letterTransformationMenu(letters);
			loop = false;
		}
		else {
			// Failed reading 
			cout << "Would you like to retry? (y or n)" << endl;
			char response;
			std::cin >> response;
			while (response != 'Y' && response != 'y' && response != 'N' && response != 'n') {
				cout << "Would you like to retry? (y or n)" << endl;
				std::cin >> response;
			}
			if (response == 'n' || response == 'N') {
				loop = false;
			}
		}
	}

	letter = read3DLetter("output.txt");
	cout << "Receiving letter variable" << endl;
	cout << Letter::numLetters << endl;
	letter.print();
	
}

//---------------------------------------
// Function to draw 3D block
//---------------------------------------
void block(float xmin, float ymin, float zmin,
	float xmax, float ymax, float zmax)
{
	// Define 8 vertices
	float ax = xmin, ay = ymin, az = zmax;
	float bx = xmax, by = ymin, bz = zmax;
	float cx = xmax, cy = ymax, cz = zmax;
	float dx = xmin, dy = ymax, dz = zmax;
	float ex = xmin, ey = ymin, ez = zmin;
	float fx = xmax, fy = ymin, fz = zmin;
	float gx = xmax, gy = ymax, gz = zmin;
	float hx = xmin, hy = ymax, hz = zmin;

	// Draw 6 faces
	glBegin(mode);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(ax, ay, az);
	glVertex3f(bx, by, bz);
	glVertex3f(cx, cy, cz);
	glVertex3f(dx, dy, dz);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(ax, ay, az);
	glVertex3f(dx, dy, dz);
	glVertex3f(hx, hy, hz);
	glVertex3f(ex, ey, ez);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(ax, ay, az);
	glVertex3f(ex, ey, ez);
	glVertex3f(fx, fy, fz);
	glVertex3f(bx, by, bz);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(fx, fy, fz);
	glVertex3f(ex, ey, ez);
	glVertex3f(hx, hy, hz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(cx, cy, cz);
	glVertex3f(bx, by, bz);
	glVertex3f(fx, fy, fz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(hx, hy, hz);
	glVertex3f(dx, dy, dz);
	glVertex3f(cx, cy, cz);
	glEnd();
}

//---------------------------------------
// Function to draw 3D book case
//---------------------------------------
void book_case(float xpos, float ypos, float zpos,
	float xsize, float ysize, float zsize)
{
	// Define six corners of book case
	float xmin = xpos - xsize / 2;
	float xmax = xpos + xsize / 2;
	float ymin = ypos - ysize / 2;
	float ymax = ypos + ysize / 2;
	float zmin = zpos - zsize / 2;
	float zmax = zpos + zsize / 2;
	float shelf = (xsize + ysize) / 40;

	// Draw back
	block(xmin, ymin, zmax - shelf, xmax, ymax, zmax);

	// Draw sides
	block(xmin, ymin, zmin, xmin + shelf, ymax, zmax - shelf);
	block(xmax - shelf, ymin, zmin, xmax, ymax, zmax - shelf);
	block(xmin + shelf, ymin, zmin, xmax - shelf, ymin + shelf, zmax - shelf);
	block(xmin + shelf, ymax - shelf, zmin, xmax - shelf, ymax, zmax - shelf);

	// Draw shelves
	int count;
	for(count = 1; count < 4; count++)
	{
		float ystart = count * (ysize - shelf) / 4;
		block(xmin + shelf, ystart + ymin, zmin,
			xmax - shelf, ystart + ymin + shelf, zmax - shelf);
	}
}

//---------------------------------------
// Function to draw 3D table
//---------------------------------------
void table(float xpos, float ypos, float zpos,
	float xsize, float ysize, float zsize)
{
	// Define six corners of table
	float xmin = xpos - xsize / 2;
	float xmax = xpos + xsize / 2;
	float ymin = ypos - ysize / 2;
	float ymax = ypos + ysize / 2;
	float zmin = zpos - zsize / 2;
	float zmax = zpos + zsize / 2;
	float leg = (xsize + ysize) / 20;

	// Draw top
	block(xmin, ymax - leg, zmin, xmax, ymax, zmax);

	// Draw legs
	block(xmin, ymin, zmin, xmin + leg, ymax - leg, zmin + leg);
	block(xmin, ymin, zmax - leg, xmin + leg, ymax - leg, zmax);
	block(xmax - leg, ymin, zmin, xmax, ymax - leg, zmin + leg);
	block(xmax - leg, ymin, zmax - leg, xmax, ymax - leg, zmax);
}

void drawLetter(Letter letter) {
	Point* points = letter.getOriginalPoints();
	float x, y, z;

	// Draw the foreground letter
	glBegin(mode);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < letter.getNumVertices(); i++) {
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