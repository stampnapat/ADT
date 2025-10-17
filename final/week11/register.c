#include <stdio.h>
#include <string.h>

// สร้างฐานข้อมูลแบบ Global เพื่อให้ง่ายต่อการเข้าถึง
// กำหนดขนาดเผื่อไว้ตามโจทย์
char database[100001][22];
int user_count = 0;

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char input_name[22];
        scanf("%s", input_name);

        // --- ขั้นตอนที่ 1: ตรวจสอบว่าชื่อซ้ำหรือไม่ ---
        int is_found = 0;
        for (int j = 0; j < user_count; j++) {
            if (strcmp(input_name, database[j]) == 0) {
                is_found = 1;
                break;
            }
        }

        // --- ขั้นตอนที่ 2: ดำเนินการ ---

        // กรณี A: ไม่ซ้ำ
        if (is_found == 0) {
            printf("OK\n");
            strcpy(database[user_count], input_name);
            user_count++;
        }
        // กรณี B: ซ้ำ
        else {
            // 1. หา "ชื่อหลัก" (base_name)
            int len = strlen(input_name);
            int split_point = len;
            while (split_point > 0 && (input_name[split_point - 1] >= '0' && input_name[split_point - 1] <= '9')) {
                split_point--;
            }
            char base_name[22];
            strncpy(base_name, input_name, split_point);
            base_name[split_point] = '\0';

            // 2. วน Loop หา k ที่น้อยที่สุดที่ยังว่าง
            for (int k = 1; ; k++) {
                char new_name[22];
                sprintf(new_name, "%s%d", base_name, k);

                // ตรวจสอบว่า "ชื่อใหม่" ที่สร้างขึ้น ซ้ำกับใน database อีกหรือไม่
                int new_name_is_found = 0;
                for (int j = 0; j < user_count; j++) {
                    if (strcmp(new_name, database[j]) == 0) {
                        new_name_is_found = 1;
                        break;
                    }
                }

                // ถ้าไม่ซ้ำ ก็ใช้ชื่อนี้ได้เลย
                if (new_name_is_found == 0) {
                    printf("Change to %s\n", new_name);
                    strcpy(database[user_count], new_name);
                    user_count++;
                    break; // ออกจาก loop ของ k
                }
            }
        }
    }

    return 0;
}
