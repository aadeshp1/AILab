#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const vector<vector<int>> MAGIC_SQUARE = {
    {2, 9, 4},
    {7, 5, 3},
    {6, 1, 8}};

vector<vector<char>> board = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}};

char humanPlayer = 'X';
char computerPlayer = 'O';
int moves = 0;

void displayBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
            {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < 2)
        {
            cout << "---------" << endl;
        }
    }
    cout << endl;
}

bool isValidMove(int row, int col)
{
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

bool checkWin(char player)
{
    vector<int> playerMoves(9, 0);
    int index = 0;

    // Get the positions of the current player's moves
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == player)
            {
                playerMoves[index++] = MAGIC_SQUARE[i][j];
            }
        }
    }

    // Check if the sum of any row, column, or diagonal is 15 (magic number)
    for (int i = 0; i < 3; i++)
    {
        if (playerMoves[i] + playerMoves[i + 3] + playerMoves[i + 6] == 15)
        {
            return true;
        }
        if (playerMoves[i * 3] + playerMoves[i * 3 + 1] + playerMoves[i * 3 + 2] == 15)
        {
            return true;
        }
    }

    if (playerMoves[0] + playerMoves[4] + playerMoves[8] == 15)
    {
        return true;
    }
    return playerMoves[2] + playerMoves[4] + playerMoves[6] == 15;
}

bool isGameOver()
{
    return moves >= 9 || checkWin(humanPlayer) || checkWin(computerPlayer);
}

void playerMove()
{
    int row, col;
    cout << "Human Player " << humanPlayer << ", enter your move (row,column): ";
    cin >> row >> col;

    if (!isValidMove(row, col))
    {
        cout << "Invalid move. Please enter valid row and column." << endl;
        return;
    }

    board[row][col] = humanPlayer;
    moves++;
}

void computerMove()
{
    cout << "Computer Player " << computerPlayer << " is making a move..." << endl;

    srand(time(0));
    int row, col;
    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isValidMove(row, col));

    board[row][col] = computerPlayer;
    moves++;
}

void playGame()
{
    displayBoard();

    while (!isGameOver())
    {
        playerMove();
        displayBoard();
        if (checkWin(humanPlayer))
        {
            cout << "Human Player " << humanPlayer << " wins!" << endl;
            break;
        }

        if (moves == 9)
        {
            cout << "It's a draw!" << endl;
            break;
        }

        computerMove();
        displayBoard();
        if (checkWin(computerPlayer))
        {
            cout << "Computer Player " << computerPlayer << " wins!" << endl;
            break;
        }
    }
}

int main()
{
    playGame();
    return 0;
}
