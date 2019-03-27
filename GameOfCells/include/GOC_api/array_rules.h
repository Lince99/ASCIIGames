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

#ifndef ARRAY_RULES_H
#define ARRAY_RULES_H

#include <stdio.h>
#include <unistd.h>

//global variables (modified by user settings)
int RULE_DIMENSION = 8;

//signatures
int* new_rule(size_t);
int* renew_rule(size_t);
int set_rule(int*, int, int);
int get_rule(int*, int);



/*
 * alloc new array of rules (use index to access rules) and set all to 0
 */
int* new_rule(size_t dim) {
    int* rule = NULL;

    if(dim <= 0 || dim > RULE_DIMENSION)
        return NULL;
    rule = (int*) calloc(sizeof(int), dim);
    if(rule == NULL)
        perror("Error on alloc new cell rule!");

    return rule;
}

/*
 * realloc array of rules
 */
int* renew_rule(size_t dim) {
    int* rule = NULL;

    if(dim <= 0 || dim > RULE_DIMENSION)
        return NULL;
    rule = (int*) realloc(rule, dim);
    if(rule == NULL)
        perror("Error on realloc cell rule!");

    return rule;
}

/*
 * state must be >= 0
 * return 0 on success, 1 on rule NULL, 2 on wrong pos or state
 */
int set_rule(int* rule, int pos, int state) {

    if(rule == NULL)
        return 1;
    if(pos < 0 || pos >= RULE_DIMENSION || state < 0)
        return 2;
    //set rule with params
    rule[pos] = state;

    return 0;
}

/*
 * return the value of the rule on position "pos"
 * return -1 on rule NULL, -2 on wrong position request
 */
int get_rule(int* rule, int pos) {

    if(rule == NULL)
        return -1;
    if(pos < 0 || pos >= RULE_DIMENSION)
        return -2;
    return rule[pos];
}

#endif //ARRAY_RULES_H
