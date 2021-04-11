#include "input.h"

void Take_Input(WINDOW *win, WIN *win_props, Queue *q) {
    //ch is int as function keys return >8 bits
    int ch,choice,word_no,letter;
    word_no = letter = 0;
    int curr_x = 1;
    int lines_done = 0;

    //Exit when F1 is pressed
    while (word_no != q->size && ( ch = wgetch(win) ) != KEY_F(1)) {
        if (Is_Ok(ch)) {
            if (q->words[word_no].w[letter] == ch)
                choice = CORRECT;
            else 
                choice = WRONG;
            if (ch == KEY_DC || ch == KEY_BACKSPACE) {
                Handle_Backspace(&choice,&curr_x,&word_no,&letter, q);
            }

            //Show that space was typed in wrong if space was the character
            Handle_Space( q, choice, word_no, letter);

            //Change colour based on choice
            switch(choice) {
                case WRONG:
                    wattron(win, COLOR_PAIR(WRONG));
                    waddch(win,q->words[word_no].w[letter]);
                    wattroff(win, COLOR_PAIR(WRONG));
                    curr_x++; letter++;
                    break;
                case CORRECT:
                    wattron(win, COLOR_PAIR(CORRECT));
                    waddch(win,q->words[word_no].w[letter]);
                    wattroff(win, COLOR_PAIR(CORRECT));
                    curr_x++; letter++;
                    break;
                case BACK:
                    wattron(win, COLOR_PAIR(BACK));
                    mvwaddch(win,q->words[word_no].line - lines_done, curr_x,q->words[word_no].w[letter]);
                    wattroff(win, COLOR_PAIR(BACK));
                    wmove(win,q->words[word_no].line - lines_done, curr_x);
                    break;
                default:
                    break;
            }

            //Move to the next word if the current one is done
            //If moving to the next line, delete the previous line as well
            if (letter >= q->words[word_no].len) {
                word_no++;
                q->start = word_no;
                letter = 0;
                if (q->words[word_no-1].line != q->words[word_no].line) {
                    lines_done++;
                    Delete_Line(win,win_props,q,word_no,lines_done);
                    wmove(win,1, 1);
                    curr_x = 1;
                }
            }
            wrefresh(win);
        }
    }
}

void Handle_Backspace(int *choice,int *curr_x, int *word_no, int *letter, Queue *q) {
    //Checks if going back does not voilate the window boundary
    //Updates which word you were at and the coresponding letter
    if (*curr_x>1) {
        (*choice) = BACK;
        (*curr_x)--;
        if (*letter == 0) {
            (*word_no)--;
            *letter = q->words[*word_no].len - 1;
        }
        else {
            (*letter)--;
        }
    }
    else {
        *choice = 4;
    }
}

void Handle_Space(Queue *q, int choice, int word_no, int letter) {
    if (q->words[word_no].w[letter] == ' ' || q->words[word_no].w[letter] == '_') {
        if (choice == WRONG) 
            q->words[word_no].w[letter] = '_';
        else 
            q->words[word_no].w[letter] = ' ';
    }
}

int Is_Ok(int ch) {
    //If key pressed is an escape sequence(a control character), wgetch()
    //returns > 255.
    if (ch>=0 && ch <=255)
        return 1;
    //Check whether delete or backspace are pressed
    else if (ch == KEY_DC || ch == KEY_BACKSPACE)
        return 1;
    return 0;
}

void Init_Colour() {
    //Check if the terminal supports colors. Exit otherwise
    if (!has_colors()) {
        endwin();
        printf("Does not support colours\n");
        exit(1);
    }

    //Star the colour module and initialise foreground,background colour pairs
    //identified by the situations where they are used
    start_color();
    init_pair(CORRECT, COLOR_GREEN, COLOR_BLACK);
    init_pair(WRONG, COLOR_RED, COLOR_BLACK);
    init_pair(BACK, COLOR_WHITE, COLOR_BLACK);

}