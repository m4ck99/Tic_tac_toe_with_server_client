#ifndef FUNCS_H
#define FUNCS_H
void print_grid(char grid[]) ;
int set_input(char* pos, char* x_or_o, char grid[], int player);
int check(char grid[], int _1_or_2);
int validate(char* pos);
#endif