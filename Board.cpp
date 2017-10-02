#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
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
/*
takes arguments from 1 to 15, not 0 to 14
*/
int Board::make_move(int column_index,int row_index,char color){
	if(!Board::check_valid_color(color) ||  !Board::check_valid_position(column_index,row_index)){
		return -1;
	}
	if(!Board::check_free_cell(column_index,row_index)){
		return -1;
	}		
	
	board[column_index-1][row_index-1] = color;
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
		if(i < 10){
			space = string("  ");
		}else{
			space = string(" "); 
		}
		cout << i << space; 
		char p;


		for(int j = 0;j < this->height;j++){
			if(this->board[i][j] == 'e'){
				p = '_';
			}else if(this->board[i][j] == 'w'){
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
		cout << "invalid position, out of board" << endl;
		return 0;	

	}
	return 1;

}

int Board::check_free_cell(int column_index,int row_index){
	if(!Board::check_valid_position(column_index,row_index)){
		return 0;
	}
	if(this->board[column_index][row_index] != 'e'){
		cout << "this cell is occupied by color: " << this->board[column_index][row_index] << endl;
		return 0;
	}
	return 1;



}



