#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trie.h"
#include "queue.h"

// function to get a random number within a particular range
int getrand (int a, int b) {
    return (rand() % (b - a + 1)) + a;
}


// helper function to copy a word from a particular source to a destination
void copyword (char* source, char* destination, int len) {
    for (size_t i = 0; i < len; i++) {
        destination[i] = source[i];
    }
}


// function that creates a node and returns it
struct TrieNode * Create_Node () {
    struct TrieNode * temp = (struct TrieNode *) malloc (sizeof (struct TrieNode));

    if (!temp) {
        fprintf (stderr, "Failed to allocate memory for a Node\n");
        exit(1);
    } else {
        for (size_t i = 0; i < NUM_CHILDREN; i++) {
            temp->child[i] = NULL;
        }
        int endofword = 0;

        return temp;
    }
}


// function that inserts the given word into the Trie called Words
void insert_word (char *new_word, struct Trie* Words, int len) {
    struct TrieNode* current = Words->root;

    for (size_t i = 0; i < len; i++) {
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
    int inverse_probability = 160;  // used to ensure that words are of reasonable length on average

    while (!found && current) {
        plen = 0;

        for (int i = 0; i < NUM_CHILDREN; i++) {
            if (current->child[i]) {
                possibilities[plen++] = i;
            }
        }

        if (plen == 0) {
            found = 1;
        } else {
            int index = getrand(0, plen - 1);
            destination[len++] = possibilities[index];

            if (current->child[possibilities[index]]->endofword) {
                int coinflip = getrand (0, inverse_probability); // flipping a coin to figure out if we want to end our search here
                if (coinflip == inverse_probability) found = 1;
            }

            current = current->child[possibilities[index]];
            if (inverse_probability > 10) inverse_probability /= 2;
        }
    }

    return len;
}


// generates 50 words and stores them into a buffer
void generate_50_words (char* buffer) {
    int bufptr = 0;
    char current_word[50];
    for (int i = 0; i < 50; i++) {
        int len = 0;
        while (!len) {
            len = fetch_random_word (Words, current_word);
        }
        if (bufptr + len < MAX_BUFFER_SIZE) {
            for (int j = 0; j < len; j++) {
                buffer[bufptr++] = current_word[j];
            }
            buffer[bufptr++] = ' ';
        }
    }
    buffer[bufptr] = '\0';
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

void print_trie () {
    print_trie_helper (Words->root, 0);
}


// this is the equivalient of main() in this program
void init_trie () {

    // read stuff from file

    char* buffer = Read_File ("../words.txt");
    if (!Check_Words(buffer)) {
        fprintf(stderr, "Words.txt not right format");
        exit(1);  //error. Handle this.
    }

    if (buffer == NULL) {
        fprintf(stderr,"Error in reading words.txt\n");
        exit(1);   //error. Handle this
    }

    srand(time(0));

    Words = (struct Trie* ) malloc (sizeof (struct Trie));
    if (!Words) {
        fprintf (stderr, "Failed to initialise trie\n");
        exit (1);
    }

    Words->root = Create_Node ();

    /* getting words from file */

    char word_to_insert[100];
    char c, len = 0;
    int bufptr = 0;

    while (buffer[bufptr]) {
        c = buffer[bufptr];
        if (c == '\n' || c == ' ' || c == '.' || c == ',') {
            insert_word(word_to_insert, Words, len);
            len = 0;
        } else {
            word_to_insert[len++] = c;
        }
        bufptr++;
    }
    if (len > 0) insert_word(word_to_insert, Words, len);

    Destroy_Read_Buffer(buffer);

    /* char random_word[300]; */

    //print_trie ();
}

bool Check_Words(char *buffer) {
    for (size_t i = 0; buffer[i] != '\0';) {
        while(buffer[i] != '\0' && (isalnum(buffer[i]) || buffer[i] == '\'')) i++;
        if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == ',' || buffer[i] == '.')
            i++;
        else
            return 0;
    }
    return 1;
}

void destroy_children (struct TrieNode* current) {
    if (!current) return;

    for (size_t i = 0; i < 256; i++) {
        if (current->child[i]) {
            destroy_children (current->child[i]);
        }
    }

    free (current);
    return;
}

// recursively frees memory allocated for the trie and its nodes
void destroy_trie (struct Trie* Words) {
    if (!Words) return;
    struct TrieNode* root = Words->root;
    destroy_children (Words->root);
    free (Words->root);
    free (Words);
}

