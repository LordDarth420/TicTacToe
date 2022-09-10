#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
void Game(int *, int *, bool *);
void drawFirst();
void drawBoard(int squares[3][3], int *player1Count, int *player2Count);
char convertToXorO(int);
void setSquarePos(int, int *, int *);
bool checkifSomebodyWon(int squares[3][3]);
bool askUserToPlayAgain();
int main()
{
    int command;

    int player1Score, player2Score;
    player1Score = player2Score = 0;

    bool again = false;

    printf("Welcome to Tic Tac Toe!\n\n");
    printf("1: Player vs Player\n0: Exit\n");
    scanf("%d", &command);
    while(command != 0)
    {
        switch(command)
        {
            case 1:
            {
                Game(&player1Score, &player2Score, &again);
                while(again)
                {
                    system("cls");
                    Game(&player1Score, &player2Score, &again);
                }
                system("cls");
                printf("Welcome to Tic Tac Toe!\n\n");
                printf("1: Player vs Player\n0: Exit\n");
                player1Score = 0;
                player2Score = 0;
                break;
            }
        }
        scanf("%d", &command);
    }


}

void Game(int *player1Score, int *player2Score, bool *again)
{
    int squares[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
        };
    int takenSquares = 0, num;
    bool somebodyWon = false;

    drawBoard(squares, player1Score, player2Score);
    printf("Player 1: Your turn... \n\n");
    scanf("%d", &num);
    while(takenSquares != 8)
    {
        int row = 0, column = 0;
        while(num <= 0 || num > 9)
        {
            printf("Out of Bounds! Type again!\n");
            scanf("%d", &num);
        }
        setSquarePos(num, &row, &column);
        while(squares[row][column] == -1 || squares[row][column] == -2)
        {
            printf("Square is taken! Type again!\n");
            scanf("%d", &num);
            setSquarePos(num, &row, &column);
        }

        squares[row][column] = -1;
        somebodyWon = checkifSomebodyWon(squares);
        if(somebodyWon)
        {
            (*player1Score)++;
            drawBoard(squares, player1Score, player2Score);
            printf("Player 1 Wins! Play another game? (Y\\N)\n");
            *again = askUserToPlayAgain();
            break;
        }
        takenSquares++;
        drawBoard(squares, player1Score, player2Score);
        row = 0;
        column = 0;


        printf("Player 2: Your turn... \n\n");
        scanf("%d", &num);
        while(num <= 0 || num > 9)
        {
            printf("Out of Bounds! Type again!\n");
            scanf("%d", &num);
        }
        setSquarePos(num, &row, &column);
        while(squares[row][column] == -1 || squares[row][column] == -2)
        {
            printf("Square is taken! Type again!\n");
            scanf("%d", &num);
            setSquarePos(num, &row, &column);
        }
        squares[row][column] = -2;
        somebodyWon = checkifSomebodyWon(squares);
        if(somebodyWon)
        {
            (*player2Score)++;
            drawBoard(squares, player1Score, player2Score);
            printf("Player 2 Wins! Play another game? (Y\\N)\n");
            *again = askUserToPlayAgain();
            break;
        }
        takenSquares++;
        drawBoard(squares, player1Score, player2Score);

        printf("Player 1: Your turn... \n\n");
        scanf("%d", &num);
        *again = true;
    }

}
bool checkifSomebodyWon(int squares[3][3])
{
    //check diagonals
    if((squares[0][0] ==  -1 || squares[0][0] == -2) && squares[0][0] == squares[1][1] &&
       squares[1][1] && squares[1][1] == squares[2][2])
    {
        return true;
    }
    else if((squares[0][2] ==  -1 || squares[0][2] == -2) && squares[0][2] == squares[1][1] && squares[1][1] == squares[2][0])
    {
        return true;
    }
    //check horizontally
    for(int i = 0; i < 3; i++)
    {
        if((squares[i][0] == -1 || squares[i][0] == -2) &&
           squares[i][0] == squares[i][1] && squares[i][1] == squares[i][2])
        {
            return true;
        }
    }
    //check vertically
    for(int j = 0; j < 3; j++)
    {
        if((squares[0][j] == -1 || squares[0][j] == -2) &&
           squares[0][j] == squares[1][j] && squares[1][j] == squares[2][j])
        {
            return true;
        }
    }
    //if everything is clean
    return false;

}
bool askUserToPlayAgain()
{
    char answer;
    scanf(" %c", &answer);

    while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
    {
        printf("Wrong answer! Type again!\n");
        scanf(" %c", &answer);
    }

    if(answer == 'y' || answer == 'Y')
    {
        return true;
    }
    else if(answer == 'n' || answer == 'N')
    {
        return false;
    }
}
void setSquarePos(int num, int *row, int *column)
{
    int temp = 1;
    for(int i = 0; i < 3  && num + 1 != temp; i++)
    {
        for(int j = 0; j < 3 && num + 1 != temp ; j++)
        {
            if(num == temp)
            {
                *row = i;
                *column = j;
                temp++;
            }
            else{temp++;}
        }
    }
}
void drawBoard(int squares[3][3], int *player1Score, int *player2Score)
{
    system("cls");
    for(int i = 0; i < 3; i++)
    {
        printf("     |     |     \n");
        for(int j = 0; j < 3; j++)
        {
            char c = convertToXorO(squares[i][j]);
            if(j == 2)
            {
                printf("  %c  \n", c);
            }
            else{printf("  %c  |", c);}

        }
        if(i != 2)
        {
            printf("_____|_____|_____\n");
        }
        else
        {
            printf("     |     |     \n");
        }
    }
    printf("\n\nScore:\nPlayer 1: %d\tPlayer 2: %d\n\n", *player1Score, *player2Score);
}
char convertToXorO(int arg)
{
    char c;
    switch(arg)
    {
        case -1:
        {
            c = 'X';
            break;
        }
        case -2:
        {
            c = 'O';
            break;
        }
        default:
        {
            c = arg + '0';
            break;
        }
    }
    return c;
}
