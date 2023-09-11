#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Table_Size 10  // Adjust the table size as needed

// Define a struct to hold key-value pairs
struct KeyValuePair {
    char* key;
    char* value;
};

// Define a hash table structure
struct HashTable {
    struct KeyValuePair** table;
    int size;
};

// Hash function to generate an index for a given key
int hash_fun(const char* key, int table_size) {
    int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash += key[i];
    }
    return hash % table_size;
}

// Create a new key-value pair
struct KeyValuePair* createPair(const char* key, const char* value) {
    struct KeyValuePair* pair = malloc(sizeof(struct KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    return pair;
}

// Initialize a new hash table
struct HashTable* createTable() {
    struct HashTable* table = malloc(sizeof(struct HashTable));
    table->table = malloc(sizeof(struct KeyValuePair*) * Table_Size);
    table->size = Table_Size;
    for (int i = 0; i < Table_Size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

// Insert a key-value pair into the hash table
void insert(struct HashTable* table, const char* key, const char* value) {
    int index = hash_fun(key, table->size);
    struct KeyValuePair* pair = createPair(key, value);
    table->table[index] = pair;
}

// Find the value associated with a key
const char* find(struct HashTable* table, const char* key) {
    int index = hash_fun(key, table->size);
    struct KeyValuePair* pair = table->table[index];
    if (pair && strcmp(pair->key, key) == 0) {
        return pair->value;
    }
    return NULL;  // Key not found
}

// Search for a key and print its value
void search_key(struct HashTable* table, const char* key) {
    const char* value = find(table, key);
    if (value) {
        printf("Value for key '%s': %s\n", key, value);
    } else {
        printf("Key '%s' not found\n", key);
    }
}

// Remove a key-value pair from the hash table
void removePair(struct HashTable* table, const char* key) {
    int index = hash_fun(key, table->size);
    struct KeyValuePair* pair = table->table[index];
    if (pair && strcmp(pair->key, key) == 0) {
        free(pair->key);
        free(pair->value);
        free(pair);
        table->table[index] = NULL;
    }
}

// Cleanup and free memory
void freeTable(struct HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->table[i]) {
            free(table->table[i]->key);
            free(table->table[i]->value);
            free(table->table[i]);
        }
    }
    free(table->table);
    free(table);
}

int main() {
    struct HashTable* h_table = createTable();

    insert(h_table, "A", "100");
    insert(h_table, "B", "200");
    insert(h_table, "C", "300");
    insert(h_table, "D", "400");
    insert(h_table, "E", "500");
    insert(h_table, "F", "600");
    insert(h_table, "G", "700");
    insert(h_table, "H", "800");
    insert(h_table, "I", "900");
    insert(h_table, "J", "1000");
    insert(h_table, "K", "1100");
    


    search_key(h_table, "A");
    search_key(h_table, "B");
    search_key(h_table, "C");
    search_key(h_table, "D");  // A key that doesn't exist
    search_key(h_table, "E");
    search_key(h_table, "J");
    search_key(h_table, "K");
    search_key(h_table, "L");
    search_key(h_table, "M");
    removePair(h_table, "A");
     
    search_key(h_table, "A");  // After removal

     freeTable(h_table);
    return 0;
}
