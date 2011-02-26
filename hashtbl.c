#include <string.h>
#include <stdio.h>

#include <hashtbl.h>

static hsize bkdrhash(const char *key)
{
    hsize seed = 131; // 31 131 1313 13131 131313 etc.
    hsize hash = 0;

    while (*key)
        hash = hash * seed + (*key++);

    return hash;
}

HASHTBL *hashtbl_create(hsize size, hsize (*hashfunc)(const char *))
{
    HASHTBL *hashtbl;

    if (!(hashtbl=malloc(sizeof(HASHTBL))))
        return NULL;

    if (!(hashtbl->nodes = calloc(size, sizeof(ENTRY*)))) {
        free(hashtbl);
        return NULL;
    }

    hashtbl->size = size;

    if (hashfunc)
        hashtbl->hashfunc = hashfunc;
    else
        hashtbl->hashfunc = bkdrhash;

    return hashtbl;
}


void hashtbl_destroy(HASHTBL *hashtbl)
{
    hsize n;
    ENTRY *node, *oldnode;

    for (n = 0; n < hashtbl->size; ++n) {
        node = hashtbl->nodes[n];
        while (node) {
            free(node->key);
            oldnode = node;
            node = node->next;
            free(oldnode);
        }
    }
    free(hashtbl->nodes);
    free(hashtbl);
}


int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data)
{
    ENTRY *node;
    hsize hash = hashtbl->hashfunc(key) % hashtbl->size;

    node = hashtbl->nodes[hash];

    while (node) {
        if (!strcmp(node->key, key)) {
            node->data = data;
            return 0;
        }
        node = node->next;
    }

    if (!(node = malloc(sizeof(ENTRY)))) return -1;
    if (!(node->key = strdup(key))) {
        free(node);
        return -1;
    }
    node->data = data;
    node->next = hashtbl->nodes[hash];
    hashtbl->nodes[hash] = node;

    return 0;
}


int hashtbl_remove(HASHTBL *hashtbl, const char *key)
{
    ENTRY *node, *prevnode = NULL;
    hsize hash = hashtbl->hashfunc(key) % hashtbl->size;

    node = hashtbl->nodes[hash];
    while (node) {
        if (!strcmp(node->key, key)) {
            free(node->key);
            if (prevnode)
                prevnode->next = node->next;
            else
                hashtbl->nodes[hash] = node->next;
            free(node);
            return 0;
        }
        prevnode = node;
        node = node->next;
    }

    return -1;
}


void *hashtbl_get(HASHTBL *hashtbl, const char *key)
{
    ENTRY *node;
    hsize hash = hashtbl->hashfunc(key) % hashtbl->size;

    node = hashtbl->nodes[hash];
    while (node) {
        if (!strcmp(node->key, key)) {
            fprintf(stderr, "get key=%s, data=%p\n", node->key, node->data);
            return node->data;
        }
        node = node->next;
    }

    return NULL;
}

int hashtbl_resize(HASHTBL *hashtbl, hsize size)
{
    HASHTBL newtbl;
    hsize n;
    ENTRY *node,*next;

    newtbl.size = size;
    newtbl.hashfunc = hashtbl->hashfunc;

    if (!(newtbl.nodes = calloc(size, sizeof(ENTRY*))))
        return -1;

    for (n = 0; n < hashtbl->size; ++n) {
        for (node = hashtbl->nodes[n]; node; node = next) {
            next = node->next;
            hashtbl_insert(&newtbl, node->key, node->data);
            hashtbl_remove(hashtbl, node->key);

        }
    }

    free(hashtbl->nodes);
    hashtbl->size = newtbl.size;
    hashtbl->nodes = newtbl.nodes;

    return 0;
}

void hashtbl_dump(HASHTBL *hashtbl, FILE *stream)
{
    int i;
    ENTRY *entry;
    for (i = 0; i < hashtbl->size; ++i) {
        entry = hashtbl->nodes[i];
        if (entry)
            printf("\n[%d]", i);
        while (entry) {
            printf(" -> (\"%s\":%p)", entry->key, entry->data);
            entry = entry->next;
        }
    }
    printf("\n");
}
