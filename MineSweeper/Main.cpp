#include"Scene.h"
//To play:
//input the density of the mine you want(the value must be between 0 and 1)
//"#"represents the untouched grid and ghe digits represent the number of mines around this grid
//input the coordinate of the grid you want to reveal
//the coordinate starts from 1 and the format is(row,column)
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
		mine.RevealMine(row - 1, column - 1);
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
