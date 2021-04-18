#include "terminal.h"

typedef struct entry{
    char name[30];
    int score;
}Entry;

void Display_Scores(WINDOW *win, WIN *win_props, int *screen_no);

