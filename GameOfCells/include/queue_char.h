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

#ifndef QUEUE_CHAR_H
#define QUEUE_CHAR_H

#include <stdlib.h>
#include <unistd.h>

#ifndef QUEUE_LIMIT
    #define QUEUE_LIMIT 10000
#endif

int queue_dim = 0;

//queue struct for undo and redo (bidirectional list)
typedef struct Q_CHAR q_char;
struct Q_CHAR {
    char value;
    int y;
    int x;
    q_char* next;
    q_char* prev;
};

/*
 * create new node and return it
 */
q_char* initQ_char(char val, int y, int x) {
    q_char* node = NULL;

    node = (q_char*) malloc(sizeof(q_char));
    if(node == NULL) {
        perror("Error add element to queue! (init)\n");
        return NULL;
    }
    node->value = val;
    node->y = y;
    node->x = x;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

/*
 * add at the tail of the queue 1 new node
 */
q_char* pushQ_char(q_char* head, char val, int y, int x) {
    q_char* node = NULL;
    q_char* q = head;

    node = initQ_char(val, y, x);
    if(node == NULL)
        return NULL;
    if(q == NULL)
        return node;
    while(q->next != NULL)
        q = q->next;
    node->prev = q;
    q->next = node;

    return head;
}

/*
 * remove last node of the queue
 */
q_char* popQ_char(q_char* head) {
    q_char* q = head;

    if(q == NULL)
        return NULL;
    while(q->next != NULL)
        q = q->next;
    q->next = NULL;

    return head;
}

/*
 * remove first node of the queue
 */
q_char* popHeadQ_char(q_char* q) {

    if(q == NULL)
        return NULL;
    if(q->next == NULL)
        return NULL;
    q = q->next;
    q->prev = NULL;

    return q;
}

/*
 * get last node in the queue
 */
q_char* getLastQ_char(q_char* head) {

    if(head == NULL)
        return NULL;
    while(head->next != NULL)
        head = head->next;

    return head;
}

/*
 * free the queue from start
 */
void freeQ_char(q_char* q) {
    q_char* tmp = NULL;

    if(q == NULL)
        return;
    while(q->prev != NULL) {
        q = q->prev;
    }
    while(q->next != NULL) {
        tmp = q;
        q = q->next;
        free(tmp);
    }

}

#endif //QUEUE_CHAR_H
