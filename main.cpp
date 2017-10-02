#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "headers/Board.hpp"

using namespace std;

int main(int argc,char** argv){

	printf("start\n");
	Board b1;
	b1.make_move(1,2,'w');
	b1.print_board();
	

}
