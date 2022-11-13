#ifndef ROW_NODES__H__
#define ROW_NODES__H__

#define TYPE_INTEGER 1
#define TYPE_VARCHAR 2

struct page_struct;
struct table_struct;

/* A table defined by name, size and column types.
   A page cache vector is provided to avoid loading
   pages too many times. */
typedef struct table_struct{
    int *t_columns;
    int n_columns;
    int n_rows;
    int n_loaded_pages;
    struct page_struct **loaded_pages;
    char *name;
} table_struct;

typedef struct page_struct{
    table_struct *table;
    int page_number;
    int n_rows;
    char *page_start;
} page_struct;

page_struct *load_page(table_struct *, int);
int free_page(page_struct *);
int get_row_size(table_struct *);

#endif
