#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include "Board.hpp"

using std::string;
class Game {

	public:
		int turns = 0;
		char our_color = ' ';
		char opponent_color = ' ';
		int white_turn = 0;
		Board gameBoard = Board();
		string columns = string("ABCDEFGHIJKLMNO");

		int store_move(string move_from_read);
		int make_move(int c, int r);
		//int make_move();
	//private:
			
};

#endif
