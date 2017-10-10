//Based on the theory described here: http://www.renju.nu/wp-content/uploads/sites/46/2016/09/Go-Moku.pdf
#include <queue>
#include <ctime>
#include <random>
#include <tuple>
#include <vector>
#include "../Board.cpp"
#include "../headers/Evaluation.hpp"
using namespace std;

tuple<int, int> firstMove(Board board){
    /*     
    The most logical first move is dead-center of the board, so the AI should do just this.
    @param:     board   The playing board.
    @returns:   A tuple containing the coordinates of the move.
     */
    int x = board.size / 2;
    return make_tuple(x, x);
}

tuple<int, int> secondMove(Board board){
    /*
    The most strategic second move is diagonal-adjacent to the first placed tile.
    This move is more strategic if it's diagonal into the larger area of the board, if possible
    @param:     board   The playing board.
    @returns:   A tuple containing the coordinates of the move.
    */
    // Get position of first tile
    int y1 = board.black[0][0];
    int x1 = board.black[0][1];
    int y2 = 0;
    int x2 = 0;

    if (y1 <= board.size / 2) {
        y2 = 1;
    } else {
        y2 = -1;
    }

    if (x1 <= board.size / 2) {
        x2 = 1;
    } else {
        x2 = -1;
    }

    return make_tuple(y1 + y2, x1 + x2);
}

tuple<int, int> randomMove(Board board) {
    /*
    Randomly chooses a location to place the tile
    @param:     board   The playing board.
    @returns:   A tuple containing the coordinates of the move.
    */
    bool go = true;
    int y = 0;
    int x = 0;

    while (go) {
        x = rand() % (board.size - 1);
        y = rand() % (board.size - 1);
        go = !board.validMove((y, x));
    }
    return make_tuple(x, y);
}

int evalFunction(Board board, tuple<int, int> position, bool mode) {
    /* 
    Evaluates the importance of a given position on the board, based on the number of ways
        the board can connect if a tile is placed there. The position is weighted exponentially
        based on the number of pieces that can be connected from that position. The mode controls
        whether the player is "on the attack" or "defending" (think Min/Max?), where connections are
        weighted heavier in attack mode - thus the function prefers taking a winning move in "attack"
        mode over taking a move that blocks another players winning move.
    @param:     board       The playing board.
    @param:     position    Coordinates of a location on the board.
    @param:     mode        Positional strategy. True if "attack", false if "defend".
    @returns:   The importance/strategic value of the position.
    */

    //int x0 = position[0];
    //int y0 = position[1];
    int x0 = get<0>(position);
    int y0 = get<1>(position);
    int evalution = 0;
    vector<tuple<int, int>> opts = {make_tuple(1, 0), make_tuple(0, 1), make_tuple(1, 1), make_tuple(1, -1)};

    // Determine how we're weighing the evaluation (for attack or defend)

    string color = board.our_color;
    string not_color;
    if (color == "white") {
        not_color = "Black";
    } else {
        not_color = "white";
    }

    // Evaluate all neighboring nodes of current position
    for (tuple<int, int> pair : opts) {

        // Establish the position and instantiate the pathlist
        int x1 = get<0>(pair);
        int y1 = get<1>(pair);
        
        int evaluation = 0;
        vector<string> pathlist = {"."};


        for (int j : array<int, 2> = {1, -1}) {
            for (int i = 1; i <= board.connect; i++) {

                // Determine new coordinates to check for potential impact on position's value
                int y2 = y0 + y1 * i * j;
                int x2 = x0 + x1 * i * j;
                int x_ol = x2 + x1 * j;
                int y_ol = y2 + y1 * j;

                // Check if the projected position is not on the board, is already taken by the opponent,
                //  or if move would form an overline. If yes, then break. Otherwise, check to see
                //  where the move is added to the list of paths
                if(!board.cell_exists(x2, y2) || board.get_cell(x2, y2).color == not_color)
                    || (i + 1 == board.connect && board.cell_exists(x_ol, y_ol)
                    && board.get_cell(x_ol, y_ol).color == color) {
                        break;
                    } else if (j > 0) { // Insert at back of list if right of position
                        pathlist.push_back(board.get_cell(x2, y2).color);
                    } else if (j < 0) { // Insert at front of list if left of position
                        pathlist.insert(0, board.get_cell(x2, y2).color);
                    }

                // Determine the number of connections that can be formed at the given position
                int paths_num = pathlist.size() - board.connect + 1;
                int consec = 0;
                // Determine the total consecutive score for the given position
                if (paths_num > 0) {
                    for (int i = 0; i <= paths_num; i++) {
                        if (mode) {
                            consec = pathlist[i:i + board.connect].count(color);
                        } else {
                            consec = pathlist[i:i + board.connect].count(not_color);
                        }

                        if (consec != board.connect - 1) {
                            if (consec != 0) {
                                evaluation += pow(5, consec);
                            }
                        } else {
                            if (mode) {
                                evaluation += pow(10, 9);
                            } else {
                                evaluation += pow(10, 8);
                            }
                        }
                    }
                }
            }
        }
    }
    return evaluation;
}

int evaluatePosition(Board board, tuple<int, int> position) {
    /*
    Evaluates the net value of a given position on the board by finding summing the position's
        value to both the player and their opponent. By choosing the position with the most value
        to the player and the most value to the opponent, we are effectively making the move with 
        the greatest offensive and defensive value, thus making it the most strategic. An invalid
        move is returned with an importance value of 0.
    @param:     board       The playing board.
    @param:     position    Coordinates of a location on the board.
    @returns:   The importance/strategic value of the position.
    */
    int x = get<0>(position);
    int y = get<1>(position);

    if (board.cell_exists(x, y)) {
        int result = evalFunction(board, position, true) + evalFunction(board, position, false);
        return result;
    } else {
        return 0;
    }

}

vector<tuple<int, int>> attackArea(tuple<int, int> initPair, int connect) {
    /* 
    Determines the coordinates of connect spaces at a position.
    @param:     pair        The starting coordinates in the format (y, x).
    @param:     connect     Connect size.
    @returns:   A list containing coordinates of connect spaces.
    */
    vector<tuple<int, int>> area;
    tuple<int, int> opts = make_tuple(make_tuple(1, 0), make_tuple(0, 1), make_tuple(1, 1), make_tuple(1, -1));

    int x = get<0>(initPair);
    int y = get<1>(initPair);

    for (tuple<int, int> pair : opts) {
        int x1 = get<0>(Pair);
        int y1 = get<1>(Pair);

        for (int j : make_tuple(1, -1)) {
            for (int i = 1; i <= connect; i++){
                int x2 = x + x1 * i * s;
                int y2 = y + y1 * i * s;
                area.push_back(make_tuple(x2, y2));
            }

        }
    }
    return area;
}

tuple<int, tuple<int, int>> topMoves(Board board, int limit) {
    /* 
    Determines a limited amount of "top moves" based on the evaluatePosition function.
    @param:     board       The playing board.
    @param:     limit       The number of "top" moves to return.
    @returns:   A map of the top moves available along with their values as the key.
    */

    vector<tuple> spots;
    vector<tuple> topList;
    priority_queue<int, tuple<int, int>> topQueue;

    // 
    board.print_board();

    // For each piece on the board
    for (tuple<int, int> n : board.get_filled_coordinates()) {

        // For each potential connect space within range
        for (tuple<int, int> m : attackArea(n, board.connect)) {

            int x = get<0>(m);
            int y = get<1>(m);

            // If the connect space is on the board, add to list of potential spots
            if (board.cell_exists(x, y) && !board.get_filled_coordinates().find(m)) {
                spots.push_back(m);
            }
        }
    }

    // Evaluate potential of each spot, and add to queue
    for (tuple<int, int> p : spots) {
        topQueue.push(evaluatePosition(board, p) * (-1), p);
    }

    for (int z = 0; z <= limit; z++) {
        topList.push_back(topQueue.pop());
    }

    return topList.front();
}

tuple<int, tuple<int, int>> evaluationFunction(Board board) {
    return topMoves(board, 1);
}