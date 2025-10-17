#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100003

typedef struct {
    char* name;
} Entry;

Entry database[TABLE_SIZE];

unsigned int hash1(const char* str) {
    unsigned long hash_value = 5381;
    int c;
    while ((c = *str++)) {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    return hash_value % TABLE_SIZE;
}

unsigned int hash2(const char* str) {
    unsigned long hash_value = 0;
    int c;
    while ((c = *str++)) {
        hash_value = c + (hash_value << 6) + (hash_value << 16) - hash_value;
    }
    return (hash_value % (TABLE_SIZE - 1)) + 1;
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
       database[i].name = NULL;
    }
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char input_name[22];
        scanf("%s", input_name);

        unsigned int index = hash1(input_name);
        unsigned int step = hash2(input_name);
        int is_found = 0;

        while (database[index].name != NULL) {
            if (strcmp(database[index].name, input_name) == 0) {
                is_found = 1;
                break;
            }
            index = (index + step) % TABLE_SIZE;
        }

        if (!is_found) {
           database[index].name = strdup(input_name);
           printf("OK\n");
        }else {
            int len = strlen(input_name);
            int split_point = len;
            while (split_point > 0 && isdigit(input_name[split_point - 1])) {
                split_point--;
           }
           char base_name[22];
           strncpy(base_name, input_name, split_point);
          base_name[split_point] = '\0';

         for (int k = 1; ; k++) {
             char new_name[22];
                sprintf(new_name, "%s%d", base_name, k);

                unsigned int new_index = hash1(new_name);
               unsigned int new_step = hash2(new_name);
               int new_name_is_found = 0;

               while (database[new_index].name != NULL) {
                   if (strcmp(database[new_index].name, new_name) == 0) {
                       new_name_is_found = 1;
                       break;
                   }
                    new_index = (new_index + new_step) % TABLE_SIZE;
               }

               if (!new_name_is_found) {
                  database[new_index].name = strdup(new_name);
                  printf("Change to %s\n", new_name);
                 break;
             }
         }
     }
  }

    return 0;
}
