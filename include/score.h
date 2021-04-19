#include <time.h>
#include "stack.h"

struct Score {
    int net_WPM;
    int gross_WPM;
    int all_typed_entries;
    int uncorrected_errors;
    struct Stack* prev_entry_state;
    time_t start_time;
};
