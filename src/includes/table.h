#ifndef ROW_NODES__H__
#define ROW_NODES__H__

#define TYPE_INTEGER 1
#define TYPE_VARCHAR 2
#define COLUMNS_INCREMENT 16

/* A table defined by name, size and column types.
   A page cache vector is provided to avoid loading
   pages too many times. */
typedef struct table_struct{
    int max_columns;
    int *t_columns;
    char **column_names;
    int n_columns;
    int n_rows;
    int max_loaded_pages;
    int n_loaded_pages;
    struct page_struct **loaded_pages;
    char *name;
    struct database *table_database;
} table_struct;

typedef struct page_struct{
    struct table_struct *table;
    char dirty;
    int page_number;
    int n_rows;
    char *page_start;
} page_struct;

table_struct *initialize_table(char *);
int free_table(table_struct *);
int add_column(table_struct *, char *, int);
page_struct *load_page(table_struct *, int);
int free_page(page_struct *);
int get_row_size(table_struct *);

#endif
