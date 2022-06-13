#include "container_of.h"
#include "_stddef.h"

#ifndef _LIST_H

#define _LIST_H

#define LIST_HEAD_INIT(name) {&(name), &(name)}

#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)


#define list_for_each(pos, head) \
        for((pos) = (head)->next; pos != head; pos = pos -> next)

#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)

#ifndef __ASSEMBLY_DEF

struct list_head {
    struct list_head *prev, *next;
};

static inline void __list_add(struct list_head *prev, struct list_head *new, struct list_head *next){
    prev -> next = new;
    new -> prev = prev;
    new -> next = next;
    next -> prev = new;
}

static inline void __list_del(struct list_head *prev, struct list_head *next){
    prev -> next = next;
    next -> prev = prev;
}

static inline void list_add(struct list_head *prev, struct list_head *new){
    __list_add(prev, new, new -> next);
}

static inline void list_del(struct list_head *head){
    __list_del(head -> prev, head -> next);

    head -> prev = NULL;
    head -> next = NULL;
}
#endif
#endif
