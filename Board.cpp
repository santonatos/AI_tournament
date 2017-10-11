#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <functional>
#include "headers/Board.hpp"
using namespace std;

Board::Board(void){
	for(int i = 0;i < this->width;i++){
		for(int j = 0;j < this->height;j++){
			this->board[i][j] = 'e';
		}
	}
	this->turns = 0;
	for(int k = 0;k < this->width;k++){
		this->columns_map[k] = columns[k];

	}
}
string Board::get_our_color(){

	return this->our_color;

}

vector<std::tuple<int, int>> Board::get_opponent_move_list(){
	return this->opponent_moves;


}

bool Board::valid_move(std::tuple<int, int> move){

	int r = this->check_free_cell(get<0>(move),get<1>(move));
	if(r == 1)return true;
	else return false;
}

bool Board::cell_exists(std::tuple<int, int> cell){
	int r = this->check_valid_position(get<0>(cell),get<1>(cell));
	if(r == 1)return true;
	else return false;	


}

string Board::get_cell_color(std::tuple<int, int> cell){
	int c = get<0>(cell);
	int r = get<1>(cell);
	if(board[c][r] == 'w'){
		return string("white");
	}else if(board[c][r] == 'b'){
		return string("black");
	}else{
		return string("empty");
	}
	return string("empty");

}
vector<std::tuple<int, int>> Board::get_filled_spaces(){
	vector<std::tuple<int, int>> myv;
	for(int i = 0;i < this->width;i++){
		for(int j = 0;j < this->height;j++){
			if (this->board[i][j] != 'e'){
		auto new_tuple = std::make_tuple (i+1,j+1);
		myv.push_back(new_tuple);

			}
		}
	}
	return myv;




}
/*
takes arguments from 1 to 15, not 0 to 14
*/
int Board::make_move(int column_index,int row_index,char color){
	if(!Board::check_valid_color(color) ||  !Board::check_valid_position(column_index,row_index)){
		return -1;
	}
	/*if(!Board::check_free_cell(column_index-1,row_index-1)){
		return -1;
	}*/		
	if(board[column_index-1][row_index-1] != 'e'){
		fprintf(stdout,"[WARNING] this cell is already filled, but will be overwritten\n");
	} 
	board[column_index-1][row_index-1] = color;

	if(board[column_index-1][row_index-1] != 'e' && board[column_index-1][row_index-1] != this->our_color_char){
		auto new_tuple = std::make_tuple (column_index,row_index);
		this->opponent_moves.push_back(new_tuple);
	}

	return 1;
}


void Board::print_board(){
	cout << "   ";
	for(int k = 0;k < this->width;k++){
		cout << columns_map[k] << " ";
	}
	cout << endl;
	for(int i = 0;i < this->width;i++){
		string space;
		if(i +1 < 10){
			space = string("  ");
		}else{
			space = string(" "); 
		}
		cout << i + 1 << space; 
		char p;


		for(int j = 0;j < this->height;j++){
			if(this->board[j][i] == 'e'){
				p = '_';
			}else if(this->board[j][i] == 'w'){
				p = 'X';
			}else{
				p = 'O';
			}
			cout << p << " ";
		}
		cout << endl;
	}


}

int Board::check_valid_color(char color){

	for(int i = 0;i < 3;i++ ){
		if(this->colors[i] == color){
			return 1;
		}
	}
	return 0;

}

int Board::check_valid_position(int column_index,int row_index){
	if(column_index > 15 || column_index < 1 || row_index > 15 || row_index < 1){
		cout << "[WARNING] invalid position, out of board" << endl;
		return 0;	

	}
	return 1;

}

int Board::check_free_cell(int column_index,int row_index){
	if(!Board::check_valid_position(column_index,row_index)){
		cout << "[WARNING] out of board " << endl;
		return 0;
	}
	if(this->board[column_index - 1][row_index -1] != 'e'){
		cout << "[WARNING] this cell is occupied by color: " << this->board[column_index-1][row_index-1] << endl;
		return 0;
	}
	return 1;



}



/*// List (vector) of opponent's moves, in order of first to last
vector<tuple<int, int>> Board::get_opponent_move_list(){
	vector<tuple<int, int>> temp = {make_tuple(0, 0)};
	return temp;	
}

// Get our team's color
string Board::get_our_color() {
	return "";
}

// Checks if move is valid
bool Board::valid_move(tuple<int, int> move) {
	return false;
}


// Checks if cell is within the board
bool Board::cell_exists(tuple<int, int> cell) {
	return false;
}

// Gets color of cell
string Board::get_cell_color(tuple<int, int> cell) {
	return "Function not written yet.";
}

// Gets list (vector) of filled spaces on the board
vector<tuple<int, int>> Board::get_filled_spaces() {
	vector<tuple<int, int>> temp = {make_tuple(0, 0)};
	return temp;
}*/
