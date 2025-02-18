#include <stdio.h>
#include <string.h>


char board[5][5][3] = {{' ', ' ', ' ', ' ', ' '},
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
void moveAgent(int row,int column, char player);
void checkWin();

void moveMove(int row,int column,int rowE,int columnE);
void displayBoardBack();

int main(void){

    strcpy(board[3][2], "J1");
    strcpy(board[3][1], "Q1");
    strcpy(board[3][3], "K1");

    strcpy(board[4][1], "J2");
    strcpy(board[4][2], "Q2");
    strcpy(board[4][3], "K2");

    boardBack[3][1] = '1';
    boardBack[3][3] = '1';
    boardBack[3][2] = '1';

    boardBack[4][1] = '2';
    boardBack[4][2] = '2';
    boardBack[4][3] = '2';

    printf("\n\nWelcome to the Funny Board Game\n");
    printf("Player 1 : J1,Q1,K1\n");
    printf("Player 2 : J2,Q2,K2\n");

    while (start == 1) {
        checkWin();

        // displayBoardBack();
        displayBoard();
        printf("Player %c, select agent\n",player);

        printf("Enter the row [1-5]: ");
        scanf("%d", &row);

        printf("Enter the column [1-5]: ");
        scanf("%d", &column);

        moveAgent(row-1,column-1,player);

        // printf(checkWin());
        if(player == '2')
            player = '1';
        else
            player ='2';
        checkWin();

    }

}


void displayBoard() {

    printf("\n  ____________________\n");
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            if(j == 0){
                int num = i+1;
                printf("%d| %c ",num, board[i][j][0]);
            }
            else{
                printf("| %s ", board[i][j]);

            }

        }

        printf("|");
        printf("\n  ____________________\n");

    }
    printf("  1   2   3   4   5\n");

}

// void displayBoardBack() {

//     printf("\n  ____________________\n");
//     for (int i = 0; i < 5; i++) {

//         for (int j = 0; j < 5; j++) {

//             if(j == 0){
//                 int num = i+1;
//                 printf("%d| %c ",num, boardBack[i][j]);
//             }
//             else{
//                 printf("| %c ", boardBack[i][j]);

//             }

//         }

//         printf("|");
//         printf("\n  ____________________\n");

//     }
//     printf("  1   2   3   4   5\n");

// }


void moveAgent(int row,int column, char player) {

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
                turn++;
        }

        else{
            printf("Not your agent please select again !!!\n");
        }
}

void  checkWin(){
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
    if (board[rowE][columnE][0] ==  ' '|| 
        (board[rowE][columnE][0] == 'K' && board[row][column][0] == 'J') || 
        (board[rowE][columnE][0] == 'J' && board[row][column][0] == 'Q') || 
        (board[rowE][columnE][0] == 'Q' && board[row][column][0] == 'K')) {

        strcpy(board[rowE][columnE],board[row][column]);  // Copy character
        strcpy(board[row][column], " ");  // Set empty space
        boardBack[rowE][columnE] = boardBack[row][column];  // Copy character
        boardBack[row][column] = ' ';  // Set empty space
    }

    else if(board[rowE][columnE][0] == board[row][column][0] ){
        strcpy(board[rowE][columnE], " ");
        strcpy(board[row][column], " ");
        boardBack[rowE][columnE] = ' ';
        boardBack[row][column] = ' ';
    }

    else{
        printf("!!! Please select again !!!\n\n");
    }
}