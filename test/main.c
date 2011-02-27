#include <stdio.h>
#include <common/hashtbl.h>

#define TBL_SIZ 1013
#define ELE_CNT 1000

HSIZE hash_func(const char *key);
void help();

int main(int argc, const char *argv[])
{
    HASHTBL *tbl;
    ENTRY *entry;
    HSIZE tblsiz, elecnt;
    char *line = NULL;
    int ret, i, cnt, len = 0;

    if (argc == 0) {
        tblsiz = TBL_SIZ;
        elecnt = ELE_CNT;
    }
    else if (argc != 3) {
        help(argc, argv);
        exit(EXIT_FAILURE);
    }
    else {
        tblsiz = atoi(argv[1]);
        elecnt = atoi(argv[2]);
    }

    entry = malloc(sizeof(ENTRY));
    tbl = hashtbl_create(tblsiz, NULL);
    printf("tbl = %p\n", tbl);
    for (i = 1, cnt = 0; i < elecnt; ++i) {
        if ( (ret = getline(&line, &len, stdin)) == -1) {
            fprintf(stderr, "getline() failed\n");
            continue;
        }
        if ( ret > 0 && line[ret-1] == '\n')
            line[ret-1] = '\0';
        entry->key = line;
        hashtbl_insert(tbl, entry->key, (void*)i);
        ++cnt;
    }
    printf("insert %d elements\n", cnt);
    printf("ele cnt = %d\n", tbl->count);
    hashtbl_remove(tbl, "www.domain3912.com");
    hashtbl_remove(tbl, "www.domain92492.com");
    hashtbl_remove(tbl, "www.domain77224.com");
    hashtbl_remove(tbl, "www.domain68464.com");
    hashtbl_remove(tbl, "www.domain12497.com");
    hashtbl_remove(tbl, "www.domain43997.com");
    printf("ele cnt = %d\n", tbl->count);
    for (i = 0, cnt = 0; i < tbl->size; ++i) {
        entry = tbl->nodes[i];
        if (entry)
            --cnt;
        while (entry) {
            fprintf(stderr, "%s:%d\n", entry->key, (int)entry->data);
            ++cnt;
            entry = entry->next;
        }
    }
    printf("tbl %d collisions\n", cnt);
    hashtbl_dump(tbl, stdout);

    if (line)
        free(line);

    return 0;
}

HSIZE hash_func(const char *key) {
    HSIZE hash = 0;
    while (*key)
        hash += (*key++);
    return hash;
}

void help(int argc, char *argv[])
{
    printf("%s <table size> <element count>\n", argv[0]);
}
