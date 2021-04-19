#include "dummy_header.h"
#include "terminal.h"
#include "queue.h"
#include "input.h"
#include "trie.h"
#include <ncurses.h>

int main() {
    // lead to main menu from here

    init_trie();
    /* printf("Done initializing the trie\n"); */

    Init_Terminal();
    Init_Colour();

    //Put under the start() function
    //Preprocessing
    WIN text_window_props;
    WINDOW *text_window = Init_Local_Window(&text_window_props);
    Queue q;
    /* char *buff = Read_File("../text.txt"); */
    char buff[1000];
    generate_30_words (buff);
    Create_Queue(buff, &q);

    Determine_Line_No(&q,&text_window_props);

    //Display the box with the words
    Display_Box(text_window,&text_window_props,true);
    Display_Text(text_window,&text_window_props,&q, 0);

    Take_Input(text_window, &text_window_props, &q);
    //Till here

    //The local window is automatically deallocated when Exit_Terminal is called
    Exit_Terminal();

    Destroy_Queue(&q);
    //Display_Queue(&q);
    return 0;
}
