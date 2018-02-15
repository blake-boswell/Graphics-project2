//
// Created by blake on 1/30/2018.
//

#include "Letter.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

Letter::Letter() {
	numLetters++;
	char letter = '-';
	float originalHeight = -1;
	float originalWidth = -1;
	float originalDepth = 1;
	int numVertices = -1;

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

// ===================================================
// ==    From here on deals with the letter menu    ==
// == and generating the letter objects from a file ==
// ===================================================

bool isFloatOrInt(string input) {
	string delimeter = ".";
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
	writer.open(filename);
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
	for (int i = 0; i < Letter::numLetters; i++) {
		if (letters[i].getLetter() == letter) {
			cout << "You chose " << letter << endl;
			string xSize;
			string ySize;
			string zSize;

			cout << "Enter X size" << endl;
			cin >> xSize;
			// Error handling
			while (!isFloatOrInt(xSize)) {
				cout << "Please enter only numbers." << endl;
				cout << "Enter X size" << endl;
				cin >> xSize;
			}
			float x = std::stof(xSize);

			cout << "Enter Y size" << endl;
			cin >> ySize;
			// Error handling
			while (!isFloatOrInt(ySize)) {
				cout << "Please enter only numbers." << endl;
				cout << "Enter Y size" << endl;
				cin >> ySize;
			}
			float y = std::stof(ySize);

			cout << "Enter Z size (thickness)" << endl;
			cin >> zSize;
			// Error handling
			while (!isFloatOrInt(zSize)) {
				cout << "Please enter only numbers." << endl;
				cout << "Enter Z size" << endl;
				cin >> zSize;
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
		}
	}
	// Free the unused memory
	delete[] letters;
}

void Letter::letterTransformationMenu(Letter letters[]) {
	bool loop = true;
	string response;
	char input;
	while (loop) {
		// prompt user for what letter they want to generate
		cout << "What letter do you want to generate? (L, N, T, E, F)" << endl;
		cin >> response;
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

Letter* Letter::readLetters(string fileName) {
	ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		cout << "Reading file..." << endl;
		string pair;
		string line;
		char letter;
		int numVertices;
		int index;
		int splitIndex;
		float x;
		float y;

		// Read numLetter line
		getline(file, line, '\n');
		int numLetters = std::stoi(line);
		Letter* letters = new Letter[numLetters];
		// Read blank line
		getline(file, line, '\n');
		// Read in letters and vertices
		for (int i = 0; i < numLetters; i++) {
			// Read letter line
			getline(file, line, '\n');
			letter = line[0];
			letters[i].setLetter(letter);
			// Read numVertices line
			getline(file, line, '\n');
			numVertices = std::stoi(line);
			letters[i].setNumVertices(numVertices);
			Point* points = new Point[numVertices];
			// Read original points
			getline(file, line);
			index = 0;
			while (line != "") {
				pair = line;
				// Extract the x and y
				string delimeter = ",";
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
				getline(file, line);
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

void Letter::read3DLetter(string filename) {
	ifstream file;
	file.open(filename);
	if (file.is_open()) {
		cout << "Reading file (3D)..." << endl;
		string point;
		string line;
		char letterChar;
		int numVertices;
		int index;
		int splitIndex;
		float x;
		float y;
		float z;
		// Read in letters and vertices

		// Read letter line
		getline(file, line, '\n');
		letterChar = line[0];
		this->letter = letterChar;
		// Read numVertices line
		getline(file, line, '\n');
		numVertices = std::stoi(line);
		this->numVertices = numVertices;
		Point* points = new Point[numVertices];
		// Read original points
		getline(file, line);
		index = 0;
		while (line != "") {
			point = line;
			// Extract the x, y, and z
			string delimeter = ",";
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
			getline(file, line);
		}
		// Set the letter's points to the points array we just made
		this->setOriginalPoints(points, numVertices);
		// delete points;
		delete[] points;
		cout << "File read complete." << endl;
	}
}

string getFileName() {
	// default file
	string fileName = "letters.txt";
	// Prompt user for a file to read from
	string response;
	char input;
	cout << "Welcome!" << endl;
	cout << "Read data from default file? (y or n)" << endl;
	cin >> response;
	input = response[0];
	// Error handling
	while (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
		cout << "Please respond with y or n" << endl;
		// re-prompt
		cout << "Read data from default file? (y or n)" << endl;
		cin >> input;
	}
	if (input == 'n' || input == 'N') {
		cout << "Please enter the name of the file you wish to read from:" << endl;
		cin >> fileName;
	}
	return fileName;
}

void Letter::generateLetters() {
	// Clear old values in output.txt
	remove("output.txt");
	// Get user input for letter models
	bool loop = true;
	while (loop) {
		string fileName = getFileName();
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
			cin >> response;
			while (response != 'Y' && response != 'y' && response != 'N' && response != 'n') {
				cout << "Would you like to retry? (y or n)" << endl;
				cin >> response;
			}
			if (response == 'n' || response == 'N') {
				loop = false;
			}
		}
	}
}

