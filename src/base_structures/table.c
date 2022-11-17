#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "../includes/table.h"
#include "../includes/page_operations.h"


table_struct *initialize_table(char *name)
{
    table_struct *output_table;
    int name_len;

    output_table = (table_struct *) malloc(sizeof(table_struct));
    name_len = strlen(name);
    output_table->name = (char *) malloc((name_len + 1) * sizeof(char));
    strcpy(output_table->name, name);
    output_table->max_columns = 0;
    output_table->n_columns = 0;
    output_table->max_loaded_pages = 0;
    output_table->n_loaded_pages = 0;
    output_table->t_columns = NULL;
    output_table->column_names = NULL;
    output_table->loaded_pages = NULL;

    return output_table;
}

int free_table(table_struct *table)
{
    int i;

    if(!table)
        return 0;

    if(table->name)
        free(table->name);

    if(table->t_columns)
        free(table->t_columns);

    if(table->column_names) {
        for(i=0; i<table->n_columns; i++) {
            if(table->column_names)
                free(table->column_names[i]);
        }
        free(table->column_names);
    }
    if(table->loaded_pages) {
        for(i=0; i<table->n_loaded_pages; i++)
            free_page(table->loaded_pages[i]);

        free(table->loaded_pages);
    }

    free(table);
    return 1;
}

int resize_columns_vectors(table_struct *table, int new_size)
{
    if(!table->t_columns)
        table->t_columns = (int *) malloc(new_size * sizeof(int));
    else
        table->t_columns = (int *) realloc(table->t_columns, new_size * sizeof(int));

    if(!table->column_names)
        table->column_names = (char **) malloc(new_size * sizeof(char **));
    else
        table->column_names = (char **) realloc(table->column_names, new_size * sizeof(char **));

    return new_size;
}

int add_column(table_struct *table, char *column_name, int column_type)
{
    int last_index;
    int l_name;

    if(table->n_columns == table->max_columns)
        table->max_columns = resize_columns_vectors(table, table->max_columns + COLUMNS_INCREMENT);

    last_index = table->n_columns;
    table->n_columns += 1;

    l_name = strlen(column_name);
    table->column_names[last_index] = (char *) malloc((l_name + 1) * sizeof(char));
    strcpy(table->column_names[last_index], column_name);
    table->t_columns[last_index] = column_type;

    return table->n_columns;
}

int get_row_size(table_struct *table)
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

page_struct *initialize_page()
{
    page_struct *output_page;

    output_page = (page_struct *) malloc(sizeof(page_struct));

    output_page->n_rows = 0;
    output_page->table = NULL;
    output_page->page_number = 0;
    output_page->page_start = (char *) NULL;

    return output_page;
}

page_struct *load_page(table_struct *table, int page_number)
{
    int n_rows, row_size;
    FILE *page_handler;
    page_struct *output_page;

    page_handler = get_page_handler(table, page_number);
    row_size = get_row_size(table);

    output_page = initialize_page();

    output_page->table = table;
    output_page->page_number = page_number;

    if(!fscanf(page_handler, "%d", &n_rows))
        return (page_struct *) NULL;

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
