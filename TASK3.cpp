/*Build a simple console-based Tic-Tac-Toe game that
allows two players to play against each other

TASK 3
TIC-TAC-TOE GAME

Game Board: Create a 3x3 grid as the game board.
Players: Assign"X"and "O" to two players.
Display Board: Show the current state of the board.
Player Input: Prompt the current player to enter their move.
Update Board: Update the game board with the player's move.
Check for Win: Check if the current player has won.
Check for Draw: Determine if the game is a draw.
Switch Players: Alternate turns between
"X"and "O"players.
Display Result: Show the result of the game (win, draw, or ongoing).
Play Again: Ask if the players want to play another game.*/

#include <bits/stdc++.h>
using namespace std;
void gameboard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int status(char board[3][3], char player) {
    //rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) 
        return 0;
    }
    //diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return 0;
}


void BOARD(char board[3][3]) {
   int num = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '0' + num;
           num++;
        }
    }
}

int main() {
    char board[3][3];
    char Player;
    int move, turns;
    char playagain;

    do {
        // Initialize game
        Player = 'X';
        turns = 0;
        BOARD(board);

        while (turns < 9) {
            gameboard(board);
            cout<< "Player " << Player << ", enter your move (1-9): ";
            cin >> move;

           
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

        
            if (move < 1 || move > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "Invalid move. Try again.\n";
                continue;
            }

        
            board[row][col] = Player;

            
            if (status(board,Player)) {
            gameboard(board);
                cout << "Player " << Player << " wins!\n";
                break;
            }

           
            Player = (Player == 'X') ? 'O' : 'X';
            turns++;
        }

        if (turns == 9) {
            gameboard(board);
            cout << "It's a draw!\n";
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playagain;

    } while (playagain == 'y' || playagain == 'Y');

    cout << "Thank you for playing!\n";
    return 0;
}
