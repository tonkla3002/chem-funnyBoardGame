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
void playMove(int row,int column, char player);
void checkStatus();

void selectChess();
void moveMove(int row,int column,int rowE,int columnE);


int main(void){

    board[3][3] = 'J';
    board[3][1] = 'Q';
    board[3][2] = 'K';

    board[4][1] = 'j';
    board[4][2] = 'q';
    board[4][3] = 'k';

    boardBack[3][1] = '1';
    boardBack[3][3] = '1';
    boardBack[3][2] = '1';

    boardBack[4][1] = '2';
    boardBack[4][2] = '2';
    boardBack[4][3] = '2';

    while (start == 1) {
        checkStatus();

        displayBoard();
        printf("Player %c, select agent\n",player);


       selectChess();

        // printf(checkStatus());
        if(player == '2')
            player = '1';
        else
            player ='2';
        checkStatus();

    }

}


void displayBoard() {
    printf("\n    1   2   3   4   5\n");
    printf("  +---+---+---+---+---+\n");
    for (int i = 0; i < 5; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < 5; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n  +---+---+---+---+---+\n");
    }
}



void playMove(int row,int column, char player) {

    int movement = 0;

    if (boardBack[row][column] == player) {

        printf("\n1)Up\n2)Left\n3)Right\n4)Down\nSelect your movement :");
        scanf("%d", &movement);

        switch (movement) {
            case 1:
                moveMove(row,column,row-1,column);
                break;

            case 2:
                moveMove(row,column,row,column-1);
                break;

            case 3:
                moveMove(row,column,row,column+1);
                break;

            case 4:
                moveMove(row,column,row+1,column);
                break;
            
        }
    }
}

void selectChess(){
    printf("1)J\n2)Q\n3)K\nSelect your agent : ");
    int agent;
    char chess;
    scanf("%d", &agent);
    
    switch (agent) {
        case 1: chess = 'J'; break;
        case 2: chess = 'Q'; break;
        case 3: chess = 'K'; break;
        default: 
            printf("Please select again !!!\n");
            return;
    }
    char chesslower = tolower(chess);
    printf("chess lower : %c\n",chesslower);
    int found = 0;
    if (player == '1') {
        printf("Player 1\n");
        for (int i = 0; i < 5 && !found; i++) {
        for (int j = 0; j < 5; j++) {
            if (boardBack[i][j] == player && board[i][j] == chess) {
                playMove(i, j, player);
                found = 1; // Mark as found
                break; // Exit inner loop
            }
        }
    }
    }
    else if(player == '2')
    {
        printf("Player 2\n");
        for (int i = 0; i < 5 && !found; i++) {
        for (int j = 0; j < 5; j++) {
            if (boardBack[i][j] == player && board[i][j] == chesslower) {
                playMove(i, j, player);
                found = 1; // Mark as found
                break; // Exit inner loop
                }
            }
        }
    }
}


void  checkStatus(){
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (boardBack[i][j] == '1' ) {
                count1++;
            }
            else if(boardBack[i][j] == '2' ){
                count2++;
            }
        }
    }
    if(count1 == 0 && count2 == 0){
        printf("!!!! DRAW !!!!");
        displayBoard();
        start = 0;
    }
    else if(count1 == 0){
        printf("!!!! Plyer 2 WIN !!!!");
        displayBoard();
        start = 0;
    }
    else if(count2 == 0){
        printf("!!!! Plyer 1 WIN !!!!");
        displayBoard();
        start = 0;
    }
}

void moveMove(int row,int column,int rowE,int columnE) {
     if(board[rowE][columnE] == ' ' || 
        (board[rowE][columnE] == 'k' && board[row][column] == 'J') || 
        (board[rowE][columnE] == 'j' && board[row][column] == 'Q') || 
        (board[rowE][columnE] == 'q' && board[row][column] == 'K') ||
        (board[rowE][columnE] == 'K' && board[row][column] == 'j') || 
        (board[rowE][columnE] == 'J' && board[row][column] == 'q') || 
        (board[rowE][columnE] == 'Q' && board[row][column] == 'k')  ){

            board[rowE][columnE] = board[row][column];
            board[row][column] = ' ';
            boardBack[rowE][columnE] = boardBack[row][column];
            boardBack[row][column] = ' ';      
    }
    
    else if(board[rowE][columnE] == board[row][column] ){
        board[rowE][columnE] = ' ';
        board[row][column] = ' ';
        boardBack[rowE][columnE] = ' ';
        boardBack[row][column] = ' ';
    }

    else{
        printf("!!! Please select again !!!\n\n");
    }
    turn++;
}