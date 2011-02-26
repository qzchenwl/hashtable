#include <stdio.h>
#include <hashtbl.h>

#define TBL_SIZ 1013
#define ELE_CNT 1000

hsize hash_func(const char *key);
void help();

int main(int argc, const char *argv[])
{
    HASHTBL *tbl, *tbl2;
    ENTRY *entry;
    hsize tblsiz, elecnt;
    char *line = NULL;
    int ret, i, cnt, cnt2, len = 0;

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
    tbl2 = hashtbl_create(tblsiz, hash_func);
    for (i = 0, cnt = 0; i < elecnt; ++i) {
        if ( (ret = getline(&line, &len, stdin)) == -1) {
            fprintf(stderr, "getline() failed\n");
            continue;
        }
        if ( ret > 0 && line[ret-1] == '\n')
            line[ret-1] = '\0';
        entry->key = line;
        hashtbl_insert(tbl, entry->key, (void*)i);
        hashtbl_insert(tbl2, entry->key, (void*)i);
        ++cnt;
    }
    printf("insert %d elements\n", cnt);

    for (i = 0, cnt = 0, cnt2 = 0; i < tbl->size; ++i) {
        entry = tbl->nodes[i];
        if (entry)
            --cnt;
        while (entry) {
            ++cnt;
            entry = entry->next;
        }

        entry = tbl2->nodes[i];
        if (entry)
            --cnt2;
        while (entry) {
            ++cnt2;
            entry = entry->next;
        }
    }
    printf("tbl %d collisions\n", cnt);
    printf("tbl2 %d collisions\n", cnt2);

    hashtbl_dump(tbl, stdout);
    hashtbl_dump(tbl2, stdout);


    if (line)
        free(line);

    return 0;
}

hsize hash_func(const char *key) {
    hsize hash = 0;
    while (*key)
        hash += (*key++);
    return hash;
}

void help(int argc, char *argv[])
{
    printf("%s <table size> <element count>\n", argv[0]);
}
