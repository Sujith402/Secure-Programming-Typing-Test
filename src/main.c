#include "dummy_header.h"
#include "terminal.h"
#include "queue.h"
#include "input.h"
#include <ncurses.h>


int main() {
    // lead to main menu from here

    Init_Terminal();
    Init_Colour();

    //Put under the start() function
    WIN text_window_props;
    WINDOW *text_window = Init_Local_Window(&text_window_props);
    Display_Box(text_window,&text_window_props,true);
    Queue q;
    char *buff = Read_File("../text.txt");
    Create_Queue(buff, &q);
    Display_Text(text_window,&text_window_props,&q);
    
    Take_Input(text_window, &q);
    //Till here

    Exit_Terminal();
    
    //Display_Queue(&q);
    return 0;
}
