#include "UI.h"

char& UI::at(int i, int j) { if (i > N || j > M) return ch[0]; return ch[i * (M + 1) + j]; }

UI::UI() {
	ch = new char [(N + 1) * (M + 1)];
	clear();
}

UI::~UI() {
	delete[] ch;
}

void UI::clear() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			at(i, j) = ' ';
		}
		at(i, M) = '\n';
	}
	at(N, 0) = '\0';
}

void UI::print() {
	// fputs(ch, stdout);
	puts(ch);
}

void UI::drawLine(float x1, float y1, float x2, float y2) {
	int x1i = x1 * N / RN;
	int y1i = y1 * M / RM;
	int x2i = x2 * N / RN;
	int y2i = y2 * M / RM;

	//printf("(%d %d) ----- (%d %d)\n", x1i, y1i, x2i, y2i);

	int dx = abs(x1i - x2i), dy = abs(y1i - y2i);

	if (dx > dy) {
		if (x1i > x2i) {
			std::swap(x1i, x2i);
			std::swap(y1i, y2i);
		}
		for (int i = std::max(x1i, 0); i < std::min(x2i + 1, N); i++) {
			int j;
			if (x2i == x1i) j = y1i;
			else j = round(y1i + 1.0 * (y2i - y1i) * (i - x1i) / (x2i - x1i));
			if (j < 0 || j >= M) continue;
			at(i, j) = '#';
		}
	} else {
		if (y1i > y2i) {
			std::swap(x1i, x2i);
			std::swap(y1i, y2i);
		}
		for (int i = std::max(y1i, 0); i < std::min(y2i + 1, M); i++) {

			int j;
			if (y2i == y1i) j = x1i;
			else j = round(x1i + 1.0 * (x2i - x1i) * (i - y1i) / (y2i - y1i));


			//printf("(%d %d)\n", j, i);

			if (j < 0 || j >= N) continue;
			at(j, i) = '#';
		}
	}
}
