#include <stdio.h>
#include "score.h"

struct Score* init_score () {
    struct Score* score = (struct Score*) malloc (sizeof (struct Score));

    score->all_typed_entries = 0;
    score->gross_WPM = 0;
    score->net_WPM = 0;
    score->start_time = time(0);
    score->uncorrected_errors = 0;
    score->correct_entries = 0;
    score->accuracy = 0;
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
            if (pop(current_score->prev_entry_state) == 0) {
                current_score->uncorrected_errors--;
            }
            break;
        case 1:
            current_score->all_typed_entries++;
            current_score->correct_entries++;
            push (current_score->prev_entry_state, 1);
            break;
    }

    float time_taken = (float) (time(0) - current_score->start_time) / 60.0;
    float denominator = (float) 5 * time_taken;
    float gross_WPM = (float) current_score->all_typed_entries / denominator;
    float net_WPM = gross_WPM - (float) (current_score->uncorrected_errors / time_taken);
    float accuracy = ((float) current_score->correct_entries / (float) current_score->all_typed_entries);

    current_score -> gross_WPM = gross_WPM;
    current_score -> net_WPM = net_WPM;
    if (current_score->net_WPM < 0) current_score->net_WPM = 0;
    current_score -> accuracy = accuracy * 100.0;

    /* print_score (current_score); */

    return current_score;
}

// displays the score onto the terminal
void print_score (struct Score* score) {
    printf("All typed entries: %d\tUncorrected Errors: %d\n", score->all_typed_entries, score->uncorrected_errors);
    printf("Gross WPM: %d\tNet WPM: %d\tAccuracy: %d\n", score->gross_WPM, score->net_WPM, score->accuracy);
    printf("Start time: %ld\n", score->start_time);
    printf("End time: %ld\n", time(0));
    printf("Correct Entries: %d\n", score->correct_entries);
}

void print_stack (struct Score* score) {
    int x;
    printf("Printing Stack: ");

    while ((x = pop (score->prev_entry_state)) != -1) {
        printf("%d ", x);
    }

    printf("\n");
}
