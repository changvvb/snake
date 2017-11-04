#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include "function.h"

int score,v,dif,hscore,boolhscore = 0;
int px1, px2, py1, py2;
struct snake* pHead;
struct snake* pLast;
int key, checkNum, direction = 'd';

void init() 
{
    choose(&dif,&v);
    initial();
    highest(&hscore);
	px2 = 21 + (COLS-mainscr_col)/4*2;
	py2 = 14 + (LINES-mainscr_line)/2;
	random_x(&px1,&px2);
	random_y(&py1,&py2);
	pLast = &snake;
	pHead = creat(pLast,4);
}

int main()
{

    init();
	while(direction != 113)
	{	
		if(checkNum != 1)
			walk(pLast, direction);
		addfood(py1,px1);
		addScore(dif,score,&hscore,&boolhscore);
		refresh();
		usleep(v);
		key = getch();
		switch(key)
		{
			case KEY_UP:
				if(direction != 'w' && direction !='s')
					direction = 'w';
				break;
			case KEY_DOWN:
				if(direction != 's' && direction !='w')
					direction = 's';
				break;
			case KEY_RIGHT:
				if(direction != 'd' && direction !='a')
					direction = 'd';
				break;
			case KEY_LEFT:
				if(direction != 'a' && direction !='d')
					direction = 'a';
				break;
			case 'w':
				if(direction != 'w' && direction !='s')
					direction = 'w';
				break;
			case 's':
				if(direction != 's' && direction !='w')
					direction = 's';
				break;
			case 'd':
				if(direction != 'd' && direction !='a')
					direction = 'd';
				break;
			case 'a':
				if(direction != 'a' && direction !='d')
					direction = 'a';
				break;
			case 113:
				direction = 113; break;
			case 'p':
				timeout(-1);
				move(LINES/2,COLS/2-12);
				addstr("PAUSE! Enter <p> to continue!");
				refresh();
				while(getch() != 'p');
				timeout(0);
			default:
				break;
		}
		checkNum = check(pLast,pHead,py1,px1,direction);
		if(checkNum == 1)
		{
			score ++;
			pHead = add(pHead,py1,px1);
			random_x(&px1,&px2);
			random_y(&py1,&py2);
		}
		else if(checkNum == 0 || checkNum == 2)
		{
            if(0==gameover(dif,&score,hscore,boolhscore)) {
                init();
                continue;
            }
            else 
    			break;
		}
	}
	endwin();
	return 0;
}
