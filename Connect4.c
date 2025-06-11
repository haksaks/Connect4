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
void checkVertically(char** board, int height, int i, int j){
    if(board[i][j] != ' ' && i < height-3){
        if(board[i][j] == board[i+1][j]){
            if(board[i][j] == board[i+2][j]){
                if(board[i][j] == board[i+3][j]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkVertically(board, height, i+3, j);
                }
            }else{
                checkVertically(board, height, i+2, j);
            }
        }else{
            checkVertically(board, height, i+1, j);
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
void checkDiagonallyRigth(char** board, int width, int height, int i, int j){
    if(i < height-3 && j < width-3){
        if(board[i][j] == board[i+1][j+1] && board[i][j] != ' '){
            if(board[i][j] == board[i+2][j+2]){
                if(board[i][j] == board[i+3][j+3]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkDiagonallyRigth(board, width, height, i+3, j+3);
                }
            }else{
                checkDiagonallyRigth(board, width, height, i+2, j+2);
            }
        }else{
            checkDiagonallyRigth(board, width, height, i+1, j+1);
        }
    }
}

//checking for a diagonal line of 4 tokens of the same player from rigth to left
void checkDiagonallyLeft(char** board, int width, int height, int i, int j){
    if(i < height-3 && j > 2){
        if(board[i][j] == board[i+1][j-1] && board[i][j] != ' '){
            if(board[i][j] == board[i+2][j-2]){
                if(board[i][j] == board[i+3][j-3]){
                    if(board[i][j] == 'O'){
                        winer = 1;
                    }else{
                        winer = 2;
                    }
                }else{
                    checkDiagonallyLeft(board, width, height, i+3, j-3);
                }
            }else{
                checkDiagonallyLeft(board, width, height, i+2, j-2);
            }
        }else{
            checkDiagonallyLeft(board, width, height, i+1, j-1);
        }
    }
}

//using the four functions above until one finds the winer if there is
void winerCheck(char** board, int width, int height){
    for(int j=0; j<width; j++){
        checkVertically(board, height, 0, j);
        if(winer > 0){
            break;
        }
    }

    if(winer == 0){
        for(int i=0; i<height; i++){
            checkHorizontally(board, width, i, 0);
            if(winer > 0){
                break;
            }
        }
    }

    if(winer == 0){
        for(int i=0; i<height; i++){
            checkDiagonallyRigth(board, width, height, i, 0);
            if(winer > 0){
                break;
            }
        }
    }
    if(winer == 0){
        for(int j=0; j<width; j++){
            checkDiagonallyRigth(board, width, height, 0, j);
            if(winer > 0){
                break;
            }
        }
    }

    if(winer == 0){
        for(int i=0; i<height; i++){
            checkDiagonallyLeft(board, width, height, i, width-1);
            if(winer > 0){
                break;
            }
        }
    }
    if(winer == 0){
        for(int j=width-1; j>2; j--){
            checkDiagonallyLeft(board, width, height, 0, j);
            if(winer > 0){
                break;
            }
        }
    }
}

//the player chooses a column to place his token in
void playerTurn(int n, char** board, int width, int height){
    printf("\nPlayer%d turn!\n", n);
    int column;
    int isfull = 1;
    do{
        scanf("%d", &column);
        if(column<1 || column>width){
            printf("No such column. Pick from 1-%d\n", width);
        }else{
            for(int i=0; i<height; i++){
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
    
    printBoard(board, width, height);
    winerCheck(board, width, height);
}

int score(char** board, int width , int height)
{
    int score = 0;

    for(int row = 0 ; row < height ; row++)
    {
        for(int col = 0 ; col < width - 3 ; col++)
        {
            int ai = 0;
            int op = 0;
            for(int i = 0 ; i < 4 ; i++)
            {
                if(board[row][col+i] == 'X') ai++;
                else if(board[row][col+i] == 'O') op++;
            }
            if(ai == 4) score+=100;
            else if(ai == 3 && op == 0) score+=6;
            else if(ai == 2 && op == 0) score+=2;
            else if(op == 2 && ai ==0) score-=2;
            else if(op == 3 && ai == 0) score-=15;
        }
    }

    for(int col = 0 ; col < width ; col++)
    {
        for(int row = 0 ; row < height - 3 ; row++)
        {
            int ai = 0;
            int op = 0;
            for(int i = 0 ; i < 4 ; i++)
            {
                if(board[row+i][col] == 'X') ai++;
                else if(board[row+i][col] == 'O') op++;
            }
            if(ai == 4) score+=100;
            else if(ai == 3 && op == 0) score+=6;
            else if(ai == 2 && op == 0) score+=2;
            else if(op == 2 && ai ==0) score-=2;
            else if(op == 3 && ai == 0) score-=15;
        }
    }

    for(int row = 0 ; row < height - 3; row++)
    {
        for(int col = 0 ; col < width - 3 ; col++)
        {
            int ai = 0;
            int op = 0;
            for(int i = 0 ; i < 4 ; i++)
            {
                if(board[row+i][col+i] == 'X') ai++;
                else if(board[row+i][col+i] == 'O') op++;
            }
            if(ai == 4) score+=100;
            else if(ai == 3 && op == 0) score+=6;
            else if(ai == 2 && op == 0) score+=2;
            else if(op == 2 && ai ==0) score-=2;
            else if(op == 3 && ai == 0) score-=15;
        }
    }

    for(int row = 0 ; row < height - 3; row++)
    {
        for(int col = 3 ; col < width ; col++)
        {
            int ai = 0;
            int op = 0;
            for(int i = 0 ; i < 4 ; i++)
            {
                if(board[row+i][col-i] == 'X') ai++;
                else if(board[row+i][col-i] == 'O') op++;
            }
            if(ai == 4) score+=100;
            else if(ai == 3 && op == 0) score+=6;
            else if(ai == 2 && op == 0) score+=2;
            else if(op == 2 && ai ==0) score-=2;
            else if(op == 3 && ai == 0) score-=15;
        }
    }

    return score;
}

void aiTurn(char** board, int width, int height)
{
    printf("\nPlayer2 turn!\n");
    int *scores = malloc(width*sizeof(int));
    int isfull = 1;
    for(int col = 0 ; col < width ; col++)
    {
        int h;

        for(int i=0; i<height; i++)
        {
            if(board[i][col] == ' '){
                board[i][col] = 'X';
                isfull = 0;
                h = i;
                break;
            }
        }
        if(isfull == 0)
        {
            scores[col]=score(board,width,height);
            board[h][col] = ' ';
        }
        else 
        {
            scores[col] = -1000;
        } 
        isfull = 1;
    }

    printf("\n");

    int max = scores[0];
    int col = 0;
    for(int i = 1 ; i<width ; i++)
    {
        if(scores[i]>max)
        {
            max = scores[i];
            col = i;
        }
    }

    for(int i=0; i<height; i++)
    {
        if(board[i][col] == ' ')
        {
            board[i][col] = 'X';
            isfull = 0;
            break;
        }
    }
    
    
    printBoard(board, width, height);
    winerCheck(board, width, height);
}

int main(void){
    char filename[20];
    printf("Enter name of text file\n");
    printf("Must be less than 20 symbols\n");
    scanf("\n%s", filename);
    printf("\n");

    FILE * file = fopen(filename, "w+");

    int width;
    int height;
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

    //getting input for the height of the board
    do{
        printf("Enter height of the board\n");
        printf("It must not be more than 20 or less than 4.\n");
        scanf("%d", &height);
        if(height<4){
            printf("Too small\n");
        }
        if(height>40){
            printf("Too big\n");
        }
    }while(height>40 || height<4);
    printf("\n");

    //creating a double array for the board
    char ** board = calloc(height, sizeof(char*));
    for(int i=0; i<height; i++){
        board[i] = calloc(width, sizeof(char));
        for(int j=0; j<width; j++){
            board[i][j] = ' ';
        }
    }

    //choosing singleplayer or multiplayer
    char type;
    do{
        printf("Choose Gamemode:\n");
        printf("'s' - singleplayer\n");
        printf("'m' - multyplayer\n");
        scanf("\n%c", &type);
        if(type != 's' && type != 'm'){
            printf("Invalid option\n");
        }
    }while(type != 's' && type != 'm');
    printf("\n");

    //printing the empty board
    printBoard(board, width, height);
    printf("Start Game\n");

    //singleplayer - the player takes his turn and then the ai
    if(type == 's'){
        int turns = 0;
        while(1){
            if(turns%2==0) playerTurn(turns%2+1, board, width, height);
            else aiTurn(board,width,height);
            for(int i=height-1; i>=0; i--){
                for(int j=0; j<width; j++){
                    fprintf(file, "|%c", board[i][j]);
                }
                fprintf(file, "|\n");
            }
            fprintf(file, "\n");

            turns++;
            if(turns == width*height || winer > 0){
                break;
            }
        }
        printf("\n");
    }
    //multiplayer - players taking turns until one wins or the board is full
    else if(type == 'm'){
        int turns = 0;
        while(1){
            playerTurn(turns%2+1, board, width, height);
            for(int i=height-1; i>=0; i--){
                for(int j=0; j<width; j++){
                    fprintf(file, "|%c", board[i][j]);
                }
                fprintf(file, "|\n");
            }
            fprintf(file, "\n");

            turns++;
            if(turns == width*height || winer > 0){
                break;
            }
        }
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
    for(int i=0; i<height; i++){
        free(board[i]);
    }
    free(board);

    fclose(file);

    return 0;
}