#include <stdio.h>
#include <ctype.h>

char board[5][5] = {{' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '}};

char boardBack[5][5] = {{' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '}};

int column, row;
int turn = 1;
int start = 1;
char player = '1';

void displayBoard();
void playMove(int row, int column, char player);
void checkStatus();

void selectChess();
void moveMove(int row, int column, int rowE, int columnE);
void eatAgentQ(int row, int column, int rowE, int columnE);
void displayBoardBack();
void moveMoveE(int row, int column, int movement);
void checkGoalChess();

int main(void)
{

    board[0][3] = 'J';
    board[0][1] = 'Q';
    board[0][2] = 'K';

    board[4][1] = 'j';
    board[4][2] = 'q';
    board[4][3] = 'k';

    boardBack[0][1] = '1';
    boardBack[0][3] = '1';
    boardBack[0][2] = '1';

    boardBack[4][1] = '2';
    boardBack[4][2] = '2';
    boardBack[4][3] = '2';

    while (start == 1)
    {
        checkStatus();
        checkGoalChess();
        // displayBoardBack();
        displayBoard();
        printf("Player %c, select agent\n", player);

        selectChess();

        // printf(checkStatus());
        if (player == '2')
            player = '1';
        else
            player = '2';
        checkStatus();
    }
}

void displayBoard()
{
    printf("\n    1   2   3   4   5\n");
    printf("  +---+---+---+---+---+\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d |", i + 1);
        for (int j = 0; j < 5; j++)
        {
            printf(" %c |", board[i][j]);
        }
        printf("\n  +---+---+---+---+---+\n");
    }
}

void displayBoardBack()
{
    printf("\n    1   2   3   4   5\n");
    printf("  +---+---+---+---+---+\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d |", i + 1);
        for (int j = 0; j < 5; j++)
        {
            printf(" %c |", boardBack[i][j]);
        }
        printf("\n  +---+---+---+---+---+\n");
    }
}

void playMove(int row, int column, char player)
{

    int movement = 0;
    int space = 0;

    // if (boardBack[row][column] == player) {

    if (boardBack[row][column] == 'e' || boardBack[row][column] == 'E')
    {
        printf("\n1)Vertical\n2)Horizontal\nSelect your movement :");
        scanf("%d", &movement);
        moveMoveE(row, column, movement);
    }
    else if (boardBack[row][column] == 'g' || boardBack[row][column] == 'G')
    {
        printf("\n1)Up\n2)Left\n3)Right\n4)Down\nSelect your movement :");
        scanf("%d", &movement);
        printf("\n1)1 channel\n2)2 channel\nSelect your movement :");
        scanf("%d", &space);
        switch (movement)
        {
        case 1:
            moveMove(row, column, row - space, column);
            break;

        case 2:
            moveMove(row, column, row, column - space);
            break;

        case 3:
            moveMove(row, column, row, column + space);
            break;

        case 4:
            moveMove(row, column, row + space, column);
            break;
        }
    }
    else
    {
        printf("\n1)Up\n2)Left\n3)Right\n4)Down\nSelect your movement :");
        scanf("%d", &movement);
        switch (movement)
        {
        case 1:
            moveMove(row, column, row - 1, column);
            break;

        case 2:
            moveMove(row, column, row, column - 1);
            break;

        case 3:
            moveMove(row, column, row, column + 1);
            break;

        case 4:
            moveMove(row, column, row + 1, column);
            break;
        }
    }
}

void selectChess()
{
    printf("1)J\n2)Q\n3)K\nSelect your agent : ");
    int agent;
    char chess;
    scanf("%d", &agent);

    switch (agent)
    {
    case 1:
        chess = 'J';
        break;
    case 2:
        chess = 'Q';
        break;
    case 3:
        chess = 'K';
        break;
    default:
        printf("Please select again !!!\n");
        return;
    }
    char chesslower = tolower(chess);
    int found = 0;
    if (player == '1')
    {
        printf("Player 1\n");
        for (int i = 0; i < 5 && !found; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (boardBack[i][j] != ' ' && board[i][j] == chess)
                {
                    playMove(i, j, player);
                    found = 1; // Mark as found
                    break;     // Exit inner loop
                }
            }
        }
    }
    else if (player == '2')
    {
        printf("Player 2\n");
        for (int i = 0; i < 5 && !found; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (boardBack[i][j] != ' ' && board[i][j] == chesslower)
                {
                    playMove(i, j, player);
                    found = 1; // Mark as found
                    break;     // Exit inner loop
                }
            }
        }
    }
}

void checkStatus()
{
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (boardBack[i][j] == '1' || boardBack[i][j] == 'G' || boardBack[i][j] == 'E')
            {
                count1++;
            }
            else if (boardBack[i][j] == '2' || boardBack[i][j] == 'g' || boardBack[i][j] == 'e')
            {
                count2++;
            }
        }
    }
    if (count1 == 0 && count2 == 0)
    {
        printf("!!!! DRAW !!!!");
        displayBoard();
        start = 0;
    }
    else if (count1 == 0)
    {
        printf("!!!! Plyer 2 WIN !!!!");
        displayBoard();
        start = 0;
    }
    else if (count2 == 0)
    {
        printf("!!!! Plyer 1 WIN !!!!");
        displayBoard();
        start = 0;
    }
}

void moveMove(int row, int column, int rowE, int columnE)
{
    if (board[rowE][columnE] == ' ' ||
        (board[rowE][columnE] == 'k' && board[row][column] == 'J') ||
        (board[rowE][columnE] == 'j' && board[row][column] == 'Q') ||
        (board[rowE][columnE] == 'q' && board[row][column] == 'K') ||
        (board[rowE][columnE] == 'K' && board[row][column] == 'j') ||
        (board[rowE][columnE] == 'J' && board[row][column] == 'q') ||
        (board[rowE][columnE] == 'Q' && board[row][column] == 'k'))
    {
        if ((board[row][column] == 'K' && board[rowE][columnE] == 'q'))
        {
            boardBack[row][column] = 'E';
        }
        else if ((board[row][column] == 'k' && board[rowE][columnE] == 'Q'))
        {
            boardBack[row][column] = 'e';
        }
        board[rowE][columnE] = board[row][column];
        board[row][column] = ' ';
        boardBack[rowE][columnE] = boardBack[row][column];
        boardBack[row][column] = ' ';
    }

    else if (board[rowE][columnE] == ' ' ||
             (board[rowE][columnE] == 'k' && board[row][column] == 'K') ||
             (board[rowE][columnE] == 'q' && board[row][column] == 'Q') ||
             (board[rowE][columnE] == 'j' && board[row][column] == 'J') ||
             (board[rowE][columnE] == 'K' && board[row][column] == 'k') ||
             (board[rowE][columnE] == 'Q' && board[row][column] == 'q') ||
             (board[rowE][columnE] == 'J' && board[row][column] == 'j'))
    {
        board[rowE][columnE] = ' ';
        board[row][column] = ' ';
        boardBack[rowE][columnE] = ' ';
        boardBack[row][column] = ' ';
    }

    else
    {
        printf("!!! Please select again !!!\n\n");
    }
    turn++;
}

void moveMoveG(int row, int column, int rowE, int columnE)
{
    if (board[rowE][columnE] == ' ' ||
        (board[rowE][columnE] == 'k' && board[row][column] == 'J') ||
        (board[rowE][columnE] == 'j' && board[row][column] == 'Q') ||
        (board[rowE][columnE] == 'q' && board[row][column] == 'K') ||
        (board[rowE][columnE] == 'K' && board[row][column] == 'j') ||
        (board[rowE][columnE] == 'J' && board[row][column] == 'q') ||
        (board[rowE][columnE] == 'Q' && board[row][column] == 'k'))
    {
        board[rowE][columnE] = board[row][column];
        board[row][column] = ' ';
        boardBack[rowE][columnE] = boardBack[row][column];
        boardBack[row][column] = ' ';
    }

    else if (board[rowE][columnE] == ' ' ||
             (board[rowE][columnE] == 'k' && board[row][column] == 'K') ||
             (board[rowE][columnE] == 'q' && board[row][column] == 'Q') ||
             (board[rowE][columnE] == 'j' && board[row][column] == 'J') ||
             (board[rowE][columnE] == 'K' && board[row][column] == 'k') ||
             (board[rowE][columnE] == 'Q' && board[row][column] == 'q') ||
             (board[rowE][columnE] == 'J' && board[row][column] == 'j'))
    {
        board[rowE][columnE] = ' ';
        board[row][column] = ' ';
        boardBack[rowE][columnE] = ' ';
        boardBack[row][column] = ' ';
    }

    else
    {
        printf("!!! Please select again !!!\n\n");
    }
    turn++;
}

void moveMoveE(int row, int column, int movement)
{
    int rowE, columnE;

    switch (movement)
    {
    case 1:
        printf("Select row to move : ");
        scanf("%d", &rowE);
        rowE--;
        moveMove(row, column, rowE, column);
        break;
    case 2:
        printf("Select column to move : ");
        scanf("%d", &columnE);
        columnE--;
        moveMove(row, column, row, columnE);

        break;
    default:
        break;
    }
    turn++;
}

void checkGoalChess()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (boardBack[0][j] == '2')
            {
                boardBack[0][j] = 'g';
            }
            else if (boardBack[4][j] == '1')
            {
                boardBack[4][j] = 'G';
            }
        }
    }
}

void eatAgentQ(int row, int column, int rowE, int columnE)
{
    if ((board[row][column] == 'K' && board[rowE][columnE] == 'q'))
    {
        boardBack[row][column] = 'E';
    }
    else if ((board[row][column] == 'k' && board[rowE][columnE] == 'Q'))
    {
        boardBack[row][column] = 'e';
    }
}
