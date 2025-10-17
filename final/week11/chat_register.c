#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100003

typedef struct Entry {
    char* name;
    struct Entry* next;
} Entry;

Entry* database[TABLE_SIZE] = {NULL};

unsigned int hash(const char* str) {
    unsigned long hash_value = 5381;
    int c;
    while ((c = *str++)) {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    return hash_value % TABLE_SIZE;
}

int find_name_in_chain(Entry* head, const char* name) {
    Entry* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void add_name_to_chain(Entry** head, const char* name) {
    Entry* new_entry = malloc(sizeof(Entry));
    new_entry->name = strdup(name);
    new_entry->next = *head;
    *head = new_entry;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char input_name[22];
        scanf("%s", input_name);

        unsigned int index = hash(input_name);

        if (find_name_in_chain(database[index], input_name)) {
            int len = strlen(input_name);
            int split_point = len;
            while (split_point > 0 && (input_name[split_point - 1] >= '0' && input_name[split_point - 1] <= '9')) {
                split_point--;
            }
            char base_name[22];
            strncpy(base_name, input_name, split_point);
            base_name[split_point] = '\0';

            for (int k = 1; ; k++) {
                char new_name[22];
                sprintf(new_name, "%s%d", base_name, k);

                unsigned int new_index = hash(new_name);
                if (!find_name_in_chain(database[new_index], new_name)) {
                    printf("Change to %s\n", new_name);
                    add_name_to_chain(&database[new_index], new_name);
                    break;
                }
            }
        } else {
            printf("OK\n");
            add_name_to_chain(&database[index], input_name);
        }
    }

    return 0;
}
