#pragma once

#include <stdio.h>

#define MAX_WORDS 256

typedef struct word {
    char *w;
    int len;
    int line;
}Word;

typedef struct queue {
    int size; //number of words in the queue
    int start; //which index (word) to start displaying from
    Word words[MAX_WORDS]; //an array of words
}Queue;

char *Read_File( char *fileName );
void Create_Queue(char *fileName, Queue *words);
void Display_Queue(Queue *q);