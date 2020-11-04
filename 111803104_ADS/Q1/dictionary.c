#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "dictionary.h"

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)
#define MULTIPLIER (97)

struct elt{
    struct elt *next;
    char *key;
    char *value;
};

struct dict{
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
};


/* dictionary initialization code used in both create and grow */
Dict internalcreate(int size){
    Dict d;
    int i;

    d = malloc(sizeof(*d));

    assert(d != 0);

    d->size = size;
    d->n = 0;
    d->table = malloc(sizeof(struct elt *) * d->size);

    assert(d->table != 0);

    for(i = 0; i < d->size; i++) d->table[i] = 0;

    return d;
}


Dict create(void){
    return internalcreate(INITIAL_SIZE);
}


void destroy(Dict d){
    int i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            free(e->value);
            free(e);
        }
    }

    free(d->table);
    free(d);
}


static unsigned long hash_function(const char *s){
    unsigned const char *us;
    unsigned long h;

    h = 0;

    for(us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
    }

    return h;
}


static void grow(Dict d){
    Dict d2;            /* new dictionary we'll create */
    struct dict swap;   /* temporary structure for brain transplant */
    int i;
    struct elt *e;

    d2 = internalcreate(d->size * GROWTH_FACTOR);

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = e->next) {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * patch out the strdups inside DictInsert
             * to avoid this problem */
            insert(d2, e->key, e->value);
        }
    }

    /* the hideous part */
    /* We'll swap the guts of d and d2 */
    /* then call DictDestroy on d2 */
    swap = *d;
    *d = *d2;
    *d2 = swap;

    destroy(d2);
}


/* insert a new key-value pair into an existing dictionary */
void insert(Dict d, const char *key, const char *value){
    struct elt *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = malloc(sizeof(*e));

    assert(e);

    e->key = strdup(key);
    e->value = strdup(value);

    h = hash_function(key) % d->size;

    e->next = d->table[h];
    d->table[h] = e;

    d->n++;
    //printf("%ld\n", h);
    /* grow table if there is not enough room */
    if(d->n >= d->size * MAX_LOAD_FACTOR) {
        grow(d);
    }
}


/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *search(Dict d, const char *key){
    struct elt *e;
    int count = 0;
    for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next) {
        if(!strcmp(e->key, key)) {
            /* got it */
            count++;
            return e->value;
        }
    }
    printf("%d", count);
    return 0;
}


//update function
void update(Dict d, char *key, char *value){
	struct elt *e;
	for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next) {
        if(!strcmp(e->key, key)) {
            /* got it */
           free(e->value);
           e->value = strdup(value);
           break;
        }
    }

    
	
}


/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void Delete(Dict d, const char *key){
    struct elt **prev;          /* what to change when elt is deleted */
    struct elt *e;              /* what to delete */

    for(prev = &(d->table[hash_function(key) % d->size]); *prev != 0; prev = &((*prev)->next)){
        if(!strcmp((*prev)->key, key)){
            /* got it */
            e = *prev;
            *prev = e->next;

            free(e->key);
            free(e->value);
            free(e);
		  d->n--;
            return;
        }
    }
}


/* sort in ascending order */
void sortasc(Dict d){
    int flag = 0;
    int i;
    char **key;
    char **value;
    key = (char **)malloc(d->n * sizeof(char*));
    value = (char **)malloc(d->n * sizeof(char *));
    struct elt *e;
    int c = 0;
    struct elt *next;
    for(i =0; i < d->size - 1; i++){
        for (e = d->table[i]; e != 0; e = next)
        {   
            next = e->next;
            key[c] = (char *)malloc(strlen(e->key) + 1);
            value[c] = (char *)malloc(strlen(e->value) + 1);
            key[c] = strdup(e->key);
            value[c] = strdup(e->value);
            c++;
            
        }
        
    }
    quicksort(key, value, 0, d->n - 1, flag);
    for(i = 0; i < d->n ; i++){
        printf("%s: %s\n", key[i], value[i]);
    }
}


/* sort in descending order */
void sortdesc(Dict d){

    int flag = 1;
    int i;
    char **key;
    char **value;
    key = (char **)malloc(d->n* sizeof(char*));
    value = (char **)malloc(d->n * sizeof(char*));
    struct elt *e;
    int c = 0;
    int prevc = 0;
    struct elt *next;
    for(i = 0; i < d->size; i++){
        for (e = d->table[i]; e != 0; e = next)
        {
            next = e -> next;
            key[c] = (char*)malloc(strlen(e->key) + 1);
            value[c] = (char*)malloc(strlen(e->value) + 1);
            key[c] = strdup(e->key);
            value[c] = strdup(e->value);
            c++;
        }
    }
    quicksort(key, value, 0, d->n - 1, flag);
    for(i = 0; i < d->n ; i++){
        printf("%s: %s\n", key[i], value[i]);
    }
    
}


/* partition */
int partition(char **key, char **value, int start, int end, int flag){
    char x[100000];
    strcpy(x,key[end]);
    char temp[100000];
    char temp2[100000];
    int i = start;
    int j = 0;
    for(j = start; j <end; j++){
    	   if(flag == 1){
		   if(strcmp(key[j],x) >= 0){
		       //swap
		       strcpy(temp, key[j]);
		       strcpy(temp2, value[j]);
		       free(key[j]);
		       free(value[j]);
		       key[j] = (char*)malloc(strlen(key[i]) + 1);
		       value[j] = (char*)malloc(strlen(value[i]) + 1);
		       strcpy(key[j], key[i]);
		       strcpy(value[j], value[i]);
		       free(key[i]);
		       free(value[i]);
		       key[i] = (char *)malloc(strlen(temp) + 1);
		       value[i] = (char*)malloc(strlen(temp2) + 1);
		       strcpy(key[i], temp);
		       strcpy(value[i], temp2);
		       i += 1;
		   }
	   }
	   if(flag == 0){
		   if(strcmp(key[j],x) <= 0){
		       //swap
		       strcpy(temp, key[j]);
		       strcpy(temp2, value[j]);
		       free(key[j]);
		       free(value[j]);
		       key[j] = (char*)malloc(strlen(key[i]) + 1);
		       value[j] = (char*)malloc(strlen(value[i]) + 1);
		       strcpy(key[j], key[i]);
		       strcpy(value[j], value[i]);
		       free(key[i]);
		       free(value[i]);
		       key[i] = (char *)malloc(strlen(temp) + 1);
		       value[i] = (char*)malloc(strlen(temp2) + 1);
		       strcpy(key[i], temp);
		       strcpy(value[i], temp2);
		       i += 1;
		   }
	   }
    }

    //swap i and end
    strcpy(temp, key[i]);
    strcpy(temp2, value[i]);
    free(key[i]);
    free(value[i]);
    key[i] = (char *)malloc(strlen(key[end]) + 1);
    value[i] = (char *)malloc(strlen(value[end]) + 1);
    strcpy(key[i], key[end]);
    strcpy(value[i], value[end]);
    free(key[end]);
    free(value[end]);
    key[end] = (char *)malloc(strlen(temp) + 1);
    value[end] = (char*)malloc(strlen(temp2) + 1);
    strcpy(key[end], temp);
    strcpy(value[end], temp2);
    return i;
}


/* quicksort */
void quicksort(char **key, char **value, int start, int end, int flag){
    if(start < end){
        int p = partition(key,value,start, end, flag);
        quicksort(key, value, start, p - 1, flag);
        quicksort(key, value, p+1, end, flag);
    }
}
