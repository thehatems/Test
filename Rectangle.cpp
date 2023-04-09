#include <iostream>
#include "Rectangle.h"
#include <array>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

double d1, d2, d3, d4;

Rectangle::Rectangle(int x1, int y1
					,int x2, int y2
					,int x3, int y3
					,int x4, int y4) {
	
	setFunction(x1, y1,
				x2, y2,
				x3, y3,
				x4, y4);
}

void Rectangle::setFunction(int x1, int y1,
							int x2, int y2,
							int x3, int y3,
							int x4, int y4) {

	if (x1 > 0 && x1 < 20 && y1 > 0 && y1 < 20
		&& x2 > 0 && x2 < 20 && y2 > 0 && y2 < 20
		&& x3 > 0 && x3 < 20 && y3 > 0 && y3 < 20
		&& x4 > 0 && x4 < 20 && y4 > 0 && y4 < 20) {
		d1 = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		d2 = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
		d3 = sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2));
		d4 = sqrt(pow(x4 - x1, 2) + pow(y4 - y1, 2));
		if (d1 == d3 && d2 == d4) {
			;
		}
		else {
			throw invalid_argument("\nThis is not a rectangle\n");
			this->x1 = this->x2 = this->x3 = this->x4 =
				this->y1 = this->y2 = this->y3 = this->y4 = 0;
		}
	}
	else {
		throw invalid_argument("\nThe coordinates aren't BETWEEN 0-20\n");
		this->x1 = this->x2 = this->x3 = this->x4 =
			this->y1 = this->y2 = this->y3 = this->y4 = 0;
	}
}

void Rectangle::length() {
	if (d1 > d2) {
		l = d1;
	}
	else {
		l = d2;
	}

}

void Rectangle::width() {
	if (d1 > d2) {
		w = d2;
	}
	else {
		w = d1;
	}
}

bool Rectangle::square() {
	if (l == w) {
		return true;
	}
	else {
		return false;
	}
}

double Rectangle::perimeter() {
	return 2 * (w + l);
}

double Rectangle::area() {
	return w * l;
}

void Rectangle::setFillCharacter(char fillChar) {
	this->fillChar = fillChar;
}

void Rectangle::setPerimeterCharacter(char periChar) {
	this->periChar = periChar;
}

//gcd, we'll need this function to fill the perimeter of the rectangle
int gcd(int n1, int n2) {
	int large, small;
	if (n1 == n2) {
		return 1;	
	}
	else {

		// the used algorithm needs the first number to be the largest so...
		if (abs(n1) < (n2)) {
			small = abs(n1);
			large = abs(n2);
		}
		else {
			small = abs(n2);
			large = abs(n1);
		}

		//then we proceed with the algorithm
		int x = small;
		while (x >= 1) {
			if (large % x == 0 && small % x == 0) {
				break;
			}
			x--;
		}
		return x;
	}
}


string Rectangle::draw() {
	//creating the array needed carry out the printing
	const int row{ 25 };
	const int col{ 25 };
	array<array<char, col>, row> box{};
	for (auto& x : box) {
		for (auto& y : x) {
			y = ' ';
		}
	}
	
	//filling all 4 corners
	box[x1][y1] = periChar;
	box[x2][y2] = periChar;
	box[x3][y3] = periChar;
	box[x4][y4] = periChar;
	
	
	//filling all borders
	array <int, 5> arrX{ x1, x2, x3, x4, x1 };
	array <int, 5> arrY{ y1, y2, y3, y4, y1 };
	for (int counterXY{ 0 }; counterXY <= 3; counterXY++) {
		int x1Here = arrX[counterXY]; int x2Here = arrX[counterXY + 1];
		int y1Here = arrY[counterXY]; int y2Here = arrY[counterXY + 1];

		//defining yLarger, ySmaller, xLarger, xSmaller
		int yLarger, ySmaller, xLarger, xSmaller;
		if (y2Here > y1Here) {
			yLarger = y2Here;
			ySmaller = y1Here;
		}
		else {
			yLarger = y1Here;
			ySmaller = y2Here;
		}
		if (x2Here > x1Here) {
			xLarger = x2Here;
			xSmaller = x1Here;
		}
		else {
			xLarger = x1Here;
			xSmaller = x2Here;
		}

		//if the border is on a vertical row
		if (x1Here - x2Here == 0) {
			ySmaller++;
			while (ySmaller < yLarger) {
				box[x1Here][ySmaller] = periChar;
				ySmaller++;
			}
		}

		//if the border is on a horizontal column
		else if (y1Here - y2Here == 0) {
			xSmaller++;
			while (xSmaller < xLarger) {
				box[xSmaller][y1Here] = periChar;
				xSmaller++;
			}
		}

		//if the border is neither vertical nor horizontal but diagonal
		else {
			//copied from the rational function
			int numeX = xLarger - xSmaller;
			int denoY = yLarger - ySmaller;
			int x = gcd(numeX, denoY);
			if (x == 1) {
				numeX = denoY = 1;
			}
			else {
				numeX /= x;
				denoY /= x;
			}

			//checking the signs of numerators and denominators... it's important in case
			//you need to add Xs and subtract Ys simultanously
			if (x1Here - x2Here > 0) {
				numeX = -numeX;
			}
			else {
				numeX = numeX;
			}
			if (y1Here - y2Here > 0) {
				denoY = -denoY;
			}
			else {
				denoY = denoY;
			}
			x1Here += numeX;
			y1Here += denoY;
			while (x1Here != x2Here) {
				box[x1Here][y1Here] = periChar;
				x1Here += numeX;
				y1Here += denoY;
			}
		}
	}
	
	
	//filling the body of the rectangle
	//scanning every dot in the box array to see if it's inside the rectangle or not
	for (int x3{ 0 }; x3 < 25; x3++) {
		for (int y3{ 0 }; y3 < 25; y3++) {

			//checking each scanned dot with each pair of corners from the rectangle...that results in 4 triangles
			double triangleAreas{ 0 };
			for (int counterXY{ 0 }; counterXY <= 3; counterXY++) {
				int x1 = arrX[counterXY]; int x2 = arrX[counterXY+1];
				int y1 = arrY[counterXY]; int y2 = arrY[counterXY+1];

				//summing the areas of the 4 triangles
				triangleAreas += 0.5 * abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2));
			}

			//checking if the summed areas match the rectangle's area
			double rectangleArea = floor(area() * 10 + .5) / 10;
			triangleAreas = floor(triangleAreas * 10 + .5) / 10;
			if (triangleAreas == rectangleArea) {

				//if so then the scanned dot is inside the rectangle	
				box[x3][y3] = fillChar;
			}
			else {
				//if not the the scanned dot is not inside the rectangle
				;
			}
		}
	}
	
	
	//printing..........notice that we're printing upside down starting from row number 25
	string drawFinal = "";
	for (int x{ 24 }; x >= 0; x--) {
		for (int y{ 0 }; y < 25; y++) {
			drawFinal += box[y][x];
		}
		drawFinal += "\n";
	}
	return drawFinal;
}


