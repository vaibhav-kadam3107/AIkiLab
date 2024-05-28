#include <iostream>
using namespace std;
#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
int win[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {2, 4, 6}, {0, 4, 8}};
int turn = 0;

void initialise() {
    for (int i = 0; i < 9; i++) {
            board[i] = 2;
    }
}

void showInstructions() {
    cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 7 | 8 | 9 \n\n";
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won\n";
    else
        cout << "HUMAN has won\n";
}
void printBoard()
{
    cout << "-------" << endl;
    for (int i = 0; i < 9; i += 3)
    {
        cout << "|";
        for (int j = i; j < i + 3; ++j)
        {
            if (board[j] == 2)
            {
                cout << " "
                     << "|";
            }
            else if (board[j] == 3)
            {
                cout << "X"
                     << "|";
            }
            else
            {
                cout << "O"
                     << "|";
            }
        }
        cout << endl;
        for (int j = 0; j < 3; ++j)
        {
            cout << "--";
        }
        cout << "-";
        cout << endl;
    }
}

int posswin(int x)
{
    for (int i = 0; i < 8; i++)
    {
        int c = 0, mt = -01;
        for (int j = 0; j < 3; j++)
        {
            if (board[win[i][j]] == x)
                c++;
            else if (board[win[i][j]] == 2)
                mt = win[i][j];
            else
                c--;
        }
        if (c == 2)
            return mt;
    }
    return -1;
}

int winner()
{
    int x;
    if (turn % 2 == 0)
        x = 3;
    else
        x = 5;

    for (int i = 0; i < 8; i++)
    {
        int c = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[win[i][j]] == x)
                c++;
        }
        if (c == 3)
            return 1;
    }
    return 0;
}

int make2()
{
    if (board[4] == 2)
        return 4;
    else if (board[1] == 2)
        return 1;
    else if (board[3] == 2)
        return 3;
    else if (board[5] == 2)
        return 5;
    else if (board[7] == 2)
        return 7;
}

void go(int n)
{
    if (turn % 2 == 0)
    {
        board[n] = 5;
    }
    else
    {
        board[n] = 3;
    }

    turn++;
}

void nextmove()
{
    int x;
    int self;
    if (turn % 2 == 0)
    {
        self = 5;
        x = 3;
    }
    else
    {
        self = 3;
        x = 5;
    }

    if (posswin(self) != -1)
    {
        go(posswin(self));
    }
    else if (posswin(x) != -1)
    {
        go(posswin(x));
    }
    else
    {
        go(make2());
    }
}

void playTicTacToe(int whoseTurn)
{
    turn = 1;
    initialise();
    showInstructions();
    while (turn<=9)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            if (turn == 1)
                go(0);
            else if (turn == 2)
                (board[4] == 2) ? go(4) : go(0);
            else if (turn == 3)
                (board[8] == 2) ? go(8) : go(2);
            else
            {
                nextmove();
            }
            printBoard();
            if (winner())
            {
                declareWinner(whoseTurn);
                break;
            }
            whoseTurn = HUMAN;
        }
        else
        {
            cout << "You can insert in the following positions : ";
            for (int i = 0; i < 9; i++)
                if (board[i] == 2)
                    cout << i + 1 << " ";
            cout << endl
                 << endl;
            cout << "Enter the position = ";
            cin >> n;
            n--;

            if (board[n] == 2 && n < 9 && n >= 0)
            {
                go(n);
                cout << endl;
                printBoard();
                if (winner())
                {
                    declareWinner(whoseTurn);
                    break;
                }
                whoseTurn = COMPUTER;
            }
            else if (board[n] != 2 && n < 9 && n >= 0)
            {
                cout << "\nPosition is occupied, select any one place from the available places\n\n";
            }
            else if (n < 0 || n > 8)
            {
                cout << "Invalid position\n";
            }
        }
    }
    if (winner() == 0)
    {
        cout << "\nIts a DRAW\n";
    }
}

int main()
{
    cout << "\t\t\t Tic-Tac-Toe\n\n";
    char cont = 'y';
    do
    {
        char choice;
        cout << "Do you want to start first?(y/n) : ";
        cin >> choice;

        if (choice == 'n')
            playTicTacToe(COMPUTER);
        else if (choice == 'y')
            playTicTacToe(HUMAN);
        else
            cout << "Invalid choice\n";

        cout << "\nDo you want to quit(y/n) : ";
        cin >> cont;
    } while (cont == 'n');
    return 0;
}