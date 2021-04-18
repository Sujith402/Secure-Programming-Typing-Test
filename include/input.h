#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>

#include "high_score.h"


#define WRONG 1
#define CORRECT 2
#define BACK 3

typedef struct text_window_state {
    int word_no, letter;
    int curr_x;
    int lines_done;
}Text_Window_State;

void Init_Text_Window_State(Text_Window_State* state);
void Take_Input(WINDOW *win, WIN *win_props, Queue *q, int *screen_no, Text_Window_State* state);
void Handle_Backspace(int *res,Text_Window_State* state, Queue *q);
void Handle_Space(Queue *q, int res, int word_no, int letter);
void Init_Colour();