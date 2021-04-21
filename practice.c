#include <stdio.h>
#include <ncurses.h>

int main() {
    int ch;
    char s[100],s2[100];
    char buff[200];
    fgets(buff,200,stdin);
    printf("Number scanned: %d\n",sscanf(buff, "%s %d\n%s",s,&ch,s2));
    printf("%s\n%d\n%s\n",s,ch, s2);
}