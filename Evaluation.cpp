// Based on the theory described here: http://www.renju.nu/wp-content/uploads/sites/46/2016/09/Go-Moku.pdf
#include "headers/Board.hpp"
#include "headers/Evaluation.hpp"
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
    tuple<int, int> opponent_moves = board.get_opponent_move_list().front();
    int x1 = get<0>(opponent_moves);
    int y1 = get<1>(opponent_moves);
    int x2 = 0;
    int y2 = 0;

    if (x1 <= board.size / 2) {
        x2 = 1;
    } else {
        x2 = -1;
    }

    if (y1 <= board.size / 2) {
        y2 = 1;
    } else {
        y2 = -1;
    }

    return make_tuple(x1 + x2, y1 + y2);
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
    tuple<int, int> move;

    while (go) {
        x = rand() % (board.size - 1);
        y = rand() % (board.size - 1);
        move = make_tuple(x, y);
        go = !board.valid_move(move);
    }
    return move;
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
    int evaluation = 0;
    vector<tuple<int, int>> opts = {make_tuple(1, 0), make_tuple(0, 1), make_tuple(1, 1), make_tuple(1, -1)};

    // Determine how we're weighing the evaluation (for attack or defend)

    string color = board.get_our_color();
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
        
        vector<string> pathlist = {"."};

        array<int, 2> modifier = {1, -1};
        for (int j : modifier) {
            for (int i = 1; i <= board.connect; i++) {

                // Determine new coordinates to check for potential impact on position's value
                int y2 = y0 + y1 * i * j;
                int x2 = x0 + x1 * i * j;
                int x_ol = x2 + x1 * j;
                int y_ol = y2 + y1 * j;
                tuple<int, int> x2y2 = make_tuple(x2, y2);
                tuple<int, int> xy_ol = make_tuple(x_ol, y_ol);

                // Check if the projected position is not on the board, is already taken by the opponent,
                //  or if move would form an overline. If yes, then break. Otherwise, check to see
                //  where the move is added to the list of paths
                if((!board.cell_exists(x2y2) || board.get_cell_color(x2y2) == not_color) \
                    || (i + 1 == board.connect && board.cell_exists(xy_ol) \
                    && board.get_cell_color(xy_ol) == color)) {
                        break;
                    } else if (j > 0) { // Insert at back of list if right of position
                        pathlist.push_back(board.get_cell_color(x2y2));
                    } else if (j < 0) { // Insert at front of list if left of position
                        pathlist.insert(pathlist.begin(), board.get_cell_color(x2y2));
                    }

                // Determine the number of connections that can be formed at the given position
                int paths_num = pathlist.size() - board.connect + 1;
                int consec = 0;

                // Determine the total consecutive score for the given position
                if (paths_num > 0) {
                    for (int i = 0; i <= paths_num; i++) {
                        if (mode) {
                            consec = count(&pathlist[i], &pathlist[i+board.connect], color);
                        } else {
                            consec = count(&pathlist[i], &pathlist[i+board.connect], not_color);
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

    if (board.cell_exists(make_tuple(x, y))) {
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
    vector<tuple<int, int>> opts = {make_tuple(1, 0), make_tuple(0, 1), make_tuple(1, 1), make_tuple(1, -1)};

    int x = get<0>(initPair);
    int y = get<1>(initPair);

    for (tuple<int, int> pair : opts) {
        int x1 = get<0>(pair);
        int y1 = get<1>(pair);

        array<int, 2> modifier = {1, -1};
        for (int j : modifier) {
            for (int i = 1; i <= connect; i++){
                int x2 = x + x1 * i * j;
                int y2 = y + y1 * i * j;
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

    vector<tuple<int, int>> spots;
    vector<tuple<int, tuple<int, int>>> topList;

    // Using lambda to compare elements.
    auto cmp = [](const tuple<int, tuple<int, int>>& left, const tuple<int, tuple<int, int>>& right) {
        return get<0>(left) < get<0>(right);
    };
    priority_queue<tuple<int, tuple<int, int>>, vector<tuple<int, tuple<int, int>>>, decltype(cmp)> topQueue(cmp);

    // 
    board.print_board();

    vector<tuple<int, int>> filled_spaces = board.get_filled_spaces();

    // For each piece on the board
    for (tuple<int, int> n : filled_spaces) {

        // For each potential connect space within range
        for (tuple<int, int> m : attackArea(n, board.connect)) {

            int x = get<0>(m);
            int y = get<1>(m);

            // If the connect space is on the board, add to list of potential spots
            if (board.cell_exists(make_tuple(x, y)) && \
                find(filled_spaces.begin(), filled_spaces.end(), m) == filled_spaces.end()) {
                spots.push_back(m);
            }
        }
    }

    // Evaluate potential of each spot, and add to queue
    for (tuple<int, int> p : spots) {
        topQueue.push(make_tuple(evaluatePosition(board, p) * (-1), p));
    }

    for (int z = 0; z <= limit; z++) {
        topList.push_back(topQueue.top());
        topQueue.pop();
    }

    return topList.front();
}

tuple<int, tuple<int, int>> evaluationFunction(Board board) {
    return topMoves(board, 1);
}