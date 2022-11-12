#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<unistd.h>
#include "../includes/row_nodes.h"
#include "../includes/page_operations.h"


int get_row_size(table_struct *table);
{
    int i, value_size, row_size=0;

    for(i=0; i<table->n_columns; i++)
    {
        switch(table->t_columns[i])
        {
            case TYPE_INTEGER:
                value_size = sizeof(int);
            case TYPE_VARCHAR:
                value_size = sizeof(char);
        }

        row_size += value_size;
    }

    return row_size;
}

page_struct *load_page(table_struct *table, int page_number)
{
    int n_rows, row_size;
    FILE *page_handler;
    page_struct *output_page;

    page_handler = get_page_handler(table, page_number);
    row_size = get_row_size(table);

    fscanf(page_handler, "%d", &n_rows);

    output_page = (page_struct *) malloc(sizeof(page_struct));

    output_page->n_rows = n_rows;
    output_page->table = table;
    output_page->page_number = page_number;
    output_page->page_start = (char *) malloc(row_size * n_rows + 1);

    populate_page_from_handler(output_page, page_handler);

    fclose(page_handler);

    return output_page;
}

int free_page(page_struct *page)
{
    if(page == NULL)
        return 0;

    if(page->page_start != NULL)
        free(page->page_start);

    free(page);

    return 1;
}
