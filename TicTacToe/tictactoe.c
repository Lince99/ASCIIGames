#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//signatures
void draw_borders(WINDOW *screen, char cross, char side, char horiz);



int main(int argc, char *argv[]) {
    int parent_x, parent_y;
    int old_size_x, old_size_y;

    initscr();
    noecho();
    curs_set(FALSE);
    // get our maximum window dimensions
    getmaxyx(stdscr, parent_y, parent_x);
    // set up initial windows
    WINDOW *main_w = newwin(parent_y, parent_x, 0, 0);

    while(1) {
        getmaxyx(stdscr, parent_y, parent_x);
        if(old_size_x != parent_x || old_size_y != parent_y) {
            wclear(main_w);
        }
        // draw border
        draw_borders(main_w, '+', '|', '-');
        //refresh window
        wrefresh(main_w);
        old_size_x = parent_x;
        old_size_y = parent_y;
    }
    /*for(int i = 1; i <= 5; i++) {
        mvwprintw(score, 1, 2, "Time = %d", i);
        wrefresh(score);
        sleep(1);
    }*/
    // clean up
    delwin(field);
    delwin(score);

    endwin();

    return 0;
}

void draw_borders(WINDOW *screen, char cross, char side, char horiz) {
    int x, y, i;
    getmaxyx(screen, y, x);
    // 4 corners
    mvwprintw(screen, 0, 0, "%c", cross);
    mvwprintw(screen, y-1, 0, "%c", cross);
    mvwprintw(screen, 0, x-1, "%c", cross);
    mvwprintw(screen, y-1, x-1, "%c", cross);
    // sides
    for (i = 1; i < (y-1); i++) {
        mvwprintw(screen, i, 0, "%c", side);
        mvwprintw(screen, i, x-1, "%c", side);
    }
    // top and bottom
    for (i = 1; i < (x-1); i++) {
        mvwprintw(screen, 0, i, "%c", horiz);
        mvwprintw(screen, y-1, i, "%c", horiz);
    }
}
