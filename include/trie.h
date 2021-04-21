#include<ctype.h>
#include<stdbool.h>

#define NUM_CHILDREN 256
#define MAX_BUFFER_SIZE 1000

struct TrieNode {
    struct TrieNode* child[NUM_CHILDREN];
    int endofword;
};

struct Trie {
    struct TrieNode* root;
} *Words;

int fetch_random_word (struct Trie* Words, char* destination);

void init_trie ();

void generate_50_words (char* buffer);

bool Check_Words(char * buffer);
