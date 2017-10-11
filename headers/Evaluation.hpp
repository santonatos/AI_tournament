#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <queue>
#include <random>
#include <tuple>
#include <vector>
#include <algorithm>
#include "Board.hpp"
using namespace std;

tuple<int, int> firstMove(Board board);
tuple<int, int> secondMove(Board board);
tuple<int, int> randomMove(Board board);

int evalFunction(Board board, tuple<int, int> position, bool mode);
int evaluatePosition(Board board, tuple<int, int> position);
vector<tuple<int, int>> attackArea(tuple<int, int> initPair, int connect);

tuple<int, tuple<int, int>> topMoves(Board board, int limit);
tuple<int, tuple<int, int>> evaluationFunction(Board board);

#endif