#ifndef BOARD_HPP
#define BOARD_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>

class Board {

	public:
		const int width = 15;
		const int height = 15;
		const int size = (width + height) / 2;
		const int connect = 5;
		int turns;
		char board[15][15];

		Board();
		int make_move(int column_index,int row_index,char color);
		void print_board();
		// List (vector) of opponent's moves, in order of first to last
		std::vector<std::tuple<int, int>> get_opponent_move_list();
		// Returns our team's color
		std::string get_our_color();
		// Checks if move is valid
		bool valid_move(std::tuple<int, int> move);
		// Checks if cell is within the board
		bool cell_exists(std::tuple<int, int> cell);
		// Gets color of cell
		std::string get_cell_color(std::tuple<int, int> cell);
		// Gets list (vector) of filled spaces on the board
		std::vector<std::tuple<int, int>> get_filled_spaces();


	private:
		const char columns[16] = "ABCDEFGHIJKLMNO";
		std::map<int,char> columns_map;	
		const char colors[4] = "ewb";

		int check_valid_color(char color);
		int check_valid_position(int column_index,int row_index);
		int check_free_cell(int column_index,int row_index);
			
};

#endif
