#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

typedef struct
{
    int length;
    char** elements;
    const char** keys;
} HashTable;

HashTable* hashtable_init(int length);
void hashtable_put(HashTable* hashtable, const char* key, void* element);
void* hashtable_get(HashTable* hashtable, const char* key);
void hashtable_destroy(HashTable* hashtable);

static int hash(const char* key, int run, int max);

#endif
