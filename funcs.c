#include <stdio.h>
#include <stdlib.h>

void print_grid(char grid[]) {
    system("clear");
    printf("    1     2     3\n      |     |\na  %c  |  %c  |  %c\n _____|_____|_____\n      |     |\nb  %c  |  %c  |  %c\n _____|_____|_____\n      |     |\nc  %c  |  %c  |  %c \n      |     |     \n", 
    grid[0], grid[1], grid[2],
    grid[3], grid[4], grid[5], 
    grid[6], grid[7], grid[8]);
}
int set_input(char* pos, char* x_or_o, char grid[], int player) {
    if ((int)pos[0] < 97 || (int)pos[0] > 99 || pos[1] > '3' || pos[1] < '1') { //comparing against ascii values
        printf("Invalid position!\n");
        return;
    }
    int b = 0;
    if (pos[0] == 'a') {
        b = 0;
    }
    if (pos[0] == 'b') {
        b = 3;
    }
    if (pos[0] == 'c') {
        b = 6;
    }
    if (pos[1] == '2') {
        b += 1;
    }
    if (pos[1] == '3') {
        b += 2;
    }
    if (grid[b] == 'X' || grid[b] == 'O') {
        printf("Already marked by player %d\n", (player == 1) ? 2 : 1);
        return;
    }
    grid[b] = x_or_o[0];
    print_grid(grid);
    player = (player == 1) ? 2 : 1;
}
int check(char grid[], int player) {

    if ((grid[0] == grid[1] && grid[1] == grid[2] && grid[0] != '-') ||  
        (grid[3] == grid[4] && grid[4] == grid[5] && grid[3] != '-') ||  
        (grid[6] == grid[7] && grid[7] == grid[8] && grid[6] != '-')) {
            system("clear");
            printf("Player %d won!!\n", (player == 1) ? 2 : 1);
            return 1; 
    }

    if ((grid[0] == grid[3] && grid[3] == grid[6] && grid[0] != '-') ||  
        (grid[1] == grid[4] && grid[4] == grid[7] && grid[1] != '-') ||  
        (grid[2] == grid[5] && grid[5] == grid[8] && grid[2] != '-')) {
            system("clear");
            printf("Player %d won!!\n", (player == 1) ? 2 : 1);
            return 1; 
    }

    if ((grid[0] == grid[4] && grid[4] == grid[8] && grid[0] != '-') ||  
        (grid[2] == grid[4] && grid[4] == grid[6] && grid[2] != '-')) {
            system("clear");
            printf("Player %d won!!\n", (player == 1) ? 2 : 1);            
            return 1; 
    }
    else {
        return 0; 
    }
}
