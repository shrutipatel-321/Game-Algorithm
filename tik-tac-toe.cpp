#include <bits/stdc++.h>
using namespace std;

struct Board
{
    char board[3][3];
    Board()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
    }

    char getCell(int x, int y)
    {
        return board[x][y];
    }
    void setCell(int x, int y, char player)
    {
        // assert(board[x][y]==' ');
        board[x][y] = player;
    }
    char check_end()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
            {
                return board[i][0];
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
            {
                return board[0][i];
            }
        }
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
        {
            return board[0][0];
        }
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
        {
            return board[0][2];
        }
        int cnt = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                    cnt++;
            }
        }
        if (cnt == 0)
        {
            return 'D';
        }
        else
        {
            return 'C';
        }
    }
    void print_board()
    {
        cout << "\n    0     1     2    \n";
        cout << "   _________________\n";
        cout << "  |     |     |     |\n";
        cout << "0 |  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << "  |     |     |     |\n";
        cout << "1 |  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << "  |     |     |     |\n";
        cout << "2 |  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
    }
};
inline char otherPlayer(char player)
{ // otherPlayer('X') ='0', otherPlayer('0') ='X'
    return player ^ 'X' ^ '0';
}
char decide_state(Board board, char player, bool printWinMove)
{
    char is_already_end = board.check_end();
    if (is_already_end != 'C')
    {
        if (is_already_end == player)
        {
            return 'W';
        }
        else if (is_already_end == 'D')
        {
            return 'D';
        }
        else
        {
            return 'L';
        }
    }
    else
    {
        // explore
        int possible = 0;
        int lossing_moves = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            { // choices
                if (board.getCell(i, j) == ' ')
                { // check
                    possible++;
                    board.setCell(i, j, player);
                    char new_result = decide_state(board, otherPlayer(player), 0);
                    board.setCell(i, j, ' ');
                    if (new_result == 'W')
                    {
                        lossing_moves++;
                    }
                    else if (new_result == 'L')
                    {
                        if (printWinMove)cout << i << " " << j << '\n';
                        return 'W';
                    }
                }
            }
        }
        if (possible == lossing_moves)
        {
            return 'L';
        }
        else
        {
            return 'D';
        }
    }
}
Board createInput()
{
    string s;
    Board board;
    cout << "Enter Board Config:\n";

    for (int i = 0; i < 3; i++)
    {
        getline(cin, s);
        board.setCell(i, 0, s[0]);
        board.setCell(i, 1, s[1]);
        board.setCell(i, 2, s[2]);
    }
    return board;
}
int main()
{
    Board temp = createInput();
    cout << "Input current move(X,0):";
    char ch;
    cin >> ch;
    temp.print_board();
    cout << decide_state(temp, ch, 1);
}