#include <time.h>
#include "stack.h"

struct Score {
    int net_WPM;
    int gross_WPM;
    int all_typed_entries;
    int uncorrected_errors;
    int correct_entries;
    int accuracy;
    struct Stack* prev_entry_state;
    time_t start_time;
};

struct Score* init_score ();
struct Score* calculate_score (struct Score* current_score, int choice);
void print_score (struct Score* score);
void print_stack (struct Score* score);
