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
#include <unistd.h>
#include <time.h>
#include<stdlib.h>

#define snake_BODY "s "
extern int mainscr_col;
extern int mainscr_line;
struct snake
{
	int x_pos, y_pos;
	char* body;
	struct snake *pre;
}snake;

extern WINDOW* mainscr;;

struct snake* creat(struct snake *pLast, int snake_long);
struct snake* add(struct snake *pHead, int y_pos, int x_pos);
void walk(struct snake *pLast, int direction);
int check(struct snake *pLast, struct snake *pHead, int y_pos, int x_pos, int direction);
int random_x(int *px1, int *px2);
int random_y(int *py1, int *py2);
void addfood(int py, int px);
void addScore(int dif, int score, int* hscore, int* boolhscore);
void choose(int* dif,int* v);
int gameover(int dif, int* score, int hscore, int boolhscore);
void highest(int* hscore);
void initial(void);

#endif
