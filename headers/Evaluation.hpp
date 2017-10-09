#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <queue>
#include <time>
#include <random>
#include <tuple>

tuple firstMove(Board board);
tuple secondMove(Board board);
tuple randomMove(Board board);

int evalFunction(Board board, tuple position, bool mode);
int evaluatePosition(Board board, tuple position);
list<tuple> attackArea(tuple initPair, int connect);

tuple topMoves(Board board, int limit);
tuple evaluationFunction(Board board);

#endif