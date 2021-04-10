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
    int x = 0;
    int y = 0;
    int xMax = winProps->width - 1;
    int yMax = winProps->height - 1;
    wmove(win,1,1);
    for (int i=q->start; i<q->size; i++) {
        if (x+q->words[i].len - 1 < xMax) {
            wprintw(win,q->words[i].w);
            x+=q->words[i].len;
        }
        else {
            if (y+1 <= yMax) {
                y+=2;
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



//To use later
//void Change_Colour() {
//    if (!has_colors()) {
//        endwin();
//        printf("Does not support colours\n");
//        exit(1);
//    }
//    start_color();
//    init_pair(1,COLOR_RED,COLOR_BLACK);
//    attron(COLOR_PAIR(1));
//    print_line(stdscr, 10, 0, COLS, "Coloured line");
//    attroff(COLOR_PAIR(1));
//
//}

void print_line(WINDOW *win, int starty, int startx, int width, char *str) {
    int length;
    float offset;

    length = strlen(str);
    offset = (width - length)/2;
    int x = startx + (int) offset;
    mvwprintw(win, starty, x, "%s", str);
    refresh();
}

void Exit_Terminal() {
    endwin();
}