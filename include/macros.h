#ifndef MACROS_H
#define MACROS_H

#include "common.h"

// ===== screen =====
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// ===== math =====
#define ABS(x) ((x) < 0 ? -(x) : (x))

#define ANGLE_FULL    1024
#define ANGLE_HALF    512
#define ANGLE_QUARTER 256
#define ANGLE_MASK    0x3FF

#define ANGLE_BILLBOARD 0x8000

// ===== wave_uty =====
#define WAVE_DECODE_MAX 48

#define WAVE_SEGMENT       8
#define WAVE_SEGMENT_ADDR  0x08000000
#define WAVE_SEGMENT_COUNT 6

#define WAVE_OFFSET_MASK 0x80FFFFFF

#define WAVE_DATA_TLB 0x40000000

// ===== anime =====
#define ANIME_KIND_MASK 0x70000000
#define ANIME_PROXY     0x00000001 // Draw the proxy display list in place of each model.
#define ANIME_REF_MASK  0x8FFFFFFE

#define ANIME_ADDR_MASK 0x8FFFFFFF

#define ANIME_GLIST_LOOKAT 0x10000000 // Load look-at vectors after executing the display list.
#define ANIME_GLIST_COPY   0x20000000 // Copy the display list into the frame list instead of calling it.
#define ANIME_GLIST_RELOAD 0x40000000 // Re-execute the display list and reload lights for each model.

#define ANIME_NO_MODEL 0x0FFFFF00

#define ANIME_HDR_LOCAL(hdr)   (((hdr) / 0x80000000) & 1)
#define ANIME_HDR_CAMERAS(hdr) (((hdr) >> 28) & 7)
#define ANIME_HDR_LIGHTS(hdr)  (((hdr) >> 24) & 0xF)
#define ANIME_HDR_ROOTS(hdr)   (((hdr) >> 8) & 0x7FFF)
#define ANIME_HDR_FRAMES(hdr)  ((hdr) & 0xFF)

#define ANIME_ROT_BILLBOARD 0x4000

#define ANIME_TRACK_MASK       0xBFFF // Masks out ANIME_ROT_BILLBOARD.
#define ANIME_TRACK_CONST_MIN  0xA000
#define ANIME_TRACK_CONST_BIAS 0xB000
#define ANIME_TRACK_FIXED      0x8000 // Sample frame 0 only.
#define ANIME_TRACK_INDEX_MASK 0x7FFF

#define ANIME_TARGET_MASK      0xF0000000
#define ANIME_TARGET_NTH_JOINT 0xF0000000
#define ANIME_TARGET_NTH_ROOT  0xE0000000

#define ANIME_REF_SOLID(solid, v)                                                                                            \
    ((s_anime_ref = (v))                                                                                                     \
            ? ((s_anime_ref & K0BASE) ? s_anime_ref                                                                          \
                  : (s_anime_ref > WAVE_SEGMENT_ADDR)                                                                        \
                      ? (solid)->SegWave[((s_anime_ref >> 24) & 0xF) - WAVE_SEGMENT].data + (s_anime_ref & WAVE_OFFSET_MASK) \
                      : (solid)->SegWave[0].data + (s_anime_ref & WAVE_OFFSET_MASK))                                         \
            : 0)
#define ANIME_REF(v)                ANIME_REF_SOLID(g_anime_solid, v)
#define KEY(i)                      (s_anime_keys[i])
#define JOINT_AT(j, i)              ((AnimeJoint *) ((int) (j) + (i) * 0x18))
#define NEG_IF_HALF_TURN(ra, rb, c) ((ra) == ANGLE_BILLBOARD || (rb) == ANGLE_BILLBOARD ? -(c) : 0.0f)

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
#define OS_SC_LAST_MSG     4 // Must hold the highest message ID.
#define OS_SC_MAX_MESGS    8

// OSScTask flags.
#define OS_SC_NEEDS_RDP     0x0001 // Task uses the RDP.
#define OS_SC_NEEDS_RSP     0x0002 // Task uses the RSP.
#define OS_SC_DRAM_DLIST    0x0004 // RSP and RDP communicate through DRAM.
#define OS_SC_PARALLEL_TASK 0x0010 // Must be the first graphics task in the list.
#define OS_SC_LAST_TASK     0x0020 // Last task in the frame queue.
#define OS_SC_SWAPBUFFER    0x0040 // Swap frame buffers upon graphics task completion.

#define OS_SC_RCP_MASK  0x0003 // Mask for RCP requirement flags.
#define OS_SC_TYPE_MASK 0x0007 // Mask for all task type flags.

// ===== pic =====
#define PIC_NO_COLOR ((int) 0x80000000)

// ===== rom_trans =====
#define LOAD_FILE_MAX       0x520
#define LOAD_VRAM_START(id) D_80054ACC[(unsigned int) (((id) - 1) * 2) + 0]
#define LOAD_VRAM_END(id)   D_80054ACC[(unsigned int) (((id) - 1) * 2) + 1]
#define LOAD_ROM_START(id)  (D_800573C8.offsets[(id) - 1] & LOAD_ROM_MASK)
#define LOAD_ROM_END(id)    (D_800573C8.offsets[(id) - 1 + 1] & LOAD_ROM_MASK)

#define LOAD_ROM_COMPRESSED 0x80000000
#define LOAD_ROM_MASK       0x7FFFFFFF

// ===== obj =====
#define OBJ_KIND_NONE  0
#define OBJ_KIND_2D    1
#define OBJ_KIND_SOLID 2
#define OBJ_KIND_MOJI  3
#define OBJ_KIND_BG    4
#define OBJ_KIND_GBG   5
#define OBJ_HIDDEN     0x80
#define OBJ_KIND_MASK  0x7F

#define LAYER_SORT_ENABLE  0x01
#define LAYER_SORT_REVERSE 0x80

#define SPRITE_ATTR_SCROLL_LAYER 0x000F // Index of the ObjMoji layer used for scrolling.
#define SPRITE_ATTR_CLIP_LAYER   0x00F0 // Index of the ObjMoji layer used for clipping.
#define SPRITE_ATTR_SCROLL_X     0x0100
#define SPRITE_ATTR_SCROLL_Y     0x0200
#define SPRITE_ATTR_CLIP         0x0400
#define SPRITE_ATTR_KILL_OFF_X   0x2000 // Free the sprite when it leaves the clip area.
#define SPRITE_ATTR_KILL_OFF_Y   0x4000
#define SPRITE_ATTR_PALETTE      0x8000 // Sprite uses an associated palette.

#define SPRITE_PART_TEX_MASK 0x1FFF
#define SPRITE_PART_SKIP     0x2000
#define SPRITE_PART_TEXTURE  0x4000 // Load the texture index specified in the low bits before drawing.
#define SPRITE_PART_END      0x8000

#define SPRITE_FMT_TYPE_MASK 0x07
#define SPRITE_FMT_SIZE_MASK 0x18
#define SPRITE_FMT_4B        0x00
#define SPRITE_FMT_8B        0x08
#define SPRITE_FMT_16B       0x10
#define SPRITE_PALETTE_NONE  0xFF

// ===== pal =====
#define PAL_ENTRY_CLEAR 0xFE
#define PAL_ENTRY_KEEP  0xFF

// ===== gbg =====
#define GBG_CI       0x0001
#define GBG_IA       0x0002
#define GBG_4B       0x0004
#define GBG_8B       0x0008 // 8-bit texture; defaults to 16-bit if neither GBG_4B nor GBG_8B is set.
#define GBG_XLU      0x0010
#define GBG_CUTOUT   0x0020
#define GBG_RAW_DATA 0x2000 // Caller provides texture_data and palette_data directly.
#define GBG_CLIP     0x4000 // Clip to min_x and max_y instead of wrapping by texture size.
#define GBG_PANORAMA 0x8000 // 640-texel CI8 image drawn at double size.

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

// ===== audiomgr =====
#define AUDIO_STACKSIZE 0x4000

// ===== yamamoto =====
#define LINK2D_WORK(task) ((Link2DWork *) (task)->work)
#define LINK3D_WORK(task) ((Link3DWork *) (task)->work)

// ===== ripple =====
#define RIPPLE_WORK(task) ((RippleWork *) (task)->work)

#define RIPPLE_SMOOTH         0x000001 // Compute vertex normals.
#define RIPPLE_TEXTURED       0x000002
#define RIPPLE_MIRROR_S       0x000004
#define RIPPLE_MIRROR_T       0x000010
#define RIPPLE_XLU            0x000040
#define RIPPLE_HILITE         0x000080
#define RIPPLE_LOOKAT         0x000100
#define RIPPLE_NO_SIMULATE    0x000200 // Disable wave height simulation.
#define RIPPLE_DOUBLE_BUFFER  0x000400 // Allocate separate vertex and display list buffers per graphics pool.
#define RIPPLE_COPY_GLIST     0x000800
#define RIPPLE_SCROLL         0x001000 // Enable two scrolling texture layers.
#define RIPPLE_REBUILD        0x002000 // Rebuild display lists every frame when RIPPLE_COPY_GLIST is set.
#define RIPPLE_FOG            0x004000
#define RIPPLE_STATIC_BUFFERS 0x010000 // Buffers are managed by the caller.
#define RIPPLE_CI4            0x100000

#define GDP_LOAD_MULTI_BLOCK_AT(pkt, timg, tmem, rtile, width, height, uls, ult, masks, maskt)                       \
    {                                                                                                                \
        gDPSetTextureImage(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, timg);                                               \
        gDPSetTile(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, tmem, G_TX_LOADTILE, 0,                                      \
            G_TX_WRAP | G_TX_NOMIRROR, maskt, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, masks, G_TX_NOLOD);             \
        gDPLoadSync(pkt);                                                                                            \
        gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0, (width) * (height) - 1, CALC_DXT(width, G_IM_SIZ_16b_BYTES));         \
        gDPPipeSync(pkt);                                                                                            \
        gDPSetTile(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((width) * G_IM_SIZ_16b_LINE_BYTES) + 7) >> 3, tmem, rtile, 0, \
            G_TX_WRAP | G_TX_NOMIRROR, maskt, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, masks, G_TX_NOLOD);             \
        gDPSetTileSize(pkt, rtile, uls, ult, ((width) - 1) << G_TEXTURE_IMAGE_FRAC,                                  \
            ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                                                 \
    }

// ===== fade =====
#define FADE_WORK(task) ((FadeWork *) (task)->work)

// ===== okutani =====
#define FLASH_WORK(task)    ((FlashWork *) (task)->work)
#define VELOCITY_WORK(task) ((VelocityWork *) (task)->work)
#define TINT_WORK(task)     ((TintWork *) (task)->work)

// ===== vram =====
#define COL_HIT      0x7FFF
#define COL_LIST_END 0xFFFF

// ===== controller_pak =====
#define PAK_COMPANY_CODE 0x4134     // "A4" (Konami).
#define PAK_GAME_CODE    0x4E473545 // "NG5E".

#define PAK_HEADER_SIZE 256
#define PAK_SLOT_SIZE   1280
#define PAK_FILE_SIZE   (PAK_HEADER_SIZE + 3 * PAK_SLOT_SIZE)

#define PAK_ERR_NO_PAK        0x100
#define PAK_ERR_NO_CONTROLLER 0x101
#define PAK_ERR_CRC           0x102
#define PAK_ERR_VIBRATION_PAK 0x200

// ===== rom_queue =====
#define WAVE_REQ_WAIT_SWAP 0x20000000 // Defer loading until the graphics pool swaps.
#define WAVE_REQ_LAST      0x40000000 // Marks the final request in the queue.
#define WAVE_REQ_ID_MASK   0x0FFFFFFF

// ===== scenario =====
#define SCRIPT_OP_EQ         0x8002
#define SCRIPT_OP_NE         0x8003
#define SCRIPT_OP_LET        0x8004
#define SCRIPT_OP_IF         0x8006
#define SCRIPT_OP_END        0x8008
#define SCRIPT_OP_SET        0x8009
#define SCRIPT_OP_JUMP       0x800A
#define SCRIPT_OP_CALL       0x800B
#define SCRIPT_OP_LT         0x800C
#define SCRIPT_OP_GT         0x800D
#define SCRIPT_OP_LE         0x800E
#define SCRIPT_OP_GE         0x800F
#define SCRIPT_OP_TEXT       0x8010
#define SCRIPT_OP_MENU       0x8011
#define SCRIPT_OP_MENU_END   0x8012
#define SCRIPT_OP_ADD        0x8013
#define SCRIPT_OP_SUB        0x8014
#define SCRIPT_OP_COPY       0x8015
#define SCRIPT_OP_SET_PRINT  0x8016
#define SCRIPT_OP_SET_PRINT2 0x8017
#define SCRIPT_OP_FLAG_SET   0x8020
#define SCRIPT_OP_FLAG_CLEAR 0x8021
#define SCRIPT_OP_FLAG_JUMP  0x8022
#define SCRIPT_OP_EQ_VAR     0x8030
#define SCRIPT_OP_NE_VAR     0x8031
#define SCRIPT_OP_LT_VAR     0x8032
#define SCRIPT_OP_GT_VAR     0x8033
#define SCRIPT_OP_LE_VAR     0x8034
#define SCRIPT_OP_GE_VAR     0x8035

#define SCRIPT_FACE_NONE 0x100

#define SCRIPT_HELD_WORK(task) ((ScriptHeldWork *) (task)->work)
#define SCRIPT_WORK(task)      ((ScriptWork *) (task)->work)

// ===== sd_location =====
#define SOUND_TASK_WORK(task) ((SoundTaskWork *) (task)->work)

// ===== solid_atari =====
#define SOLID_SEG_ADDR(solid, v)                                                                                 \
    (((v) != 0) ? (((v) & K0BASE) ? (v)                                                                          \
                      : ((v) > WAVE_SEGMENT_ADDR)                                                                \
                          ? (solid)->SegWave[(((v) >> 24) & 0xF) - WAVE_SEGMENT].data + ((v) & WAVE_OFFSET_MASK) \
                          : (solid)->SegWave[0].data + ((v) & WAVE_OFFSET_MASK))                                 \
                : 0)

// ===== dracam =====
#define DRACAM_WORK(task) ((DracamWork *) (task)->work)
#define DRALIG_WORK(task) ((DraligWork *) (task)->work)

#define DRACAM_MOVING_EYE_X 0x01
#define DRACAM_MOVING_EYE_Y 0x02
#define DRACAM_MOVING_EYE_Z 0x04
#define DRACAM_MOVING_AT_X  0x08
#define DRACAM_MOVING_AT_Y  0x10
#define DRACAM_MOVING_AT_Z  0x20
#define DRACAM_MOVING_FOVY  0x40

#define DRACAM_DIST(a, b) (((a) < (b)) ? -((a) - (b)) : ((a) - (b)))

#define DRACAM_STEP(value, target, speed)               \
    if (1e-05 < (speed)) {                              \
        if (DRACAM_DIST((target), (value)) < (speed)) { \
            (value) = (target);                         \
            (speed) = 0.0f;                             \
        } else if ((target) < (value)) {                \
            (value) -= (speed);                         \
        } else {                                        \
            (value) += (speed);                         \
        }                                               \
    }

// ===== file_12 =====
#define ENEMY_MGR        ((EnemyMgr *) D_8015CC30)
#define ENEMY_WORK(task) ((EnemyWork *) (task)->work)

// ===== file_11 =====
#define PLAYER_GRAVITY                        0.6666666f
#define PLAYER_WORK(task)                     ((PlayerWork *) (task)->work)
#define PLAYER_FX_WORK(task)                  ((PlayerFxWork *) (task)->work)
#define PLAYER_STOP(task)                     (PLAYER_WORK(task)->max_speed = 0.0f, PLAYER_WORK(task)->move_accel = 1.0f)
#define PLAYER_SET_ACTION(task, action, func) (PLAYER_WORK(task)->state = (action), func_8003521C((void (*)(Task *, Obj *))(func)))

// ===== 5907F0 =====
#define CAMERA_WORK(task) ((CameraWork *) (task)->work)

// ===== 5AE300 =====
#define PLAYER_EFFECT_WORK(task) ((PlayerEffectWork *) (task)->work)

#endif // MACROS_H
