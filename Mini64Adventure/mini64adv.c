/*
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
 * Main
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    //initialize Ncurses
    initscr();

    //test colors
    if(!has_colors()) {
        //stop Ncurses because without colors you can't play it
        endwin();
        perror("Your terminal does not support colors!\n");
        exit(1);
    }

    //stop Ncurses
    endwin();

    return 0;
}