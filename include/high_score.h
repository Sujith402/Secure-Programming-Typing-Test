#include "terminal.h"

#define TEXT 1
#define HIGH_SCORE 2
#define USER_PROMPT 3
#define EXIT 4

#define ENTER_KEY 10

typedef struct entry{
    char name[31];
    char score[11];
}Entry;

int Initialize_Entries(Entry *entries, char *buff);
void Display_Scores(WINDOW *win, WIN *win_props, int *screen_no);

int switch_screen(int ch);
int Update_High_Score(WINDOW *win, WIN *win_props, int *screen_no, char *name);
int Is_Ok(int ch);

void Update_File(char *fileName, char *user_name, int score); 
    
void print_entry(WINDOW *win, WIN* win_props, int y, Entry curr_entry);
void Check_Scores(char* fileName);

