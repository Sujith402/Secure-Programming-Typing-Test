#define NUM_CHILDREN 256

struct TrieNode {
    struct TrieNode* child[NUM_CHILDREN];
    int endofword;
};

struct Trie {
    struct TrieNode* root;
};

int fetch_random_word (struct Trie* Words, char* destination);

void initialize_trie ();
