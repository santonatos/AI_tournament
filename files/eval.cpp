#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "headers/Game.hpp"

using namespace std;

int[] eval(Game::gameBoard, string last_move) {
	// For now
	bool placed = false;
	string column, row;
	for(int k =0;k < last_move.length();k++){
		if(k == 0){
			column = last_move[k];
		}else{
			row += last_move[k]; 
		}
	}
	int move_x = Game::columns.find(last_move_list[0]) + 1;
	int move_y = stoi(last_move_list[1]);
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(gameBoard.check_free_cell(move_x + i, move_y + j)) {
				placed = true;
				return {move_x + i, move_y + j};
			}
		}
	}
	while (!placed) {
		rand_x = rand() % 15;
		rand_y = rand() % 15;
		if (gameBoard.check_free_cell(rand_x, rand_y) {
			return {rand_x, rand_y};
		}
	}
}