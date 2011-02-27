#ifndef _HASHTBL_H
#define _HASHTBL_H

#include <stdio.h>
#include<stdlib.h>

typedef size_t HSIZE;

typedef struct hashnode {
    char *key;
    void *data;
    struct hashnode *next;
} ENTRY;

typedef struct hashtbl {
    HSIZE size;
    HSIZE count;
    ENTRY **nodes;
    HSIZE (*hashfunc)(const char *);
} HASHTBL;

HASHTBL *hashtbl_create(HSIZE size, HSIZE (*hashfunc)(const char *));
void hashtbl_destroy(HASHTBL *hashtbl);
int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data);
int hashtbl_remove(HASHTBL *hashtbl, const char *key);
void *hashtbl_get(HASHTBL *hashtbl, const char *key);
int hashtbl_resize(HASHTBL *hashtbl, HSIZE size);
void hashtbl_dump(HASHTBL *hashtbl, FILE *stream);

#define DEF_SIZE 100000
#define HASHTBL_INIT(hashtbl) (hashtbl = hashtbl_create(DEF_SIZE, NULL))

#endif
