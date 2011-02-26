#include <stdio.h>
#include <hashtbl.h>

#define TBL_SIZ 100
#define ELE_CNT 200

int main(int argc, const char *argv[])
{
    HASHTBL *tbl;
    ENTRY *entry;
    char *line = NULL;
    int ret, i, cnt, len = 0;

    entry = malloc(sizeof(ENTRY));
    tbl = hashtbl_create(TBL_SIZ, NULL);
    for (i = 0, cnt = 0; i < ELE_CNT; ++i) {
        if ( (ret = getline(&line, &len, stdin)) == -1) {
            perror("getline():");
            continue;
        }
        if ( ret > 0 && line[ret-1] == '\n')
            line[ret-1] = '\0';
        entry->key = line;
        hashtbl_insert(tbl, entry->key, (void*)i);
        ++cnt;
    }
    printf("insert %d elements\n", cnt);

    hashtbl_dump(tbl,stdout);

    for (i = 0, cnt = 0; i < tbl->size; ++i) {
        entry = tbl->nodes[i];
        if (entry)
            --cnt;
        while (entry) {
            ++cnt;
            entry = entry->next;
        }
    }
    printf("\n");
    printf("%d collisions\n", cnt);

    if (line)
        free(line);

    return 0;
}
