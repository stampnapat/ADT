#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100003 // ใช้จำนวนเฉพาะที่ใหญ่กว่า n max เพื่อลด collision

// --- 1. โครงสร้างข้อมูลสำหรับ SuffixList ---
typedef struct {
    int* suffixes;
    int count;
    int capacity;
} SuffixList;

SuffixList* create_suffix_list() {
    SuffixList* list = malloc(sizeof(SuffixList));
    list->capacity = 8; // เริ่มต้นด้วยขนาด 8
    list->suffixes = malloc(sizeof(int) * list->capacity);
    list->count = 0;
    return list;
}

void add_suffix(SuffixList* list, int suffix) {
    if (list->count == list->capacity) {
        list->capacity *= 2;
        list->suffixes = realloc(list->suffixes, sizeof(int) * list->capacity);
    }
    list->suffixes[list->count++] = suffix;
}

int contains_suffix(SuffixList* list, int suffix) {
    for (int i = 0; i < list->count; i++) {
        if (list->suffixes[i] == suffix) {
            return 1; // Found
        }
    }
    return 0; // Not found
}

void free_suffix_list(SuffixList* list) {
    free(list->suffixes);
    free(list);
}


// --- 2. โครงสร้างข้อมูลสำหรับ Hash Table ---
typedef struct Entry {
    char* key;
    SuffixList* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** entries;
    int size;
} HashTable;

// ฟังก์ชัน hash แบบ djb2
unsigned long hash_function(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

HashTable* create_table(int size) {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = size;
    table->entries = calloc(size, sizeof(Entry*));
    return table;
}

SuffixList* ht_get(HashTable* table, const char* key) {
    unsigned long slot = hash_function(key) % table->size;
    Entry* entry = table->entries[slot];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void ht_set(HashTable* table, const char* key, SuffixList* value) {
    unsigned long slot = hash_function(key) % table->size;
    Entry* entry = table->entries[slot];

    if (entry == NULL) {
        table->entries[slot] = malloc(sizeof(Entry));
        table->entries[slot]->key = strdup(key);
        table->entries[slot]->value = value;
        table->entries[slot]->next = NULL;
        return;
    }
    
    // จัดการ Collision (chaining)
    Entry* prev;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            // Key exist, should not happen in this problem logic
            // but for safety, free old value if any
            free_suffix_list(entry->value);
            entry->value = value;
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    prev->next = malloc(sizeof(Entry));
    prev->next->key = strdup(key);
    prev->next->value = value;
    prev->next->next = NULL;
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Entry* entry = table->entries[i];
        while (entry != NULL) {
            Entry* next = entry->next;
            free(entry->key);
            free_suffix_list(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(table->entries);
    free(table);
}


// --- 3. Main Logic ---
int main() {
    int n;
    scanf("%d", &n);

    HashTable* db = create_table(TABLE_SIZE);
    char s[22]; // ความยาวไม่เกิน 20 + null terminator + buffer

    for (int i = 0; i < n; i++) {
        scanf("%s", s);

        // แยกส่วนประกอบ
        int len = strlen(s);
        int split_point = len;
        while (split_point > 0 && isdigit(s[split_point - 1])) {
            split_point--;
        }

        char base_name[22];
        strncpy(base_name, s, split_point);
        base_name[split_point] = '\0';
        
        int suffix_num = 0;
        if (split_point < len) {
            suffix_num = atoi(&s[split_point]);
        }
        
        SuffixList* used_suffixes = ht_get(db, base_name);

        if (used_suffixes == NULL) { // กรณีชื่อหลักใหม่
            printf("OK\n");
            SuffixList* new_list = create_suffix_list();
            add_suffix(new_list, suffix_num);
            ht_set(db, base_name, new_list);
        } else { // กรณีชื่อหลักเคยมีแล้ว
            if (!contains_suffix(used_suffixes, suffix_num)) {
                printf("OK\n");
                add_suffix(used_suffixes, suffix_num);
            } else {
                int k = 1;
                while (contains_suffix(used_suffixes, k)) {
                    k++;
                }
                printf("Change to %s%d\n", base_name, k);
                add_suffix(used_suffixes, k);
            }
        }
    }

    free_table(db);
    return 0;
}
