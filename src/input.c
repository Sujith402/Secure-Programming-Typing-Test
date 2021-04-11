#include "input.h"

void Take_Input(WINDOW *win,Queue *q) {
    //ch is int as function keys return >8 bits
    int ch;
    int res;
    int word_no = 0;
    int letter = 0;
    int col = 1;
    FILE *fp = fopen("../debug.txt","a+");
    while (word_no != q->size && ( ch = wgetch(win) ) != '0') {
        if (Is_Ok(ch)) {
            if (q->words[word_no].w[letter] == ch)
                res = 1;
            else 
                res = 0;
            if (ch == KEY_DC || ch == KEY_BACKSPACE) {
                Handle_Backspace(&res,&col,&word_no,&letter, q);
                fprintf(fp,"%c\n",ch);
            }
            fprintf(fp,"%c\n",ch);
            Handle_Space( q, res, word_no, letter);
            switch(res) {
                case 0:
                    wattron(win, COLOR_PAIR(WRONG));
                    waddch(win,q->words[word_no].w[letter]);
                    wattroff(win, COLOR_PAIR(WRONG));
                    col++; letter++;
                    break;
                case 1:
                    wattron(win, COLOR_PAIR(CORRECT));
                    waddch(win,q->words[word_no].w[letter]);
                    wattroff(win, COLOR_PAIR(CORRECT));
                    col++; letter++;
                    break;
                case -1:
                    wattron(win, COLOR_PAIR(BACK));
                    mvwaddch(win,q->words[word_no].line, col,q->words[word_no].w[letter]);
                    wattroff(win, COLOR_PAIR(BACK));
                    wmove(win,q->words[word_no].line, col);
                    break;
                default:
                    break;
            }
            if (letter >= q->words[word_no].len) {
                word_no++;
                q->start = word_no;
                letter = 0;
                if (q->words[word_no-1].line != q->words[word_no].line) {
                    wmove(win,q->words[word_no].line, 1);
                    col = 1;
                }
            }
            wrefresh(win);
        }
    }
    fclose(fp);
}

void Handle_Backspace(int *res,int *col, int *word_no, int *curr, Queue *q) {
    if (*col>1) {
        (*res) = -1;
        (*col)--;
        if (*curr == 0) {
            (*word_no)--;
            *curr = q->words[*word_no].len - 1;
        }
        else {
            (*curr)--;
        }
    }
    else {
        *res = 4;
    }
}

void Handle_Space(Queue *q, int res, int word_no, int letter) {
    if (q->words[word_no].w[letter] == ' ' || q->words[word_no].w[letter] == '_') {
        if (res == 0) 
            q->words[word_no].w[letter] = '_';
        else 
            q->words[word_no].w[letter] = ' ';
    }
}

int Is_Ok(int ch) {
    if (ch>=0 && ch <=255)
        return 1;
    else if (ch == KEY_DC || ch == KEY_BACKSPACE)
        return 1;
    return 0;
}

void Init_Colour() {
    if (!has_colors()) {
        endwin();
        printf("Does not support colours\n");
        exit(1);
    }
    start_color();
    init_pair(CORRECT, COLOR_GREEN, COLOR_BLACK);
    init_pair(WRONG, COLOR_RED, COLOR_BLACK);
    init_pair(BACK, COLOR_WHITE, COLOR_BLACK);

    refresh();
}