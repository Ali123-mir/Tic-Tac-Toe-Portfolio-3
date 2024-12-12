#include <iostream>

#include <fstream>

#include <vector>


using namespace std;


int gamesPlayed = 0;

int playerOneWins = 0;

int playerTwoWins = 0;

int ties = 0;


void displayBoard(const vector<char>& board);

bool checkWin(const vector<char>& board, char player);

bool checkTie(const vector<char>& board);

void updateGameReport();

void resetBoard(vector<char>& board);


int main() {

    vector<char> board(9, ' '); 

    char playAgain = 'y';


    cout << "Welcome to Tic-Tac-Toe!\n";


    while (playAgain == 'y' || playAgain == 'Y') {

        resetBoard(board);

        char currentPlayer = 'X';

        bool gameOver = false;


        while (!gameOver) {

            displayBoard(board);

            int move;

            cout << "Player " << currentPlayer << ", enter your move (1-9): ";

            cin >> move;


            if (move < 1 || move > 9 || board[move - 1] != ' ') {

                cout << "Invalid move. Try again.\n";

                continue;

            }


            board[move - 1] = currentPlayer;


            if (checkWin(board, currentPlayer)) {

                displayBoard(board);

                cout << "Player " << currentPlayer << " wins!\n";

                gamesPlayed++;

                if (currentPlayer == 'X') playerOneWins++;

                else playerTwoWins++;

                gameOver = true;

            } else if (checkTie(board)) {

                displayBoard(board);

                cout << "It's a tie!\n";

                gamesPlayed++;

                ties++;

                gameOver = true;

            } else {

                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

            }

        }


        cout << "Do you want to play again? (y/n): ";

        cin >> playAgain;

    }


    updateGameReport();

    cout << "Game report saved. Thank you for playing!\n";


    return 0;

}


void displayBoard(const vector<char>& board) {

    cout << "\n";

    for (int i = 0; i < 9; i += 3) {

        cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "\n";

        if (i < 6) cout << "---|---|---\n";

    }

    cout << "\n";

}


bool checkWin(const vector<char>& board, char player) {

    const int winPatterns[8][3] = {

        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 

        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 

        {0, 4, 8}, {2, 4, 6}             

    };


    for (auto& pattern : winPatterns) {

        if (board[pattern[0]] == player && board[pattern[1]] == player && board[pattern[2]] == player) {

            return true;

        }

    }

    return false;

}


bool checkTie(const vector<char>& board) {

    for (char cell : board) {

        if (cell == ' ') return false;

    }

    return true;

}


void updateGameReport() {

    ofstream reportFile("game_report.txt");

    if (!reportFile) {

        cerr << "Error: Unable to create game report file.\n";

        return;

    }


    reportFile << "Tic-Tac-Toe Game Report\n";

    reportFile << "========================\n";

    reportFile << "Games Played: " << gamesPlayed << "\n";

    reportFile << "Player 1 Wins: " << playerOneWins << "\n";

    reportFile << "Player 2 Wins: " << playerTwoWins << "\n";

    reportFile << "Ties: " << ties << "\n";


    reportFile.close();

}


void resetBoard(vector<char>& board) {

    fill(board.begin(), board.end(), ' ');

}
