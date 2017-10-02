#include"Scene.h"
int main() {
	double density;
	std::cout << "please input the density" << std::endl;
	std::cin >> density;
	for (int i = 0; i < 30; i++) {
		std::cout << "\n";
	}
	MineScene<10,10> mine(density);
	mine.PrintScene();
	int row, column;
	while (true) {
		std::cin >> row >> column;
		mine.RevealMine(row, column);
		mine.PrintScene();
		if (mine.gameover) {
			for (int i = 0; i < 30; i++) {
			    std::cout << "\n";
			}
			std::cout << "Game Over!";
			break;
		}
		if(mine.Determinewin()){
			for (int i = 0; i < 30; i++) {
				std::cout << "\n";
			}
			std::cout << "You Win!";
			break;
		}
	}
	getchar();
	getchar();
}
