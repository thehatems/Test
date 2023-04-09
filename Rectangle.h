#include <string>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
	explicit Rectangle(int = 1, int = 1, int = 1, int = 1
					, int = 1, int = 1, int = 1, int = 1);
	void length();
	void width();
	double perimeter();
	double area();
		
	void setFunction(int, int, int, int
				    ,int, int, int, int);

	bool square();

	std::string draw();
	void setFillCharacter(char);
	void setPerimeterCharacter(char);

private:
	double l;
	double w;
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;

	char fillChar;
	char periChar;
};

#endif