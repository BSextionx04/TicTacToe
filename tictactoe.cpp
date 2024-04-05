#include <iostream>

using namespace std;
bool checkPlayerChoice(int playerChoice) { //if 1 or 2 returns true, false else
    if (playerChoice == 1 || playerChoice == 2)
    {
        return true;
    }
    else {
        return false;
    }
}
bool checkDraw(bool gameOver, int turns) {
    if (!gameOver && turns == 9)
    {
        return true;
    }
    else {
        return false;
    }
}
bool checkWin(char board[3][3], char player) { // draw if after 9 tries nobody has won
    if (board[0][0] == player && board[0][1] == player && board[0][2] == player || //checks possible horizantal wins
        board[1][0] == player && board[1][1] == player && board[1][2] == player ||
        board[2][0] == player && board[2][1] == player && board[2][2] == player ||
        board[0][0] == player && board[1][0] == player && board[2][0] == player || //checks possible vertical wins
        board[0][1] == player && board[1][1] == player && board[2][1] == player ||
        board[0][2] == player && board[1][2] == player && board[2][2] == player ||
        board[0][0] == player && board[1][1] == player && board[2][2] == player || //checks possible diagonal wins
        board[0][2] == player && board[1][1] == player && board[2][0] == player
    ) 
    {
        return true;
    }
    else {
        return false;
    }
}

void printBoard(char board[3][3]) { //prints board after each turn
    cout << "-------------\n"; 
    for (int i = 0; i < 3; i++) { 
        cout << "| "; 
        for (int j = 0; j < 3; j++) { 
            cout << board[i][j] << " | "; 
        } 
        cout << "\n-------------\n"; 
    }
}

bool checkTurn(int row, int col, char board[3][3]) {
    if ((row == 1 || row == 2 || row == 3) && (col == 1 || col == 2 || col == 3)) //runs if row & column (1-3)
    {
        if (board[row - 1][col - 1] == '-') //check if space is full
        {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void cputurn(int& row, int& col, char board[3][3]) {
    while (true)
    {
        srand(time(NULL));
        row = (rand() % 3) + 1;
        col = (rand() % 3) + 1;

        if (checkTurn(row, col, board)) //checks to make sure cpu turn is valid
        {
            break;
        }
    }
}
void playervcpu(bool& gameOver) { //finished...add logic for cpu
    char board[3][3];
    int row, col;
    char player;
    int turns = 0;

    for (int i = 0; i < 3; i++) //sets all spaces on board to default '-'
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }
    
    cout << "You will be using 'x' on the board, the cpu will be using 'o'" << endl;
    printBoard(board);
    while (!gameOver)
    {

        cout << "\nIt is the player's turn what row (1-3) and column (1-3) would you like to choose: ";
        cin >> row >> col;
        if (checkTurn(row, col, board)) //cpu only goes is turn is valid
        {
            board[row - 1][col - 1] = 'x';
            printBoard(board);
            player = 'x';
            if (checkWin(board, player)) //true = game over
            {
                cout << "Congratulations you won!" << endl;
                gameOver = true;
                break;
            }
            ++turns;
            if(checkDraw(gameOver, turns)) {
                cout << "The game has ended in a draw!" << endl;
                gameOver = true;
                break;
            }
            cout << "\nIt is the CPU's turn" << endl;
            cputurn(row, col, board); //cpu should have valid turn after running through loop
            board[row - 1][col - 1] = 'o';
            printBoard(board);
            player = 'o';
            if (checkWin(board, player))
            {
                cout << "The CPU has won" << endl;
                gameOver = true;
                break;
            }
            ++turns;
            if(checkDraw(gameOver, turns)) {
                cout << "The game has ended in a draw!" << endl;
                gameOver = true;
                break;
            }
        }
        else {
            cout << "Row: " << row << " and column: " << col << " is not a valid turn. Try again." << endl;
        }
    }
    
}

void playervplayer(bool gameOver) {
    char board[3][3];
    int row, col;
    char player;
    char marker;
    int turns = 0;
    int i = 0;

    for (int i = 0; i < 3; i++) //sets all spaces on board to default '-'
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }

    cout << "\nPlayer 1 will be using 'x' on the board, Player 2 will be using 'o'" << endl;
    printBoard(board);

    while (!gameOver)
    {
        if (i % 2 == 0)
        {
            player = '1';
            marker = 'x';
        }
        else {
            player = '2';
            marker = 'o';
        }
        ++i;
        cout << "\nIt is Player " << player << "'s turn what row (1-3) and column (1-3) would you like to choose: ";
        cin >> row >> col;
        if (checkTurn(row, col, board))
        {
            board[row - 1][col - 1] = marker;
            printBoard(board);
            if (checkWin(board, marker))
            {
                cout << "Congratulations Player " << player << " has won!" << endl;
                gameOver = true;
                break;
            }
            ++turns;
            if(checkDraw(gameOver, turns)) {
                cout << "The game has ended in a draw!" << endl;
                gameOver = true;
                break;
            }
        }   
        else {
            cout << "Row: " << row << " and column: " << col << " is not a valid turn. Try again." << endl;
        }
    }
}

int main() {
    int playerChoice;
    bool gameOver = false;
    /*2 playing modes - player v cpu (randomized cpu entry) & player v player
    2d array
    */
   cout << "Welcome to Tic Tac Toe!" << endl;
   cout << "\n[1] Player v CPU\n[2] Player v Player" << endl;
   cout << "\nSelect which mode you would like to play: ";
   while (!gameOver)
   {
    cin >> playerChoice;
    if (checkPlayerChoice(playerChoice)) //only runs if playerChoice is 1 or 2
    {
        switch (playerChoice)
        {
        case 1: //playervCPU
            playervcpu(gameOver);
            break;
        case 2: //playervplayer
            playervplayer(gameOver);
            break;
        }
    }
    else {
        cout << playerChoice << " is not an option. Please try again.\n" << endl;
        cout << "[1] Player v CPU\n[2] Player v Player" << endl;
        cout << "\nSelect which mode you would like to play: ";
    }
    break;
   }
}