#include "terminal.h"

void Init_Terminal() {
    initscr();
    cbreak();
    noecho();

    clear();
}

void Update_Terminal() {
    
}

WINDOW *Init_Local_Window(WIN *win) {
    win->width = (0.8) * COLS;
    win->height = (0.6) * LINES;
    win->startx = (COLS - win->width)/2;
    win->starty = (LINES - win->height)/2;


    win->border.bb = win->border.tt = '-';
    win->border.ll = win->border.rr = '|';
    win->border.tl = win->border.tr = '+';
    win->border.bl = win->border.br = '+';
    WINDOW *local_win = newwin(win->height,win->width,win->starty,win->startx);

    //Allow for detecting function key presses when getting input in the window
    keypad(local_win,true);
    return local_win;
}

void Display_Box(WINDOW *win, WIN *win_props, bool visible) {
    int x,y,w,h;
    Border border = win_props->border;

    x = win_props->startx;
    y = win_props->starty;
    w = win_props->width;
    h = win_props->height;

    if (visible) {
        wborder(win, border.ll,border.rr,border.tt,border.bb,
            border.tl,border.tr,border.bl,border.br);
    }
    else {
        wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    }
    wrefresh(win);
}

void Display_Text(WINDOW *win,WIN *winProps, Queue *q) {
    int x = 1;
    int y = 1;
    int xMax = winProps->width - 1;
    int yMax = winProps->height - 1;
    wmove(win,y,x);
    for (int i=q->start; i<q->size; i++) {
        if (x+q->words[i].len - 1 < xMax) {
            wprintw(win,q->words[i].w);
            x+=q->words[i].len;
        }
        else {
            if (y+1 <= yMax) {
                y++;
                x = 1;
                mvwprintw(win,y,x,q->words[i].w);
                x+=q->words[i].len;
            }
        }
        q->words[i].line = y;
    }
    wmove(win,1,1);
    wrefresh(win);
}

void Exit_Terminal() {
    endwin();
}