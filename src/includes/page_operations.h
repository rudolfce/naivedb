#ifndef PAGE_OPERATIONS__H__
#define PAGE_OPERATIONS__H__

#include<stdio.h>
#include "row_nodes.h"


FILE *get_page_handler(table_struct *, int);
void populate_page_from_handler(page_struct *, FILE *);

#endif
