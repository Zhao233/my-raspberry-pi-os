#include "mm.h"

/**
 * allocation memory ‘bit map’
 * each slot present the state of a page,if 1 means this page is allocated, if 0 means this page is "free"
 * */
static unsigned short mem_map [ PAGING_PAGE ] = {0,};

// accelarate the process of finding the free page
static int leftmost_free_page_index = 0;

/**
 * allocate free page
 * find free page from mem_map
 * return: page-alinged address of free page
 * */
unsigned long get_free_page()
{
    for(int i = 0; i < PAGING_PAGE; i++ ){
        if(mem_map[i] == 0){
            mem_map[i] = 1;
            return LOW_MEMORY + i*PAGE_SIZE;
        }
    }

    return 0;
}

void free_page(unsigned long p){
    mem_map[ (p - LOW_MEMORY) / PAGE_SIZE ] = 0;
}
