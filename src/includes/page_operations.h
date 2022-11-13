#ifndef PAGE_OPERATIONS__H__
#define PAGE_OPERATIONS__H__

#include<stdio.h>

#define K 1024
#define PAGE_SIZE 512*K

struct table_struct;
struct page_struct;

void get_table_path(struct table_struct *, char *);
FILE *get_page_handler(struct table_struct *, int);
int populate_page_from_handler(struct page_struct *, FILE *);

#endif
