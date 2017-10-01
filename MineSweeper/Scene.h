//Scene of MineSweeper
//By 78ij
#ifndef SCENE_H
#define SCENE_H

#include<random>
#include<vector>
#include<sys/timeb.h>
#include<iostream>
#include<Windows.h>

//Define Types of Grids
#define NotMineAndUntouched 0
#define IsMineAndUntouched 1
#define NotMineAndRevealed 2
#define FlaggedAndIsMine 3
#define FlaggedAndNotMine 4

std::vector<int> random2(int, int);

template<int rows,int columns>
class MineScene {
public:
	    int Data[rows][columns];
		MineScene() = default;
		MineScene(double density);
		void PrintScene();
		void RevealMine(int row, int column);
		bool TestMine(int row, int column);
		int  ExamMine(int row, int column);
		void GameOver();
};


template<int rows, int columns>
void MineScene<rows, columns>::PrintScene() {
	for (int i = 0; i < 30; i++)
		std::cout << "\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (Data[i][j] == NotMineAndUntouched || Data[i][j] == IsMineAndUntouched) {
				std::cout << "# ";
			}
			if (Data[i][j] == NotMineAndRevealed) {
				int MineNum = ExamMine(i, j);
				std::cout << MineNum << " ";
			}
		}
		std::cout << std::endl;
	}
}
template<int rows, int columns>
MineScene<rows, columns>::MineScene(double density) {
	int GridNumber = rows * columns;
	int MineNum = (int)(density * GridNumber);
	std::vector<std::vector<int>> MineCoordinate;
	std::vector<int> temp;
	MineCoordinate.push_back(random2(rows, columns));
	for (int i = 1; i < MineNum; i++) {
		while (true) {
			temp = random2(rows, columns);
			Sleep(1);
			if (isequal(temp, MineCoordinate)) {
				MineCoordinate.push_back(temp);
				break;
			}
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Data[i][j] = NotMineAndUntouched;
		}
	}
	for (int i = 0; i < MineNum; i++) {
		Data[MineCoordinate[i][0]][MineCoordinate[i][1]] = IsMineAndUntouched;
	}
}

template<int rows,int columns>
void MineScene<rows, columns>::RevealMine(int row, int column) {
	if (Data[rows][columns] == IsMineAndUntouched) {
		GameOver();
		return;
	}
	if (Data[row][column] == 2) return;

	if (TestMine(row, column)) {
		Data[row][column] = NotMineAndRevealed;
		if (row - 1 >= 0 && column - 1 >= 0) RevealMine(row - 1, column - 1);
		if (row - 1 >= 0) RevealMine(row - 1, column);
		if (row - 1 >= 0 && column + 1 < columns) RevealMine(row - 1, column + 1);
		if (column - 1 >= 0) RevealMine(row, column - 1);
		if (column + 1 < columns) RevealMine(row, column + 1);
		if (row + 1 < rows) RevealMine(row + 1, column);
		if (row + 1 < rows && column - 1 >= 0) RevealMine(row + 1, column - 1);
		if (row + 1 < rows && column + 1 < columns) RevealMine(row + 1, column + 1);
	}
	else {
		Data[row][column] = NotMineAndRevealed;
		return;
	}
	return;
}
template<int rows, int columns>
void MineScene<rows, columns>::GameOver() {
	std::cout << "GameOver!";
}
//A SB function
template<int rows,int columns>
bool MineScene<rows, columns>::TestMine(int row, int column) {
	int auxData[rows][columns];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (Data[i][j] == 0 || Data[i][j] == 2)
				auxData[i][j] = 0;
		}
	}
	if (row != 0 && column != 0 && row != rows - 1 && column != columns - 1) {
		if (auxData[row - 1][column - 1] == 0 && auxData[row - 1][column] == 0 && auxData[row - 1][column + 1] == 0 && auxData[row][column - 1] == 0 && auxData[row][column + 1] == 0 && auxData[row + 1][column - 1] == 0 && auxData[row + 1][column] == 0 && auxData[row + 1][column + 1] == 0)
			return 1;
	}
	if (row == 0 && column != 0 && row != rows - 1 && column != columns - 1) {
		if (auxData[row][column - 1] == 0 && auxData[row][column + 1] == 0 && auxData[row + 1][column - 1] == 0 && auxData[row + 1][column] == 0 && auxData[row + 1][column + 1] == 0)
			return 1;
	}
	if (row != 0 && column == 0 && row != rows - 1 && column != columns - 1) {
		if (auxData[row - 1][column] == 0 && auxData[row - 1][column + 1] == 0 && auxData[row][column + 1] == 0 && auxData[row + 1][column] == 0 && auxData[row + 1][column + 1] == 0)
			return 1;
	}
	if (row != 0 && column != 0 && row == rows - 1 && column != columns - 1) {
		if (auxData[row - 1][column - 1] == 0 && auxData[row - 1][column] == 0 && auxData[row - 1][column + 1] == 0 && auxData[row][column - 1] == 0 && auxData[row][column + 1] == 0)
			return 1;
	}
	if (row != 0 && column != 0 && row != rows - 1 && column == columns - 1) {
		if (auxData[row - 1][column - 1] == 0 && auxData[row - 1][column] == 0&& auxData[row][column - 1] == 0 && auxData[row + 1][column - 1] == 0 && auxData[row + 1][column] == 0)
			return 1;
	}
	if (row == 0 && column == 0 ) {
		if (auxData[row][column + 1] == 0 && auxData[row + 1][column] == 0 && auxData[row + 1][column + 1] == 0)
			return 1;
	}
	if (row == rows - 1  && column == columns - 1) {
		if (auxData[row - 1][column - 1] == 0 && auxData[row - 1][column] == 0  && auxData[row][column - 1] == 0)
			return 1;
	}
	if (row == 0 && column == columns - 1) {
		if (auxData[row][column - 1] == 0 && auxData[row + 1][column - 1] == 0 && auxData[row + 1][column] == 0)
			return 1;
	}
	if (column == 0 && row == rows - 1) {
		if (auxData[row - 1][column] == 0 && auxData[row - 1][column + 1] == 0 && auxData[row][column + 1] == 0)
			return 1;
	}


	return 0;
}
//Another SB function
template<int rows,int columns>
int MineScene<rows, columns>::ExamMine(int row, int column) {
	int result = 0;
	if (row - 1 >= 0 && column - 1 >= 0 && Data[row - 1][column - 1] == IsMineAndUntouched) 
		result++;
	if (row - 1 >= 0 && Data[row - 1][column ] == IsMineAndUntouched)
		result++;
	if (column - 1 >= 0 && Data[row][column - 1] == IsMineAndUntouched)
		result++;
	if (Data[row][column] == IsMineAndUntouched)
		result++;
	if (row + 1 < rows && Data[row + 1][column] == IsMineAndUntouched)
		result++;
	if (row + 1 < rows && column + 1 < columns && Data[row + 1][column + 1] == IsMineAndUntouched)
		result++;
	if (row - 1 >= 0 && column + 1 < columns && Data[row - 1][column + 1] == IsMineAndUntouched)
		result++;
	if (row + 1 < rows && column - 1 >= 0 && Data[row + 1][column - 1] == IsMineAndUntouched)
		result++;
	return result;
}
std::vector<int> random2(int rows, int columns) {
	struct timeb timeSeed;
	ftime(&timeSeed);
	std::default_random_engine engine;
	engine.seed(timeSeed.millitm);
	std::uniform_int_distribution<int> distributionr(0, rows - 1);
	std::uniform_int_distribution<int> distributionc(0, columns - 1);
	int r = distributionr(engine);
	int c = distributionc(engine);
	std::vector<int> coordinate;
	coordinate.push_back(r);
	coordinate.push_back(c);
	return coordinate;
}
bool isequal(std::vector<int> temp, std::vector<std::vector<int>> target) {
	for (auto temp2 : target) {
		if (temp2 == temp)
			return 0;
	}
	return 1;
}
#endif