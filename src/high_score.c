#include "high_score.h"

void Display_Scores(WINDOW *win, WIN *win_props, int *screen_no) {

    int ch;
    wmove(win,1,1);
    wrefresh(win);

    char *buff = Read_File("../High_Scores.txt");

    if (buff == NULL) {
        fprintf(stderr, "High Scores file does not exist");
        exit(1);
    }

    /*int start = 0,j;
    int max_size;
    Entry entries[50];

    for (int i=0; buff[i] != '\0'; i++) {
        while ( buff[i] != '\0' && buff[i]!=' ' && buff[i] != '\n') i++;
        if (buff[i] == ' ') {
            max_size = i-start > 30 ? 30 : i-start;
            strncpy(entries[j].name, &buff[start], max_size);
        }
        else if (buff[i] == '\n') {
            entries[j].score = 0;
            for (int k=start; k<i; k++) {
                entries[j].score = entries[j].score * 10 + (buff[k] - '0');
            }
        }
        start = i+1;
    }*/

    while (true) {
        ch = wgetch(win);
        if (ch == KEY_F(1)){
            *screen_no = 3;
            break;
        }
        else if (ch == KEY_F(2)){
            *screen_no = 1;
            break;
        }
    }

    free(buff);
}