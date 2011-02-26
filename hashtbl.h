#ifndef _HASHTBL_H
#define _HASHTBL_H

#include<stdlib.h>

typedef size_t hsize;

typedef struct hashnode {
    char *key;
    void *data;
    struct hashnode *next;
} ENTRY;

typedef struct hashtbl {
    hsize size;
    ENTRY **nodes;
    hsize (*hashfunc)(const char *);
} HASHTBL;

HASHTBL *hashtbl_create(hsize size, hsize (*hashfunc)(const char *));
void hashtbl_destroy(HASHTBL *hashtbl);
int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data);
int hashtbl_remove(HASHTBL *hashtbl, const char *key);
void *hashtbl_get(HASHTBL *hashtbl, const char *key);
int hashtbl_resize(HASHTBL *hashtbl, hsize size);

#endif
