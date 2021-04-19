#include <stdio.h>
#include "score.h"

struct Score* init_score () {
    struct Score* score;
    score->all_typed_entries = 0;
    score->gross_WPM = 0;
    score->net_WPM = 0;
    score->start_time = time(0);
    score->uncorrected_errors = 0;
    score->prev_entry_state = init_stack();
    return score;
}

struct Score* calculate_score (struct Score* current_score, int choice) {
    switch (choice) {
        case 0:                 // wrong
            current_score->all_typed_entries++;
            current_score->uncorrected_errors++;
            push (current_score->prev_entry_state, 0);
            break;
        case -1:
            current_score->all_typed_entries--;
            if (pop(current_score->prev_entry_state) == 0) {
                current_score->uncorrected_errors--;
            }
            break;
        case 1:
            current_score->all_typed_entries++;
            push (current_score->prev_entry_state, 1);
            break;
    }
    float denominator = (float) 5 * (time(0) - current_score->start_time);
    current_score -> gross_WPM = current_score->all_typed_entries / denominator;
    current_score -> net_WPM = current_score->gross_WPM - (current_score->uncorrected_errors / (denominator * 5));
    return current_score;
}
