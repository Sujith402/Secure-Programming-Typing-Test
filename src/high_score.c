#include "high_score.h"

void Display_Scores() {

    WIN score_window_props;
    WINDOW *score_window = Init_Local_Window(&score_window_props,0.8,0.6);
    Display_Box(score_window, &score_window_props, true);

}