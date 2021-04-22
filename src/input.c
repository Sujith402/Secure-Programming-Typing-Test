#include "input.h"
#include "terminal.h"

void Init_Text_Window_State(Text_Window_State* state) {
    state->word_no = state->letter = 0;
    state->curr_x = 0;
    state->lines_done = 0;
}

void Take_Input(WINDOW *win, WIN *win_props, WINDOW *score_window, WIN *score_window_props, Queue *q, int *screen_no, Text_Window_State* state, struct Score* score, int least_score) {
    //ch is int as function keys return >8 bits
    chtype ch;   //chtype comes from ncurses. Always is able to hold character codes.
    int choice;

    state->word_no = (int) q->start;
    state->letter = 0;
    state->curr_x = 1;
    state->lines_done = 0;


    //Exit when F1 is pressed
    while (state->word_no != (int) q->size && ( ch = (chtype) wgetch(win) ) != KEY_F(1) ) {
        if (ch == KEY_F(2) || ch == KEY_F(3) || ch == KEY_F(4))
            break;
        if (Is_Ok(ch)) {
            Display_Current_Score (score_window, score_window_props, score);
            wmove(win,q->words[state->word_no].line - state->lines_done, state->curr_x);

            if (q->words[state->word_no].w[state->letter] == (char) ch)
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
                    waddch(win, (chtype) q->words[state->word_no].w[state->letter]);
                    wattroff(win, COLOR_PAIR(WRONG));
                    state->curr_x++; state->letter++;
                    calculate_score (score, 0);
                    break;
                case CORRECT:
                    wattron(win, COLOR_PAIR(CORRECT));
                    waddch(win, (chtype) q->words[state->word_no].w[state->letter]);
                    wattroff(win, COLOR_PAIR(CORRECT));
                    state->curr_x++; state->letter++;
                    calculate_score (score, 1);
                    break;
                case BACK:
                    wattron(win, COLOR_PAIR(BACK));
                    mvwaddch(win, (int) (q->words[state->word_no].line - state->lines_done), state->curr_x, (chtype) q->words[state->word_no].w[state->letter]);
                    wattroff(win, COLOR_PAIR(BACK));
                    wmove(win, q->words[state->word_no].line - state->lines_done, state->curr_x);
                    calculate_score (score, -1);
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
                    q->start = (size_t) state->word_no;
                    (state->lines_done)++;
                    Delete_Line(win,win_props,q,state->word_no,state->lines_done);
                    wmove(win,1, 1);
                    state->curr_x = 1;
                }
            }
            wrefresh(win);
        }
    }
    if (score->net_WPM >= least_score && state->word_no == (int) q->size) {
            FILE *fp = fopen("../debug.txt","a");
            fprintf(fp,"%d\n",end_game);
            fclose(fp);
        end_game = 1;
        *screen_no = USER_PROMPT;
            fp = fopen("../debug.txt","a");
            fprintf(fp,"%d\n",end_game);
            fclose(fp);
    }
    else 
        *screen_no = switch_screen((int) ch);
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
