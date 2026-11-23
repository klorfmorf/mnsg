#ifndef MACROS_H
#define MACROS_H

#include "common.h"

// ===== wave_uty =====
#define WAVE_DECODE_MAX 48

// ===== anime =====
#define ANIME_REF_SOLID(solid, v)                                                                           \
    ((s_anime_ref = (v))                                                                                    \
            ? ((s_anime_ref & 0x80000000) ? s_anime_ref                                                     \
                  : (s_anime_ref > 0x08000000)                                                              \
                      ? (solid)->SegWave[((s_anime_ref >> 24) & 0xF) - 8].data + (s_anime_ref & 0x80FFFFFF) \
                      : (solid)->SegWave[0].data + (s_anime_ref & 0x80FFFFFF))                              \
            : 0)
#define ANIME_REF(v)                ANIME_REF_SOLID(g_anime_solid, v)
#define KEY(i)                      (s_anime_keys[i])
#define JOINT_AT(j, i)              ((AnimeJoint *) ((int) (j) + (i) * 0x18))
#define NEG_IF_HALF_TURN(ra, rb, c) ((ra) == 0x8000 || (rb) == 0x8000 ? -(c) : 0.0f)

// ===== is_debug =====
#define IS_DEBUG_BUFFER      ((IsDebug *) 0xB1FF0000)
#define IS_DEBUG_MAGIC       0x49533634
#define IS_DEBUG_BUFFER_SIZE 0xFFE0
#define KMC_DEBUG_ADDR       ((int *) 0xBFF00000)

// ===== sched =====
#define OS_SC_STACKSIZE 0x2000

#define OS_SC_RETRACE_MSG  1
#define OS_SC_DONE_MSG     2
#define OS_SC_RDP_DONE_MSG 3
#define OS_SC_PRE_NMI_MSG  4
#define OS_SC_LAST_MSG     4 // this should have highest number
#define OS_SC_MAX_MESGS    8

// OSScTask flags
#define OS_SC_NEEDS_RDP     0x0001 // uses the RDP
#define OS_SC_NEEDS_RSP     0x0002 // uses the RSP
#define OS_SC_DRAM_DLIST    0x0004 // SP & DP communicate through DRAM
#define OS_SC_PARALLEL_TASK 0x0010 // must be first gfx task on list
#define OS_SC_LAST_TASK     0x0020 // last task in queue for frame
#define OS_SC_SWAPBUFFER    0x0040 // swapbuffers when gfx task done

#define OS_SC_RCP_MASK  0x0003 // mask for needs bits
#define OS_SC_TYPE_MASK 0x0007 // complete type mask

// ===== pic =====
#define PIC_NO_COLOR ((int) 0x80000000)

// ===== rom_trans =====
#define LOAD_FILE_MAX       0x520
#define LOAD_VRAM_START(id) D_80054ACC[(unsigned int) (((id) - 1) * 2) + 0]
#define LOAD_VRAM_END(id)   D_80054ACC[(unsigned int) (((id) - 1) * 2) + 1]
#define LOAD_ROM_START(id)  (D_800573C8.offsets[(id) - 1] & 0x7FFFFFFF)
#define LOAD_ROM_END(id)    (D_800573C8.offsets[(id) - 1 + 1] & 0x7FFFFFFF)

// ===== string =====
#define TEXT_LABEL_NONE        0
#define TEXT_LABEL_STRING      1
#define TEXT_LABEL_HEXADECIMAL 2

// ===== task =====
#define TASK_STATUS_FIELD_UPDATE   0x01
#define TASK_STATUS_MENU_UPDATE    0x02
#define TASK_STATUS_SUSPEND_UPDATE 0x04
#define TASK_STATUS_SUSPEND_DRAW   0x10
#define TASK_STATUS_MENU_DRAW      0x40
#define TASK_STATUS_FIELD_DRAW     0x80
#define TASK_STATUS_UPDATE_MASK    0x07
#define TASK_STATUS_DRAW_MASK      0xD0

// ===== sys =====
#define GAME_STEP_INIT             0x00
#define GAME_STEP_PAK_MANAGER      0x01
#define GAME_STEP_CONTROLLER_CHECK 0x02
#define GAME_STEP_KONAMI_LOGO      0x03
#define GAME_STEP_TEAM_LOGO        0x04
#define GAME_STEP_TITLE            0x05
#define GAME_STEP_OPENING          0x06
#define GAME_STEP_DEMO             0x07
#define GAME_STEP_DIARY            0x08
#define GAME_STEP_INTRO            0x09
#define GAME_STEP_LEVEL_SELECT     0x0A
#define GAME_STEP_WARP_SAVE        0x0B
#define GAME_STEP_WARP_NEXT        0x0C
#define GAME_STEP_PLAY             0x0D
#define GAME_STEP_GAME_OVER        0x0E
#define GAME_STEP_OPTIONS          0x0F
#define GAME_STEP_STAFF_ROLL_START 0x10
#define GAME_STEP_STAFF_ROLL       0x11

#endif // MACROS_H
