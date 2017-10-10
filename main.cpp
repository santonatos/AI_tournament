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
	int first_time = 1;
	while(stay){
		if(check_end()){
			//EXIT LOOP, GAME
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
				gomoku.make_first_move(1,move);
				first_time = 0;
				continue;
			}else if(first_time){
				//we play second
				gomoku.our_color = 'b';
				gomoku.opponent_color = 'w';
				first_time = 0;
				gomoku.make_first_move(2,move);
				continue;
			}else if((move.compare("") == 0 || move.compare(" ") == 0 || move.compare("\n") == 0) && !first_time){

				fprintf(stdout,"[WARNING] why is the movefile empty again\n");
			}

			//OUR REGULAR TURN
			gomoku.store_move(move);
			gomoku.gameBoard.print_board();

			//TODO 
			//gomoku.make_next_move()

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
