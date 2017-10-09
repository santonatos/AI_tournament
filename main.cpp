#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "headers/Board.hpp"
#include "headers/FileIO.hpp"
#include "headers/Game.hpp"

using namespace std;

int main(int argc,char** argv){

	string groupname = string("agentSmurf");
	string group_filename = string("agentSmurf.go");
	printf("start\n");
	int stay = 1;
	Game gomoku = Game();
	int start = 1;
	while(stay){
		if(check_end()){
			//EXIT LOOP, GAME
			stay = 0;
		}else if(check_turn(group_filename)){

			//TODO next 3 lines
			//gomoku.eval(gomoku.board)
			//gomoku.make_move();
			//write_file();

		}else{
			string move = read_file();
			if(move.compare("") == 0 || move.compare(" ") == 0 || move.compare("\n") == 0){
				//we play first
				gomoku.our_color = 'w';
				gomoku.opponent_color = 'b';
				//TODO gomoku.make_our_first_move();
				start = 0;
				continue;
			}else if(start){
				//we play second
				gomoku.our_color = 'b';
				gomoku.opponent_color = 'w';
				start = 0;
				//TODO gomoku.make_our_first_move();
				continue;
			}

			gomoku.store_move(move);
			gomoku.gameBoard.print_board();



		}
		//cout <<"turn: " << check_turn(group_filename) << endl;
		//cout << "endgame file: " << check_end() << endl;
	//read_file();
	//write_file("us","A","5");

	}
	//Board b1;
	//b1.make_move(1,2,'w');
	//b1.print_board();
	//read_file();
	write_file("us","A","5");
	

}
