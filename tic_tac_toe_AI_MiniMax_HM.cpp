#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 3;

void printBoard(const vector<vector<char>> &board)
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

bool isWinner(const vector<vector<char>> &board, char player)
{

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }

    return false;
}

bool isBoardFull(const vector<vector<char>> &board)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int evaluateBoard(const vector<vector<char>> &board)
{
    if (isWinner(board, 'X'))
        return 10;
    else if (isWinner(board, 'O'))
        return -10;
    else
        return 0;
}

int minimax(vector<vector<char>> &board, int depth, bool isMaximizing)
{
    int score = evaluateBoard(board);

    if (score != 0)
        return score;

    if (isBoardFull(board))
        return 0;

    if (isMaximizing)
    {
        int best = -1000;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    best = max(best, minimax(board, depth + 1, !isMaximizing));
                    board[i][j] = ' ';
                }
            }
        }
        return best - depth;
    }
    else
    {
        int best = 1000;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    best = min(best, minimax(board, depth + 1, !isMaximizing));
                    board[i][j] = ' ';
                }
            }
        }
        return best + depth;
    }
}

pair<int, int> findBestMove(vector<vector<char>> &board)
{
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal)
                {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main()
{
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));

    int currentPlayer = 0;

    while (true)
    {
        cout << "Current Board:" << endl;
        printBoard(board);

        if (currentPlayer == 0)
        {
            cout << "Player X's turn." << endl;

            int row, col;
            cout << "Enter row and column (0-2) separated by space: ";
            cin >> row >> col;

            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ')
            {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            board[row][col] = 'X';
        }
        else
        {
            cout << "Player O's turn." << endl;

            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = 'O';

            cout << "Computer plays at " << bestMove.first << ", " << bestMove.second << endl;
        }

        if (isWinner(board, 'X'))
        {
            cout << "Player X wins!" << endl;
            break;
        }
        else if (isWinner(board, 'O'))
        {
            cout << "Player O wins!" << endl;
            break;
        }
        else if (isBoardFull(board))
        {
            cout << "It's a tie!" << endl;
            break;
        }

        currentPlayer = 1 - currentPlayer;
    }

    return 0;
}