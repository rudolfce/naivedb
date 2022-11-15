#ifndef DATABASE__H__
#define DATABASE__H__

struct farm;
struct database;

typedef struct database{
    char *name;
    int n_tables;
    struct table_struct **tables;
    struct farm *database_farm;
} database;

typedef struct farm{
    char *path;
    int n_databases;
    database **databases;
} farm;

#endif
