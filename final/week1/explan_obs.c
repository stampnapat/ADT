#include <stdio.h>                      // ใช้ scanf/printf
#include <stdlib.h>                     // ใช้ malloc/free

#define MAX_NODES 200005                // ขนาดสูงสุดของจำนวนโหนดที่รองรับ
#define NEEDS_COVER 0                   // สถานะ: ยังไม่ถูกครอบคลุม (ต้องให้พ่อครอบ)
#define HAS_TOWER   1                   // สถานะ: โหนดนี้มีเสา
#define COVERED     2                   // สถานะ: ถูกครอบคลุมโดยลูกที่มีเสา

struct node {                           // โครงสร้างของ adjacency list (linked list)
    int city;                           // ปลายทางของเส้นเชื่อม (เพื่อนบ้าน)
    struct node* next;                  // พอยน์เตอร์ไปโหนดลิสต์ตัวถัดไป
};

struct node* adj_list[MAX_NODES];       // อาเรย์เก็บหัวลิสต์ของเพื่อนบ้านแต่ละโหนด
int status[MAX_NODES];                  // สถานะของแต่ละโหนด (0/1/2 ตาม define)
int visited[MAX_NODES];                 // ทำเครื่องหมายว่าถูกเยี่ยมแล้ว (ใช้ตอนวิ่งข้ามคอมโพเนนต์)
int total_towers = 0;                   // ตัวนับจำนวนเสาทั้งหมด

void add_edge(int u, int v) {                                           // เพิ่มเส้นเชื่อม u-v แบบสองทิศ
    struct node* new_node1 = (struct node*)malloc(sizeof(struct node)); // สร้างโหนดลิสต์สำหรับ u -> v
    new_node1->city = v;                                                // ตั้งปลายทางเป็น v
    new_node1->next = adj_list[u];                                      // ชี้ไปยังหัวลิสต์เดิมของ u
    adj_list[u] = new_node1;                                            // อัปเดตหัวลิสต์ของ u ให้เป็นโหนดใหม่

    struct node* new_node2 = (struct node*)malloc(sizeof(struct node)); // สร้างโหนดลิสต์สำหรับ v -> u
    new_node2->city = u;                                                // ตั้งปลายทางเป็น u
    new_node2->next = adj_list[v];                                      // ชี้ไปยังหัวลิสต์เดิมของ v
    adj_list[v] = new_node2;                                            // อัปเดตหัวลิสต์ของ v ให้เป็นโหนดใหม่
}

void dfs(int current_city, int parent_city) {               // DFS แบบ post-order, รู้ว่าพ่อคือใคร
    visited[current_city] = 1;                              // ทำเครื่องหมายว่าโหนดนี้ถูกเยี่ยมแล้ว

    struct node* temp = adj_list[current_city];             // temp ไว้ไล่เพื่อนบ้านของโหนดปัจจุบัน
    while (temp != NULL) {                                  // วนเพื่อนบ้านทั้งหมด
        int neighbor_city = temp->city;                     // เพื่อนบ้านตัวหนึ่ง
        if (neighbor_city != parent_city) {                 // ข้ามพ่อ (ไม่ย้อนกลับ)
            dfs(neighbor_city, current_city);               // ลงไปประมวลผลลูกก่อน (post-order)
        }
        temp = temp->next;                                  // ไปเพื่อนบ้านตัวถัดไป
    }

    int child_needs_cover = 0;                              // ตัวแปรเช็คว่ามีลูกที่ยัง NEEDS_COVER ไหม
    temp = adj_list[current_city];                          // รีเซ็ต temp เพื่อไล่ดูอีกรอบ
    while (temp != NULL) {                                  // วนเพื่อนบ้านของ current อีกครั้ง
        int neighbor_city = temp->city;                     // เพื่อนบ้าน
        if (neighbor_city != parent_city &&                 // ไม่ใช่พ่อ
            status[neighbor_city] == NEEDS_COVER) {         // และลูกคนนั้นยังไม่ถูกครอบคลุม
            child_needs_cover = 1;                          // เจอแล้วว่ามีลูกต้องการให้ครอบ
            break;                                          // พอเลย ไม่ต้องหาเพิ่ม
        }
        temp = temp->next;                                  // ไปเพื่อนบ้านตัวถัดไป
    }

    if (child_needs_cover) {                                // ถ้ามีลูกที่ NEEDS_COVER
        status[current_city] = HAS_TOWER;                   // ต้องวางเสาที่โหนดปัจจุบัน
        total_towers++;                                     // เพิ่มจำนวนเสา
    } else {                                                // ไม่งั้น (ไม่มีลูกที่ต้องให้ครอบ)
        int child_has_tower = 0;                            // เช็คว่ามีลูกที่มีเสาไหม
        temp = adj_list[current_city];                      // รีเซ็ต temp
        while (temp != NULL) {                              // วนเพื่อนบ้านอีกรอบ
            int neighbor_city = temp->city;                 // เพื่อนบ้าน
            if (neighbor_city != parent_city &&             // ไม่ใช่พ่อ
                status[neighbor_city] == HAS_TOWER) {       // ถ้าลูกสักคนมีเสา
                child_has_tower = 1;                        // โหนดปัจจุบันถูกครอบคลุมได้
                break;                                      // หยุดได้
            }
            temp = temp->next;                              // ไปเพื่อนบ้านตัวถัดไป
        }
        
        if (child_has_tower) {                              // ถ้าลูกมีเสาอย่างน้อยหนึ่งคน
            status[current_city] = COVERED;                 // โหนดปัจจุบันจึงเป็นสถานะ COVERED
        } else {                                            // ถ้าไม่มีลูกมีเสา และไม่มีลูก NEEDS_COVER
            status[current_city] = NEEDS_COVER;             // ปัจจุบันยังไม่ถูกครอบ ต้องให้พ่อครอบ
        }
    }
}

int main() {
    int num_edges;                                          // จำนวนเส้นเชื่อมทั้งหมด (รวมทุกคอมโพเนนต์)
    scanf("%d", &num_edges);                                // อ่านจำนวนเส้นเชื่อม

    int max_id = 0;                                         // ไว้เก็บหมายเลขโหนดสูงสุดที่พบ
    for (int i = 0; i < num_edges; i++) {                   // อ่านเส้นเชื่อมทีละเส้น
        int u, v;                                           // โหนดต้นทางและปลายทาง
        scanf("%d %d", &u, &v);                             // อ่านคู่โหนด
        add_edge(u, v);                                     // เพิ่มเส้นเชื่อมสองทิศทางใน adjacency list
        
        if (u > max_id) max_id = u;                         // อัปเดตโหนดสูงสุดที่เห็น
        if (v > max_id) max_id = v;                         // อัปเดตโหนดสูงสุดที่เห็น
    }

    for (int i = 0; i <= max_id; i++) {                     // ไล่ทุกหมายเลขโหนดตั้งแต่ 0..max_id
        if (adj_list[i] != NULL && !visited[i]) {           // ถ้าโหนดนี้อยู่ในกราฟ และยังไม่ถูกเยี่ยม
            dfs(i, -1);                                     // เริ่ม DFS คอมโพเนนต์นี้ โดยให้พ่อ = -1
            if (status[i] == NEEDS_COVER) {                 // หลัง DFS ถ้ารูทยังคง NEEDS_COVER
                total_towers++;                             // ต้องวางเสาที่รูทด้วย
            }
        }
    }

    printf("%d\n", total_towers);                           // พิมพ์จำนวนเสารวม

    return 0;                                               // จบโปรแกรม
}

