#ifndef BOARD_HPP
#define BOARD_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

class Board {

	public:
		const int width = 15;
		const int height = 15;
		int turns;
		char board[15][15];

		Board();
		int make_move(int column_index,int row_index,char color);
		void print_board();


	private:
		const char columns[16] = "ABCDEFGHIJKLMNO";
		std::map<int,char> columns_map;	
		const char colors[4] = "ewb";

		int check_valid_color(char color);
		int check_valid_position(int column_index,int row_index);
		int check_free_cell(int column_index,int row_index);
			
};

#endif
