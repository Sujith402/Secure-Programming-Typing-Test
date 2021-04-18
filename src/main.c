
#include "dummy_header.h"
#include "terminal.h"
#include "queue.h"
#include "input.h"
#include "trie.h"
#include <ncurses.h>


int main() {
    // lead to main menu from here

    int screen_no = 1;

    init_trie();
    /* printf("Done initializing the trie\n"); */

    Init_Terminal();
    Init_Colour();

    int score = 5000;

    Queue q;
    /* char *buff = Read_File("../text.txt"); */
    char buff[1000];
    generate_30_words (buff);
    Create_Queue(buff, &q);

    Text_Window_State state;
    Init_Text_Window_State(&state);

    Check_Scores("../High_Scores.txt");
    //Put under the start() function
    //Preprocessing
    while (true) {
        if (screen_no == TEXT) {
            WIN text_window_props;
            WINDOW *text_window = Init_Local_Window(&text_window_props, 0.6, 0.8);

            Determine_Line_No(&q,&text_window_props);

            //Display the box with the words
            Display_Box(text_window,&text_window_props,true);
            Display_Text(text_window,&text_window_props,&q, state.lines_done);

            Take_Input(text_window, &text_window_props, &q, &screen_no, &state);

            //wborder(text_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
            Destroy_Window(text_window);
        }

        else if (screen_no == HIGH_SCORE) {
            WIN score_window_props;
            WINDOW *score_window = Init_Local_Window(&score_window_props,0.8,0.6);
            Display_Box(score_window, &score_window_props, true);            
            //keypad(score_window,true);
            Display_Scores(score_window, &score_window_props,&screen_no);

            Destroy_Window(score_window);
        }

        else if (screen_no == USER_PROMPT) {
            WIN take_name_window_props;
            WINDOW *take_name_window = Init_Local_Window(&take_name_window_props,0.2,0.3);
            Display_Box(take_name_window, &take_name_window_props, &screen_no);

            char user_name[31];
            int flag = Update_High_Score(take_name_window,&take_name_window_props, &screen_no, user_name);
            
            if (flag)
                Update_File("../High_Scores.txt",user_name, score);
            
            Destroy_Window(take_name_window);
        }
        else {
            break;
        }
    }
        //Till here

    //The local window is automatically deallocated when Exit_Terminal is called

    Exit_Terminal();

    Destroy_Queue(&q);
    //Display_Queue(&q);
    return 0;
}
