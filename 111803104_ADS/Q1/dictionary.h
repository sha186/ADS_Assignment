typedef struct dict *Dict;

/* create a new empty dictionary */
Dict create(void);

/* destroy a dictionary */
void destroy(Dict);

/* insert a new key-value pair into an existing dictionary */
void insert(Dict, const char *key, const char *value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *search(Dict, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void Delete(Dict, const char *key);

/* update(change) the value of a particular key */
void update(Dict, char *key, char *value);

/* sort in descending order */
void sortdesc(Dict);

/* sort in ascending order */
void sortasc(Dict);

/* partition used in quicksort */
int partition(char **key, char **value, int, int, int);

/* quicksort*/
void quicksort(char **key, char **value, int, int, int);
