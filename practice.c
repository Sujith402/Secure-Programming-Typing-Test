#include <stdio.h>
#include <ncurses.h>

int main() {
    char c;
    initscr();
    cbreak();
    c = getch();
    printf("Entered character is: %c\n",c);
    getch();
    endwin();
}