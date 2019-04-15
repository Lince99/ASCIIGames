/* Copyright (C) 2019  Lince99
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

#ifndef QUEUE_CHAR_H
#define QUEUE_CHAR_H

#include <stdlib.h>
#include <unistd.h>

#ifndef QUEUE_LIMIT
    #define QUEUE_LIMIT 1000000
#endif

int queue_dim = 0;

//queue struct for undo and redo (bidirectional list)
typedef struct Q_CHAR q_char;

//signatures
q_char* initQ_char(int, int, int);
q_char* pushQ_char(q_char*, int, int, int);
q_char* popQ_char(q_char*);
q_char* popHeadQ_char(q_char*);
q_char* getLastQ_char(q_char*);
int queue_to_file(q_char*, char*);
q_char* file_to_queue(q_char* queue, char* filename);
int sizeQ_char(q_char*);
void freeQ_char(q_char*);



struct Q_CHAR {
    int value;
    int y;
    int x;
    q_char* next;
    q_char* prev;
};

/*
 * create new node and return it
 */
q_char* initQ_char(int val, int y, int x) {
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
q_char* pushQ_char(q_char* head, int val, int y, int x) {
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
 * remove last node of the queue
 */
q_char* popHeadQ_char(q_char* head) {

    if(head == NULL)
        return NULL;
    if(head->next == NULL)
        return NULL;
    head = head->next;
    head->prev = NULL;

    return head;
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

void printQ_char_stdout(q_char* head) {
    printf("queue:\n");
    if(head == NULL) {
        printf("Void!\n");
        return;
    }
    while(head != NULL) {
        printf("%c[%d,%d]", head->value, head->y, head->x);
        if(head->next != NULL)
            printf(", ");
        else
            printf(".");
        head = head->next;
    }
    printf("\n");
}

/*
 * write into "filename" the queue, return 0 on success, 1 on nil error, 2 on IO
 */
int queue_to_file(q_char* q, char* filename) {
    FILE* fp = NULL;

    if(q == NULL || filename == NULL)
        return 1;
    fp = fopen(filename, "w+");
    if(fp == NULL)
        return 2;
    while(q->prev != NULL)
        q = q->prev;
    //TODO OPTIMIZE OUTPUT
    while(q != NULL) {
        fprintf(fp, "'%c' %d %d\n", q->value, q->y, q->x);
        q = q->next;
    }
    fclose(fp);

    return 0;
}

/*
 * load queue from file, appending structs to queue
 */
q_char* file_to_queue(q_char* queue, char* filename) {
    q_char* q = queue;
    FILE* fp = NULL;
    char value = 0;
    int y = 0;
    int x = 0;

    //append (goes to the end)
    if(q != NULL) {
        while(q->next != NULL)
            q = q->next;
    }
    fp = fopen(filename, "r");
    if(fp == NULL)
        return queue;
    //TODO FIX LOAD LOOP
    //read line per line
    while(fscanf(fp, "'%c' %d %d\n", &value, &y, &x) != EOF) {
        q = pushQ_char(q, value, y, x);
        //printf("r= %d %d %d\n", value, y, x);
        queue_dim++;
    }

    return queue;
}

/*
 * Return the size of the queue
 */
int sizeQ_char(q_char* q) {
    int size = 0;

    if(q == NULL)
        return -1;
    while(q->next != NULL) {
        q = q->next;
        size++;
    }

    return size;
}

/*
 * free the queue from start
 */
void freeQ_char(q_char* head) {
    q_char* tmp = NULL;

    if(head == NULL)
        return;
    while(head->prev != NULL)
        head = head->prev;
    while(head->next != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

}

#endif //QUEUE_CHAR_H
