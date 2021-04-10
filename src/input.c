#include "input.h"

void Take_Input(WINDOW *win,Queue *q) {
    char ch;
    int res;
    int word_no = 0;
    int curr = 0;
    while (word_no != q->size && ( ch = getch() ) != '0') {
        if (q->words[word_no].w[curr] == ch)
            res = 1;
        else 
            res = 0;
        switch(res) {
            case 0:
                wattron(win, COLOR_PAIR(WRONG));
                waddch(win,q->words[word_no].w[curr]);
                wattroff(win, COLOR_PAIR(WRONG));
                break;
            case 1:
                wattron(win, COLOR_PAIR(CORRECT));
                waddch(win,q->words[word_no].w[curr]);
                wattroff(win, COLOR_PAIR(CORRECT));
                break;
        }
        wrefresh(win);
        curr++;
        if (curr >= q->words[word_no].len) {
            word_no++;
            q->start = word_no;
            curr = 0;
            if (q->words[word_no-1].line != q->words[word_no].line) {
                wmove(win,q->words[word_no].line, 1);
            }
        }
    }
}

void Init_Colour() {

    start_color();
    init_pair(CORRECT, COLOR_GREEN, COLOR_BLACK);
    init_pair(WRONG, COLOR_RED, COLOR_BLACK);
}