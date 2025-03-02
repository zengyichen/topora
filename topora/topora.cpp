#include "Model.h"
#include "UI.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>

void clearScreen(){
	system("cls");
}


void printIntro() {
	clearScreen();
	puts(
		"欢迎使用 topora！\n"
		"topora 根据用户输入的参数，建立三维拓扑结构。\n"
		"目前支持 TO PO RA 三类建模方式，详见 README.md。\n"
		"按 q 退出程序。\n"
		"\n"
		"\n"
		"(按任意键继续)\n"
	);
	char key = _getch();
	
	// quit if ESC is pressed
	if (key == 27 || key == 'Q' || key == 'q') {
		exit(0);
	}
}


ModelType selectModelType() {
	clearScreen();
	puts(
		"请选择建模类型：\n"
		"1. TO\n"
		"2. PO\n"
		"3. RA\n"
		"\n"
		"\n"
		"(按 1, 2, 3 选择，按任意键继续)\n"
	);
	char key = _getch();
	if (key == '1') {
		return TO;
	} else if (key == '2') {
		return PO;
	} else if (key == '3') {
		return RA;
	} else {
		return TO;
	}
}

// return whether the input is valid
bool inputArgs(Model& model, ModelType type) {
	clearScreen();
	if (type == TO) {
		puts(
			"TO 型需要以下参数：\n"
			"1. sliceNum（>= 2 整数）：层数\n"
			"2. edgeNum（>= 2 整数）：每层边数\n"
			"3. radius（长度为 sliceNum 的浮点数序列）：每层半径\n"
			"4. pointOffset（整数）：层间连边的间隔\n"
			"5. angleOffset（浮点数）：层间旋转的角度\n"
			"\n"
			"\n"
		);

		int sliceNum, edgeNum, pointOffset;
		float angleOffset;
		std::vector<float> radius;

		puts("\n1. sliceNum（>= 2 整数）：层数");
		std::cin >> sliceNum;
		if (sliceNum < 2) {
			puts("层数必须大于等于 2\n");
			return false;
		}

		puts("\n2. edgeNum（>= 2 整数）：每层边数");
		std::cin >> edgeNum;
		if (edgeNum < 2) {
			puts("每层边数必须大于等于 2\n");
			return false;
		}

		puts("\n3. radius（长度为 sliceNum 的浮点数序列）：每层半径");
		for (int i = 0; i < sliceNum; i++) {
			float r;
			std::cin >> r;
			radius.push_back(r);
		}

		puts("\n4. pointOffset（整数）：层间连边的间隔");
		std::cin >> pointOffset;
		pointOffset = (pointOffset % edgeNum + edgeNum) % edgeNum;

		puts("\n5. angleOffset（浮点数）：层间旋转的角度");
		std::cin >> angleOffset;

		model.buildTO(sliceNum, edgeNum, radius, pointOffset, angleOffset);

	} else if (type == PO) {
		puts(
			"PO 型需要输入以下参数：\n"
			"1. xRange\n"
			"2. yRange\n"
			"3. x2Coef\n"
			"4. y2Coef\n"
			"5. xyCoef\n"
			"6. xCoef\n"
			"7. yCoef\n"
			"\n"
			"f(x, y) = x^2 * x2Coef + y^2 * y2Coef + x * y * xyCoef + x * xCoef + y * yCoef\n"
			"(0 <= x <= xRange), (0 <= y <= yRange)\n"
			"其中 xRange, yRange 为正整数，x2Coef, y2Coef, xyCoef, xCoef, yCoef 为浮点数。\n"
			"\n"
			"\n"
		);

		int xRange, yRange;
		float x2Coef, y2Coef, xyCoef, xCoef, yCoef;

		puts("\n1. xRange（正整数）");
		std::cin >> xRange;
		if (xRange <= 0) {
			puts("xRange 必须为正整数\n");
			return false;
		}
		
		puts("\n2. yRange（正整数）");
		std::cin >> yRange;
		if (yRange <= 0) {
			puts("yRange 必须为正整数\n");
			return false;
		}

		puts("\n3. x2Coef");
		std::cin >> x2Coef;

		puts("\n4. y2Coef");
		std::cin >> y2Coef;

		puts("\n5. xyCoef");
		std::cin >> xyCoef;

		puts("\n6. xCoef");
		std::cin >> xCoef;

		puts("\n7. yCoef");
		std::cin >> yCoef;

		model.buildPO(xRange, yRange, x2Coef, y2Coef, xyCoef, xCoef, yCoef);

	} else if (type == RA) {
		puts(
			"RA 型需要输入以下参数：\n"
			"1. sliceNum \n"
			"2. sinCoef\n"
			"3. sinArg\n"
			"4. cosCoef\n"
			"5. cosArg\n"
			"6. base\n"
			"\n"
			"f(x) = sinCoef * sin(sinArg * x) + cosCoef * cos(cosArg * x) + base\n"
			"x 为圆均分 sliceNum 所得角度。\n"
			"其中 sliceNum 为 >= 2 整数，其余为浮点数。\n"
			"\n"
			"\n"
		);
		
		int sliceNum, sinArg, cosArg;
		float sinCoef, cosCoef, base;

		puts("\n1. sliceNum（>= 2 整数）");
		std::cin >> sliceNum;
		if (sliceNum < 2) {
			puts("sliceNum 必须大于等于 2\n");
			return false;
		}

		puts("\n2. sinCoef");
		std::cin >> sinCoef;

		puts("\n3. sinArg");
		std::cin >> sinArg;

		puts("\n4. cosCoef");
		std::cin >> cosCoef;

		puts("\n5. cosArg");
		std::cin >> cosArg;

		puts("\n6. base");
		std::cin >> base;

		model.buildRA(sliceNum, sinCoef, sinArg, cosCoef, cosArg, base);
	}

	std::cin.ignore(100, '\n');

	return true;
}

bool readArgsFromFile(Model& model, const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		puts("文件打开失败\n");
		return false;
	}

	ModelType type;
	std::string str;

	file >> str;

	if (str == "TO") {
		type = TO;

		int sliceNum, edgeNum, pointOffset;
		float angleOffset;
		std::vector<float> radius;

		file >> sliceNum;
		if (sliceNum < 2) {
			puts("层数必须大于等于 2\n");
			return false;
		}

		file >> edgeNum;
		if (edgeNum < 2) {
			puts("每层边数必须大于等于 2\n");
			return false;
		}

		for (int i = 0; i < sliceNum; i++) {
			float r;
			file >> r;
			radius.push_back(r);
		}

		file >> pointOffset;
		pointOffset = (pointOffset % edgeNum + edgeNum) % edgeNum;

		file >> angleOffset;

		model.buildTO(sliceNum, edgeNum, radius, pointOffset, angleOffset);
	} else if (str == "PO") {
		type = PO;

		int xRange, yRange;
		float x2Coef, y2Coef, xyCoef, xCoef, yCoef;

		file >> xRange;
		if (xRange <= 0) {
			puts("xRange 必须为正整数\n");
			return false;
		}

		file >> yRange;
		if (yRange <= 0) {
			puts("yRange 必须为正整数\n");
			return false;
		}

		file >> x2Coef;
		file >> y2Coef;
		file >> xyCoef;
		file >> xCoef;
		file >> yCoef;

		model.buildPO(xRange, yRange, x2Coef, y2Coef, xyCoef, xCoef, yCoef);

	} else if (str == "RA") {
		type = RA;

		int sliceNum, sinArg, cosArg;
		float sinCoef, cosCoef, base;

		file >> sliceNum;
		if (sliceNum < 2) {
			puts("sliceNum 必须大于等于 2\n");
			return false;
		}

		file >> sinCoef;
		file >> sinArg;
		file >> cosCoef;
		file >> cosArg;
		file >> base;

		model.buildRA(sliceNum, sinCoef, sinArg, cosCoef, cosArg, base);
	} else {
		return false;
	}

	file.close();

	return true;
}


void showModel(Model& model) {
	clearScreen();
	puts(
		"模型已建立。\n"
		"请仔细阅读以下提示：\n"
		"\n"
		"1. 请使用等宽字体，并滚轮缩放至合适大小。\n"
		"2. 请调整输入法为英文模式。\n"
		"3. 使用 QWEASD 移动相机，UIOJKL 旋转相机。\n"
		"4. 按 x 退出，之后滚轮缩放还原大小。\n"
		"\n"
		"\n"
		"(准备完成后，按任意键继续)\n"
	);
	
	_getch();

	Camera cam;
	UI ui;

	cam.rotate(Vector({ARC(180), ARC(0), ARC(0)}));
	cam.move(Vector({0, 0, 2}));

	while (1) {
		//clearScreen();
		// 比 system("cls") 更快
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };
		SetConsoleCursorPosition( hConsole, coordScreen );

		ui.clear();
		model.renderAscii(cam, ui);
		ui.print();

		char key = _getch();
		if (key == 's' || key == 'S') {
			cam.move(Vector({ 0, 0, 0.1 }));
		} else if (key == 'w' || key == 'W') {
			cam.move(Vector({ 0, 0, -0.1 }));
		} else if (key == 'q' || key == 'Q') {
			cam.move(Vector({ -0.1, 0, 0 }));
		} else if (key == 'e' || key == 'E') {
			cam.move(Vector({ 0.1, 0, 0 }));
		} else if (key == 'd' || key == 'D') {
			cam.move(Vector({ 0, -0.1, 0 }));
		} else if (key == 'a' || key == 'A') {
			cam.move(Vector({ 0, 0.1, 0 }));
		} else if (key == 'l' || key == 'L') {
			cam.rotate(Vector({ ARC(1), 0, 0 }));
		} else if (key == 'j' || key == 'J') {
			cam.rotate(Vector({ ARC(-1), 0, 0 }));
		} else if (key == 'i' || key == 'I') {
			cam.rotate(Vector({ 0, ARC(1), 0 }));
		} else if (key == 'k' || key == 'K') {
			cam.rotate(Vector({ 0, ARC(-1), 0 }));
		} else if (key == 'o' || key == 'O') {
			cam.rotate(Vector({ 0, 0, ARC(1) }));
		} else if (key == 'u' || key == 'U') {
			cam.rotate(Vector({ 0, 0, ARC(-1) }));
		} else if (key == 'x' || key == 'X' || key == 27) {
			break;
		}

		Sleep(10);
	}
}

int main(int argc, char** argv) {

	if (argc == 1) {
	
		Model model;

		while (1) {
			printIntro();
			ModelType type = selectModelType();

			bool succeed = inputArgs(model, type);
		
			if (!succeed) {
				puts("输入有误，请重新输入。\n"
					"\n"
					"\n"
					"(按任意键继续)\n"
				);
				_getch();
				continue;
			}

			showModel(model);
		}
	} else if (argc == 2) {

		Model model;

		readArgsFromFile(model, argv[1]);

		showModel(model);

	} else {
		puts("参数错误\n"
			"\n"
			"\n"
			"使用方法：\n"
			"topora.exe：运行交互界面，手动输入参数。\n"
			"topora.exe [filename]：从文件读取参数。\n"
		);
	}

	return 0;
}
