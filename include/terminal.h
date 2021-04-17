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

WINDOW *Init_Local_Window(WIN *win, float height, float width);

void Display_Box(WINDOW *win, WIN *win_props, bool visible);
void Determine_Line_No(Queue *q, WIN *win_props);
void Display_Text(WINDOW *win, WIN *win_props, Queue *q, int lines_done);

void Delete_Line(WINDOW *win, WIN *win_props, Queue *q, int word_no,int lines_done);

void Exit_Terminal();
