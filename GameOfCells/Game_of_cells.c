/*
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



int main(int argc, char** argv) {
    WINDOW *main_w;
    int term_y, term_x;
    int main_y, main_x;

    //initialize Ncurses
    initscr();

    //get current terminal window max coordinates
    getmaxyx(stdscr, term_y, term_x);

    main_y = term_y;
    main_x = term_x;

    //create the main window
    main_w = newwin(term_y, term_x, main_y, main_x);

    //wait user input
    getch();

    //free Ncurses window
    delwin(main_w);

    //stop Ncurses
    endwin();

    return 0;
}
