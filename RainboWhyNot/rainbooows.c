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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "include/colors.h"

//signatures
void print_rainbow(int count, int mult, char ch);
void print_rainbow_row(int mult, char ch);

//globals
unsigned int slep = 8000; /* default sleep for readability questions */

int main(int argc, char** argv) {
    int m = 1;
    int c = 1;
    char ch = ' ';

    if(argc > 1) {
        c = atoi(argv[1]);
    }
    if(argc > 2) {
        m = atoi(argv[2]);
    }
    if(argc > 3) {
        slep = (unsigned int)atoi(argv[3])*1000;
    }
    print_rainbow(c, m, ch);
    printf(ANSI_CLEAN);

    return 0;
}


/*
 * procedure that print rainbow like a snake
 */
void print_rainbow(int count, int mult, char ch) {
    int x = 0;
    int n = 0;
    int y = 0;

    while(true) {
        //ch = '\\';
        for(n = 0; n < count; n++) {
            for(x = 0; x < n; x++)
                printf(ANSI_RESET " ");
            print_rainbow_row(mult, ch);
            //for(; x < n; x++) {
            //    printf(ANSI_BG_BLACK ANSI_BLACK " ");
            //}
            printf(ANSI_RESET "\n");
            usleep(slep);
        }
        //ch = '/';
        for(n = count-1; n >= 0; n--) {
            for(x = 0; x < n; x++)
                printf(ANSI_RESET " ");
            print_rainbow_row(mult, ch);
            printf(ANSI_RESET "\n");
            usleep(slep);
        }
    }

}

/*
 * procedure that print only 1 row with colors
 */
void print_rainbow_row(int mult, char ch) {
    int tmp = 0;

    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BOLD ANSI_BG_MAGENTA ANSI_MAGENTA "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BG_MAGENTA ANSI_MAGENTA "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BOLD ANSI_BG_BLUE ANSI_BLUE "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BG_BLUE ANSI_BLUE "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BOLD ANSI_BG_GREEN ANSI_GREEN "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BG_GREEN ANSI_GREEN "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BOLD ANSI_BG_YELLOW ANSI_YELLOW "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BG_YELLOW ANSI_YELLOW "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BOLD ANSI_BG_RED ANSI_RED "%c", ch);
    for(tmp = 0; tmp < mult; tmp++)
        printf(ANSI_BG_RED ANSI_RED "%c", ch);

}
