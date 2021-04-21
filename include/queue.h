#pragma once

#include <stdio.h>

#define MAX_WORDS 256

typedef struct word {
    char *w;
    int len;
    int line;
}Word;

typedef struct queue {
    size_t size; //number of words in the queue
    size_t start; //which index (word) to start displaying from
    Word words[MAX_WORDS]; //an array of words
}Queue;

char *Read_File( char *fileName );
void Create_Queue(char *buffer, Queue *words);
void Destroy_Queue(Queue *q);
void Destroy_Read_Buffer(char *buff);

void Display_Queue(Queue *q);
