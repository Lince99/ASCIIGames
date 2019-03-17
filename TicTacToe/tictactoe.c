#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef MAX_MAT_DIM
    #define MAX_MAT_DIM 10
#endif

//signatures
WINDOW* newWindow(int* nlines, int* ncols, int y, int x);
void printGrid(WINDOW* w, int lines, int cols, int dim);
char* getName(WINDOW* w, int ncols, int n_player);



int main(int argc, char *argv[]) {
    //window params
    WINDOW* main_w;
    int nlines = 0;
    int ncols = 0;
    int y = 0;
    int x = 0;
    //user params
    int turn = 0; //odd = player0, even = player1
    int ch = 0;
    int player_y = 0;
    int player_x = 0;
    char* player0_name = NULL;
    char* player1_name = NULL;
    //matrix params
    int mat_y = 3;
    int mat_x = 0;
    if(argc > 1) {
        mat_y = atoi(argv[1]);
        if(mat_y <= 0 || mat_y >= MAX_MAT_DIM)
            mat_y = 3;
    }
    mat_x = mat_y;
    int matrix[mat_y][mat_x];

    //initialize Ncurses
    initscr();

    //create a new window
    main_w = newWindow(&nlines, &ncols, 0, 0);
    //ask for players info
    player0_name = getName(main_w, ncols, 0);
    player1_name = getName(main_w, ncols, 1);
    //draw tic tac toe static grid
    printGrid(main_w, nlines, ncols, mat_y);
    //continue the game until q is reached
    while(ch != 'q') {
        getmaxyx(main_w, nlines, ncols);

        ch = wgetch(main_w);
        /*//CHANGE BALL POSITION
        //if on top
        if(y == 0)
            direction_y = 1;
        //if on bottom
        else if(y == nlines-1)
            direction_y = 0;
        //if on left
        if(x == 0)
            direction_x = 1;
        //if on right
        else if(x == ncols-1)
            direction_x = 0;

        //CHANGE PLAYER POSITION
        wrefresh(main_w);
        ch = wgetch(main_w);
        switch(ch) {
            case 'w':
                if(player_y > 0)
                    player_y--;
                break;
            case 's':
                if(player_y < nlines-1-player_dim)
                    player_y++;
                break;
            case 'l':
                if(DELAY < SPEED_MAX_LIMIT)
                    DELAY += 1000;
                break;
            case 'p':
                if(DELAY > SPEED_MIN_LIMIT)
                    DELAY -= 1000;
                break;
            case 'q':
                mvwprintw(main_w, 0, 0, "Quitting...");
                wgetch(main_w);
                break;
            default:
                break;
        }
        wattron(main_w, A_BOLD);
        mvwprintw(main_w, player_y, player_x, "#");
        mvwprintw(main_w, player_y+1, player_x, "#");
        mvwprintw(main_w, player_y+2, player_x, "#");
        wattroff(main_w, A_BOLD);
        //check collision
        if(x == player_x) {
            if(y == player_y || y == player_y-1 || y == player_y-2) {
                collision = 1;
                direction_x = !direction_x;
            }
            else
                collision = 0;
        }
        else
            collision = 0;

        //move cursor
        if(direction_y)
            y++;
        else
            y--;
        if(direction_x)
            x++;
        else
            x--;
        mvwprintw(main_w, y, x, "%c", ball);

        mvwprintw(main_w, nlines-2, ncols-20, "y=%d x=%d delay=%d", y, x, (int)DELAY/1000);
        if(collision)
            mvwprintw(main_w, nlines-1, ncols-10, "COLLISION");
        */
        //update window content
        wrefresh(main_w);
        wclear(main_w);
    }

    //free Ncurses window
    delwin(main_w);
    //stop Ncurses
    endwin();

    return 0;
}

/*
 * initscr() MUST have been already called
 */
WINDOW* newWindow(int* lines, int* cols, int y, int x) {
    WINDOW* w = NULL;
    int nlines = *lines;
    int ncols = *cols;

    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    w = newwin(nlines, ncols, y, x);

    //cbreak();
    raw();
    nodelay(w, 1);
    keypad(w, 1);
    curs_set(0);
    noecho();

    return w;
}

void printGrid(WINDOW* w, int lines, int cols, int dim) {
    int y = 0;
    int x = 0;
    int line_div = 0;
    int col_div = 0;

    /*
        |   |
     ---+---+---
        |   |
     ---+---+---
        |   |
    */

    if(w == NULL)
        return;
    wmove(w, 0, 0);
    line_div = (int)lines/dim;
    col_div = (int)cols/dim;

    for(y = 0; y < lines; y++) {
        for(x = 0; x < cols; x++) {
            if((int)x%dim == 0)
                mvwprintw(w, y, x, "|");
            if((int)y%dim == 0)
                mvwprintw(w, y, x, "-");
            if(x == y)
                mvwprintw(w, y, x, "+");
        }
    }
    wrefresh(w);

}

char* getName(WINDOW* w, int ncols, int n_player) {
    char* name = NULL;

    if(w == NULL)
        return NULL;
    mvwprintw(w, 0, 0, "Insert Player #%d name:", n_player);
    wmove(w, 1, 0);
    wgetnstr(w, name, (int)(ncols/2)-3);
    wclear(w);
    wrefresh(w);

    return name;
}
