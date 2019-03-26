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

#ifndef QUEUE_CHAR_H
#define QUEUE_CHAR_H

#include <stdlib.h>
#include <unistd.h>

//global variables (modified by user settings)
int QUEUE_LIMIT = 10000;

//signatures
typedef struct QCHAR qchar;
qchar* init_qchar(char, int, int);
qchar* push_qchar(qchar*, char, int, int);
qchar* pop_qchar(qchar*);
qchar* pophead_qchar(qchar*);
qchar* getlast_qchar(qchar*);
int getsize_qchar(qchar*);
void free_qchar(qchar*);



//queue struct for undo and redo (bidirectional list)
struct QCHAR {
    char value;
    int y;
    int x;
    qchar* next;
    qchar* prev;
};

/*
 * create new node and return it
 */
qchar* init_qchar(char val, int y, int x) {
    qchar* node = NULL;

    node = (qchar*) malloc(sizeof(qchar));
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
qchar* push_qchar(qchar* head, char val, int y, int x) {
    qchar* node = NULL;
    qchar* q = head;

    node = init_qchar(val, y, x);
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
qchar* pop_qchar(qchar* head) {
    qchar* q = head;

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
qchar* pophead_qchar(qchar* q) {

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
qchar* getlast_qchar(qchar* head) {

    if(head == NULL)
        return NULL;
    while(head->next != NULL)
        head = head->next;

    return head;
}

/*
 * return the current size of the queue
 */
int getsize_qchar(qchar* head) {
    qchar* tmp = head;
    int size = 0;

    if(head == NULL)
        return 0;
    while(tmp->prev != NULL) {
        size++;
        tmp = tmp->prev;
    }
    while(head->next != NULL) {
        size++;
        head = head->next;
    }

    return size;
}

/*
 * free the queue from start
 */
void free_qchar(qchar* q) {
    qchar* tmp = NULL;

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
