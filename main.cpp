#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "headers/Board.hpp"
#include "headers/FileIO.hpp"
#include "headers/Game.hpp"
#include <unistd.h>

//string eval(Board gameBoard, string last_move);
using namespace std;

Game gomoku = Game();
int main(int argc,char** argv){

	//cout << "STOI" << stoi("5 ");
	string groupname = string("agentSmurf");
	string group_filename = string("agentSmurf.go");
	printf("start\n");
	int stay = 1;
	//Game gomoku = Game();
	int first_time = 1;
	int c = 0;
	while(stay){
		c++;
		if(check_end()){
			//EXIT LOOP, GAME
			break;
			stay = 0;
			continue;
		}else if(check_turn(group_filename)){
			cout << "OUR Turn" << endl;
			string move = read_file();
			//OUR FIRST MOVE
			if((move.compare("") == 0 || move.compare(" ") == 0 || move.compare("\n") == 0) && first_time){
				//we play first
				gomoku.our_color = 'w';
				gomoku.opponent_color = 'b';
				gomoku.gameBoard.our_color = string("white");
				gomoku.gameBoard.our_color_char = 'w';
				gomoku.make_first_move(1,move);
				first_time = 0;
				continue;
			}else if(first_time){
				//we play second
				gomoku.our_color = 'b';
				gomoku.opponent_color = 'w';
				gomoku.gameBoard.our_color = string("black");
				gomoku.gameBoard.our_color_char = 'b';
				first_time = 0;
				gomoku.make_first_move(2,move);
				continue;
			}else if((move.compare("") == 0 || move.compare(" ") == 0 || move.compare("\n") == 0) && !first_time){

				fprintf(stdout,"[WARNING] why is the movefile empty again\n");
			}

			//OUR REGULAR TURN
			gomoku.store_move(move);
			gomoku.gameBoard.print_board();
			gomoku.make_next_move();


		}


	}

	

}







/*string eval(Board gameBoard, string last_move) {
	// For now
	bool placed = false;
	string move = string("");
	string column, row;
	for(int k =0;k < last_move.length();k++){
		if(k == 0){
			column = last_move[k];
		}else{
			row += last_move[k]; 
		}
	}
	int move_x = gomoku.columns.find(column) + 1;
	int move_y = stoi(row);
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(gameBoard.check_free_cell(move_x + i, move_y + j)) {
				placed = true;
				//return {move_x + i, move_y + j};
				move += to_string(move_x + i) + string(" ") + to_string(move_y + j); 
				return move;
			}
		}
	}
	while (!placed) {
		int rand_x = rand() % 15 + 1;
		int rand_y = rand() % 15 + 1;
		if (gameBoard.check_free_cell(rand_x, rand_y)) {
		//	return {rand_x, rand_y};
				move += to_string(rand_x) + string(" ") + to_string(rand_y); 
				return move;

		}
	}
}*/
