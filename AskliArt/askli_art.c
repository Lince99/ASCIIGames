/* Copyright (C) 2019 Lince99
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see http://www.gnu.org/licenses .
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "include/queue_char.h"
#include "include/curses_manager.h"
#include "include/ascii_matrix.h"

//signatures
void welcome_message(WINDOW*);
void print_info(WINDOW*, char*, int, int, int, bool);

//globals
unsigned int TERM_MIN_Y = 11;
unsigned int TERM_MIN_X = 37;
unsigned short int TERM_HAS_COLORS = 0;
unsigned short int TAB_COUNT = 4;



int main(int argc, char *argv[]) {
    WINDOW *main_w;
    q_char* queue = NULL;
    q_char* move_queue = NULL;
    int ncols = 0;
    int nlines = 0;
    int x = 0;
    int y = 0;
    unsigned short int in_mode = 0;
    //user input var
    int ch = 0;
    int usr_req = 0;
    char* usr_str = NULL;
    int** matrix = NULL;
    int mat_y = 0;
    int mat_x = 0;

    //initialize Ncurses
    initscr();
    //initialize color pairs
    TERM_HAS_COLORS = init_colors();

    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);
    //Minimum terminal size requirement
    if(ncols < TERM_MIN_Y || nlines < TERM_MIN_X) {
        mvwprintw(main_w, 0, 0, "TOO SMALL!");
        endwin();
        return 2;
    }
    welcome_message(stdscr);
    //initiate input settings
    raw();
    nonl();
    keypad(main_w, 1);
    nodelay(main_w, 0); //1 for more responsive but cpu intensive
    intrflush(main_w, 0); //1 to inherit from tty drive
    curs_set(1);
    draw_borders(main_w);
    //start cursor position
    y = (int)nlines/2;
    x = (int)ncols/2;
    wmove(main_w, y, x);
    //init ascii art matrix
    mat_y = nlines-1;
    mat_x = ncols-1;
    matrix = init_matrix(mat_y, mat_x);
    //error on malloc
    if(matrix == NULL) {
        print_info(main_w, "Error on canvas alloc!", 0, 0, 1, TRUE);
        endwin();
        return 1;
    }

    //program run forever until user press CTRL+q
    while(1) {
        //get the user input
        ch = wgetch(main_w);
        //if no input (or nodelay set to 1 will return ERR after a while)
        if(ch == ERR) {
            usleep(25000);
            continue;
        }

        //resize the window UNCOMMENT THIS IF KEY_RESIZE doesn't work
        //getmaxyx(stdscr, nlines, ncols);

        switch(ch) {
            //detect quit command
            case CTRL('q'):
                wclear(main_w);
                wattr_on(main_w, COLOR_PAIR(1), NULL);
                draw_borders(main_w);
                wattr_off(main_w, COLOR_PAIR(1), NULL);
                //ask the user if he/she's sure to quit
                print_info(main_w, "Confirm exit? [Y/n]", 1, 1, 3, TRUE);
                if(!is_void_matrix(matrix, mat_y, mat_x))
                    print_info(main_w, "WARNING: unsaved Data!", 2, 2, 1, TRUE);
                wrefresh(main_w);
                usr_req = mvwgetch(main_w, 1, 21);
                if(usr_req == 'Y' || usr_req == 'y') {
                    //free Ncurses window
                    delwin(main_w);
                    //free undo and redo queue
                    freeQ_char(queue);
                    //free ascii matrix
                    free_matrix(matrix, mat_y);
                    //stop Ncurses
                    endwin();
                    //and exit from program
                    return 0;
                }
                wclear(main_w);
                break;

            //return to start coordinates
            case KEY_HOME:
                x = 1;
                y = 1;
                break;

            //goes to bottom right
            case KEY_END:
                x = mat_y;
                y = mat_x;
                break;

            //Up Arrow
            case KEY_UP:
                if(y-1 >= 1)
                    y--;
                break;
            //Down Arrow or enter
            case KEY_DOWN:
                if(y+1 < nlines-1)
                    y++;
                break;
            //Left Arrow or backspace
            case KEY_LEFT:
                if(x-1 >= 1)
                    x--;
                break;
            //Right Arrow
            case KEY_RIGHT:
                if(x+1 < ncols-1)
                    x++;
                break;

            //tab will do the same as KEY_RIGHT, but for TAB_COUNT times
            case CTRL('i'):
                for(int tab_c = 0; tab_c < TAB_COUNT-1; tab_c++) {
                    if(x+1 < ncols-1)
                        x++;
                    else
                        break;
                }
                break;

            //shift+tab will do the same as KEY_LEFT, but for TAB_COUNT times
            case KEY_BTAB:
                for(int tab_c = 0; tab_c < TAB_COUNT-1; tab_c++) {
                    if(x-1 >= 1)
                        x--;
                    else
                        break;
                }
                break;

            //shift+home returns at the start of the line
            case KEY_SHOME:
                x = 1;
                break;

            //shift+end geos at the end of the line
            case KEY_SEND:
                x = mat_x;
                break;

            //backspace will do the same as KEY_LEFT
            case KEY_BACKSPACE:
                if(x-1 >= 1)
                    x--;
                break;

            //window resize management
            case KEY_RESIZE:
                getmaxyx(main_w, nlines, ncols);
                if(y >= nlines-1)
                    y = nlines-1;
                if(x >= ncols-1)
                    y = ncols-1;
                wclear(main_w);
                draw_borders(main_w);
                //update ascii matrix size (only bigger, not smaller)
                if(nlines-1 > mat_y)
                    matrix = resize_matrix(matrix, &mat_y, &mat_x,
                                                   nlines-1, mat_x);
                if(ncols-1 > mat_x)
                    matrix = resize_matrix(matrix, &mat_y, &mat_x,
                                                   mat_y, ncols-1);
                break;

            //change input mode (from sequential to insert)
            case CTRL('m'):
                if(in_mode == 0) //insert in the same position (require arrows to move left)
                    in_mode = 1;
                else if(in_mode == 1) //sequential insertion mode (after 1 char, move to left)
                    in_mode = 0;
                break;

            //undo
            case CTRL('z'):
                //clear last input
                mvwprintw(main_w, y, x, " ");
                //remove from matrix
                matrix[y-1][x-1] = 0;
                //check if there is a queue
                if(move_queue == NULL)
                    break;
                //move queue pointer to the previous input
                if(move_queue->prev != NULL) {
                    move_queue = move_queue->prev;
                    //and is inside borders
                    if(move_queue->y < nlines-1 && move_queue->x < ncols-1) {
                        //save the old character
                        usr_req = move_queue->value;
                        y = move_queue->y;
                        x = move_queue->x;
                        wmove(main_w, y, x);
                        //mvwprintw(main_w, y, x, "%c", usr_req);
                        //update matrix content
                        matrix[y-1][x-1] = usr_req;
                    }
                }
                break;

            //redo
            case CTRL('y'):
                if(move_queue == NULL)
                    break;
                //move queue pointer to the next input
                if(move_queue->next != NULL) {
                    move_queue = move_queue->next;
                    //and is inside borders
                    if(move_queue->y < nlines-1 && move_queue->x < ncols-1) {
                        //print the redo char
                        usr_req = move_queue->value;
                        y = move_queue->y;
                        x = move_queue->x;
                        wmove(main_w, y, x);
                        //mvwprintw(main_w, y, x, "%c", usr_req);
                        //update matrix content
                        matrix[y-1][x-1] = usr_req;
                    }
                }
                break;

            //reset option
            case CTRL('R'):
                wclear(main_w);
                wattr_on(main_w, COLOR_PAIR(3), NULL);
                draw_borders(main_w);
                wattr_off(main_w, COLOR_PAIR(3), NULL);
                //free undo and redo queue
                if(queue != NULL) {
                    print_info(main_w, "Reset undo queue? [Y/n] ", 
                               1, 1, 4, FALSE);
                    wrefresh(main_w);
                    usr_req = wgetch(main_w);
                    curs_set(0);
                    if(usr_req == 'Y' || usr_req == 'y') {
                        freeQ_char(queue);
                        queue = NULL;
                        move_queue = NULL;
                        queue_dim = 0;
                        if(queue == NULL && move_queue == NULL) {
                            print_info(main_w, "Undo queue clear", 
                                       2, 1, 2, FALSE);
                            wrefresh(main_w);
                        }
                        else {
                            endwin();
                            return 3;
                        }
                    }
                }
                //remove matrix content
                free_matrix(matrix, mat_y);
                //and re-init ascii art matrix
                getmaxyx(main_w, nlines, ncols);
                mat_y = nlines-1;
                mat_x = ncols-1;
                matrix = init_matrix(mat_y, mat_x);
                if(matrix != NULL) {
                    print_info(main_w, "New matrix created", 
                               3, 1, 2, FALSE);
                    wrefresh(main_w);
                    wgetch(main_w);
                }
                else {
                    endwin();
                    return 2;
                }
                //update the screen
                curs_set(1);
                wclear(main_w);
                break;

            /*
            //TODO READ STRING, LOAD MATRIX FROM FILE
            //load option
            case CTRL('L'):
                wclear(main_w);
                draw_borders(main_w);
                //request file name from user
                mvwprintw(main_w, 1, 1, "Load filename:\n");
                usr_str = get_input_str(main_w);
                free(matrix);
                matrix = file_to_matrix(usr_str, &mat_y, &mat_x);
                if(matrix != NULL)
                    mvwprintw(main_w, 1, 1, "Ascii art \"%s\" load!", usr_str);
                else {
                    mat_y = nlines-1;
                    mat_x = ncols-1;
                    matrix = init_matrix(mat_y, mat_x);
                }
                wgetch(main_w);
                break;
            */
            /*TODO FIX HERE
            //save option
            case CTRL('S'):
                wclear(main_w);
                draw_borders(main_w);
                //ask file name from user
                print_info(main_w, "Insert filename\n:", 
                               1, 1, 4, FALSE);
                usr_str = get_input_str(main_w);
                //save matrix to file and print info if there are some errors
                usr_req = matrix_to_file(matrix, mat_y, mat_x, usr_str);
                if(usr_req == 0) {
                    print_info(main_w, "Ascii art saved!", 
                               3, 1, 2, FALSE);
                    //ask if user want to save undo/redo queue
                    print_info(main_w, "Also save queue? [Y/n] ", 
                               4, 1, 4, FALSE);
                    wrefresh(main_w);
                    usr_req = wgetch(main_w);
                    if(usr_req == 'Y' || usr_req == 'y')
                        queue_to_file(queue, strcat(usr_str, "_queue.txt"));
                }
                else if(usr_req == 1)
                    print_info(main_w, "Error nil on save!", 
                               3, 1, 1, FALSE);
                else if(usr_req == 2)
                    print_info(main_w, "Error on save file!", 
                               3, 1, 1, TRUE);
                wrefresh(main_w);
                wgetch(main_w);
                wclear(main_w);
                break;
            */

            //here ascii art is printed
            default:
                if(!isAlphaNum(ch))
                    break;
                //save char into ascii matrix
                matrix[y-1][x-1] = ch;
                //add char into undo queue
                queue = pushQ_char(queue, ch, y, x);
                //start undo and redo
                move_queue = getLastQ_char(queue);
                //respect defined memory limit
                if(queue_dim >= QUEUE_LIMIT)
                    queue = popHeadQ_char(queue);
                else
                    queue_dim++;
                //sequential is enabled
                if(in_mode == 1) {
                    if(x+1 < ncols-1)
                        x++;
                }
                break;
        }
        //print data to the screen
        draw_borders(main_w);
        print_matrix(main_w, matrix, mat_y, mat_x);
        //move to the desired position
        wmove(main_w, y, x);
        //update window content
        wrefresh(main_w);
    }

    return 2;
}

/*
 * first print before the real program start
 */
void welcome_message(WINDOW* win) {
    //print general info
    draw_borders(win);
    curs_set(0);
    noecho();
    keypad(win, 1);
    nodelay(win, 0);
    mvwprintw(win, 1, 1, " Use arrows or Tab to move");
    mvwprintw(win, 2, 1, "_Use CTRL+S to Save");
    mvwprintw(win, 3, 1, "_Use CTRL+L to Load file");
    mvwprintw(win, 4, 1, " Use CTRL+Z to undo");
    mvwprintw(win, 5, 1, " Use CTRL+Y for redo");
    mvwprintw(win, 6, 1, " Use CTRL+R to Reset");
    mvwprintw(win, 7, 1, " Use CTRL+Q to Quit");
    mvwprintw(win, 8, 1, " Use CTRL+M to change Mode");
    attron(A_BOLD);
    mvwprintw(win, 9, 1, "Press any button to continue");
    attroff(A_BOLD);
    wrefresh(win);
    wgetch(win);
    wclear(win);
}

/*
 * print information on "win" with "dye" color:
 * 1 = RED = Error
 * 2 = GREEN = Answer
 * 3 = YELLOW = Warning
 * 4 = BLUE = Question
 * 5 = CYAN = Variable
 * 6 = MAGENTA = Info
 * 7 = WHITE = Normal text
 * 8 = BLACK = Hide
 *
 * important = true = bold
 */
void print_info(WINDOW* win, char* msg, int y, int x, int dye, bool important) {

    //enable style
    if(TERM_HAS_COLORS)
        wattr_on(win, COLOR_PAIR(dye), NULL);
    if(important)
        wattr_on(win, A_BOLD, NULL);
    //print info
    mvwprintw(win, y, x, "%s", msg);
    //disable style
    if(TERM_HAS_COLORS)
        wattr_off(win, COLOR_PAIR(dye), NULL);
    if(important)
        wattr_off(win, A_BOLD, NULL);

}
