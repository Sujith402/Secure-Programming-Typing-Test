#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>

#include "queue.h"

#define CORRECT 2
#define WRONG 1
#define BACK 3


void Take_Input(WINDOW *win, Queue *q);
void Handle_Backspace(int *res,int *col, int *word_no, int *curr, Queue *q);
void Handle_Space(Queue *q, int res, int word_no, int letter);
int Is_Ok(int ch);
void Init_Colour();