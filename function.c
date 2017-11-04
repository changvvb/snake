#include "function.h"

int main();

int mainscr_col = 100;
int mainscr_line = 35;
#define RECORD_FILE "~/.snack"

WINDOW *mainscr = NULL;

struct snake* creat(struct snake *pLast, int snake_long)
{
	int i;
	struct snake *p;
	p = pLast;
	p->x_pos = (int)((COLS-mainscr_col)/4)*2+1;
	p->y_pos = (LINES-mainscr_line)/2+3;
	p->body = "  ";
	for(i = 1; i <= snake_long; i += 2)
	{
		p->pre = (struct snake*)malloc(sizeof(struct snake));
		p = p->pre;
		p->body = snake_BODY;
		p->x_pos = (COLS-mainscr_col)/4*2+i;
		p->y_pos = (LINES-mainscr_line)/2+3;
	}
	p->pre = NULL;
	return p;
}

struct snake* add(struct snake *pHead, int y_pos, int x_pos)
{
	pHead->pre = (struct snake*)malloc(sizeof(struct snake));
	pHead = pHead->pre;
	pHead->pre = NULL;
	pHead->y_pos = y_pos;
	pHead->x_pos = x_pos;
	pHead->body = snake_BODY;
	return pHead;
}

void walk(struct snake *pLast, int direction)
{
	init_pair(1,COLOR_BLUE,COLOR_BLUE);
	attron(COLOR_PAIR(1));
	if(direction != ERR)
	{
		erase();
		box(mainscr,'|','o');
		struct snake* p = pLast;
		while(p->pre != NULL)
		{
			p->x_pos = p->pre->x_pos;
			p->y_pos = p->pre->y_pos;
			p = p->pre;
		}
		switch(direction)
		{
			case 'w':
				(p->y_pos) --; break;
			case 's':
				(p->y_pos) ++; break;
			case 'd':
				(p->x_pos) += 2; break;
			case 'a':
				(p->x_pos) -= 2; break;
			default:
				break;
		}
		p = pLast;
		while(p != NULL)
		{
			mvwaddstr(stdscr,p->y_pos,p->x_pos,p->body);
			p = p->pre;
		}
		attroff(COLOR_PAIR(1));
		
	}
}

int check(struct snake *pLast, struct snake *pHead, int y_pos, int x_pos, int direction)
{
	switch(direction)
	{
		case 'w':
			y_pos ++; break;
		case 's':
			y_pos --; break;
		case 'd':
			x_pos -= 2; break;
		case 'a':
			x_pos += 2; break;
		default:
			break;
	}
	
	struct snake *p;
	int exam;
	for(p = pLast; p->pre != NULL; p = p->pre)
	{
		if(pHead->x_pos == p->x_pos && pHead->y_pos == p->y_pos)
		{
			exam = 1;
			break;
		}
		else
			exam = 0;
	}
	
	if (pHead->x_pos == x_pos && pHead->y_pos == y_pos)
		return 1;
	else if (pHead->x_pos == (COLS-mainscr_col)/4*2-1 || pHead->x_pos == (COLS-mainscr_col)/4*2-1 + mainscr_col || pHead->y_pos == (LINES-mainscr_line)/4*2 || pHead->y_pos == (LINES-mainscr_line)/4*2+mainscr_line-1)
		return 0;
	else if (exam == 1)
		return 2;
}

int random_x(int *px1, int *px2)
{
	*px1 = *px2;
	*px2 = ((rand() % (mainscr_col - 2)) + (COLS-mainscr_col)/4*2)/2*2+1; 
	return *px1;
}

int random_y(int *py1, int *py2)
{
	*py1 = *py2;
	*py2 = (rand() % (mainscr_line - 2)) + (LINES-mainscr_line)/4*2+1; 
	return *py1;
}

void addfood(int py, int px)
{
	init_pair(2,COLOR_RED,COLOR_RED);
	attron(COLOR_PAIR(2));
	move(py,px);
	addstr("  ");
	attroff(COLOR_PAIR(2));
}

void addScore(int dif, int score, int* hscore, int* boolhscore)
{
	int score0 = dif*score;
	move(10,(COLS-mainscr_col)/2+mainscr_col); 
	if(dif == 10)
		addstr("Diffculity: Easy");
	else if(dif == 50)
		addstr("Diffculity: Middle");
	else
		addstr("Diffculity: Difficult");
	if (score0 > *hscore)
	{
		*hscore = score0;
		*boolhscore = 1;
	}
	move(12,(COLS-mainscr_col)/2+mainscr_col); 
	printw("Score:%10d",score0);
	move(14,(COLS-mainscr_col)/2+mainscr_col);
	printw("Highest Score:%6d",*hscore);
	
}

void choose(int* dif,int* v)
{
	initscr();
	erase();
	noecho();
	start_color();refresh();
	int a,i;
	char* str0 = "GREEDY snake V1.0";
	move(5,COLS/2-25);
	for(;*str0!='\0';str0++)
	{
		addch(*str0);usleep(100000);refresh();
	}
	usleep(2000000);
	char* str1 = "Please make this window biggest!!!!!";
	move(7,COLS/2-25);
	for(;*str1!='\0';str1++)
	{
		addch(*str1);usleep(100000);refresh();
	}
	char* str2 = "Use <UP><DOWN><LEFT><RIGHT> or <w><s><a><d> to control the game.";
	move(9,COLS/2-25);
	for(;*str2!='\0';str2++)
	{
		addch(*str2);usleep(50000);refresh();
	}
	char* str3 = "Enter <1> <2> <3> to choose difficulity.";
	move(11,COLS/2-25);
	for(;*str3!='\0';str3++)
	{
		addch(*str3);usleep(50000);refresh();
	}
	move(13,COLS/2-25);
	addstr("1.Easy");
	move(14,COLS/2-25);
	addstr("2.Middle");
	move(15,COLS/2-25);
	addstr("3.Difficult");
	refresh();
	while(a!='1'&&a!='2'&&a!='3')
	{
		a = getch();
	}
	if(a == '1')
	{
		move(17,COLS/2-25);addstr("You have chosen Easy. Game will begin at once. "); *v = 200000; *dif = 10;
	}
	else if(a == '2')
	{
		move(17,COLS/2-25);addstr("You have chosen Middle. Game will begin at once. "); *v = 100000; *dif = 50;
	}
	else if(a == '3')
	{
		move(17,COLS/2-25);addstr("You have chosen Difficult. Game will begin at once. "); *v = 50000; *dif = 100;
	}
	refresh();
	usleep(500000);
}

void gameover(int dif, int* score, int hscore, int boolhscore)
{
	//usleep(1500000);
	//timeout(-1); getch();
	init_pair(1,COLOR_RED,COLOR_WHITE);
	attron(COLOR_PAIR(1));
	if (boolhscore)
	{
		FILE *fp;
		fp = fopen(RECORD_FILE,"w");
		fprintf(fp,"%d",hscore);
		fclose(fp);
		move(LINES/2-2,COLS/2 - 7);
		addstr("You are great!!!");
	}
	move(LINES/2,COLS/2 - 4);
	addstr("GAME OVER!");
	move(LINES/2+2,COLS/2 - 7);
	printw("Your score is %d",dif*(*score));
	move(LINES/2+4,COLS/2 - 15);
	addstr("Enter 'q' to quit, 'c' to continue.");
	refresh();
	attroff(COLOR_PAIR(1));
	printf("\033[?25h");
	int a = getch();
	while(a != 'c' && a != 'q')
		a = getch();
	if(a == 'c')
	{
		*score = 0;
		main();
	}
}

int highest(int* hscore)
{
	FILE *fp;
	char p[10];
	fp = fopen(RECORD_FILE,"a+");
	fscanf(fp,"%s",p);
	*hscore = atoi(p);
	fclose(fp);
}

void initial(void)
{
	start_color();
	initscr();
	printf("\033[?25l");
	noecho();
	keypad(stdscr,true);
	timeout(0);
	srand(time(NULL));
	mainscr = subwin(stdscr,mainscr_line,mainscr_col,(LINES-mainscr_line)/4*2,(COLS-mainscr_col)/4*2);
	box(mainscr,'|','o');
}
