#pragma once

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "queue.h"

typedef struct BORDER {
   chtype tl,tr,bl,br,ll,rr,bb,tt;
}Border;

typedef struct WIN {
    int startx, starty;
    int width, height;
    Border border;
}WIN;


void Init_Terminal();

WINDOW *Init_Local_Window(WIN *win);
void Display_Box(WINDOW *win, WIN *win_props, bool visible);
void Display_Text(WINDOW *win, WIN *win_props, Queue *q);

void Change_Colour();
void print_line(WINDOW *win, int starty, int startx, int width, char *str);

void Exit_Terminal();
