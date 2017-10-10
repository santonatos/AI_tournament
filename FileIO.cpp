#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

string read_file(){
  struct stat buffer;   
  if (stat (string("movefile").c_str(), &buffer) == 0){ 
	  ifstream myfile ("movefile");
	  string line;
	  string line2 = string("");
	  int c = 0;
	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line, ' ') )
	    {
	      if(c == 1 || c == 2){
		line2 += line;
		//cout <<"line2: "<< line2 << "line: "<<line << endl;
		}
	      //cout << line << '\n';
	      c++;
	    }

	    myfile.close();
	  }
	  else{
		cout << "Unable to open file";
		return string("cannot open");
	  }
	  return line2;
  }else{
	  cout << "movefile does not exist, cannot read it" << endl;
	  return string("no movefile");

  }

}


int write_file(string groupname,string column,string row){

  struct stat buffer;   
  if (stat (string("movefile").c_str(), &buffer) == 0){ 
	  ofstream myfile ("movefile");
	  string input = string("");
	  if (myfile.is_open())
	  {
	    input += groupname + string(" ") + column + string(" ") + row;
	    myfile << input;
	    myfile.close();
	  }
	  else cout << "Unable to open file";
	  return 0;
  }else{
	  cout << "movefile does not exist, cannot write on it" << endl;
	  return -1;

  }


}


int check_turn(string go_name){
  struct stat buffer;   
  return (stat (go_name.c_str(), &buffer) == 0); 
}

int check_end(){
  struct stat buffer;   
  return (stat (string("endgame").c_str(), &buffer) == 0);  
  
}


