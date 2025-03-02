#ifndef UI_H
#define UI_H

#include <cstdio>
#include <cstdlib>
#include <algorithm>

class UI {

private:

	static const int N = 150;
	static const int M = 600;
	static const int RN = 2;
	static const int RM = 4;

	char* ch;

	char& at(int i, int j);

public:
	UI();
	~UI();

	void clear();

	void print();

	void drawLine(float x1, float y1, float x2, float y2);

};


#endif
