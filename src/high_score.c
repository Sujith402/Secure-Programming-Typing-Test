#include "high_score.h"

//update the entries with the necessary info
//buffer has already been sanitized so no checks are performed here
int Initialize_Entries(Entry *entries, char *buff) {
    int start = 0,curr_entry = 1;
    size_t max_size;

    strcpy(entries[0].name,"NAMES");
    strcpy(entries[0].score, "SCORES");

    if (buff != NULL) {
        for (size_t i=0;curr_entry != MAX_HIGH_SCORE_ENTRIES && buff[i] != '\0'; i++) {
            while ( buff[i] != '\0' && buff[i]!=' ' && buff[i] != '\n') i++;
            if (buff[i] == ' ') {
                max_size = i-start > 30 ? 30 : i-start;
                strncpy(entries[curr_entry].name, &buff[start], max_size);
                entries[curr_entry].name[max_size] = '\0';
            }
            else if (buff[i] == '\n') {
                max_size = i-start > 10 ? 10 : i-start;
                strncpy(entries[curr_entry].score, &buff[start], max_size);
                entries[curr_entry].score[max_size] = '\0';
                curr_entry++;
            }
            start = i+1;
        }
    }
    return curr_entry;
}

//Read the high_scores file and make the entries. Display onto high_score window
void Display_Scores(WINDOW *win, WIN *win_props, int *screen_no) {

    int ch;
    wmove(win,1,1);
    wrefresh(win);

    char *buff = Read_File("../High_Scores.txt");

    Entry entries[MAX_HIGH_SCORE_ENTRIES];

    int max_entries = Initialize_Entries(entries,buff); 

    int x = (win_props->width - strlen("High Scores"))/2;
    mvwprintw(win,1,x,"HIGH SCORES");

    int y = 2;
    for (int i=0; i<max_entries && y!=win_props->height - 1; i++) {
        print_entry(win,win_props,y,entries[i]);
        y++;
    }
    wrefresh(win);

    while ((ch = wgetch(win)) != KEY_F(1) && ch != KEY_F(2) && ch != KEY_F(3) && ch != KEY_F(4)) {

    }

    *screen_no = switch_screen(ch);

    Destroy_Read_Buffer(buff);
}

//Change the current screen number (used in main to actually change screen)
int switch_screen(int ch) {
    int screen_no;
    switch(ch) {
        case KEY_F(1):
            screen_no = TEXT;
            break;
        case KEY_F(2):
        case ENTER_KEY:
            screen_no = HIGH_SCORE;
            break;
        case KEY_F(3):
            screen_no = USER_PROMPT;
            break;
        default:
            screen_no = EXIT;
            break;
    }
    return screen_no;
}

//Ask for username input
//Does not take function keys except F1, F2, F3, F4, enter
int Update_High_Score(WINDOW *win, WIN *win_props, int *screen_no, char *name) {
    chtype ch;
    int curr_x = 2;
    int y = (win_props->height - 3)/2 + 2;
    int word_length = 0;
    bool flag = 0;  //whether update_file is called or not
    wmove(win,1,1);
    wprintw(win,"Enter user name: ");
    wmove(win,y,curr_x);

    while ((ch = wgetch(win)) != KEY_F(1) && ch != KEY_F(2) && ch != KEY_F(3) && ch != KEY_F(4)) {
        if (ch == ENTER_KEY) {
            if (word_length!=0){
                flag = 1;
                break;
            }
        }
        else if (Is_Ok(ch)) {
            if (ch == KEY_BACKSPACE || ch == KEY_DC) {
                if (curr_x > 2) {
                    curr_x--;
                    mvwaddch(win,y,curr_x,' ');
                    wmove(win,y,curr_x);
                    word_length--;
                }
            }
            else if (curr_x - 2 <= MAX_USER_NAME_LENGTH){
                waddch(win, ch);
                if (ch != ' ')
                    name[word_length++] = ch;
                else 
                    name[word_length++] = '_';
                curr_x++;
            }
        }
    }

    name[word_length] = '\0';

    *screen_no = switch_screen(ch); 
    return flag;
}

void Update_File(char *fileName, char *user_name, int score) {
    char *buff = Read_File(fileName);

    long int curr_score;
    size_t start;
    size_t i = 0;
    char temp;

    FILE* fp = fopen(fileName,"w+");

    //adding user as 1st entry
    if (buff == NULL || buff[i] == '\0') {
        fprintf(fp,"%s %d\n",user_name,score);
        fclose(fp);
        return;
    }

    //check each users' scores
    //go to line where the file score is lesser than the player score
    //add line
    for (i=0; buff[i] != '\0'; i++) {
        start = i;
        while ( buff[i] != '\0' && buff[i]!=' ' && buff[i] != '\n') i++;
        if (buff[i] == ' ') {
            curr_score = 0;
            i++;
            while (buff[i] != '\n' && buff[i] != '\0'){
                //check for integer overflow
                if (curr_score <= ( INT32_MAX - (buff[i]- '0') )/10) {
                    curr_score = curr_score *10 + buff[i] - '0';
                }
                else {
                    //add in something here. For now it just doesn't take the other integers
                    //into account
                }
                i++;
            }
            if (score >= curr_score) {
                temp = buff[start];
                buff[start] = '\0';

                if (start != 0)
                    fprintf(fp,"%s",buff);
                fprintf(fp,"%s %d\n",user_name,score);

                buff[start] = temp;
                fprintf(fp,"%s",&buff[start]);

                fclose(fp);
                Destroy_Read_Buffer(buff);
                return;
            }
        }
        
    }

    //adding an entry as the last line to the file
    fprintf(fp,"%s",buff);
    fprintf(fp,"%s %d\n",user_name,score);
    fclose(fp);
    Destroy_Read_Buffer(buff);

}

bool Is_Ok(chtype ch) {
    //If key pressed is an escape sequence(a control character), wgetch()
    //returns > 255.
    if (ch>=0 && ch <=255)
        return 1;
    //Check whether delete or backspace are pressed
    else if (ch == KEY_DC || ch == KEY_BACKSPACE)
        return 1;
    return 0;
}

//add in lines in high_score window
void print_entry(WINDOW *win, WIN* win_props, int y, Entry curr_entry) {

    int x = 1 + (win_props->width/2 - strlen(curr_entry.name))/2;
    mvwprintw(win,y,x,curr_entry.name);

    x = win_props->width/2 + (win_props->width/2 - strlen(curr_entry.score))/2;

    
    mvwprintw(win,y,x,curr_entry.score);

}

//High Score input sanitization
//Delete the file and create a new one if it is not in proper format
void Check_Scores(char *fileName) {
    FILE* fp = fopen(fileName,"r");
    int max_line_size = 45;
    char buffer[max_line_size];
    char temp_buff[45];
    int score;
    if (fp == NULL) {
        fp = fopen(fileName,"w");
        fclose(fp);
        return;
    }
    while (fgets(buffer,max_line_size,fp) != NULL) {
        if (sscanf(buffer,"%s %d %s\n",temp_buff,&score,temp_buff) != 2){
            fclose(fp);
            fp = fopen(fileName,"w+");
            //fprintf(fp,"%d\n",sscanf(buffer,"%s %d\n",temp_buff,&score));
            fclose(fp);
            break;
        }
    }
}
