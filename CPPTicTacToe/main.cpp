//
//  main.cpp
//  CPPTicTacToe
//
//  Created by Alex Chan on 5/29/23.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Player {
public:
    string name;
    char symbol;
    Player(string name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }
};

class TicTacToeGame {
public:
    Player* p1;
    Player* p2;
    vector<vector<char>> board;
    Player* current;
    Player* winner = nullptr;

    TicTacToeGame(Player* p1, Player* p2) {
        this->p1 = p1;
        this->p2 = p2;
        for (int i=0; i<3; i++) {
            board.push_back({});
            for (int j=0; j<3; j++) {
                board[i].push_back('.');
            }
        }
        current = p1;
    }
    
    void printBoard() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void swapPlayers() {
        if (current == p1) {
            current = p2;
        } else {
            current = p1;
        }
    }
    
    bool checkIfBoardFull() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[i][j] == '.') {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool checkIfWinnerDeclared() {
        // check rows
        for (int i=0; i<3; i++) {
            if (board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                winner = current;
                return true;
            }
        }
        // check columns
        for (int j=0; j<3; j++) {
            if (board[0][j] != '.' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                winner = current;
                return true;
            }
        }
        // check diagonals
        if (board[0][0] != '.' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            winner = current;
            return true;
        }
        if (board[0][2] != '.' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            winner = current;
            return true;
        }
        return false;
    }
    
    bool executePlayerMove(int tile) {
        if (tile < 1 || tile > 9) {
            return false;
        }
        int offset = tile-1;
        int i = offset / 3;
        int j = offset % 3;
        if (board[i][j] != '.') {
            return false;
        }
        board[i][j] = current->symbol;
        return true;
    }
    
    bool executeTurn() {
        bool validMove = false;
        do {
            cout << "It is now Player " << current->name << "'s turn." << endl;
            string tile;
            cin >> tile;
            validMove = executePlayerMove(stoi(tile));
            printBoard();
        } while (!validMove);
        return (checkIfBoardFull() || checkIfWinnerDeclared());
    }
    
    void playGame() {
        while (true) {
            bool gameEnded = executeTurn();
            if (gameEnded) {
                break;
            }
            swapPlayers();
        }
        if (winner) {
            cout << "Player " << winner->name << " wins!" << endl;
        } else {
            cout << "Game ends in a draw" << endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    // Initialize players
    string name1, name2;
    cout << "Enter Player 1 Name" << endl;
    cin >> name1;
    Player* p1 = new Player(name1, 'X');
    cout << "Enter Player 2 Name" << endl;
    cin >> name2;
    Player* p2 = new Player(name2, 'O');
    TicTacToeGame* game = new TicTacToeGame(p1, p2);
    game->playGame();
    return 0;
}
