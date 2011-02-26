#include <stdio.h>
#include <hashtbl.h>

int main(int argc, const char *argv[])
{
    HASHTBL *tbl;
    ENTRY *entry;
    entry = calloc(1, sizeof(*entry));
    tbl = hashtbl_create(100, NULL);
    hashtbl_insert(tbl, "chenwl", (void*)200);
    entry->data = hashtbl_get(tbl, "cwl");
    printf("cwl --> %d\n", (int)entry->data);
    entry->data = hashtbl_get(tbl, "chenwl");
    printf("chenwl --> %d\n", (int)entry->data);
    return 0;
}
