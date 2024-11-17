
#include <iostream>
#include <vector>
#include <map>
#include <limits>
using namespace std;

vector<int> play_board(10, 2);
int human, AI;
map<int, char> mapping = {{2, '-'}, {3, 'X'}, {5, 'O'}};
bool humanTurn;
int DEPTH = 4;
int count_rec = 0;

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

bool check_winner(int symbol)
{
    vector<vector<int>> winningCombos = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

    for (const auto &combo : winningCombos)
        if (play_board[combo[0]] == symbol && play_board[combo[1]] == symbol && play_board[combo[2]] == symbol)
            return true;

    return false;
}

void Go(int n)
{
    if (n < 1 || n > 9 || play_board[n] != 2)
    {
        cout << "Invalid move attempt: " << n << endl;
        return;
    }
    play_board[n] = humanTurn ? human : AI;
    humanTurn = !humanTurn;
}

vector<int> Generate_moves()
{
    vector<int> empty_positions;
    for (int i = 1; i < play_board.size(); i++)
    {
        if (play_board[i] == 2)
        {
            empty_positions.push_back(i);
        }
    }
    return empty_positions;
}

int posswin(int p)
{
    int product = p * p * 2;
    for (int i = 1; i <= 7; i += 3)
    {
        if (play_board[i] * play_board[i + 1] * play_board[i + 2] == product)
        {
            if (play_board[i] == 2)
                return i;
            if (play_board[i + 1] == 2)
                return i + 1;
            if (play_board[i + 2] == 2)
                return i + 2;
        }
    }

    for (int i = 1; i <= 3; ++i)
    {
        if (play_board[i] * play_board[i + 3] * play_board[i + 6] == product)
        {
            if (play_board[i] == 2)
                return i;
            if (play_board[i + 3] == 2)
                return i + 3;
            if (play_board[i + 6] == 2)
                return i + 6;
        }
    }

    if (play_board[1] * play_board[5] * play_board[9] == product)
    {
        if (play_board[1] == 2)
            return 1;
        if (play_board[5] == 2)
            return 5;
        if (play_board[9] == 2)
            return 9;
    }

    if (play_board[3] * play_board[5] * play_board[7] == product)
    {
        if (play_board[3] == 2)
            return 3;
        if (play_board[5] == 2)
            return 5;
        if (play_board[7] == 2)
            return 7;
    }

    return 0;
}

int static_rating()
{
    int score = 0;

    if (check_winner(AI))
    {
        score += 100;
    }
    else if (check_winner(human))
    {
        score -= 100;
    }
    if (posswin(AI) != 0)
    {
        score += 50;
    }
    if (posswin(human) != 0)
    {
        score -= 50;
    }
    if (play_board[5] == AI)
    {
        score += 25;
    }
    else if (play_board[5] == human)
    {
        score -= 25;
    }
    for (int corner : {1, 3, 7, 9})
    {
        if (play_board[corner] == AI)
        {
            score += 20;
        }
        else if (play_board[corner] == human)
        {
            score -= 20;
        }
    }
    for (int side : {2, 4, 6, 8})
    {
        if (play_board[side] == AI)
        {
            score += 10;
        }
        else if (play_board[side] == human)
        {
            score -= 10;
        }
    }
    return score;
}

int minimax(int depth, bool isMaximizing, int pass_score, int best_score)
{
    count_rec++;
    if (check_winner(AI))
        return 100 - depth;
    if (check_winner(human))
        return -100 + depth;
    if (Generate_moves().empty())
        return 0;
    if (depth >= DEPTH)
    {
        return static_rating();
    }
int bestScore = numeric_limits<int>::min();
    // int bestMoveScore = numeric_limits<int>::min();
    for (int move : Generate_moves())
    {
        
        // play_board[move] = isMaximizing ? AI : human;
        play_board[move] = (depth % 2 == 0) ? AI : human;
        int score = -minimax(depth + 1, !isMaximizing, -best_score, -pass_score);
        play_board[move] = 2;
        
        bestScore = max(bestScore, score);
        pass_score = max(pass_score, score);
        if (best_score <= pass_score)
        {
            break;
        }
        best_score=best_score;
    }
    
    return best_score;
    // return pass_score;
}

void AI_Moves()
{
    int bestScore = numeric_limits<int>::min();
    int bestMove = -1;

    for (int move : Generate_moves())
    {
        play_board[move] = AI;
        int score = minimax(0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
        play_board[move] = 2;

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
        cout << "Evaluating move " << move << ", score: " << score << endl;
        // cout << "score_returned : " << bestScore << endl;
    }
    if (bestMove != -1)
    {
        Go(bestMove);
        cout << "AI chooses move: " << bestMove << " with score: " << bestScore << endl;
    }
}

bool is_playboard_full()
{
    return Generate_moves().empty();
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
            int move;
            do
            {
                cout << "Your move (1-9): ";
                cin >> move;
                if (cin.fail() || move < 1 || move > 9 || play_board[move] != 2)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid move! Try again." << endl;
                }
            } while (move < 1 || move > 9 || play_board[move] != 2);

            Go(move);
        }
        else
        {
            cout << "============COMPUTER'S TURN ==========================" << endl;
            AI_Moves();
        }

        if (check_winner(human))
        {
            DisplayBoard();
            cout << "CONGRATULATIONS! YOU WIN!" << endl;
            break;
        }
        else if (check_winner(AI))
        {
            DisplayBoard();
            cout << "SORRY! YOU LOSE!" << endl;
            break;
        }
        else if (is_playboard_full())
        {
            DisplayBoard();
            cout << "IT'S A DRAW!" << endl;
            break;
        }
    }
    cout << "Total number of Recursions: " << count_rec;
    return 0;
}