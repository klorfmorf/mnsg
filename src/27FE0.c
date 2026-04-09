#include "common.h"

typedef struct COL_PLANE {
    f32 normal_x;
    f32 normal_y;
    f32 normal_z;
    f32 distance;
    s8  type;
} COL_PLANE;

typedef struct COL_TREE {
    u16 next_tree;
    u16 type;
    u16 scale;
    s16 box_max_x;
    s16 box_max_y;
    s16 box_max_z;
    s16 box_min_x;
    s16 box_min_y;
    s16 box_min_z;
} COL_TREE;

typedef struct COL_NODE {
    u16 a;
    s16 b;
    s16 c;
} COL_NODE;

extern COL_PLANE* D_80168F60_169B60;
extern COL_NODE*  D_80168F64_169B64;

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_800273E0_27FE0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_800277C0_283C0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_80027A7C_2867C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_80027B38_28738.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_800283E8_28FE8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_80028B28_29728.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_80028BC0_297C0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_80029560_2A160.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_80029E08_2AA08.s")

s32 func_80029E58_2AA58(f32 origin_x, f32 origin_y, f32 origin_z, f32 scale, void* p, void* n) {
    int TERMINATE = 0xFFFF;
    
    u8 *nodes;
    u16 node;
    s32 next_tree;
    
    COL_PLANE *planes;
    s32 plane;
    
    f32 normal_x;
    f32 normal_y;
    f32 normal_z;
    f32 distance;
    f32 dot_product;
    f32 signed_distance;
    
    s16 back;
    s16 front;

    node = 0;

    planes = (COL_PLANE*)p;
    nodes = (u8*)n;

    while (1) {
        next_tree = ((u16*)((u8*)nodes + (node * 6)))[0];

        while ((((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_max_x * scale) < origin_x || origin_x < (((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_min_x * scale) ||
               (((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_max_z * scale) < origin_z || origin_z < (((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_min_z * scale) ||
               (((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_max_y * scale) < origin_y || origin_y < (((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_min_y * scale)) {
            if (next_tree == TERMINATE) {
                return 0;
            }
            
            node = next_tree;
            next_tree = ((u16*)((u8*)nodes + (next_tree * 6)))[0];
        }

        node += 3;

        while (1) {
            plane = ((u16*)((u8*)nodes + (node * 6)))[0];
            
            normal_x = planes[plane].normal_x;
            normal_y = planes[plane].normal_y;
            normal_z = planes[plane].normal_z;
            distance = planes[plane].distance * scale;

            dot_product = (origin_x * normal_x) + (origin_y * normal_y) + (origin_z * normal_z);
            signed_distance = dot_product + distance;

            if (signed_distance < 0.0) {
                /* Behind the plane */
                back = ((s16*)((u8*)nodes + (node * 6)))[1];
                
                if (back == 0) {
                    /* In solid space */
                    return 0x7FFF;
                } else {
                    /* This node not a leaf, jump to its back child */
                    node = back;
                }
            } else {
                /* In front of the plane */
    	        front = ((s16*)((u8*)nodes + (node * 6)))[2];
                
                if (front == 0) {
                    /* In empty space, terminate or jump to the next tree structure */
                    if (next_tree == TERMINATE) {
                        /* In empty space */
                        return 0;
                    }

                    /* Another tree exists, break out of the inner loop */
                    node = next_tree;
                    break;
                } else {
                    /* This node not a leaf, jump to its front child */
                    node = front;   
                }
            }
        }
    }
}

s32 func_8002A168_2AD68(f32 origin_x, f32 origin_y, f32 origin_z) {
    int TERMINATE = 0xFFFF;
    
    u8 *nodes;
    u16 node;
    s32 next_tree;
    
    COL_PLANE *planes;
    s32 plane;
    
    f32 normal_x;
    f32 normal_y;
    f32 normal_z;
    f32 distance;
    f32 dot_product;
    f32 signed_distance;
    
    s16 back;
    s16 front;

    node = 0;
    
    if (D_80168F60_169B60 == 0) {
        return 0;
    }
    
    planes = (COL_PLANE*)D_80168F60_169B60;
    nodes = (u8*)D_80168F64_169B64;

    while (1) {
        next_tree = ((u16*)((u8*)nodes + (node * 6)))[0];

        while (((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_max_x < origin_x || origin_x < ((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_min_x ||
               ((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_max_y < origin_y || (origin_y + 10.0f) < ((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_min_y ||
               ((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_max_z < origin_z || origin_z < ((COL_TREE*)((u8*)nodes + node * sizeof(COL_NODE)))->box_min_z) {
            if (next_tree == TERMINATE) {
                return 0;
            }
            
            node = next_tree;
            next_tree = ((u16*)((u8*)nodes + (next_tree * 6)))[0];
        }

        node += 3;

        while (1) {
            plane = ((u16*)((u8*)nodes + (node * 6)))[0];
            
            normal_x = planes[plane].normal_x;
            normal_y = planes[plane].normal_y;
            normal_z = planes[plane].normal_z;
            distance = planes[plane].distance;

            dot_product = (origin_x * normal_x) + (origin_y * normal_y) + (origin_z * normal_z);
            signed_distance = dot_product + distance;

            if (signed_distance < 0.0) {
                /* Behind the plane */
                back = ((s16*)((u8*)nodes + (node * 6)))[1];
                
                if (back == 0) {
                    /* In solid space */
                    return 0x7FFF;
                } else {
                    /* This node not a leaf, jump to its back child */
                    node = back;
                }
            } else {
                /* In front of the plane */
    	        front = ((s16*)((u8*)nodes + (node * 6)))[2];
                
                if (front == 0) {
                    /* In empty space, terminate or jump to the next tree structure */
                    if (next_tree == TERMINATE) {
                        /* In empty space */
                        return 0;
                    }

                    /* Another tree exists, break out of the inner loop */
                    node = next_tree;
                    break;
                } else {
                    /* This node not a leaf, jump to its front child */
                    node = front;   
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_8002A458_2B058.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_8002A718_2B318.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_8002A750_2B350.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/27FE0/func_8002A7BC_2B3BC.s")
