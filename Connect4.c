#include <stdio.h>
#include <stdlib.h>

int winer = 0;

//function for printing the board
void printBoard(char** board, int width, int height){
    for(int i=height-1; i>=0; i--){
        for(int j=0; j<width; j++){
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
}

//checking for a vertical line of 4 tokens of the same player
void checkVertically(char** board, int heigth, int i, int j){
    if(board[i][j] != ' ' && i < heigth-3){
        if(board[i][j] == board[i+1][j]){
            if(board[i][j] == board[i+2][j]){
                if(board[i][j] == board[i+3][j]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkVertically(board, heigth, i+3, j);
                }
            }else{
                checkVertically(board, heigth, i+2, j);
            }
        }else{
            checkVertically(board, heigth, i+1, j);
        }
    }
}

//checking for a horizontal line of 4 tokens of the same player
void checkHorizontally(char** board, int width, int i, int j){
    if(j < width-3){
        if(board[i][j] == board[i][j+1] && board[i][j] != ' '){
            if(board[i][j] == board[i][j+2]){
                if(board[i][j] == board[i][j+3]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkHorizontally(board, width, i, j+3);
                }
            }else{
                checkHorizontally(board, width, i, j+2);
            }
        }else{
            checkHorizontally(board, width, i, j+1);
        }
    }
}

//checking for a diagonal line of 4 tokens of the same player from left to rigth
void checkDiagonallyRigth(char** board, int width, int heigth, int i, int j){
    if(i < heigth-3 && j < width-3){
        if(board[i][j] == board[i+1][j+1] && board[i][j] != ' '){
            if(board[i][j] == board[i+2][j+2]){
                if(board[i][j] == board[i+3][j+3]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkDiagonallyRigth(board, width, heigth, i+3, j+3);
                }
            }else{
                checkDiagonallyRigth(board, width, heigth, i+2, j+2);
            }
        }else{
            checkDiagonallyRigth(board, width, heigth, i+1, j+1);
        }
    }
}

//checking for a diagonal line of 4 tokens of the same player from rigth to left
void checkDiagonallyLeft(char** board, int width, int heigth, int i, int j){
    if(i < heigth-3 && j > 2){
        if(board[i][j] == board[i+1][j-1] && board[i][j] != ' '){
            if(board[i][j] == board[i+2][j-2]){
                if(board[i][j] == board[i+3][j-3]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkDiagonallyLeft(board, width, heigth, i+3, j-3);
                }
            }else{
                checkDiagonallyLeft(board, width, heigth, i+2, j-2);
            }
        }else{
            checkDiagonallyLeft(board, width, heigth, i+1, j-1);
        }
    }
}

//using the four functions above until one finds the winer if there is
void winerCheck(char** board, int width, int heigth){
    for(int j=0; j<width; j++){
        checkVertically(board, heigth, 0, j);
        if(winer > 0){
            break;
        }
    }

    if(winer == 0){
        for(int i=0; i<heigth; i++){
            checkHorizontally(board, width, i, 0);
            if(winer > 0){
                break;
            }
        }
    }

    if(winer == 0){
        for(int i=0; i<heigth; i++){
            checkDiagonallyRigth(board, width, heigth, i, 0);
            if(winer > 0){
                break;
            }
        }
    }
    if(winer == 0){
        for(int j=0; j<width; j++){
            checkDiagonallyRigth(board, width, heigth, 0, j);
            if(winer > 0){
                break;
            }
        }
    }

    if(winer == 0){
        for(int i=0; i<heigth; i++){
            checkDiagonallyLeft(board, width, heigth, i, width-1);
            if(winer > 0){
                break;
            }
        }
    }
    if(winer == 0){
        for(int j=width-1; j>2; j--){
            checkDiagonallyLeft(board, width, heigth, 0, j);
            if(winer > 0){
                break;
            }
        }
    }
}

//the player chooses a column to place his token in
void playerTurn(int n, char** board, int width, int heigth){
    printf("\nPlayer%d turn!\n", n);
    int column;
    int isfull = 1;
    do{
        scanf("%d", &column);
        if(column<1 || column>width){
            printf("No such column. Pick from 1-%d\n", width);
        }else{
            for(int i=0; i<heigth; i++){
                if(board[i][column-1] == ' '){
                    if(n == 1){
                        board[i][column-1] = 'O';
                    }else{
                        board[i][column-1] = 'X';
                    }
                    isfull = 0;
                    break;
                }
            }
            if(isfull){
                printf("column is full. Pick another one!\n");
            }
        }
    }while(column<1 || column >width || isfull);
    
    printBoard(board, width, heigth);
    winerCheck(board, width, heigth);
}

int main(void){
    char filename[20];
    printf("Enter name of text file\n");
    printf("Must be less than 20 symbols\n");
    scanf("\n%s", filename);
    printf("\n");

    FILE * file = fopen(filename, "w+");

    int width;
    int heigth;
    //getting intput for the width of the board
    do{
        printf("Enter width of the board\n");
        printf("It must not be more than 40 or less than 4.\n");
        scanf("%d", &width);
        if(width<4){
            printf("Too small\n");
        }
        if(width>40){
            printf("Too big\n");
        }
    }while(width>40 || width<4);
    printf("\n");

    //getting input for the heigth of the board
    do{
        printf("Enter heigth of the board\n");
        printf("It must not be more than 20 or less than 4.\n");
        scanf("%d", &heigth);
        if(heigth<4){
            printf("Too small\n");
        }
        if(heigth>40){
            printf("Too big\n");
        }
    }while(heigth>40 || heigth<4);
    printf("\n");

    //creating a double array for the board
    char ** board = calloc(heigth, sizeof(char*));
    for(int i=0; i<heigth; i++){
        board[i] = calloc(width, sizeof(char));
        for(int j=0; j<width; j++){
            board[i][j] = ' ';
        }
    }

    //choosing singleplayer or multiplayer
    char type;
    do{
        printf("'s' - singleplayer\n");
        printf("'m' - multyplayer\n");
        scanf("\n%c", &type);
        if(type != 's' && type != 'm'){
            printf("Invalid option\n");
        }
    }while(type != 's' && type != 'm');
    printf("\n");

    //printing the empty board
    printBoard(board, width, heigth);
    printf("Start Game\n");

    //multiplayer - players taking turns until one wins or the board is full
    if(type == 'm'){
        int turns = 0;
        while(1){
            playerTurn(turns%2+1, board, width, heigth);
            for(int i=heigth-1; i>=0; i--){
                for(int j=0; j<width; j++){
                    fprintf(file, "|%c", board[i][j]);
                }
                fprintf(file, "|\n");
            }
            fprintf(file, "\n");

            turns++;
            if(turns == width*heigth || winer > 0){
                break;
            }
        }
        printf("\n");
    }else if(type == 's'){
        printf("S\n");
    }

    switch(winer){
        case 1:
            printf("Player1 wins!\n");
            break;
        case 2:
            printf("Player2 wins!\n");
            break;
        default:
            printf("Draw\n");
            break;
    }


    //freeing allocated memory
    for(int i=0; i<heigth; i++){
        free(board[i]);
    }
    free(board);

    fclose(file);

    return 0;
}