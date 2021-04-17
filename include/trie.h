#define NUM_CHILDREN 256

struct TrieNode {
    struct TrieNode* child[NUM_CHILDREN];
    int endofword;
};

struct Trie {
    struct TrieNode* root;
} *Words;

int fetch_random_word (struct Trie* Words, char* destination);

void init_trie ();

void generate_30_words (char* buffer);
