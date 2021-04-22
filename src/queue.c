#include "queue.h"
#include "terminal.h"

//Change the arguments and stuff as well
char *Read_File(char *fileName) {
    //Reading the file and popuating the queue. Change to reading the words from the trie
    char *buff;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr,"File read failed\n");
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

        if (buff == NULL) {
            fprintf(stderr,"Memory allocation to file read buffer failed\n");
            exit(1);
        }
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
    size_t wordStart = 0;
    size_t currWord = 0;
    int i;
    for(i=0; buffer[i] != '\0'; i++) {
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

    //Change the last word. Remove the space character. 
    //Update it's length
    q->size = currWord;
    int last_word_len = q->words[currWord-1].len-1;
    q->words[currWord-1].w[last_word_len] = '\0';
    q->words[currWord-1].len = last_word_len;

}

void Destroy_Queue(Queue *q) {
    int i;
    for (i=0; i<q->size; i++) {
        free(q->words[i].w);
    }
}

void Destroy_Read_Buffer(char *buff) {
    if (buff != NULL)
        free(buff);
}

//helper func for debugging
void Display_Queue(Queue *q) {
    int i;
    for (i=0;i<q->size;i++) {
        printf("%s  %d\n",q->words[i].w,q->words[i].len);
    }
    printf("\n");
}
