#ifndef COMPLEMENT_H
#define COMPLEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- TDA Lista ---
typedef struct List List;

List *list_create();
void list_pushBack(List *L, void *dato);
void *list_first(List *L);
void *list_next(List *L);
void list_clean(List *L);
int list_erase(List *L, void *dato);

// --- TDA Mapa (Hash Map) ---
typedef struct Map Map;

Map *map_create(int capacity);
void map_insert(Map *M, const char *key, void *value);
void *map_search(Map *M, const char *key);
void *map_first(Map *M);
void *map_next(Map *M);

#endif