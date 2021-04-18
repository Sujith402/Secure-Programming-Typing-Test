#include "input.h"

void Init_Text_Window_State(Text_Window_State* state) {
    state->word_no = state->letter = 0;
    state->curr_x = 0;
    state->lines_done = 0;
}

void Take_Input(WINDOW *win, WIN *win_props, Queue *q, int *screen_no, Text_Window_State* state) {
    //ch is int as function keys return >8 bits
    int ch,choice;

    state->word_no = q->start;
    state->letter = 0;
    state->curr_x = 1;
    state->lines_done = 0;


    //Exit when F1 is pressed
    while (state->word_no != q->size && ( ch = wgetch(win) ) != KEY_F(1) && ch != KEY_F(2)) {

        if (Is_Ok(ch)) {
            if (q->words[state->word_no].w[state->letter] == ch)
                choice = CORRECT;
            else
                choice = WRONG;
            if (ch == KEY_DC || ch == KEY_BACKSPACE) {
                Handle_Backspace(&choice,state, q);
            }

            //Show that space was typed in wrong if space was the character
            Handle_Space( q, choice, state->word_no, state->letter);

            //Change colour based on choice
            switch(choice) {
                case WRONG:
                    wattron(win, COLOR_PAIR(WRONG));
                    waddch(win,q->words[state->word_no].w[state->letter]);
                    wattroff(win, COLOR_PAIR(WRONG));
                    state->curr_x++; state->letter++;
                    break;
                case CORRECT:
                    wattron(win, COLOR_PAIR(CORRECT));
                    waddch(win,q->words[state->word_no].w[state->letter]);
                    wattroff(win, COLOR_PAIR(CORRECT));
                    state->curr_x++; state->letter++;
                    break;
                case BACK:
                    wattron(win, COLOR_PAIR(BACK));
                    mvwaddch(win,q->words[state->word_no].line - state->lines_done, state->curr_x,q->words[state->word_no].w[state->letter]);
                    wattroff(win, COLOR_PAIR(BACK));
                    wmove(win,q->words[state->word_no].line - state->lines_done, state->curr_x);
                    break;
                default:
                    break;
            }

            //Move to the next word if the current one is done
            //If moving to the next line, delete the previous line as well
            if (state->letter >= q->words[state->word_no].len) {
                state->word_no++;
                state->letter = 0;
                if (q->words[state->word_no-1].line != q->words[state->word_no].line) {
                    q->start = state->word_no;
                    (state->lines_done)++;
                    Delete_Line(win,win_props,q,state->word_no,state->lines_done);
                    wmove(win,1, 1);
                    state->curr_x = 1;
                }
            }
            wrefresh(win);
        }
    }
    if (ch == KEY_F(2)) {
        *screen_no = 2;
    }
    else {
        *screen_no = 3;
    }
}

void Handle_Backspace(int *choice,Text_Window_State* state, Queue *q) {
    //Checks if going back does not voilate the window boundary
    //Updates which word you were at and the coresponding letter
    if (state->curr_x>1) {
        (*choice) = BACK;
        (state->curr_x)--;
        if (state->letter == 0) {
            (state->word_no)--;
            state->letter = q->words[state->word_no].len - 1;
        }
        else {
            (state->letter)--;
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
