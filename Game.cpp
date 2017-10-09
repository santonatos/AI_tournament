#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "headers/Game.hpp"

using namespace std;

/*Game::Game(void){
	int i;
}*/

int Game::store_move(string move_from_read){

	string column = string(""); //string(move_from_read.c_str()[0]);
	string row = string("");
	cout << "input: " << move_from_read << endl;
	for(int i =0;i < move_from_read.length();i++){
		if(i == 0){
			column = move_from_read[i];
		}else{
			row += move_from_read[i] + row;
			cout << "row: " << row << endl; 
		}
	}
	
	int row_index = stoi(row);
	int column_index = Game::columns.find(column) +  1;
	cout << "row index: " << row_index << "  column_index" << column_index << endl; 
	if(Game::white_turn){
		Game::gameBoard.make_move(column_index,row_index,'w');
		this->white_turn = 0;
		
	}else{
		Game::gameBoard.make_move(column_index,row_index,'b');
		this->white_turn = 1;
	}
	return 0;

}


int Game::make_move(int c, int r){

return 0;
}

