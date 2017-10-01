#include"Scene.h"
int main() {
	MineScene<10, 10> mine(0.05);
	mine.PrintScene();
	int row, column;
	while (true) {
		std::cin >> row >> column;
		mine.RevealMine(row, column);
		mine.PrintScene();
	}
	getchar();
}
