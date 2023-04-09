#include <iostream>
#include "Rectangle.h"
#include <stdexcept>

using namespace std;

int main() {
	cout << "please Enter 4 coordinates\n" << endl;

	cout << "Your coordinates are (x1,y1) (x2,y2) (x3,y3) (x4,y4)" << endl;
	
	cout << "x1: "; int x1; cin >> x1;
	
	cout << "y1: "; int y1; cin >> y1;
	
	cout << "x2: "; int x2; cin >> x2;
	
	cout << "y2: "; int y2; cin >> y2;
	
	cout << "x3: "; int x3; cin >> x3;
	
	cout << "y3: "; int y3; cin >> y3;
	
	cout << "x4: "; int x4; cin >> x4;
	
	cout << "y4: "; int y4; cin >> y4;
	
	Rectangle rectangle1;
	try {
		rectangle1 = Rectangle{ x1, y1
				,x2, y2
				,x3, y3
				,x4, y4 };
	}
	catch (invalid_argument& ex) {
		cout << ex.what();
		return 0;
	}

	cout << "Enter a character for the body of the rectangle: ";
	char body; cin >> body;
	rectangle1.setFillCharacter(body);

	cout << "Enter a character for the border of the rectangle: ";
	char border; cin >> border;
	rectangle1.setPerimeterCharacter(border);
	
	cout << "\n\n" << rectangle1.draw();

}