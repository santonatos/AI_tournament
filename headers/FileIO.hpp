#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <string>

using std::string;

string read_file();
int write_file(string groupname,string column,string row);
int check_turn(string group_filename);
int check_end();

#endif
