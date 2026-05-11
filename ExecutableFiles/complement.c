#include "../DeclarationFiles/complement.h"

// --- IMPLEMENTACIÓN LISTA ---
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

struct List {
    Node *head;
    Node *tail;
    Node *current;
};

List *list_create() {
    List *L = (List *)malloc(sizeof(List));
    L->head = L->tail = L->current = NULL;
    return L;
}

void list_pushBack(List *L, void *dato) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = dato;
    newNode->next = NULL;
    if (L->tail == NULL) {
        L->head = L->tail = newNode;
    } else {
        L->tail->next = newNode;
        L->tail = newNode;
    }
}

void *list_first(List *L) {
    if (L == NULL || L->head == NULL) return NULL;
    L->current = L->head;
    return L->current->data;
}

void *list_next(List *L) {
    if (L == NULL || L->current == NULL || L->current->next == NULL) return NULL;
    L->current = L->current->next;
    return L->current->data;
}

int list_erase(List *L, void *dato) {
    Node *actual = L->head;
    Node *anterior = NULL;
    while (actual != NULL) {
        if (actual->data == dato) {
            if (anterior == NULL) L->head = actual->next;
            else anterior->next = actual->next;
            if (actual == L->tail) L->tail = anterior;
            free(actual);
            return 1;
        }
        anterior = actual;
        actual = actual->next;
    }
    return 0;
}

// --- IMPLEMENTACIÓN MAPA (HASH MAP) ---
typedef struct HashNode {
    char key[500]; 
    void *value;
    struct HashNode *next;
} HashNode;

struct Map {
    HashNode **buckets;
    int capacity;
    int current_bucket;
    HashNode *current_node;
};

unsigned int hash(const char *key, int capacity) {
    unsigned int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key++;
    }
    return hash_val % capacity;
}

Map *map_create(int capacity) {
    Map *M = (Map *)malloc(sizeof(Map));
    M->capacity = capacity;
    M->buckets = (HashNode **)calloc(capacity, sizeof(HashNode *));
    M->current_bucket = -1;
    M->current_node = NULL;
    return M;
}

void map_insert(Map *M, const char *key, void *value) {
    unsigned int idx = hash(key, M->capacity);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    strncpy(newNode->key, key, 499); 
    newNode->key[499] = '\0';
    newNode->value = value;
    newNode->next = M->buckets[idx];
    M->buckets[idx] = newNode;
}

void *map_search(Map *M, const char *key) {
    unsigned int idx = hash(key, M->capacity);
    HashNode *temp = M->buckets[idx];
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) return temp->value;
        temp = temp->next;
    }
    return NULL;
}

void *map_first(Map *M) {
    for (int i = 0; i < M->capacity; i++) {
        if (M->buckets[i] != NULL) {
            M->current_bucket = i;
            M->current_node = M->buckets[i];
            return M->current_node->value;
        }
    }
    return NULL;
}

void *map_next(Map *M) {
    if (M->current_node != NULL && M->current_node->next != NULL) {
        M->current_node = M->current_node->next;
        return M->current_node->value;
    }
    for (int i = M->current_bucket + 1; i < M->capacity; i++) {
        if (M->buckets[i] != NULL) {
            M->current_bucket = i;
            M->current_node = M->buckets[i];
            return M->current_node->value;
        }
    }
    return NULL;
}