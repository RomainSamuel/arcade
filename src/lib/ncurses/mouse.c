#include <ncurses.h>
#include <stdio.h>
 
int main()
{
    char   buffer[1024];
    MEVENT event;
    int    c;
 
    initscr();
    cbreak();
    noecho();
    curs_set(0); /* Invisible cursor */
    halfdelay(1); /* Don't wait for more than 1/10 seconds for a keypress */
    keypad(stdscr, TRUE); /* Enable keypad mode */
    mousemask(BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED, NULL);
 
    while (1) {
 
        c = wgetch(stdscr);
 
        printf("coucou\n");
        /* Enter or newline exits the program. */
        if (c == '\r' || c == '\n')
            break;
 
        /* No event? */
        if (c == ERR)
            sprintf(buffer, "Nothing happened.");
        else
        if (KEY_MOUSE == c) {
            /* Mouse event. */
            if (OK == getmouse(&event))
                sprintf(buffer, "Mouse at row %3d, column %3d: 0x%08lx", event.y, event.x, (unsigned long)event.bstate);
            else
                sprintf(buffer, "Bad mouse event.");
        } else
            sprintf(buffer, "Key '%s' (0x%04x = %d) pressed.", keyname(c), c, c);
     }
 
    endwin();
 
    return 0;
}
