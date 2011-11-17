/* Game: snake      version: 1.0    date:2011/08/22 
 * Author: Dream Fly 
 * filename: snake.h 
 */  
  
#define SNAKE_SYMBOL    '@'     /* snake body and food symbol */   
#define FOOD_SYMBOL     '*'   
#define MAX_NODE        30      /* maximum snake nodes */   
#define DFL_SPEED       50      /* snake default speed */   
#define TOP_ROW     5           /* top_row */   
#define BOT_ROW     LINES - 1   
#define LEFT_EDGE   0   
#define RIGHT_EDGE  COLS - 1   
  
typedef struct node         /* Snake_node structure */  
{  
    int x_pos;  
    int y_pos;  
    struct node *prev;  
    struct node *next;  
} Snake_Node;  
  
struct position             /* food position structure */  
{  
    int x_pos;  
    int y_pos;  
} ;  
void Init_Disp();           /* init and display the interface */  
void Food_Disp();           /* display the food position */  
void Wrap_Up();             /* turn off the curses */  
void Key_Ctrl();            /* using keyboard to control snake */  
int set_ticker(int n_msecs);/* ticker */  
  
void DLL_Snake_Create();    /* create double linked list*/  
void DLL_Snake_Insert(int x, int y);    /* insert node */  
void DLL_Snake_Delete_Node();   /* delete a node */  
void DLL_Snake_Delete();        /* delete all the linked list */  
  
void Snake_Move();          /* control the snake move and judge */  
void gameover(int n);       /* different n means different state */  

 
/* Filename: snake.c    version:1.0     date: 2011/08/22 
 * Author: Dream Fly    blog: blog.csdn.net/jjzhoujun2010 
 * Usage: 'f' means speed up, 's' means speed down, 'q' means quit; 
 * Navigation key controls the snake moving.  
 * Compile: gcc snake.c -lncurses -o snake 
 */  
  
#include<stdio.h>   
#include<stdlib.h>   
#include<ncurses.h>   
#include<sys/time.h>   
#include<signal.h>   
#include"snake.h"   
  
struct position food;       /* food position */  
Snake_Node *head, *tail;    /* double linked list's head and tail */  
int x_dir = 1, y_dir = 0;   /* init dirction of the snake moving */  
int ttm = 5, ttg = 5;           /* two timers defined to control speed */  
  
void main(void)  
{  
    Init_Disp();            /* init and display the interface */  
    Food_Disp();            /* display food */  
    DLL_Snake_Create();     /* create double linked list and display snake*/  
    signal(SIGALRM, Snake_Move);  
    set_ticker(DFL_SPEED);  
    Key_Ctrl();             /* using keyboard to control snake */  
    Wrap_Up();              /* turn off the curses */  
}  
  
/* Function: Init_Disp() 
 * Usage: init and display the interface 
 * Return: none 
 */  
void Init_Disp()  
{  
    char wall = ' ';  
    int i, j;  
    initscr();  
    cbreak();               /* put termial to CBREAK mode */  
    noecho();  
    curs_set(0);            /* set cursor invisible */  
  
    /* display some message about title and wall */  
    attrset(A_NORMAL);      /* set NORMAL first */  
    attron(A_REVERSE);      /* turn on REVERSE to display the wall */  
    for(i = 0; i < LINES; i++)  
    {  
        mvaddch(i, LEFT_EDGE, wall);  
        mvaddch(i, RIGHT_EDGE, wall);  
    }  
    for(j = 0; j < COLS; j++)  
    {  
        mvaddch(0, j, '=');  
        mvaddch(TOP_ROW, j, wall);  
        mvaddch(BOT_ROW, j, wall);  
    }  
    attroff(A_REVERSE);     /* turn off REVERSE */  
    mvaddstr(1, 2, "Game: snake    version: 1.0    date: 2011/08/22");  
    mvaddstr(2, 2, "Author: Dream Fly   Blog: blog.csdn.net/jjzhoujun2010");  
    mvaddstr(3, 2, "Usage: Press 'f' to speed up, 's' to speed down,'q' to quit.");  
    mvaddstr(4, 2, "       Nagivation key controls snake moving.");  
    refresh();  
}  
  
/* Function: Food_Disp() 
 * Usage: display food position 
 * Return: none 
 */  
void Food_Disp()  
{  
    srand(time(0));  
    food.x_pos = rand() % (COLS - 2) + 1;  
    food.y_pos = rand() % (LINES - TOP_ROW - 2) + TOP_ROW + 1;  
    mvaddch(food.y_pos, food.x_pos, FOOD_SYMBOL);/* display the food */  
    refresh();  
}  
  
/* Function: DLL_Snake_Create() 
 * Usage: create double linked list, and display the snake first node 
 * Return: none 
 */  
void DLL_Snake_Create()  
{  
    Snake_Node *temp = (Snake_Node *)malloc(sizeof(Snake_Node));  
    head = (Snake_Node *)malloc(sizeof(Snake_Node));  
    tail = (Snake_Node *)malloc(sizeof(Snake_Node));  
    if(temp == NULL || head == NULL || tail == NULL)  
        perror("malloc");  
    temp->x_pos = 5;  
    temp->y_pos = 10;  
    head->prev =NULL;  
    tail->next = NULL;  
    head->next = temp;  
    temp->next = tail;  
    tail->prev = temp;  
    temp->prev = head;  
    mvaddch(temp->y_pos, temp->x_pos, SNAKE_SYMBOL);  
    refresh();  
}  
  
/* Function: Snake_Move() 
 * Usage: use Navigation key to control snake moving, and judge 
 * if the snake touch the food. 
 * Return: 
 */  
void Snake_Move()  
{  
    static int length = 1;      /* length of snake */  
    int Length_Flag = 0;        /* default snake's length no change */  
    int moved = 0;  
    signal(SIGALRM, SIG_IGN);  
    /* judge if the snake crash the wall */  
    if((head->next->x_pos == RIGHT_EDGE-1 && x_dir == 1)   
        || (head->next->x_pos == LEFT_EDGE+1 && x_dir == -1)  
        || (head->next->y_pos == TOP_ROW+1 && y_dir == -1)  
        || (head->next->y_pos == BOT_ROW-1 && y_dir == 1))  
    {  
        gameover(1);  
    }  
    /* judge if the snake crash itself */  
    if(mvinch(head->next->y_pos + y_dir, head->next->x_pos + x_dir) == '@')  
        gameover(2);  
  
    if(ttm > 0 && ttg-- == 1)  
    {  
        /* snake moves */  
        DLL_Snake_Insert(head->next->x_pos + x_dir, head->next->y_pos + y_dir);  
        ttg = ttm;      /* reset */  
        moved = 1;      /* snake can move */  
    }  
    if(moved)  
    {  
        /* snake eat the food */  
        if(head->next->x_pos == food.x_pos && head->next->y_pos == food.y_pos)  
        {  
            Length_Flag = 1;  
            length++;  
            /* Mission Complete */  
            if(length >= MAX_NODE)  
                gameover(0);  
            /* reset display the food randomly */  
            Food_Disp();  
        }  
        if(Length_Flag == 0)  
        {  
            /* delete the tail->prev node */  
            mvaddch(tail->prev->y_pos, tail->prev->x_pos, ' ');  
            DLL_Snake_Delete_Node();  
        }  
        mvaddch(head->next->y_pos, head->next->x_pos, SNAKE_SYMBOL);  
        refresh();  
    }  
    signal(SIGALRM, Snake_Move);  
}  
  
/* Function: set_ticker(number_of_milliseconds) 
 * Usage: arrange for interval timer to issue SIGALRM's at regular intervals 
 * Return: -1 on error, 0 for ok 
 * arg in milliseconds, converted into whole seconds and microseconds 
 * note: set_ticker(0) turns off ticker 
 */  
int set_ticker(int n_msecs)  
{  
    struct itimerval new_timeset;  
    long n_sec, n_usecs;  
  
    n_sec = n_msecs / 1000;                 /* int second part */  
    n_usecs = (n_msecs % 1000) * 1000L;     /* microsecond part */  
  
    new_timeset.it_interval.tv_sec = n_sec; /* set reload */  
    new_timeset.it_interval.tv_usec = n_usecs;  
  
    new_timeset.it_value.tv_sec = n_sec;    /* set new ticker value */  
    new_timeset.it_value.tv_usec = n_usecs;  
  
    return setitimer(ITIMER_REAL, &new_timeset, NULL);  
}  
  
/* Function: Wrap_Up() 
 * Usage: turn off the curses 
 * Return: none 
 */  
void Wrap_Up()  
{  
    set_ticker(0);      /* turn off the timer */  
    getchar();  
    endwin();  
    exit(0);  
}  
  
/* Function: Key_Ctrl() 
 * Usage: using keyboard to control snake action; 'f' means speed up, 
 * 's' means speed down, 'q' means quit, navigation key control direction. 
 * Return: none 
 */  
void Key_Ctrl()  
{  
    int c;  
    keypad(stdscr, true);       /* use little keyboard Navigation Key */  
    while(c = getch(), c != 'q')  
    {  
        if(c == 'f')  
        {  
            if(ttm == 1)  
                continue;  
            ttm--;  
        }  
        else if(c == 's')  
        {  
            if(ttm == 8)  
                continue;  
            ttm++;  
        }  
        if(c == KEY_LEFT)  
        {  
            if(tail->prev->prev->prev != NULL && x_dir == 1 && y_dir == 0)  
                continue; /* it can't turn reverse when snake have length */  
            x_dir = -1;  
            y_dir = 0;  
        }  
        else if(c == KEY_RIGHT)  
        {  
            if(tail->prev->prev->prev != NULL && x_dir == -1 && y_dir == 0)  
                continue;  
            x_dir = 1;  
            y_dir = 0;  
        }  
        else if(c == KEY_UP)  
        {  
            if(tail->prev->prev->prev != NULL && x_dir == 0 && y_dir == 1)  
                continue;  
            x_dir = 0;  
            y_dir = -1;  
        }  
        else if(c == KEY_DOWN)  
        {  
            if(tail->prev->prev->prev != NULL && x_dir == 0 && y_dir == -1)  
                continue;  
            x_dir = 0;  
            y_dir = 1;  
        }  
    }  
}  
  
/* Function: DLL_Snake_Insert(int x, int y) 
 * Usage: Insert node in the snake. 
 * Return: none 
 */  
void DLL_Snake_Insert(int x, int y)  
{  
    Snake_Node *temp = (Snake_Node *)malloc(sizeof(Snake_Node));  
    if(temp == NULL)  
        perror("malloc");  
    temp->x_pos = x;  
    temp->y_pos = y;  
    temp->prev = head->next->prev;  
    head->next->prev = temp;  
    temp->next = head->next;  
    head->next = temp;  
}  
  
/* Function: gameover(int n) 
 * Usage: gameover(0) means Mission Completes; gameover(1) means crashing 
 * the wall; gameover(2) means crash itself. 
 * Return: none 
 */  
void gameover(int n)  
{  
    switch(n)  
    {  
        case 0:   
            mvaddstr(LINES / 2, COLS / 3 - 4, "Mission Completes,press any key to exit.\n");  
            break;  
        case 1:  
            mvaddstr(LINES/2, COLS/3 - 4, "Game Over, crash the wall,press any key to exit.\n");  
            break;  
        case 2:  
            mvaddstr(LINES/2, COLS/3 - 4, "Game Over, crash yourself,press any key to exit.\n");  
            break;  
        default:  
            break;  
    }  
    refresh();  
    /* delete the whole double linked list */  
    DLL_Snake_Delete();  
    Wrap_Up();  
}  
  
/* Function: DLL_Snake_Delete_Node() 
 * Usage: delete a tail node, not the whole linked list 
 * Return: none 
 */  
void DLL_Snake_Delete_Node()  
{  
    Snake_Node *temp;  
    temp = tail->prev;  
    tail->prev = tail->prev->prev;  
    temp->prev->next = tail;  
    free(temp);  
}  
  
/* Function: DLL_Snake_Delete() 
 * Usage: delete the whole double linked list 
 * Return: none 
 */  
void DLL_Snake_Delete()  
{  
    while(head->next != tail)  
        DLL_Snake_Delete_Node();  
    head->next = tail->prev = NULL;  
    free(head);  
    free(tail);  
}  
