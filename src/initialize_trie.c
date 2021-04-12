#include <stdio.h>
#include <stdlib.h>
#include "Trie.h"
#include <time.h>

// TODO: 1) add support for all characters
//       2)

// function to get a random number within a particular range

int getrand (int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

// helper function to copy a word from a particular source to a destination

void copyword (char* source, char* destination, int len) {
    for (int i = 0; i < len; i++) {
        destination[i] = source[i];
    }
}


// function that creates a node and returns it

struct TrieNode * Create_Node () {
    struct TrieNode * temp = (struct TrieNode *) malloc (sizeof (struct TrieNode));

    for (int i = 0; i < NUM_CHILDREN; i++) {
        temp->child[i] = NULL;
    }

    int endofword = 0;
    return temp;
}


// function that inserts the given word into the Trie called Words

void insert_word (char *new_word, struct Trie* Words, int len) {
    struct TrieNode* current = Words->root;

    for (int i = 0; i < len; i++) {
        int ind = new_word[i];
        if (!current->child[ind]) {
            current->child[ind] = Create_Node();
        }
        current = current->child[ind];
    }

    current->endofword = 1;
}


// function that fetches a random  word from the trie

int fetch_random_word (struct Trie* Words, char* destination) {
    struct TrieNode* current = Words->root;
    if (!current) return 0;
    int possibilities[NUM_CHILDREN];
    int plen = 0;
    int found = 0;
    int len = 0;
    /* printf("Going to try fetching a word now\n"); */
    int inverse_probability = 160;

    while (!found && current) {
        plen = 0;

        for (int i = 0; i < NUM_CHILDREN; i++) {
            if (current->child[i]) {
                /* printf("First possiblility: %c\n", i); */
                possibilities[plen++] = i;
            }
        }

        if (plen == 0) {
            found = 1;
        } else {
            int index = getrand(0, plen - 1);
            /* printf("Here: %c\n", possibilities[index]); */
            destination[len++] = possibilities[index];

            if (current->child[possibilities[index]]->endofword) {
                /* printf("flipping coin\n"); */
                int coinflip = getrand (0, inverse_probability);
                if (coinflip == inverse_probability) found = 1;
            }

            /* printf("Moving to %c\n", possibilities[index]); */
            current = current->child[possibilities[index]];
            if (inverse_probability > 10) inverse_probability /= 2;
        }
    }

    return len;
}


// making two functions, that, when combined, all paths and print all words in the trie
// useful for future debugging

char word_being_printed[100];

void print_current_word (int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", word_being_printed[i]);
    }
    printf("\n");
}

void print_trie_helper (struct TrieNode* current, int ind) {
    if (!current) return;
    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (current->child[i]) {
            /* printf("Found letter %c\n", i + 'a'); */
            /* printf("Endofword Value: %d\n", current->child[i]->endofword); */
            word_being_printed[ind] = i;
            print_trie_helper (current->child[i], ind + 1);
            if (current->child[i]->endofword == 1) {
                print_current_word(ind + 1);
            }
        }
    }
}

void print_trie (struct Trie* Words) {
    print_trie_helper (Words->root, 0);
}


// this is the equivalient of main() in this program

void initialize_trie () {
    freopen ("words.txt", "r", stdin);
    srand(time(0));
    struct Trie* Words = (struct Trie* ) malloc (sizeof (struct Trie));
    Words->root = Create_Node ();

    /* getting words from file */

    char word_to_insert[100];
    char c, len = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ' || c == '.' || c == ',') {
            insert_word(word_to_insert, Words, len);
            len = 0;
        } else {
            word_to_insert[len++] = c;
        }
    }
    if (len > 0) insert_word(word_to_insert, Words, len);

    char random_word[300];

    print_trie (Words);

    /* printf("\n-----------------------------------------------------------------\n"); */
    /* for (int i = 0; i < 100; i++) { */
        /* int len = fetch_random_word(Words, random_word); */
        /* if (len) { */
            /* for (int i = 0; i < len; i++) { */
                /* printf("%c", random_word[i]); */
            /* } */
            /* printf("\n"); */
        /* } */
    /* } */
}


// will remove main in the actual application, just for testing

/* int main() { */
    /* initialize_trie(); */
/* } */
