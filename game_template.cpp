#include <bits/stdc++.h>

using namespace std;

// FILLED-IN C++ TEMPLATE FOR SOLVING GAME THEORY PROBLEMS
// THIS TEMPLATE IS FILLED IN WITH THE METHOD TO SOLVE 2023 MATHCAMP QQ 5c
// THE METHOD IS A VERY RUDIMENTARY GAME TREE FILLING ALGORITHM WITH DP

int N = 5;

struct state{
    int current_player;
    int player1_pos;
    int player2_pos;
    vector<pair<int, int>> impossible_moves;
};

vector<int> generate_moves (state game){
    vector<int> possible_moves;
    for (int i=1; i<=N; i++){
        if (i!=game.player1_pos && i!=game.player2_pos){
            if (game.current_player == 1){
                bool possible = true;
                pair<int, int> pos = make_pair(i, game.player2_pos);
                for (auto&p: game.impossible_moves){
                    if (p==pos){
                        possible = false;
                    }
                }
                if (possible){
                    possible_moves.push_back(i);
                }
            }else{
                bool possible = true;
                pair<int, int> pos = make_pair(game.player1_pos, i);
                for (auto&p: game.impossible_moves){
                    if (p==pos){
                        possible = false;
                    }
                }
                if (possible){
                    possible_moves.push_back(i);
                }
            }
        }
    }
    return possible_moves;
}

bool winning(state game){
    vector<int> moves = generate_moves(game);
    for (auto&move: moves){
        if (game.current_player == 1){
            state new_game;
            new_game.current_player = 2;
            new_game.player1_pos = move;
            new_game.player2_pos = game.player2_pos;
            new_game.impossible_moves = game.impossible_moves;
            new_game.impossible_moves.push_back(make_pair(game.player1_pos, game.player2_pos));
            if (!winning(new_game)){
                return true;
            }
        }else{
            state new_game;
            new_game.current_player = 1;
            new_game.player1_pos = game.player1_pos;
            new_game.player2_pos = move;
            new_game.impossible_moves = game.impossible_moves;
            new_game.impossible_moves.push_back(make_pair(game.player1_pos, game.player2_pos));
            if (!winning(new_game)){
                return true;
            }
        }
    }
    return false;
}

int main(){
    state game;
    game.current_player = 1;
    game.player1_pos = 1;
    game.player2_pos = N;
    game.impossible_moves = {};
    cout<<winning(game)<<endl; // 0 -> Player 2 Wins, 1 -> Player 1 Wins
}
