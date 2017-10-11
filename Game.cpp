#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <tuple>
#include "headers/Game.hpp"
#include "headers/FileIO.hpp"
#include "headers/Evaluation.hpp"
#include <sstream>

using namespace std;

/*Game::Game(void){
	int i;
}*/

int Game::store_move(string move_from_read){

	string column = string(""); //string(move_from_read.c_str()[0]);
	string row = string("");
	//cout << "input: " << move_from_read << endl;
	for(int i =0;i < move_from_read.length();i++){
		if(i == 0){
			column = move_from_read[i];
		}else{
			row += move_from_read[i] + row;
			//cout << "row: " << row << endl; 
		}
	}
	
	int row_index = stoi(row);
	int column_index = Game::columns.find(column) +  1;
	cout <<"opponent's move: " << "row index: " << row_index << "  column_index: " << column_index << endl; 
	/*if(Game::white_turn){
		Game::gameBoard.make_move(column_index,row_index,'w');
		this->white_turn = 0;
		
	}else{
		Game::gameBoard.make_move(column_index,row_index,'b');
		this->white_turn = 1;
	}*/
	Game::gameBoard.make_move(column_index,row_index,Game::opponent_color);
	return 0;

}


int Game::make_first_move(int turn,string move){
	if(turn == 1){
		Game::gameBoard.make_move(7,7,Game::our_color);	
	}else if(turn == 2){
		if(Game::gameBoard.board[7][7] == Game::opponent_color){
			Game::store_move(move);
			Game::gameBoard.make_move(7,7,Game::our_color);
			write_file("agentSmurf","G","7");
		}else{
			Game::make_next_move();
		}	

	}else{
		fprintf(stdout,"[WARNING] unknown turn for this function\n");
	}

	return 0;
}

int Game::make_move(int col, int row,char color){
	Game::gameBoard.make_move(col,row,color);
	return 0;
}

int Game::make_next_move(){
stringstream ss;
	//TODO
	//next_move = gomoku.eval(gomoku.board)
	tuple<int, tuple<int, int>> next_move  = evaluationFunction(this->gameBoard);
	auto move_tuple = get<1>(next_move);
	int c = get<0>(move_tuple);
	int r = get<1>(move_tuple);
	char col = this->columns[c -1];
	string column;
ss << col;
ss >> column;
	string r1 = to_string(r);
	this->make_move(c,r,Game::gameBoard.our_color_char);
	write_file(string("agentSmurf"),column,r1);
	return 0;



}
