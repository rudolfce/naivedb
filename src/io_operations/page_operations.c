#include<stdio.h>
#include "../includes/page_operations.h"
#include "../includes/table.h"
#include "../includes/database.h"


void get_table_path(table_struct *table, char *path)
{
    sprintf(path, "%s/%s/%s", table->table_database->database_farm->path, table->table_database->name, table->name);

    return;
}

FILE *get_page_handler(table_struct *table, int page_number)
{
    char table_path[256];

    get_table_path(table, table_path);

    return fopen(table_path, "r");
}

int populate_page_from_handler(page_struct *page, FILE *page_handler)
{
    char c;
    int i;

    c = fgetc(page_handler);
    i = 0;

    while(c != EOF)
    {
        page->page_start[i] = c;
        c = fgetc(page_handler);
        i += 1;
    }

    return i;
}
