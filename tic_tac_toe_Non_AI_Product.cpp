#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> board(3, vector<int>(3, 2)); // 2 represents a blank space
int turn = 1;
pair<int, int> winningMove = { -1, -1 };


pair<int, int> possWin(int player)
{
    pair<int, int> winningMove = {0, 0};

    for (int i = 0; i < 3; i++)
    {
        int product = board[i][0] * board[i][1] * board[i][2];
        if (product == player * player * 2)
        {
            if (board[i][0] == 2)
                winningMove = {i, 0};
            else if (board[i][1] == 2)
                winningMove = {i, 1};
            else if (board[i][2] == 2)
                winningMove = {i, 2};
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int product = board[0][i] * board[1][i] * board[2][i];
        if (product == player * player * 2)
        {
            if (board[0][i] == 2)
                winningMove = {0, i};
            else if (board[1][i] == 2)
                winningMove = {1, i};
            else if (board[2][i] == 2)
                winningMove = {2, i};
        }
    }

      if ((board[0][0] * board[1][1] * board[2][2] == player * player * 2) && (board[0][0] == 2 || board[1][1] == 2 || board[2][2] == 2))
        winningMove = {0, 0};
    else if ((board[0][2] * board[1][1] * board[2][0] == player * player * 2) && (board[0][2] == 2 || board[1][1] == 2 || board[2][0] == 2))
        winningMove = {0, 2};

    return winningMove;
}

void go(int row, int col)
{
    if (turn % 2 == 1)
        board[row][col] = 3; // 3 represents player X's move
    else
        board[row][col] = 5; // 5 represents player O's move

    turn++;
}

void makeMove()
{
    int move = 0;

    if (board[1][1] == 2)
        move = 5;
    else
    {
        for (int i = 0; i < 3; i += 2)
        {
            for (int j = 0; j < 3; j += 2)
            {
                if (board[i][j] == 2)
                {
                    move = i * 3 + j + 1;
                    break;
                }
            }
        }
    }

    if (move == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == 2)
                {
                    move = i * 3 + j + 1;
                    break;
                }
            }
        }
    }

    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    go(row, col);
}

void printBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char symbol;
            if (board[i][j] == 2)
                symbol = ' '; // Blank space
            else if (board[i][j] == 3)
                symbol = 'X'; // Player X's move
            else
                symbol = 'O'; // Player O's move

            cout << symbol;
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "---------" << endl;
    }
    cout << endl;
}


int main()
{
    while (turn <= 9)
    {
        cout << "Turn: " << turn << endl;
        printBoard();

        if (turn % 2 == 1)
        {
            cout << "Your turn (Enter row and column): ";
            int row, col;
            cin >> row >> col;

            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != 2)
            {
                cout << "Invalid move. Try again." << endl;
                continue;
            }
            go(row, col);
        }
        else
        {
            cout << "Player O's turn." << endl;
            makeMove();
        }

        pair<int, int> winner = possWin((turn % 2 == 1) ? 3 : 5);
        if (winner != make_pair(0, 0))
        {
            cout << endl;
           
            if (turn % 2 == 1)
                board[winner.first][winner.second] = 3 ;
            else
                board[winner.first][winner.second] = 5 ; 

            printBoard();

            if (turn % 2 == 1)
                cout<<"Player X wins!"<<endl;
            else
                 cout<<"Player O wins!"<<endl; ;
            break;
        }
    }

    if (turn > 9)
    {
        cout << "The game ended in a draw!" << endl;
    }

    return 0;
}
