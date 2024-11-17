#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> play_board(10, 2); 
int human, AI; 
map<int, char> mapping = {{2, '-'}, {3, 'X'}, {5, 'O'}}; 
bool humanTurn;
int TURN=1;
void DisplayBoard()
{
    for (int i = 1; i < 10; i++)
    {
        cout << mapping[play_board[i]] << "\t"; 
        if (i % 3 == 0)
        {
            cout << endl;
        }
    }
}

int posswin(int p)
{
    int rows_product, cols_product, diagonal_product, product = p * p * 2;
    for (int i = 1; i <= 7; i += 3)
    {
        rows_product = play_board[i] * play_board[i + 1] * play_board[i + 2];
        if (rows_product == product)
        {
            if (play_board[i] == 2) return i;
            if (play_board[i + 1] == 2) return i + 1;
            if (play_board[i + 2] == 2) return i + 2;
        }
    }

    for (int i = 1; i <= 3; ++i)
    {
        cols_product = play_board[i] * play_board[i + 3] * play_board[i + 6];
        if (cols_product == product)
        {
            if (play_board[i] == 2) return i;
            if (play_board[i + 3] == 2) return i + 3;
            if (play_board[i + 6] == 2) return i + 6;
        }
    }
    diagonal_product = play_board[1] * play_board[5] * play_board[9];
    if (diagonal_product == product)
    {
        if (play_board[1] == 2) return 1;
        if (play_board[5] == 2) return 5;
        if (play_board[9] == 2) return 9;
    }

    diagonal_product = play_board[3] * play_board[5] * play_board[7];
    if (diagonal_product == product)
    {
        if (play_board[3] == 2) return 3;
        if (play_board[5] == 2) return 5;
        if (play_board[7] == 2) return 7;
    }

    return 0; 
}

int make2()
{
    vector<int> moves = {5, 2, 4, 6, 8};
    for (int i : moves)
    {
        if (play_board[i] == 2)
            return i;
    }
    return 0;
}

void Go(int n)
{
     if (n < 1 || n > 9 || play_board[n] != 2)
    {
        cout << "Invalid move attempt: " << n << endl;
        return;
    }
    if (!humanTurn)
        play_board[n] = AI;
    else
        play_board[n] = human;
    humanTurn = !humanTurn; 
}

void AI_Moves()
{
    int move;
    if (TURN == 1)
    {
        Go(1);
    } 
    else if (TURN == 2)
    {
        if (play_board[5] == 2)
            Go(5);
        else
            Go(1);
    }
    else if (TURN == 3)
    {
        if (play_board[9] == 2)
            Go(9);
        else
            Go(3);
    }
    else if (TURN == 4)               //try: 2
    {
        int blockMove = posswin(human);
        if (blockMove != 0)
        {
            Go(blockMove);
        }
        else
        {
            if(play_board[2]==human && play_board[6]==human){   //small
                if(play_board[1]==2){
                    Go(1);
                }
                else Go(9);
            }
            else if(play_board[6]==human && play_board[8]==human){
                if(play_board[3]==2){
                    Go(3);
                }
                else Go(7);
            }
            else if(play_board[4]==human && play_board[8]==human){
                if(play_board[1]==2){
                    Go(1);
                }
                else Go(9);
            }
            else if(play_board[2]==human && play_board[4]==human){
                if(play_board[3]==2){
                    Go(3);
                }
                else Go(7);
            }
            else if(play_board[1]==human && play_board[8]==human){   //big 
                Go(7);
            }
            else if(play_board[3]==human && play_board[8]==human){
                Go(9);
            }
            else if(play_board[2]==human && play_board[9]==human){
                Go(3);
            }
            else if(play_board[2]==human && play_board[7]==human){
                Go(1);
            }
            else if(play_board[1]==human && play_board[9]==human){   // when user is at extreme corners.
                if(play_board[2]==2){
                    Go(2);
                }
                else Go(8);
            }
            else if(play_board[3]==human && play_board[9]==human){
                if(play_board[2]==2){
                    Go(2);
                }
                else Go(8);
            }
            else {
                for (int i = 1; i <= 9; i++)
                {
                    if (i != make2() && play_board[i] == 2)
                    {
                        Go(i);
                        break;
                    }
                }
            }
        }
    }
    else if (TURN == 5)
    {
        int winMove = posswin(AI);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = posswin(human);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else if (play_board[7] == 2)
            {
                Go(7);
            }
            else
            {
                Go(3);
            }
        }
    }
    else if (TURN == 6)
    {
        int winMove = posswin(AI);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = posswin(human);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else
            {
                Go(make2());
            }
        }
    }
    else
    {
        int winMove = posswin(AI);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = posswin(human);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else
            {
                for (int i = 1; i <= 9; i++)
                {
                    if (play_board[i] == 2)
                    {
                        Go(i);
                    }
                }
            }
        }
    }
}

bool is_playboard_full()
{
    for (int i = 1; i < play_board.size(); i++)
        if (play_board[i] == 2) return false;
    return true;
}

bool check_winner(int symbol)
{
    vector<vector<int>> winningCombos = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };

    for (const auto& combo : winningCombos)
        if (play_board[combo[0]] == symbol && play_board[combo[1]] == symbol && play_board[combo[2]] == symbol)
            return true;
    
    return false;
}

int main()
{
    cout << "Welcome to the game TIC-TAC-TOE" << endl;
    cout << "Hello player! Would you like to have the first move?" << endl;
    cout << "1) Yes, I do\n2) No, Thanks" << endl;
    
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        human = 3; // Human is 'X'
        AI = 5;    // AI is 'O'
        humanTurn = true;
    }
    else
    {
        human = 5; // Human is 'O'
        AI = 3;    // AI is 'X'
        humanTurn = false;
    }
    
    while (true)
    {
        DisplayBoard(); 

        if (humanTurn)
        {
            cout << "Your move (1-9): ";
            int move;
            cin >> move;
            TURN++;
            if (play_board[move] == 2) 
            {
                Go(move);
            }
            else
            {
                cout << "Invalid move! Try again." << endl;
                continue;
            }
            
        }
        else 
        {
            cout << "============COMPUTER'S TURN ==========================" << endl;
            TURN++;
            AI_Moves();
            
        }
        
        if (check_winner(human))
        {
            DisplayBoard();
            cout << "Congratulations! You win!" << endl;
            break;
        }
        
        if (check_winner(AI))
        {
            DisplayBoard();
            cout << "AI wins! Better luck next time." << endl;
            break;
        }

        // Check for a draw
        if (is_playboard_full())
        {
            DisplayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}