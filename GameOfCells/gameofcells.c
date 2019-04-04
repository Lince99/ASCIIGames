/*
 * This source is under MIT license
 * Copyright (c) 2019 Lince99
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * see:
 *     man 3 nonl
 *     man 3 panel
 *     man 3 scroll
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/queue_char.h"
#include "include/window_manager.h"
#include "include/goc_game_api/array_rules.h"
#include "include/goc_game_api/matrix_cell.h"
#include "include/goc_net_api/goc_server.h"
#include "include/goc_net_api/goc_client.h"



int main(int argc, char** argv) {
    WINDOW *main_w;
    int term_y, term_x;
    int main_y, main_x;
    int** matrix = NULL;
    int user_input = 0;
    int x = 0, y = 0;
    
    //player stuff
    char player_char = '#';
    

    //initialize Ncurses
    initscr();
    
    //check color support
    if(!has_colors()) {
        printw("NO COLOR SUPPORT! Quitting...");
        endwin();
        return 1;
    }
    start_color();

    //get current terminal window max coordinates
    getmaxyx(stdscr, term_y, term_x);
    main_y = term_y;
    main_x = term_x;

    //create the main window
    main_w = newwin(main_y, main_x, 0, 0);

    //initialize user input mode
    curs_set(0);
    noecho();
    raw();
    keypad(main_w, TRUE);
    nodelay(main_w, FALSE); //set TRUE for CPU intensive mode
    intrflush(main_w, FALSE);
    nonl();

    wprintw(main_w, "Press CTRL+Q to exit\n");
    attron(A_BOLD);
    wprintw(main_w, "Press any button to continue");
    attron(A_BOLD);
    wrefresh(main_w);
    wgetch(main_w);
    wclear(main_w);

    //program run forever until CTRL+Q is pressed
    while(1) {
        //get user input
        user_input = wgetch(main_w);

        //if no input is detected exit
        if(user_input == ERR)
            break;
        //if the user want to exit request the confirmation
        if(user_input == CTRL('q')) {
            wclear(main_w);
            mvwprintw(main_w, 0, 0, "Are you sure to quit? [Y/n] ");
            wrefresh(main_w);
            user_input = wgetch(main_w);
            if(user_input == 'Y' || user_input == 'y')
                break;
        }
        switch(user_input) {
            //ENTER
            case 10:
                //y++;
		        //wmove(main_w, y, x);
		        break;
            //Up Arrow
            case KEY_UP:
                if(y-1 >= 0)
                    y--;
                break;
            //Down Arrow
            case KEY_DOWN:
                if(y+1 < main_y)
                    y++;
                break;
            //Left Arrow
            case KEY_LEFT:
                if(x-1 >= 0)
                    x--;
                break;
            //Right Arrow
            case KEY_RIGHT:
                if(x+1 < main_x)
                    x++;
                break;
            //wasd keys same as arrows
            case 'w':
                if(y-1 >= 0)
                    y--;
                break;
            case 's':
                if(y+1 < main_y)
                    y++;
                break;
            case 'a':
                if(x-1 >= 0)
                    x--;
                break;
            case 'd':
                if(x+1 < main_x)
                    x++;
                break;
            //Window resize event
            case KEY_RESIZE:
                getmaxyx(main_w, main_y, main_x);
                if(y >= main_y)
                    y = main_y-1;
                if(x >= main_x)
                    x = main_x-1;
		        wclear(main_w);
                break;
            //normal char
            default:
                //if is a printable character print it
                //if(is_alphanum(user_input))
                //    mvwprintw(main_w, y, x, "%c", user_input);
                attron(COLOR_RED);
                mvwprintw(main_w, y, x, "%c", player_char);
                attroff(COLOR_RED);
    		    break;
        }

        //move to the desired position
        wmove(main_w, y, x);
        //update screen content
        wrefresh(main_w);
    }

    //free Ncurses window
    delwin(main_w);

    //stop Ncurses
    endwin();

    return 0;
}
