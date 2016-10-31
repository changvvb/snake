/*************************************************************************
	> File Name: function.h
	> Author: 
	> Mail: 
	> Created Time: Wed 06 Apr 2016 03:57:03 PM CST
 ************************************************************************/

#ifndef _FUNCTION_H
#define _FUNCTION_H
#include<stdio.h>
#include<curses.h>
#include<stdlib.h>

#define SNACK_BODY "s "
extern int mainscr_col;
extern int mainscr_line;
struct snack
{
	int x_pos, y_pos;
	char* body;
	struct snack *pre;
}Snack;

extern WINDOW* mainscr;;

struct snack* creat(struct snack *pLast, int snack_long);
struct snack* add(struct snack *pHead, int y_pos, int x_pos);
void walk(struct snack *pLast, int direction);
int check(struct snack *pLast, struct snack *pHead, int y_pos, int x_pos, int direction);
int random_x(int *px1, int *px2);
int random_y(int *py1, int *py2);
void addfood(int py, int px);
void addScore(int dif, int score, int* hscore, int* boolhscore);
void choose(int* dif,int* v);
void gameover(int dif, int* score, int hscore, int boolhscore);
int highest(int* hscore);
void initial(void);

#endif
