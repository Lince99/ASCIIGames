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
 * main
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
    int x, y = 0;

    //initialize Ncurses
    initscr();

    //get current terminal window max coordinates
    getmaxyx(stdscr, term_y, term_x);

    main_y = term_y;
    main_x = term_x;

    //create the main window
    main_w = newwin(main_y, main_x, 0, 0);

    raw();
    nodelay(main_w, 0);
    wprintw(main_w, "Press q to exit.\n");
    while(1) {
        user_input = wgetch(main_w);
        if(user_input == 'q')
            break;
        if(user_input == 10) {
            y++;
            wmove(main_w, y, 0);
        }
    }

    //free Ncurses window
    delwin(main_w);

    //stop Ncurses
    endwin();

    return 0;
}
