#ifndef DATABASE__H__
#define DATABASE__H__

struct database_farm;
struct database;

typedef struct database{
    char *name;
    struct table_struct **tables;
    struct database_farm *farm;
} database;

typedef struct database_farm{
    char *path;
    database **databases;
} database_farm;

#endif
