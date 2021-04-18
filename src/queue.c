#include "queue.h"
#include "terminal.h"

//Change the arguments and stuff as well
char *Read_File(char *fileName) {
    //Reading the file and popuating the queue. Change to reading the words from the trie
    char *buff;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        return NULL;
    }
    if (fseek(fp, 0L , SEEK_END) == 0) {
        long buffSize = ftell(fp);
        if (buffSize == -1)
            exit(1);
        if (fseek(fp, 0L, SEEK_SET) != 0) {
            fprintf(stderr,"Error in reading file");
            exit(1);
        }

        buff = (char *)malloc(sizeof(char) * (buffSize + 1));

        size_t newLen = fread(buff, sizeof(char), buffSize, fp);
        if (newLen == 0) {
            free(buff);
            return NULL;
        }
        if (ferror(fp) != 0) {
            fprintf(stderr, "Error in reading file");
            exit(1);
        }
        buff[newLen++] = '\0';
    }
    fclose(fp);
    return buff;
}

void Create_Queue(char *buffer, Queue *q) {
    q->start = 0;
    q->size = 0;
    int wordStart = 0;
    int currWord = 0;

    for (int i=0; buffer[i] != '\0'; i++) {
        //Check if max words have been read
        //Stop reading if that is the case
        if (currWord == MAX_WORDS)
            break;

        while(buffer[i] != ' ' && buffer[i] != '\0' && buffer[i] != '\n') i++;
        q->words[currWord].len = i-wordStart + 1;
        q->words[currWord].w = malloc(sizeof(char) * ( q->words[currWord].len + 1 ));
        strncpy(q->words[currWord].w, &buffer[wordStart], q->words[currWord].len-1);
        q->words[currWord].w[q->words[currWord].len-1] = ' ';
        q->words[currWord].w[q->words[currWord].len] = '\0';
        currWord++;
        wordStart = i+1;
    }

    //Change the last word. Remove the space character and reallocate the right
    //amount of memory. Update it's length
    q->size = currWord;
    int len = q->words[currWord-1].len-1;
    q->words[currWord-1].w = realloc(q->words[currWord-1].w,sizeof(char) * (len + 1));
    q->words[currWord-1].w[len] = '\0';
    q->words[currWord-1].len = len;

    //Free the memory allocated to the buffer
    //free(buffer);
}

void Destroy_Queue(Queue *q) {
    for (int i=0; i<q->size; i++) {
        free(q->words[i].w);
    }
}

//helper func for debugging
void Display_Queue(Queue *q) {
    for (int i=0;i<q->size;i++) {
        printf("%s  %d\n",q->words[i].w,q->words[i].len);
    }
    printf("\n");
}
