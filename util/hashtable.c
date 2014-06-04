#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "hashtable.h"

HashTable* hashtable_init(int length)
{
    int i;
    
    HashTable *hashtable = malloc(sizeof(HashTable));
    hashtable->elements = malloc(sizeof(char*) * length);
    hashtable->keys = malloc(sizeof(char*) * length);
    hashtable->length = length;
    
    for (i = 0; i < length; i++) {
        hashtable->keys[i] = NULL;
    }
    
    return hashtable;
}

void hashtable_put(HashTable* hashtable, const char* key, void* element)
{
    int index = hash(key, 0, hashtable->length);
    int i = 0;
    
    printf("hashtable_put: %s: %i, %s\n", key, index, hashtable->keys[index]);
    
    while (hashtable->keys[index] != NULL) {
        index = hash(key, ++i, hashtable->length);
    }
    
    hashtable->elements[index] = (char*) element;
    hashtable->keys[index] = key;
}

void* hashtable_get(HashTable* hashtable, const char* key)
{
    int index = hash(key, 0, hashtable->length);
    int i = 0;
    
    while (hashtable->keys[index] != NULL && strcmp(hashtable->keys[index], key) != 0) {
        if (hashtable->keys[index] == NULL) {
            return NULL;
        }
        
        index = hash(key, ++i, hashtable->length);
    }
    
    return (void*)hashtable->elements[index];
}

void hashtable_destroy(HashTable* hashtable)
{
    free(hashtable->elements);
    free(hashtable);
}

static int hash(const char* key, int run, int max)
{
    int value = 0;
    int key_length = strlen(key);
    int i;
    
    for (i = 0; i < key_length; i++) {
        value += key[i];
    }
    
    return (value + (int) pow(-1, run) * (int) pow((run / 2), 2)) % max;
}

