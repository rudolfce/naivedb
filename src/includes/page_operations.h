#ifndef PAGE_OPERATIONS__H__
#define PAGE_OPERATIONS__H__

#include<stdio.h>
#include "table.h"

#define K 1024
#define PAGE_SIZE 512*K

void *get_table_path(table_struct *, char *);
FILE *get_page_handler(table_struct *, int);
int populate_page_from_handler(page_struct *, FILE *);

#endif
