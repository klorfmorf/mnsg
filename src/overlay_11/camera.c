#include "common.h"
#define sqrtf _nsqrtf

/*
 * Camera overlay structure map.
 *
 * Existing common.h matches:
 *
 * TASK_W is the base of the main camera work block. The overlay keeps camera
 * state after TASK_W's 0x5c-byte header and uses the inherited callback/data
 * fields at 0x08, 0x0c, 0x10, and 0x18.
 *
 * Used as CAMERA_TASK_WORK by:
 * func_801D23C0_58E2D0, func_801D23D4_58E2E4,
 * func_801D26FC_58E60C, func_801D27A4_58E6B4,
 * func_801D2B8C_58EA9C, func_801D2BF8_58EB08,
 * func_801D2C40_58EB50, func_801D2C88_58EB98,
 * func_801D2E10_58ED20, func_801D2F64_58EE74,
 * func_801D313C_58F04C, func_801D3494_58F3A4,
 * func_801D3A04_58F914, func_801D416C_59007C,
 * func_801D46F8_590608, func_801D4828_590738,
 * func_801D48E0_5907F0, func_801D4BF0_590B00,
 * func_801D51A8_5910B8, func_801D5214_591124,
 * func_801D5374_591284, func_801D54C0_5913D0,
 * func_801D5708_591618, func_801D5DC0_591CD0,
 * func_801D5ECC_591DDC, func_801D5FA8_591EB8,
 * func_801D6098_591FA8, func_801D6164_592074,
 * func_801D628C_59219C, func_801D6444_592354,
 * func_801D650C_59241C, func_801D65FC_59250C,
 * func_801D6710_592620, func_801D67C4_5926D4,
 * func_801D6A98_5929A8, func_801D6B80_592A90,
 * func_801D7058_592F68, func_801D7194_5930A4,
 * func_801D72D4_5931E4, func_801D7818_593728,
 * func_801D7868_593778, func_801D7900_593810,
 * func_801D7C20_593B30, func_801D7DD0_593CE0,
 * func_801D80F4_594004, func_801D8290_5941A0,
 * func_801D85B0_5944C0, func_801D8634_594544,
 * func_801D896C_59487C, func_801D8E08_594D18,
 * func_801D8E94_594DA4, func_801D8F74_594E84,
 * func_801D8F94_594EA4, func_801D90D8_594FE8,
 * func_801D9480_595390, func_801D978C_59569C.
 *
 * CLS_BG_W matches the render/model work blocks at D_801FC60C, D_801FC614,
 * D_801FC61C, D_801FC628, and D_801FC634. Confirmed common.h fields include
 * tx/ty/tz at 0x08/0x0c/0x10, rx/ry/rz at 0x14/0x16/0x18, scale/time/model
 * fields through 0x30, SegWave at 0x34, and overlay flags/links from 0x64
 * onward.
 *
 * Used as CLS_BG_W by:
 * func_801D23D4_58E2E4, func_801D2D10_58EC20,
 * func_801D2E10_58ED20, func_801D2F64_58EE74,
 * func_801D416C_59007C, func_801D458C_59049C,
 * func_801D48E0_5907F0, func_801D4BF0_590B00,
 * func_801D5214_591124,
 * func_801D7058_592F68, func_801D80F4_594004,
 * func_801D8290_5941A0, func_801D8E94_594DA4,
 * func_801D90D8_594FE8, func_801D978C_59569C.
 *
 * Newly inferred overlay-local structs. Field names are provisional and are
 * based on access patterns only; field sizes and offsets are the important
 * facts to preserve while replacing typed offset accesses.
 *
 * typedef struct CAMERA_VEC3F {
 *     f32 x;
 *     f32 y;
 *     f32 z;
 * } CAMERA_VEC3F;
 *
 * Used by:
 * func_801D2F64_58EE74, func_801D4BF0_590B00,
 * func_801D55E0_5914F0, func_801D5A78_591988,
 * func_801D5DC0_591CD0, func_801D5ECC_591DDC,
 * func_801D5FA8_591EB8, func_801D6098_591FA8,
 * func_801D6B80_592A90, func_801D72D4_5931E4,
 * func_801D7720_593630, func_801D7900_593810,
 * func_801D7C20_593B30, func_801D7F20_593E30,
 * func_801D8034_593F44, func_801D8290_5941A0,
 * func_801D8634_594544, func_801D896C_59487C,
 * func_801D9480_595390.
 *
 * typedef struct CAMERA_VIEWPOINT_W {
 *     CAMERA_VEC3F pos;
 *     CAMERA_VEC3F target;
 *     u8 unk_18[2];
 *     u16 angle;
 *     f32 near_clip;
 *     f32 far_clip;
 *     u8 unk_24[0x3c];
 * } CAMERA_VIEWPOINT_W;
 *
 * Used by:
 * func_801D23D4_58E2E4, func_801D25EC_58E4FC,
 * func_801D26FC_58E60C, func_801D2734_58E644,
 * func_801D7058_592F68, func_801D8E94_594DA4,
 * func_801D90D8_594FE8.
 *
 * typedef struct CAMERA_ACTOR_WORK {
 *     u16 flags;
 *     u8 unk_02[2];
 *     f32 height;
 *     u8 unk_08[4];
 *     f32 offset_x_0c;
 *     u8 unk_10[4];
 *     f32 offset_z_14;
 *     u8 state_18;
 *     u8 unk_19[0x23];
 *     u8 unk_3c[0x1d];
 *     u8 flag_59;
 *     u8 unk_5a[0x1e];
 *     s8 camera_lock_78;
 *     u8 unk_79[0x0d];
 *     u16 flag_86;
 *     u8 unk_88[0x1c];
 *     u16 yaw_a4;
 *     u8 unk_a6[6];
 *     f32 distance_ac;
 *     f32 distance_b0;
 * } CAMERA_ACTOR_WORK;
 *
 * Used by:
 * func_801D27A4_58E6B4, func_801D48E0_5907F0,
 * func_801D5214_591124, func_801D65FC_59250C,
 * func_801D6A98_5929A8, func_801D80F4_594004,
 * func_801D8E08_594D18, func_801D8F94_594EA4,
 * func_801D90D8_594FE8.
 *
 * typedef struct CAMERA_TARGET_WORK {
 *     TASK_W task;
 *     CAMERA_ACTOR_WORK *tracked_actor;
 *     u8 mode_60;
 *     u8 lock_61;
 *     u8 flag_62;
 *     u8 unk_63;
 *     struct CAMERA_TASK_WORK *camera;
 *     f32 floor_y;
 *     u8 unk_6c[2];
 *     u16 pitch;
 *     f32 target_radius;
 *     u8 unk_74[0x10];
 *     CAMERA_VEC3F unk_84;
 *     s16 heading_90;
 *     u8 unk_92[2];
 *     u16 yaw;
 *     u8 unk_96[0x1e];
 *     CAMERA_VEC3F unk_b4;
 *     u8 unk_c0[0x0c];
 *     u8 state_cc;
 *     s8 state_cd;
 *     u8 unk_ce[0x1f];
 *     s8 cooldown_ed;
 * } CAMERA_TARGET_WORK;
 *
 * Used by:
 * func_801D23D4_58E2E4, func_801D27A4_58E6B4,
 * func_801D2D10_58EC20, func_801D2E10_58ED20,
 * func_801D313C_58F04C, func_801D48E0_5907F0,
 * func_801D5214_591124, func_801D5374_591284,
 * func_801D54C0_5913D0, func_801D650C_59241C,
 * func_801D65FC_59250C, func_801D72D4_5931E4,
 * func_801D80F4_594004, func_801D896C_59487C,
 * func_801D8F94_594EA4, func_801D90D8_594FE8,
 * func_801D9480_595390.
 *
 * typedef struct CAMERA_TASK_WORK {
 *     TASK_W task;
 *     u16 active;
 *     s8 mode_countdown;
 *     s8 settle_countdown;
 *     u8 flag_60;
 *     u8 force_update;
 *     u8 yaw_pending;
 *     u8 stable_frames;
 *     u16 base_yaw;
 *     u16 target_yaw;
 *     u16 prev_yaw;
 *     u16 orbit_yaw;
 *     u8 unk_6c[2];
 *     u16 pitch;
 *     u8 mode_step;
 *     u8 route_step;
 *     u8 unk_72;
 *     u8 pending_mode;
 *     f32 distance;
 *     u8 unk_78[0x19];
 *     s8 tune_91;
 *     s8 tune_92;
 *     s8 tune_93;
 *     s16 tune_94;
 *     s16 tune_96;
 *     u8 mode_id;
 *     s8 tune_99;
 *     s8 tune_9a;
 *     s8 tune_9b;
 *     s16 tune_9c;
 *     s16 tune_9e;
 *     u8 unk_a0[2];
 *     s8 flag_a2;
 *     u8 flag_a3;
 *     u8 unk_a4[4];
 *     u16 mode_flags;
 *     s8 flag_aa;
 *     s8 flag_ab;
 *     f32 follow_height;
 *     u16 zoom_current;
 *     u16 zoom_target;
 *     u8 unk_b4[2];
 *     u16 zoom_timer;
 *     u16 yaw_step;
 *     u16 pitch_step;
 *     u8 mode_group;
 *     u8 flags_bd;
 *     u8 unk_be[2];
 *     CAMERA_VEC3F path_pos;
 *     u16 path_yaw;
 *     u16 target_heading;
 *     s8 blend_timer;
 *     u8 current_mode;
 *     u8 scripted_mode;
 *     u8 mode_arg;
 *     s16 pitch_limit;
 *     s16 yaw_limit;
 *     f32 path_distance;
 *     u8 unk_dc[4];
 *     u8 overlay_frame;
 *     u8 overlay_state;
 *     u16 overlay_yaw;
 *     f32 distance_velocity;
 *     s8 mode_cooldown;
 * } CAMERA_TASK_WORK;
 *
 * typedef struct CAMERA_MODE_STEP {
 *     f32 distance;
 *     u16 pitch;
 *     u16 flags;
 * } CAMERA_MODE_STEP;
 *
 * typedef struct CAMERA_MODE_DEF {
 *     u8 unk_00[4];
 *     u16 flags;
 *     u8 default_step;
 *     u8 step_count;
 *     CAMERA_MODE_STEP step[3];
 *     s32 callback;
 *     u16 yaw;
 *     u8 unk_26[2];
 * } CAMERA_MODE_DEF;
 *
 * Used by:
 * func_801D25EC_58E4FC, func_801D27A4_58E6B4,
 * func_801D4828_590738, func_801D5214_591124,
 * func_801D6B80_592A90, func_801D896C_59487C.
 *
 * typedef struct CAMERA_PATH_POINT {
 *     u8 flags;
 *     u8 unk_01;
 *     s16 x;
 *     s16 y;
 *     s16 z;
 * } CAMERA_PATH_POINT;
 *
 * typedef struct CAMERA_PATH_SEGMENT {
 *     f32 dx;
 *     f32 dy;
 *     f32 dz;
 * } CAMERA_PATH_SEGMENT;
 *
 * typedef struct CAMERA_PATH_CANDIDATE {
 *     s16 heading;
 *     s16 unk_02;
 *     f32 x;
 *     f32 y;
 *     f32 z;
 *     f32 segment_distance;
 *     u8 segment_index;
 *     u8 unk_15[3];
 * } CAMERA_PATH_CANDIDATE;
 *
 * Used by:
 * func_801D313C_58F04C, func_801D3494_58F3A4,
 * func_801D3A04_58F914, func_801D4078_58FF88,
 * func_801D416C_59007C, func_801D458C_59049C,
 * func_801D46F8_590608.
 *
 * typedef struct CAMERA_OVERLAY_WORK {
 *     CLS_W header;
 *     u8 unk_08[0x28];
 *     s32 init_glist;
 *     u8 unk_34[0x30];
 *     u8 visible;
 *     u8 unk_65[0x1b];
 *     u16 rot_x;
 *     u16 rot_y;
 *     f32 dx;
 *     f32 dy;
 *     f32 dz;
 *     s16 heading;
 *     u16 pitch;
 * } CAMERA_OVERLAY_WORK;
 *
 * Used by:
 * func_801D23D4_58E2E4, func_801D6B80_592A90,
 * func_801D7058_592F68, func_801D8E94_594DA4,
 * func_801D90D8_594FE8, func_801D96E4_5955F4.
 *
 * typedef struct CAMERA_LIMIT_ENTRY {
 *     u16 mode;
 *     u16 min_yaw;
 *     u16 max_yaw;
 *     u16 unk_06;
 *     u16 divisor;
 *     u16 unk_0a;
 *     u16 unk_0c;
 * } CAMERA_LIMIT_ENTRY;
 *
 * Used by:
 * func_801D90D8_594FE8, func_801D9480_595390,
 * func_801D978C_59569C.
 *
 * typedef struct CAMERA_ROUTE_DATA {
 *     u8 unk_00[0x88];
 *     s32 point_offsets[1];
 * } CAMERA_ROUTE_DATA;
 *
 * Used by:
 * func_801D46F8_590608.
 *
 * typedef struct CAMERA_FRAME_OFFSET {
 *     f32 x;
 *     f32 z;
 * } CAMERA_FRAME_OFFSET;
 *
 * Used by:
 * func_801D4BF0_590B00.
 *
 * typedef struct CAMERA_INPUT_WORK {
 *     u8 unk_0000[0xb152];
 *     u16 buttons_held;
 *     u16 buttons_pressed;
 *     u8 unk_b156[0x1000a];
 *     f32 look_x;
 *     f32 look_y;
 * } CAMERA_INPUT_WORK;
 *
 * Used by:
 * func_801D6B80_592A90, func_801D896C_59487C.
 *
 * typedef struct CAMERA_SOLVE_WORK {
 *     u16 flag_00;
 *     u8 flag_02;
 *     u8 unk_03[0x0d];
 *     CAMERA_VEC3F scratch_vec;
 *     u8 unk_1c[4];
 *     CAMERA_VEC3F camera_vec;
 *     f32 distance;
 *     f32 distance_target;
 *     u16 yaw;
 *     u16 pitch;
 *     u16 roll;
 *     u8 unk_3a[2];
 *     f32 height;
 *     u16 yaw_target;
 *     u16 pitch_target;
 *     u16 roll_target;
 *     u8 unk_46[2];
 *     f32 height_target;
 *     u16 solve_flag;
 *     u16 blend_flag;
 *     u16 hit_flag;
 *     u16 last_heading;
 * } CAMERA_SOLVE_WORK;
 *
 * Used by:
 * func_801D27A4_58E6B4, func_801D2E10_58ED20,
 * func_801D2F64_58EE74, func_801D48E0_5907F0,
 * func_801D4BF0_590B00, func_801D5374_591284,
 * func_801D55E0_5914F0, func_801D56D0_5915E0,
 * func_801D5DC0_591CD0, func_801D5ECC_591DDC,
 * func_801D5FA8_591EB8, func_801D6098_591FA8,
 * func_801D6164_592074, func_801D628C_59219C,
 * func_801D6444_592354, func_801D650C_59241C,
 * func_801D65FC_59250C, func_801D6710_592620,
 * func_801D67C4_5926D4, func_801D6A98_5929A8,
 * func_801D6B80_592A90, func_801D7058_592F68,
 * func_801D7194_5930A4, func_801D72D4_5931E4,
 * func_801D7720_593630, func_801D7818_593728,
 * func_801D7868_593778, func_801D7900_593810,
 * func_801D7B74_593A84, func_801D7C20_593B30,
 * func_801D7DD0_593CE0, func_801D7F20_593E30,
 * func_801D8034_593F44, func_801D80F4_594004,
 * func_801D8290_5941A0, func_801D85B0_5944C0,
 * func_801D8634_594544, func_801D896C_59487C,
 * func_801D9480_595390.
 */

typedef struct CAMERA_VEC3F {
    f32 x;
    f32 y;
    f32 z;
} CAMERA_VEC3F;

typedef struct CAMERA_VIEWPOINT_W {
    CAMERA_VEC3F pos;
    CAMERA_VEC3F target;
    u8 unk_18[2];
    u16 angle;
    f32 near_clip;
    f32 far_clip;
    u8 unk_24[0x3C];
} CAMERA_VIEWPOINT_W;

typedef struct CAMERA_ACTOR_WORK {
    u16 flags;
    u8 unk_02[2];
    f32 height;
    u8 unk_08[4];
    f32 offset_x_0c;
    u8 unk_10[4];
    f32 offset_z_14;
    u8 state_18;
    u8 unk_19[0x23];
    u8 unk_3c[0x1D];
    u8 flag_59;
    u8 unk_5a[0x1E];
    s8 camera_lock_78;
    u8 unk_79[0x0D];
    u16 flag_86;
    u8 unk_88[0x1C];
    u16 yaw_a4;
    u8 unk_a6[6];
    f32 distance_ac;
    f32 distance_b0;
} CAMERA_ACTOR_WORK;

typedef struct CAMERA_TASK_WORK CAMERA_TASK_WORK;

typedef struct CAMERA_TARGET_WORK {
    TASK_W task;
    CAMERA_ACTOR_WORK *tracked_actor;
    u8 mode_60;
    u8 lock_61;
    u8 flag_62;
    u8 unk_63;
    CAMERA_TASK_WORK *camera;
    f32 floor_y;
    u8 unk_6c[2];
    u16 pitch;
    f32 target_radius;
    u8 unk_74[0x10];
    CAMERA_VEC3F unk_84;
    s16 heading_90;
    u8 unk_92[2];
    u16 yaw;
    u8 unk_96[0x1E];
    CAMERA_VEC3F unk_b4;
    u8 unk_c0[0x0C];
    u8 state_cc;
    s8 state_cd;
    u8 unk_ce[0x1F];
    s8 cooldown_ed;
} CAMERA_TARGET_WORK;

struct CAMERA_TASK_WORK {
    TASK_W task;
    u16 active;
    s8 mode_countdown;
    s8 settle_countdown;
    u8 flag_60;
    u8 force_update;
    u8 yaw_pending;
    u8 stable_frames;
    u16 base_yaw;
    u16 target_yaw;
    u16 prev_yaw;
    u16 orbit_yaw;
    u8 unk_6c[2];
    u16 pitch;
    u8 mode_step;
    u8 route_step;
    u8 unk_72;
    u8 pending_mode;
    f32 distance;
    u8 unk_78[0x19];
    s8 tune_91;
    s8 tune_92;
    s8 tune_93;
    s16 tune_94;
    s16 tune_96;
    u8 mode_id;
    s8 tune_99;
    s8 tune_9a;
    s8 tune_9b;
    s16 tune_9c;
    s16 tune_9e;
    u8 unk_a0[2];
    s8 flag_a2;
    u8 flag_a3;
    u8 unk_a4[4];
    u16 mode_flags;
    s8 flag_aa;
    s8 flag_ab;
    f32 follow_height;
    u16 zoom_current;
    u16 zoom_target;
    u8 unk_b4[2];
    u16 zoom_timer;
    u16 yaw_step;
    u16 pitch_step;
    u8 mode_group;
    u8 flags_bd;
    u8 unk_be[2];
    CAMERA_VEC3F path_pos;
    u16 path_yaw;
    u16 target_heading;
    s8 blend_timer;
    u8 current_mode;
    u8 scripted_mode;
    u8 mode_arg;
    s16 pitch_limit;
    s16 yaw_limit;
    f32 path_distance;
    u8 unk_dc[4];
    u8 overlay_frame;
    u8 overlay_state;
    u16 overlay_yaw;
    f32 distance_velocity;
    s8 mode_cooldown;
};

typedef struct CAMERA_MODE_STEP {
    f32 distance;
    u16 pitch;
    u16 flags;
} CAMERA_MODE_STEP;

typedef struct CAMERA_MODE_DEF {
    u8 unk_00[4];
    u16 flags;
    u8 default_step;
    u8 step_count;
    CAMERA_MODE_STEP step[3];
    s32 callback;
    u16 yaw;
    u8 unk_26[2];
} CAMERA_MODE_DEF;

typedef struct CAMERA_PATH_POINT {
    u8 flags;
    u8 unk_01;
    s16 x;
    s16 y;
    s16 z;
} CAMERA_PATH_POINT;

typedef struct CAMERA_PATH_SEGMENT {
    f32 dx;
    f32 dy;
    f32 dz;
} CAMERA_PATH_SEGMENT;

typedef struct CAMERA_PATH_CANDIDATE {
    s16 heading;
    s16 unk_02;
    f32 x;
    f32 y;
    f32 z;
    f32 segment_distance;
    u8 segment_index;
    u8 unk_15[3];
} CAMERA_PATH_CANDIDATE;

typedef struct CAMERA_OVERLAY_WORK {
    CLS_W header;
    u8 unk_08[0x28];
    s32 init_glist;
    u8 unk_34[0x30];
    u8 visible;
    u8 unk_65[0x1B];
    u16 rot_x;
    u16 rot_y;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 heading;
    u16 pitch;
} CAMERA_OVERLAY_WORK;

typedef struct CAMERA_LIMIT_ENTRY {
    u16 mode;
    u16 min_yaw;
    u16 max_yaw;
    u16 unk_06;
    u16 divisor;
    u16 unk_0a;
    u16 unk_0c;
} CAMERA_LIMIT_ENTRY;

typedef struct CAMERA_ROUTE_DATA {
    u8 unk_00[0x88];
    s32 point_offsets[1];
} CAMERA_ROUTE_DATA;

typedef struct CAMERA_FRAME_OFFSET {
    f32 x;
    f32 z;
} CAMERA_FRAME_OFFSET;

typedef struct CAMERA_INPUT_WORK {
    u8 unk_0000[0xB152];
    u16 buttons_held;
    u16 buttons_pressed;
    u8 unk_b156[0x1000A];
    f32 look_x;
    f32 look_y;
} CAMERA_INPUT_WORK;

typedef struct CAMERA_SOLVE_WORK {
    u16 flag_00;
    u8 flag_02;
    u8 unk_03[0x0D];
    CAMERA_VEC3F scratch_vec;
    u8 unk_1c[4];
    CAMERA_VEC3F camera_vec;
    f32 distance;
    f32 distance_target;
    u16 yaw;
    u16 pitch;
    u16 roll;
    u8 unk_3a[2];
    f32 height;
    u16 yaw_target;
    u16 pitch_target;
    u16 roll_target;
    u8 unk_46[2];
    f32 height_target;
    u16 solve_flag;
    u16 blend_flag;
    u16 hit_flag;
    u16 last_heading;
} CAMERA_SOLVE_WORK;

typedef struct CAMERA_FB_INIT_WORK {
    u8 unk_00[8];
    s32 mode;
    void *frame_buffer;
} CAMERA_FB_INIT_WORK;

#define CAMERA_TASK(ptr) ((CAMERA_TASK_WORK *)(ptr))
#define CAMERA_TARGET(ptr) ((CAMERA_TARGET_WORK *)(ptr))
#define CAMERA_ACTOR(ptr) ((CAMERA_ACTOR_WORK *)(ptr))
#define CAMERA_VIEW(ptr) ((CAMERA_VIEWPOINT_W *)(ptr))
#define CAMERA_BG(ptr) ((CLS_BG_W *)(ptr))
#define CAMERA_OVERLAY(ptr) ((CAMERA_OVERLAY_WORK *)(ptr))
#define CAMERA_TASK_EXEC_WORD(ptr, index) (*((s32 *)&CAMERA_TASK(ptr)->task.exec[index]))
#define CAMERA_SOLVE (*(CAMERA_SOLVE_WORK *)&D_8020D1A0_5C90B0)
#define CAMERA_MODE_TABLE ((CAMERA_MODE_DEF *)&D_801FC91C_5B882C)
#define CAMERA_PATH_POINTS ((CAMERA_PATH_POINT *)&D_8020CCB0_5C8BC0)
#define CAMERA_PATH_SEGMENTS ((CAMERA_PATH_SEGMENT *)&D_8020CE20_5C8D30)
#define CAMERA_PATH_CANDIDATES ((CAMERA_PATH_CANDIDATE *)&D_8020CF90_5C8EA0)
#define CAMERA_PATH_LENGTHS ((f32 *)&D_8020CDA0_5C8CB0)
#define CAMERA_PATH_LENGTHS_PREV ((f32 *)&D_8020CD9C_5C8CAC)
#define CAMERA_PATH_SCRATCH_DIST ((f32 *)&D_8020D088_5C8F98)
#define CAMERA_LIMIT_TABLE ((CAMERA_LIMIT_ENTRY *)&D_801FCC84_5B8B94)
#define CAMERA_FB_INIT ((CAMERA_FB_INIT_WORK *)&D_8006E0F0)
#define CAMERA_ROUTE(ptr) ((CAMERA_ROUTE_DATA *)(ptr))
#define CAMERA_FRAME_OFFSET(ptr) ((CAMERA_FRAME_OFFSET *)(ptr))
#define CAMERA_INPUT ((CAMERA_INPUT_WORK *)&D_800BCCC0_BD8C0)
#define CAMERA_OVERLAY_MODELS ((s32 *)&D_801FCC70_5B8B80)
#define CAMERA_OVERLAY_GLISTS ((s32 **)&D_801FCC5C_5B8B6C)
#define CAMERA_KSEG0(ptr) ((void *) ((s32) (ptr) + 0x20000000))
#define CAMERA_ROUTE_POINT(route, index) ((CAMERA_PATH_POINT *) ((s8 *) (route) + (route)->point_offsets[index]))
#define CAMERA_BG_FRAME_OFFSET(ptr) CAMERA_FRAME_OFFSET((s8 *) (ptr) + 0x80)

/* Data symbols referenced by the decompiler output. */
extern s32 D_8006D920_6E520;
extern s32 D_8006DFF8_6EBF8;
extern s32 D_8006E000;
extern s32 D_8006E008;
extern s32 D_8006E010;
extern s32 D_8006E018;
extern s32 D_8006E020_6EC20;
extern s32 D_8006E028;
extern s32 D_8006E0F0;
extern s32 D_8006E0F8;
extern s32 D_800BCCC0_BD8C0;
extern s32 D_800C7AA4;
extern s32 D_800C7AB2;
extern s32 D_800C7AE0;
extern s32 D_800C7AE8_C86E8;
extern s32 D_800C7DBC;
extern s32 D_801FC604_5B8514;
extern s32 D_801FC60C_5B851C;
extern s32 D_801FC614_5B8524;
extern s32 D_801FC61C_5B852C;
extern s32 D_801FC624_5B8534;
extern s32 D_801FC628_5B8538;
extern s32 D_801FC62C_5B853C;
extern s32 D_801FC634_5B8544;
extern s32 D_801FC7D0_5B86E0;
extern s32 D_801FC7E8_5B86F8;
extern s32 D_801FC848_5B8758;
extern s32 D_801FC8A8_5B87B8;
extern s32 D_801FC908_5B8818;
extern s32 D_801FC91C_5B882C;
extern s32 D_801FC928_5B8838;
extern s32 D_801FCBF0_5B8B00;
extern s32 D_801FCC00_5B8B10;
extern s32 D_801FCC5C_5B8B6C;
extern s32 D_801FCC70_5B8B80;
extern s32 D_801FCC84_5B8B94;
extern s32 D_801FCC8C_5B8B9C;
extern s32 D_8020AC2C_5C6B3C;
extern s32 D_8020AC30_5C6B40;
extern s32 D_8020AC38_5C6B48;
extern s32 D_8020AC40_5C6B50;
extern s32 D_8020AC50_5C6B60;
extern s32 D_8020AC58_5C6B68;
extern s32 D_8020AC60_5C6B70;
extern s32 D_8020AC68_5C6B78;
extern s32 D_8020AC70_5C6B80;
extern s32 D_8020AC78_5C6B88;
extern s32 D_8020AC80_5C6B90;
extern s32 D_8020AC88_5C6B98;
extern s32 D_8020AC90_5C6BA0;
extern s32 D_8020AC98_5C6BA8;
extern s32 D_8020ACA0_5C6BB0;
extern s32 D_8020ACA8_5C6BB8;
extern s32 D_8020ACB0_5C6BC0;
extern s32 D_8020ACB8_5C6BC8;
extern s32 D_8020ACC8_5C6BD8;
extern s32 D_8020ACD0_5C6BE0;
extern s32 D_8020ACD4_5C6BE4;
extern s32 D_8020ACD8_5C6BE8;
extern s32 D_8020ACE0_5C6BF0;
extern s32 D_8020ACE8_5C6BF8;
extern s32 D_8020ACF0_5C6C00;
extern s32 D_8020ACF8_5C6C08;
extern s32 D_8020ACFC_5C6C0C;
extern s32 D_8020AD00_5C6C10;
extern s32 D_8020AD08_5C6C18;
extern s32 D_8020CBF0_5C8B00;
extern s32 D_8020CC0C_5C8B1C;
extern s32 D_8020CC50_5C8B60;
extern s32 D_8020CCA8_5C8BB8;
extern s32 D_8020CCB0_5C8BC0;
extern s32 D_8020CD9C_5C8CAC;
extern s32 D_8020CDA0_5C8CB0;
extern s32 D_8020CE18_5C8D28;
extern s32 D_8020CE20_5C8D30;
extern s32 D_8020CF88_5C8E98;
extern s32 D_8020CF90_5C8EA0;
extern s32 D_8020D080_5C8F90;
extern s32 D_8020D088_5C8F98;
extern s32 D_8020D1A0_5C90B0;
extern s32 D_8020D1A2_5C90B2;
extern s32 D_8020D1B0_5C90C0;
extern s32 D_8020D1B4_5C90C4;
extern s32 D_8020D1C0_5C90D0;
extern s32 D_8020D1C4_5C90D4;
extern s32 D_8020D1C8_5C90D8;
extern s32 D_8020D1CC_5C90DC;
extern s32 D_8020D1D0_5C90E0;
extern s32 D_8020D1D4_5C90E4;
extern s32 D_8020D1D6_5C90E6;
extern s32 D_8020D1D8_5C90E8;
extern s32 D_8020D1DC_5C90EC;
extern s32 D_8020D1E0_5C90F0;
extern s32 D_8020D1E2_5C90F2;
extern s32 D_8020D1E4_5C90F4;
extern s32 D_8020D1E8_5C90F8;
extern s32 D_8020D1EC_5C90FC;
extern s32 D_8020D1EE_5C90FE;
extern s32 D_8020D1F0_5C9100;
extern s32 D_8020D1F2_5C9102;
extern s32 D_8020D200_5C9110;
extern s32 D_80261000;

/* External functions used by this translation unit. */
void *memcpy();
void *memset();
f32 _nsqrtf();
s32 func_80001C00_2800();
u16 func_80003A94_4694();
f32 func_80003CC8_48C8();
f32 func_80003D28_4928();
f32 func_80003D88_4988();
f32 func_80003DC0_49C0();
f32 func_80003F30_4B30();
s32 func_800148F0_154F0();
s32 func_80014B74_15774();
f32 func_8001B5AC_1C1AC();
s32 func_8001B918_1C518();
s32 func_8001C3E0_1CFE0();
s32 func_8001D394_1DF94();
s32 func_8001D460_1E060();
s32 func_8001D5B8_1E1B8();
s32 func_8001D718_1E318();
s32 func_8001DB04_1E704();
s32 func_8001E2BC_1EEBC();
s32 func_8001E4A4_1F0A4();
s32 func_8001EEF4_1FAF4();
s32 func_8001F2D8_1FED8();
s32 func_80029E08_2AA08();
s32 func_8002A458_2B058();
s32 func_8002A718_2B318();
s32 func_8002C9D4_2D5D4();
s32 func_80032850_33450();
s32 func_80035214_35E14();
s32 func_80035244_35E44();
void * func_80035854_36454();
s32 func_80035A5C_3665C();
void * func_80035EEC_36AEC();
s32 func_8003F1D8_3FDD8();
s32 func_801CF564_58B474();
s32 func_801E7DA0_5A3CB0();
s32 func_80221F70_5DD440();
s32 func_80221FB0_5DD480();

/* Camera functions. Old-style declarations keep m2c's uncertain call arity compileable. */
s32 func_801D23C0_58E2D0();
void func_801D23C8_58E2D8();
void func_801D23D4_58E2E4();
void func_801D25EC_58E4FC();
void func_801D26FC_58E60C();
void func_801D2734_58E644();
void func_801D27A4_58E6B4();
void func_801D2B58_58EA68();
void func_801D2B8C_58EA9C();
void func_801D2BD8_58EAE8();
void func_801D2BF8_58EB08();
void func_801D2C40_58EB50();
s32 func_801D2C88_58EB98();
void func_801D2D10_58EC20();
s32 func_801D2E10_58ED20();
void func_801D2F64_58EE74();
void func_801D313C_58F04C();
s8 func_801D3494_58F3A4();
u8 func_801D3A04_58F914();
f32 func_801D4078_58FF88();
void func_801D416C_59007C();
void func_801D458C_59049C();
void func_801D46F8_590608();
void func_801D4828_590738();
void func_801D48E0_5907F0();
s32 func_801D4BF0_590B00();
void func_801D51A8_5910B8();
void func_801D5214_591124();
void func_801D5338_591248();
void func_801D5374_591284();
void func_801D54C0_5913D0();
void func_801D55E0_5914F0();
u16 func_801D56D0_5915E0();
s32 func_801D5708_591618();
s8 func_801D5A78_591988();
u16 func_801D5DC0_591CD0();
u16 func_801D5ECC_591DDC();
u16 func_801D5FA8_591EB8();
u16 func_801D6098_591FA8();
void func_801D6164_592074();
void func_801D628C_59219C();
void func_801D6444_592354();
void func_801D650C_59241C();
void func_801D65FC_59250C();
void func_801D6710_592620();
void func_801D67C4_5926D4();
void func_801D6A98_5929A8();
void func_801D6B80_592A90();
s32 func_801D7058_592F68();
void func_801D7194_5930A4();
void func_801D72D4_5931E4();
u8 func_801D7720_593630();
s16 func_801D7818_593728();
void func_801D7868_593778();
u16 func_801D7900_593810();
void func_801D7B74_593A84();
s32 func_801D7C20_593B30();
u16 func_801D7DD0_593CE0();
void func_801D7F20_593E30();
s32 func_801D8034_593F44();
void func_801D80F4_594004();
s8 func_801D8290_5941A0();
void func_801D85B0_5944C0();
void func_801D8634_594544();
void func_801D896C_59487C();
s32 func_801D8E08_594D18();
void func_801D8E94_594DA4();
void func_801D8F74_594E84();
void func_801D8F94_594EA4();
void func_801D90D8_594FE8();
void func_801D9480_595390();
void func_801D96E4_5955F4();
void func_801D978C_59569C();


s32 func_801D23C0_58E2D0(arg0)
void * arg0;
{
    return CAMERA_TARGET(arg0)->camera;
}

void func_801D23C8_58E2D8(arg0, arg1)
s32 arg0;
s32 arg1;
{

}

void func_801D23D4_58E2E4() {
    void *temp_v0;

    func_801D25EC_58E4FC(&D_8020CBF0_5C8B00);
    CAMERA_VIEW(&D_8020CBF0_5C8B00)->angle = func_80003A94_4694(D_8020AC2C_5C6B3C, 240.0f / func_80003DC0_49C0(CAMERA_VIEW(&D_8020CBF0_5C8B00)->angle));
    memcpy(&D_8020CC50_5C8B60, &D_8020CBF0_5C8B00, 0x60);
    temp_v0 = func_80035854_36454(&func_801D23C8_58E2D8, CAMERA_KSEG0(&D_8020CBF0_5C8B00), &D_8006D920_6E520, 0x437A0000, 15.0f, 250.0f, 0, 0, 0, 1.0f, 1.0f, 1.0f, 0, 0);
    D_801FC624_5B8534 = temp_v0;
    D_801FC628_5B8538 = (s32) CAMERA_TASK(temp_v0)->task.unk_18;
    D_801FC62C_5B853C = func_80035EEC_36AEC(temp_v0, 2, 1);
    func_80035A5C_3665C(D_801FC624_5B8534, CAMERA_KSEG0(&D_8020CC50_5C8B60), &D_8006E0F0, 0, 0.0f, 0.0f, 0, 0, 0, 1.0f, 1.0f, 1.0f, 0, 0, 0);
    CAMERA_OVERLAY(D_801FC62C_5B853C)->visible = 1;
    D_801FC634_5B8544 = func_80035EEC_36AEC(D_801FC624_5B8534, 2, 1);
    func_80035A5C_3665C(D_801FC624_5B8534, NULL, NULL, 0, 0.0f, 0.0f, 0, 0, 0, 1.0f, 1.0f, 1.0f, 0, 0, 0);
    CAMERA_BG(D_801FC634_5B8544)->unk_64 = 1;
    CAMERA_TARGET(D_801FC604_5B8514)->camera = CAMERA_TASK(D_801FC624_5B8534);
    CAMERA_TARGET(D_801FC604_5B8514)->heading_90 = 0;
    CAMERA_TASK(D_801FC624_5B8534)->active = 1;
    D_800C7AE8_C86E8 = 1;
}

void func_801D25EC_58E4FC(arg0)
s32 arg0;
{
    f32 var_f0;
    f32 var_f2;

    if ((D_800C7AA4 == 0) || (D_800C7AA4 == 3)) {
        memcpy(arg0, &D_801FC7E8_5B86F8, 0x60);
        var_f0 = 32.5f;
        var_f2 = 40.0f;
    } else if (D_800C7AA4 == 2) {
        memcpy(arg0, &D_801FC848_5B8758, 0x60);
        var_f0 = 32.5f;
        var_f2 = 40.0f;
    } else {
        memcpy(arg0, &D_801FC8A8_5B87B8, 0x60);
        var_f0 = 33.0f;
        var_f2 = 85.0f;
    }
    CAMERA_MODE_TABLE[17].step[0].distance = var_f0;
    CAMERA_MODE_TABLE[9].step[0].distance = var_f2;
}

void func_801D26FC_58E60C(arg0)
s32 arg0;
{
    func_801D25EC_58E4FC(&D_8020CBF0_5C8B00);
    func_801D27A4_58E6B4(D_801FC624_5B8534, CAMERA_TASK(D_801FC624_5B8534)->task.unk_18);
}

void func_801D2734_58E644(arg0, arg1)
s32 arg0;
void * arg1;
{
    s32 sp42;
    s32 sp28;
    s16 var_a0;
    s16 var_v0;
    u16 temp_a1;

    func_801D25EC_58E4FC(&sp28);
    temp_a1 = CAMERA_VIEW(arg1)->angle;
    var_v0 = (sp42 - temp_a1) & 0xFFFF;
    var_a0 = var_v0;
    if (var_v0 >= 0x101) {
        var_v0 = 0x100;
        var_a0 = 0x100;
    }
    if (var_a0 < -0x100) {
        var_v0 = -0x100;
    }
    CAMERA_VIEW(arg1)->angle = (u16) (temp_a1 + var_v0);
}

void func_801D27A4_58E6B4(arg0, arg1)
void * arg0;
void * arg1;
{
    void (*mode_callbacks[5])(void *, s32);
    f32 sp54;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp4C;
    f32 sp44;
    f32 sp38;
    s32 temp_t1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_s1_2;
    u32 temp_v1;
    u8 temp_a2;
    u8 temp_a3;
    CAMERA_MODE_STEP *temp_v0;

    memcpy(mode_callbacks, &D_801FC908_5B8818, sizeof(mode_callbacks));
    temp_a2 = CAMERA_TASK(arg0)->mode_id;
    temp_a3 = CAMERA_TASK(arg0)->mode_arg;
    temp_t1 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    sp38 = CAMERA_TASK(arg0)->distance;
    memset(&CAMERA_TASK(arg0)->flag_60, 0, 0x90);
    CAMERA_TASK(arg0)->mode_group = (u8) CAMERA_TASK(arg0)->mode_group;
    CAMERA_TASK(arg0)->mode_arg = temp_a3;
    CAMERA_TASK(arg0)->follow_height = CAMERA_VIEW(temp_t1)->target.y;
    CAMERA_BG(D_801FC628_5B8538)->header.pri = 0;
    CAMERA_TASK(arg0)->tune_91 = 0x20;
    CAMERA_TASK(arg0)->tune_92 = 8;
    CAMERA_TASK(arg0)->tune_93 = 0x1C;
    CAMERA_TASK(arg0)->tune_94 = 0x96;
    CAMERA_TASK(arg0)->tune_96 = 0xFA0;
    CAMERA_TASK(arg0)->current_mode = 0xFF;
    func_801D4828_590738(arg0, temp_a2 & 0xFF, temp_a2, temp_a3);
    temp_v0 = &CAMERA_MODE_TABLE[CAMERA_TASK(arg0)->mode_id].step[CAMERA_TASK(arg0)->mode_step];
    CAMERA_TASK(arg0)->distance = temp_v0->distance;
    CAMERA_TASK(arg0)->pitch = temp_v0->pitch;
    temp_v1 = (u32) ((CAMERA_TASK(arg0)->distance * 180.0f) / 140.0f);
    CAMERA_TASK(arg0)->pitch_limit = (s16) temp_v1;
    CAMERA_TASK(arg0)->yaw_limit = (s16) temp_v1;
    sp58 = func_80003F30_4B30((CAMERA_TARGET(D_801FC604_5B8514)->yaw + 0x200) & 0xFFFF, &sp44);
    sp60 = sp44;
    sp5C = 0.0f;
    func_8001D718_1E318(&sp58, &sp4C, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84);
    CAMERA_TASK(arg0)->target_yaw = func_80003A94_4694(sp54, sp4C);
    CAMERA_SOLVE.distance = CAMERA_TASK(arg0)->distance;
    if ((sp38 != 0.0f) && ((s32) (s32) &func_801D628C_59219C == CAMERA_TASK_EXEC_WORD(arg0, 1))) {
        CAMERA_SOLVE.distance = sp38;
    }
    CAMERA_TASK(arg0)->orbit_yaw = (s16) ((CAMERA_TASK(arg0)->mode_group << 0xD) + CAMERA_TASK(arg0)->target_yaw);
    CAMERA_BG(arg1)->tx = 0.0f;
    CAMERA_BG(arg1)->ty = 0.0f;
    CAMERA_BG(arg1)->tz = 0.0f;
    mode_callbacks[(s32) CAMERA_TASK(arg0)->mode_group >> 3](arg0, temp_t1);
    func_801D2F64_58EE74(arg0, temp_t1);
    CAMERA_TASK(arg0)->tune_99 = 0x88;
    CAMERA_TASK(arg0)->tune_9a = 0x5A;
    CAMERA_TASK(arg0)->tune_9b = 0x25;
    CAMERA_TASK(arg0)->tune_9c = 0x78;
    CAMERA_TASK(arg0)->tune_9e = 0x1388;
    CAMERA_TASK(arg0)->zoom_timer = 5;
    CAMERA_TASK(arg0)->route_step = 0;
    CAMERA_TASK(arg0)->force_update = 0;
    func_80035214_35E14(arg0, &func_801D48E0_5907F0);
    func_80035244_35E44(arg0, &func_801D85B0_5944C0);
    var_s1_2 = 0;
    CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->camera_lock_78 = 0;
    CAMERA_TASK(arg0)->zoom_target = 0x100;
    CAMERA_TASK(arg0)->zoom_current = 0x100;
    do {
        temp_v0_2 = CAMERA_TASK_EXEC_WORD(arg0, 0);
        CAMERA_TASK(arg0)->yaw_pending = 0;
        if ((temp_v0_2 != 0) && !(temp_v0_2 & 0x800000)) {
            ((s32 (*)(void *, s32)) temp_v0_2)(arg0, CAMERA_TASK(arg0)->task.unk_18);
        }
        temp_v0_3 = CAMERA_TASK_EXEC_WORD(arg0, 1);
        if ((temp_v0_3 != 0) && !(temp_v0_3 & 0x800000)) {
            ((s32 (*)(void *, s32)) temp_v0_3)(arg0, CAMERA_TASK(arg0)->task.unk_18);
        }
        temp_v0_4 = CAMERA_TASK_EXEC_WORD(arg0, 2);
        if ((temp_v0_4 != 0) && !(temp_v0_4 & 0x800000)) {
            ((s32 (*)(void *, s32)) temp_v0_4)(arg0, CAMERA_TASK(arg0)->task.unk_18);
        }
        var_s1_2 += 1;
    } while (var_s1_2 != 0xF);
}

void func_801D2B58_58EA68(arg0, arg1)
s32 arg0;
s32 arg1;
{
    func_801D2D10_58EC20(0x41A00000);
    func_801D2C88_58EB98(arg0, arg1);
}

void func_801D2B8C_58EA9C(arg0, arg1)
void * arg0;
s32 arg1;
{
    func_801D2D10_58EC20(arg0, func_80003D28_4928(CAMERA_TASK(arg0)->pitch) * CAMERA_TASK(arg0)->distance);
    func_801D2C88_58EB98(arg0, arg1);
}

void func_801D2BD8_58EAE8() {
    func_801D2C88_58EB98();
}

void func_801D2BF8_58EB08(arg0, arg1)
void * arg0;
s32 arg1;
{
    if (func_801D2C88_58EB98() == 0) {
        func_801D2E10_58ED20(arg0, arg1, 0, ((CAMERA_TASK(arg0)->mode_group & 7) << 7) & 0xFFFF);
    }
}

void func_801D2C40_58EB50(arg0, arg1)
void * arg0;
s32 arg1;
{
    if (func_801D2C88_58EB98() == 0) {
        func_801D2E10_58ED20(arg0, arg1, CAMERA_TASK(arg0)->path_yaw, ((CAMERA_TASK(arg0)->mode_group & 7) << 7) & 0xFFFF);
    }
}

s32 func_801D2C88_58EB98(arg0, arg1)
void * arg0;
s32 arg1;
{
    s32 *sp1C;
    s32 var_v0;

    var_v0 = CAMERA_TASK_EXEC_WORD(arg0, 1);
    if ((s32) &func_801D67C4_5926D4 == var_v0) {
        sp1C = &func_801D67C4_5926D4;
        func_801D313C_58F04C();
        var_v0 = CAMERA_TASK_EXEC_WORD(arg0, 1);
    }
    if (((s32) &func_801D67C4_5926D4 == var_v0) || ((s32) &func_801D6710_592620 == var_v0)) {
        CAMERA_TASK(arg0)->path_yaw = 0;
        func_801D2E10_58ED20(arg0, arg1, 0, ((CAMERA_TASK(arg0)->mode_group & 7) << 7) & 0xFFFF);
        return 1;
    }
    return 0;
}

void func_801D2D10_58EC20(arg0, arg1)
s32 arg0;
f32 arg1;
{
    s32 sp2C;
    s32 sp30;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp28;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;

    sp34 = func_80003F30_4B30(CAMERA_TARGET(D_801FC604_5B8514)->yaw, &sp20);
    sp3C = sp20;
    sp38 = 0.0f;
    func_8001D718_1E318(&sp34, &sp28, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84);
    temp_f0 = (sp28 * arg1) + CAMERA_BG(D_801FC60C_5B851C)->tx;
    CAMERA_BG(D_801FC61C_5B852C)->tx = temp_f0;
    CAMERA_BG(D_801FC614_5B8524)->tx = temp_f0;
    CAMERA_BG(D_801FC60C_5B851C)->tx = temp_f0;
    temp_f0_2 = (sp2C * arg1) + CAMERA_BG(D_801FC60C_5B851C)->ty;
    CAMERA_BG(D_801FC61C_5B852C)->ty = temp_f0_2;
    CAMERA_BG(D_801FC614_5B8524)->ty = temp_f0_2;
    CAMERA_BG(D_801FC60C_5B851C)->ty = temp_f0_2;
    temp_f0_3 = (sp30 * arg1) + CAMERA_BG(D_801FC60C_5B851C)->tz;
    CAMERA_BG(D_801FC61C_5B852C)->tz = temp_f0_3;
    CAMERA_BG(D_801FC614_5B8524)->tz = temp_f0_3;
    CAMERA_BG(D_801FC60C_5B851C)->tz = temp_f0_3;
}

s32 func_801D2E10_58ED20(arg0, arg1, arg2, arg3)
void * arg0;
void * arg1;
u16 arg2;
u16 arg3;
{
    s32 sp38;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp30;
    f32 sp24;
    s16 temp_v0;
    u16 temp_t5;
    u16 temp_t8;
    u16 temp_v1;

    CAMERA_VIEW(arg1)->target.x = (f32) CAMERA_BG(D_801FC60C_5B851C)->tx;
    CAMERA_VIEW(arg1)->target.z = (f32) CAMERA_BG(D_801FC60C_5B851C)->tz;
    temp_v0 = func_801D7818_593728();
    CAMERA_SOLVE.roll = temp_v0;
    temp_t8 = temp_v0 & 0xFFFF;
    CAMERA_TASK(arg0)->orbit_yaw = temp_t8;
    if ((s32) (s32) &func_801D650C_59241C == CAMERA_TASK_EXEC_WORD(arg0, 1)) {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (temp_t8 + 0x8000);
    } else if ((arg3 == 0) && (arg2 == 0) && (CAMERA_SOLVE.height < CAMERA_SOLVE.distance)) {
        CAMERA_SOLVE.distance = CAMERA_SOLVE.height;
    }
    sp3C = func_80003F30_4B30((CAMERA_TARGET(D_801FC604_5B8514)->yaw + 0x200) & 0xFFFF, &sp24);
    sp44 = sp24;
    sp40 = 0.0f;
    func_8001D718_1E318(&sp3C, &sp30, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84);
    temp_v1 = CAMERA_TASK(arg0)->orbit_yaw;
    if ((func_80003A94_4694(sp38, sp30) - temp_v1) & 0x8000) {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (temp_v1 + arg2);
    } else {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (temp_v1 - arg2);
    }
    temp_t5 = CAMERA_TASK(arg0)->orbit_yaw + arg3;
    CAMERA_TASK(arg0)->orbit_yaw = temp_t5;
    return temp_t5 & 0xFFFF;
}

void func_801D2F64_58EE74(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 sp60;
    f32 sp64;
    f32 sp68;
    s32 sp80;
    s32 sp48;
    f32 sp3C;
    f32 sp38;
    f32 temp_f2;

    sp3C = func_80003D88_4988(CAMERA_TASK(arg0)->orbit_yaw, &sp38);
    CAMERA_SOLVE.distance_target = func_80003D28_4928(CAMERA_TASK(arg0)->pitch) * CAMERA_SOLVE.distance;
    CAMERA_SOLVE.camera_vec.x = (f32) (CAMERA_SOLVE.distance_target * sp38);
    CAMERA_SOLVE.camera_vec.z = (f32) (CAMERA_SOLVE.distance_target * sp3C);
    CAMERA_SOLVE.camera_vec.y = (f32) (func_80003CC8_48C8(CAMERA_TASK(arg0)->pitch) * CAMERA_SOLVE.distance);
    CAMERA_VIEW(arg1)->target.x = (f32) CAMERA_BG(D_801FC60C_5B851C)->tx;
    CAMERA_VIEW(arg1)->target.y = (f32) CAMERA_BG(D_801FC60C_5B851C)->ty;
    CAMERA_VIEW(arg1)->target.z = (f32) CAMERA_BG(D_801FC60C_5B851C)->tz;
    func_8002C9D4_2D5D4(&sp48, CAMERA_VIEW(arg1)->target.x, CAMERA_VIEW(arg1)->target.y, CAMERA_VIEW(arg1)->target.z, CAMERA_SOLVE.camera_vec.x, CAMERA_SOLVE.camera_vec.y, CAMERA_SOLVE.camera_vec.z, 2000.0f);
    if (sp80 == 0x7FFF) {
        temp_f2 = (f32) (1.0 - (((f64) sqrtf((sp60 * sp60) + (sp64 * sp64) + (sp68 * sp68)) + 1.0) / (f64) CAMERA_SOLVE.distance));
        if (temp_f2 > 0.0f) {
            CAMERA_SOLVE.camera_vec.x = (f32) (CAMERA_SOLVE.camera_vec.x * temp_f2);
            CAMERA_SOLVE.camera_vec.y = (f32) (CAMERA_SOLVE.camera_vec.y * temp_f2);
            CAMERA_SOLVE.camera_vec.z = (f32) (CAMERA_SOLVE.camera_vec.z * temp_f2);
        }
    }
    CAMERA_VIEW(arg1)->pos.x = (f32) (CAMERA_SOLVE.camera_vec.x + CAMERA_VIEW(arg1)->target.x);
    CAMERA_VIEW(arg1)->pos.y = (f32) (CAMERA_SOLVE.camera_vec.y + CAMERA_VIEW(arg1)->target.y);
    CAMERA_VIEW(arg1)->pos.z = (f32) (CAMERA_SOLVE.camera_vec.z + CAMERA_VIEW(arg1)->target.z);
}

void func_801D313C_58F04C(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp7C;
    s32 sp89;
    u8 sp88;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp60;
    CAMERA_PATH_SEGMENT *var_s0;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    f32 var_f2;
    s32 temp_t0;
    s32 temp_t4;
    s32 temp_t7;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_v1;
    u8 temp_s1;
    u8 temp_v1;
    u8 var_a1_2;
    CAMERA_PATH_POINT *temp_v0;
    CAMERA_PATH_CANDIDATE *temp_v0_2;
    CAMERA_PATH_POINT *temp_v1_2;

    CAMERA_TASK(arg0)->mode_group = (u8) (CAMERA_TASK(arg0)->mode_group & 0xF8);
    temp_v1 = D_801FC7D0_5B86E0;
    var_s0 = CAMERA_PATH_SEGMENTS;
    var_s1 = 0;
    if ((s32) temp_v1 > 0) {
        var_a0 = 0;
loop_2:
        if (temp_v1 == (var_a0 + 1)) {
            if (CAMERA_PATH_POINTS[(temp_v1) - 1].flags != 0) {
                var_a1 = 0;
                goto block_6;
            }
        } else {
            var_a1 = (var_a0 + 1) & 0xFF;
block_6:
            temp_v1_2 = &CAMERA_PATH_POINTS[var_a1];
            temp_v0 = &CAMERA_PATH_POINTS[var_s1];
            var_s0->dx = (f32) ((f32) temp_v0->x - (f32) temp_v1_2->x);
            temp_f12 = var_s0->dx;
            var_s0->dy = (f32) ((f32) temp_v0->y - (f32) temp_v1_2->y);
            temp_f14 = var_s0->dy;
            var_s0->dz = (f32) ((f32) temp_v0->z - (f32) temp_v1_2->z);
            temp_f2 = var_s0->dz;
            temp_f16 = sqrtf((temp_f2 * temp_f2) + ((temp_f12 * temp_f12) + (temp_f14 * temp_f14)));
            if (var_s1 != 0) {
                var_f2 = CAMERA_PATH_LENGTHS[(var_a0) - 1];
            } else {
                var_f2 = 0.0f;
            }
            temp_f0 = var_f2 + temp_f16;
            CAMERA_PATH_LENGTHS[var_s1] = temp_f0;
            D_8020CE18_5C8D28 = temp_f0;
            func_8001D394_1DF94(temp_f12, temp_f14, var_s0, var_a1);
            var_a0 = (var_s1 + 1) & 0xFF;
            var_s1 = var_a0;
            var_s0 += 1;
            if (var_a0 < (s32) D_801FC7D0_5B86E0) {
                goto loop_2;
            }
        }
    }
    func_801D416C_59007C(arg0, arg1);
    if ((s32) D_8020CF88_5C8E98 >= 2) {
        var_s0_2 = 0xFFFF;
        sp68 = func_80003F30_4B30((CAMERA_TARGET(D_801FC604_5B8514)->yaw + 0x200) & 0xFFFF, &sp60);
        sp6C = 0.0f;
        sp70 = sp60;
        func_8001D718_1E318(&sp68, &sp74, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84);
        var_a1_2 = 0;
        temp_t0 = func_80003A94_4694(sp7C, sp74);
        if ((s32) D_8020CF88_5C8E98 > 0) {
            do {
                temp_t4 = (temp_t0 - CAMERA_PATH_CANDIDATES[var_a1_2].heading) & 0xFFFF;
                var_v1 = temp_t4;
                var_a0_2 = temp_t4;
                if (temp_t4 & 0x8000) {
                    var_a0_2 = -temp_t4 & 0xFFFF;
                    var_v1 = var_a0_2;
                }
                if (var_a0_2 < var_s0_2) {
                    var_s0_2 = var_v1 & 0xFFFF;
                    sp88 = var_a1_2;
                }
                temp_t7 = (var_a1_2 + 1) & 0xFF;
                var_a1_2 = (u8) temp_t7;
            } while (temp_t7 < (s32) D_8020CF88_5C8E98);
        }
    } else {
        sp88 = sp89;
    }
    temp_v0_2 = &CAMERA_PATH_CANDIDATES[sp88];
    CAMERA_TASK(arg0)->path_pos.x = (f32) temp_v0_2->x;
    CAMERA_TASK(arg0)->path_pos.y = (f32) temp_v0_2->y;
    CAMERA_TASK(arg0)->path_pos.z = (f32) temp_v0_2->z;
    temp_s1 = temp_v0_2->segment_index;
    if (temp_s1 != 0) {
        var_f0 = CAMERA_PATH_LENGTHS[(temp_s1) - 1];
    } else {
        var_f0 = 0.0f;
    }
    CAMERA_TASK(arg0)->path_distance = (f32) (temp_v0_2->segment_distance + var_f0);
    temp_f2_2 = CAMERA_TASK(arg0)->path_distance;
    if (D_8020CE18_5C8D28 <= temp_f2_2) {
        CAMERA_TASK(arg0)->path_distance = (f32) (temp_f2_2 - D_8020CE18_5C8D28);
    }
}

s8 func_801D3494_58F3A4(arg0)
void * arg0;
{
    f32 sp6C;
    u8 sp69;
    u8 sp63;
    f32 sp54;
    f32 sp50;
    s8 sp4A;
    f32 *temp_s1;
    f32 *temp_s1_2;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f12_3;
    f32 var_f12_4;
    f32 var_f12_5;
    f32 var_f12_6;
    f32 var_f14;
    f32 var_f20;
    f32 var_f20_2;
    f32 var_f24;
    f32 var_f24_2;
    f32 var_f2;
    f32 var_f2_2;
    s32 temp_t6;
    s32 temp_t9;
    s32 var_s0;
    s32 var_s3;
    s8 var_v0;
    s8 var_v1;
    u8 temp_v1;
    u8 var_a2;
    u8 var_a3;
    u8 var_s4;
    CAMERA_PATH_CANDIDATE *temp_a0;
    CAMERA_PATH_CANDIDATE *temp_a0_2;
    CAMERA_PATH_POINT *temp_a1;
    CAMERA_PATH_POINT *temp_a2;

    sp4A = 0;
    sp6C = 6.0f;
    func_801D416C_59007C();
    if (func_801D3A04_58F914(arg0) == 0) {
        return -1;
    }
    var_f20 = D_8020AC30_5C6B40;
    var_s3 = 0;
    if ((s32) D_8020D080_5C8F90 > 0) {
        var_f24 = sp50;
        var_s4 = sp63;
        do {
            if ((s32) D_8020CF88_5C8E98 >= 2) {
                var_s0 = 0;
                if ((s32) D_8020CF88_5C8E98 > 0) {
                    temp_s1 = &CAMERA_PATH_SCRATCH_DIST[var_s3];
                    do {
                        temp_f0 = func_801D4078_58FF88(var_s0 & 0xFF, *temp_s1);
                        if (temp_f0 < 0.0f) {
                            var_f2 = -temp_f0;
                        } else {
                            var_f2 = temp_f0;
                        }
                        if (var_f20 < 0.0f) {
                            var_f12 = -var_f20;
                        } else {
                            var_f12 = var_f20;
                        }
                        if (var_f2 < var_f12) {
                            var_s4 = var_s0 & 0xFF;
                            var_f20 = temp_f0;
                            var_f24 = *temp_s1;
                        }
                        temp_t9 = (var_s0 + 1) & 0xFF;
                        var_s0 = temp_t9;
                    } while (temp_t9 < (s32) D_8020CF88_5C8E98);
                }
            } else {
                temp_s1_2 = &CAMERA_PATH_SCRATCH_DIST[var_s3];
                temp_f0_2 = func_801D4078_58FF88(0, *temp_s1_2);
                if (temp_f0_2 < 0.0f) {
                    var_f2_2 = -temp_f0_2;
                } else {
                    var_f2_2 = temp_f0_2;
                }
                if (var_f20 < 0.0f) {
                    var_f12_2 = -var_f20;
                } else {
                    var_f12_2 = var_f20;
                }
                if (var_f2_2 < var_f12_2) {
                    var_s4 = 0;
                    var_f20 = temp_f0_2;
                    var_f24 = *temp_s1_2;
                }
            }
            temp_t6 = (var_s3 + 1) & 0xFF;
            var_s3 = temp_t6;
        } while (temp_t6 < (s32) D_8020D080_5C8F90);
        sp63 = var_s4;
        sp50 = var_f24;
    }
    if (CAMERA_TASK(arg0)->flags_bd & 0x80) {
        sp6C = 6.0f * 2.0f;
    }
    if (var_f20 < 0.0f) {
        var_f12_3 = -var_f20;
    } else {
        var_f12_3 = var_f20;
    }
    if (sp6C < var_f12_3) {
        temp_f0_3 = -sp6C;
        if (var_f20 < temp_f0_3) {
            var_f20 = temp_f0_3;
        }
        if (sp6C < var_f20) {
            var_f20 = sp6C;
        }
        temp_f0_4 = sp50 + var_f20;
        var_f14 = temp_f0_4;
        if (temp_f0_4 < 0.0f) {
            var_a2 = CAMERA_PATH_POINTS[(D_801FC7D0_5B86E0) - 1].flags;
            if (var_a2 != 0) {
                var_f24_2 = CAMERA_PATH_LENGTHS[(D_801FC7D0_5B86E0) - 1] + temp_f0_4;
            } else {
                var_f24_2 = 0.0f;
            }
            sp54 = var_f24_2;
            var_f14 = sp54;
        } else {
            var_a2 = CAMERA_PATH_POINTS[(D_801FC7D0_5B86E0) - 1].flags;
            if (var_a2 != 0) {
                temp_f2 = CAMERA_PATH_LENGTHS[(D_801FC7D0_5B86E0) - 1];
                if (temp_f2 < temp_f0_4) {
                    var_f14 = temp_f0_4 - temp_f2;
                }
            } else {
                temp_f2_2 = CAMERA_PATH_LENGTHS[(D_801FC7D0_5B86E0) - 2];
                if (temp_f2_2 < temp_f0_4) {
                    var_f14 = temp_f2_2;
                }
            }
        }
        var_f20_2 = 0.0f;
        var_v1 = 0;
        if ((s32) D_801FC7D0_5B86E0 > 0) {
            var_v0 = 0;
            var_a3 = sp69;
loop_49:
            if (((s32) D_801FC7D0_5B86E0 - 1) == var_v0) {
                if (var_a2 != 0) {
                    var_a3 = 0;
                    goto block_54;
                }
            } else {
                var_a3 = (var_v0 + 1) & 0xFF;
block_54:
                temp_f0_5 = CAMERA_PATH_LENGTHS[var_v1];
                if (var_f14 < temp_f0_5) {

                } else {
                    var_v0 = (var_v1 + 1) & 0xFF;
                    var_v1 = var_v0;
                    var_f20_2 = temp_f0_5;
                    if (var_v0 < (s32) D_801FC7D0_5B86E0) {
                        goto loop_49;
                    }
                }
            }
            sp69 = var_a3;
        }
        temp_f0_6 = CAMERA_PATH_LENGTHS[var_v1];
        if (var_v1 != 0) {
            var_f12_4 = CAMERA_PATH_LENGTHS[(var_v1) - 1];
        } else {
            var_f12_4 = 0.0f;
        }
        sp54 = var_f14;
        temp_a2 = &CAMERA_PATH_POINTS[var_v1];
        temp_a1 = &CAMERA_PATH_POINTS[sp69];
        temp_f18 = (sp54 - var_f20_2) / (temp_f0_6 - var_f12_4);
        temp_a0 = &CAMERA_PATH_CANDIDATES[sp63];
        temp_f2_3 = (f32) temp_a2->x;
        temp_f14 = (f32) temp_a2->y;
        temp_a0->x = (f32) ((((f32) temp_a1->x - temp_f2_3) * temp_f18) + temp_f2_3);
        temp_f16 = (f32) temp_a2->z;
        temp_a0->y = (f32) ((((f32) temp_a1->y - temp_f14) * temp_f18) + temp_f14);
        temp_a0->z = (f32) ((((f32) temp_a1->z - temp_f16) * temp_f18) + temp_f16);
        if (var_v1 != 0) {
            var_f12_5 = CAMERA_PATH_LENGTHS[(var_v1) - 1];
        } else {
            var_f12_5 = 0.0f;
        }
        temp_a0->segment_index = var_v1;
        sp4A = 1;
        temp_a0->segment_distance = (f32) ((temp_f0_6 - var_f12_5) * temp_f18);
    }
    temp_a0_2 = &CAMERA_PATH_CANDIDATES[sp63];
    CAMERA_TASK(arg0)->path_pos.x = (f32) temp_a0_2->x;
    CAMERA_TASK(arg0)->path_pos.y = (f32) temp_a0_2->y;
    CAMERA_TASK(arg0)->path_pos.z = (f32) temp_a0_2->z;
    temp_v1 = temp_a0_2->segment_index;
    if (temp_v1 != 0) {
        var_f12_6 = CAMERA_PATH_LENGTHS[(temp_v1) - 1];
    } else {
        var_f12_6 = 0.0f;
    }
    CAMERA_TASK(arg0)->path_distance = (f32) (temp_a0_2->segment_distance + var_f12_6);
    temp_f0_7 = CAMERA_TASK(arg0)->path_distance;
    if (D_8020CE18_5C8D28 <= temp_f0_7) {
        CAMERA_TASK(arg0)->path_distance = (f32) (temp_f0_7 - D_8020CE18_5C8D28);
    }
    return sp4A;
}

u8 func_801D3A04_58F914(arg0)
void * arg0;
{
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 var_f0;
    f32 var_f0_10;
    f32 var_f0_11;
    f32 var_f0_12;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f0_9;
    f32 var_f28;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f2_4;
    f32 var_f2_5;
    f32 var_f2_6;
    f32 var_f2_7;
    f32 var_f2_8;
    f32 var_f2_9;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_t2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_v0;
    s32 var_v0_2;
    CAMERA_PATH_POINT *temp_t0;
    CAMERA_PATH_POINT *temp_t0_2;
    CAMERA_PATH_POINT *temp_t1;
    CAMERA_PATH_POINT *temp_t1_2;

    var_v0 = 0;
    if ((s32) D_801FC7D0_5B86E0 > 0) {
        var_a1 = 0;
loop_2:
        if ((D_801FC7D0_5B86E0 - 1) == var_a1) {
            var_a2 = 0;
            if (CAMERA_PATH_POINTS[(D_801FC7D0_5B86E0) - 1].flags != 0) {
                goto block_6;
            }
        } else {
            var_a2 = (var_a1 + 1) & 0xFF;
block_6:
            temp_f12 = CAMERA_TASK(arg0)->path_distance;
            temp_f14 = CAMERA_PATH_LENGTHS[var_v0];
            if (temp_f12 < temp_f14) {
                if (var_v0 != 0) {
                    var_f2 = CAMERA_PATH_LENGTHS[(var_a1) - 1];
                } else {
                    var_f2 = 0.0f;
                }
                if (var_v0 != 0) {
                    var_f0 = CAMERA_PATH_LENGTHS[(var_a1) - 1];
                } else {
                    var_f0 = 0.0f;
                }
                temp_t1 = &CAMERA_PATH_POINTS[var_v0];
                temp_t0 = &CAMERA_PATH_POINTS[var_a2];
                temp_f28 = (temp_f12 - var_f2) / (temp_f14 - var_f0);
                temp_f16 = (f32) temp_t1->x;
                CAMERA_TASK(arg0)->path_pos.x = (f32) ((((f32) temp_t0->x - temp_f16) * temp_f28) + temp_f16);
                temp_f18 = (f32) temp_t1->y;
                CAMERA_TASK(arg0)->path_pos.y = (f32) ((((f32) temp_t0->y - temp_f18) * temp_f28) + temp_f18);
                temp_f20 = (f32) temp_t1->z;
                CAMERA_TASK(arg0)->path_pos.z = (f32) ((((f32) temp_t0->z - temp_f20) * temp_f28) + temp_f20);
            } else {
                var_a1 = (var_v0 + 1) & 0xFF;
                var_v0 = var_a1;
                if (var_a1 < (s32) D_801FC7D0_5B86E0) {
                    goto loop_2;
                }
            }
        }
    }
    if (var_v0 >= (s32) D_801FC7D0_5B86E0) {
        return 0U;
    }
    D_8020D080_5C8F90 = 0;
    var_v0_2 = 0;
    if ((s32) D_801FC7D0_5B86E0 > 0) {
        var_a1_2 = 0;
loop_19:
        if ((D_801FC7D0_5B86E0 - 1) == var_a1_2) {
            var_a2_2 = 0;
            if (CAMERA_PATH_POINTS[(D_801FC7D0_5B86E0) - 1].flags != 0) {
                goto block_23;
            }
        } else {
            var_a2_2 = (var_a1_2 + 1) & 0xFF;
block_23:
            temp_t1_2 = &CAMERA_PATH_POINTS[var_v0_2];
            temp_t0_2 = &CAMERA_PATH_POINTS[var_a2_2];
            temp_t2 = temp_t1_2->x;
            temp_f12_2 = (f32) (temp_t0_2->x - temp_t2);
            temp_f18_2 = CAMERA_TASK(arg0)->path_pos.x - (f32) temp_t2;
            if (temp_f12_2 >= 0.0f) {
                var_f0_2 = temp_f18_2;
            } else {
                var_f0_2 = -temp_f18_2;
            }
            if (!(var_f0_2 < 0.0f)) {
                temp_a2 = temp_t1_2->y;
                temp_f14_2 = (f32) (temp_t0_2->y - temp_a2);
                temp_f20_2 = CAMERA_TASK(arg0)->path_pos.y - (f32) temp_a2;
                if (temp_f14_2 >= 0.0f) {
                    var_f0_3 = temp_f20_2;
                } else {
                    var_f0_3 = -temp_f20_2;
                }
                if (!(var_f0_3 < 0.0f)) {
                    temp_a2_2 = temp_t1_2->z;
                    temp_f16_2 = (f32) (temp_t0_2->z - temp_a2_2);
                    temp_f22 = CAMERA_TASK(arg0)->path_pos.z - (f32) temp_a2_2;
                    if (temp_f16_2 >= 0.0f) {
                        var_f0_4 = temp_f22;
                    } else {
                        var_f0_4 = -temp_f22;
                    }
                    if (!(var_f0_4 < 0.0f)) {
                        if (temp_f12_2 < 0.0f) {
                            var_f2_2 = -temp_f12_2;
                        } else {
                            var_f2_2 = temp_f12_2;
                        }
                        if (temp_f16_2 < 0.0f) {
                            var_f0_5 = -temp_f16_2;
                        } else {
                            var_f0_5 = temp_f16_2;
                        }
                        if (var_f0_5 < var_f2_2) {
                            if (temp_f12_2 < 0.0f) {
                                var_f2_3 = -temp_f12_2;
                            } else {
                                var_f2_3 = temp_f12_2;
                            }
                            if (temp_f14_2 < 0.0f) {
                                var_f0_6 = -temp_f14_2;
                            } else {
                                var_f0_6 = temp_f14_2;
                            }
                            if (var_f0_6 < var_f2_3) {
                                temp_f2 = temp_f18_2 / temp_f12_2;
                                temp_f30 = temp_f14_2 * temp_f2;
                                var_f28 = temp_f2;
                                if (temp_f30 < temp_f20_2) {
                                    var_f0_7 = -(temp_f30 - temp_f20_2);
                                } else {
                                    var_f0_7 = temp_f30 - temp_f20_2;
                                }
                                if (!(D_8020AC38_5C6B48 <= (f64) var_f0_7)) {
                                    temp_f0 = temp_f16_2 * temp_f2;
                                    if (temp_f0 < temp_f22) {
                                        var_f2_4 = -(temp_f0 - temp_f22);
                                    } else {
                                        var_f2_4 = temp_f0 - temp_f22;
                                    }
                                    if (D_8020AC38_5C6B48 <= (f64) var_f2_4) {
                                        goto block_99;
                                    }
                                    goto block_91;
                                }
                                goto block_99;
                            }
                            temp_f2_2 = temp_f20_2 / temp_f14_2;
                            temp_f30_2 = temp_f12_2 * temp_f2_2;
                            var_f28 = temp_f2_2;
                            if (temp_f30_2 < temp_f18_2) {
                                var_f0_8 = -(temp_f30_2 - temp_f18_2);
                            } else {
                                var_f0_8 = temp_f30_2 - temp_f18_2;
                            }
                            if (!(D_8020AC38_5C6B48 <= (f64) var_f0_8)) {
                                temp_f0_2 = temp_f16_2 * temp_f2_2;
                                if (temp_f0_2 < temp_f22) {
                                    var_f2_5 = -(temp_f0_2 - temp_f22);
                                } else {
                                    var_f2_5 = temp_f0_2 - temp_f22;
                                }
                                if (D_8020AC38_5C6B48 <= (f64) var_f2_5) {
                                    goto block_99;
                                }
                                goto block_91;
                            }
                            goto block_99;
                        }
                        if (temp_f16_2 < 0.0f) {
                            var_f2_6 = -temp_f16_2;
                        } else {
                            var_f2_6 = temp_f16_2;
                        }
                        if (temp_f14_2 < 0.0f) {
                            var_f0_9 = -temp_f14_2;
                        } else {
                            var_f0_9 = temp_f14_2;
                        }
                        if (var_f0_9 < var_f2_6) {
                            temp_f2_3 = temp_f22 / temp_f16_2;
                            temp_f30_3 = temp_f12_2 * temp_f2_3;
                            var_f28 = temp_f2_3;
                            if (temp_f30_3 < temp_f18_2) {
                                var_f0_10 = -(temp_f30_3 - temp_f18_2);
                            } else {
                                var_f0_10 = temp_f30_3 - temp_f18_2;
                            }
                            if (!(D_8020AC38_5C6B48 <= (f64) var_f0_10)) {
                                temp_f0_3 = temp_f14_2 * temp_f2_3;
                                if (temp_f0_3 < temp_f20_2) {
                                    var_f2_7 = -(temp_f0_3 - temp_f20_2);
                                } else {
                                    var_f2_7 = temp_f0_3 - temp_f20_2;
                                }
                                if (D_8020AC38_5C6B48 <= (f64) var_f2_7) {
                                    goto block_99;
                                }
                                goto block_91;
                            }
                            goto block_99;
                        }
                        temp_f2_4 = temp_f20_2 / temp_f14_2;
                        temp_f30_4 = temp_f12_2 * temp_f2_4;
                        var_f28 = temp_f2_4;
                        if (temp_f30_4 < temp_f18_2) {
                            var_f0_11 = -(temp_f30_4 - temp_f18_2);
                        } else {
                            var_f0_11 = temp_f30_4 - temp_f18_2;
                        }
                        if (!(D_8020AC38_5C6B48 <= (f64) var_f0_11)) {
                            temp_f0_4 = temp_f16_2 * temp_f2_4;
                            if (temp_f0_4 < temp_f22) {
                                var_f2_8 = -(temp_f0_4 - temp_f22);
                            } else {
                                var_f2_8 = temp_f0_4 - temp_f22;
                            }
                            if (!(D_8020AC38_5C6B48 <= (f64) var_f2_8)) {
block_91:
                                if ((s32) D_8020D080_5C8F90 < 3) {
                                    if (var_v0_2 != 0) {
                                        var_f2_9 = CAMERA_PATH_LENGTHS[(var_a1_2) - 1];
                                    } else {
                                        var_f2_9 = 0.0f;
                                    }
                                    if (var_v0_2 != 0) {
                                        var_f0_12 = CAMERA_PATH_LENGTHS[(var_a1_2) - 1];
                                    } else {
                                        var_f0_12 = 0.0f;
                                    }
                                    CAMERA_PATH_SCRATCH_DIST[D_8020D080_5C8F90] = ((CAMERA_PATH_LENGTHS[var_v0_2] - var_f0_12) * var_f28) + var_f2_9;
                                    D_8020D080_5C8F90 += 1;
                                    goto block_99;
                                }
                            } else {
                                goto block_99;
                            }
                        } else {
                            goto block_99;
                        }
                    } else {
                        goto block_99;
                    }
                } else {
                    goto block_99;
                }
            } else {
block_99:
                var_a1_2 = (var_v0_2 + 1) & 0xFF;
                var_v0_2 = var_a1_2;
                if (var_a1_2 < (s32) D_801FC7D0_5B86E0) {
                    goto loop_19;
                }
            }
        }
    }
    return D_8020D080_5C8F90;
}

f32 func_801D4078_58FF88(arg0, arg1)
s32 arg0;
f32 arg1;
{
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f12;
    s8 temp_v1;
    CAMERA_PATH_CANDIDATE *temp_v0;

    temp_v0 = &CAMERA_PATH_CANDIDATES[arg0 & 0xFF];
    temp_v1 = temp_v0->segment_index;
    if (temp_v1 != 0) {
        var_f0 = CAMERA_PATH_LENGTHS[(temp_v1) - 1];
    } else {
        var_f0 = 0.0f;
    }
    temp_f16 = (var_f0 + temp_v0->segment_distance) - arg1;
    var_f12 = temp_f16;
    if (CAMERA_PATH_POINTS[D_801FC7D0_5B86E0 - 1].flags != 0) {
        if (temp_f16 < 0.0f) {
            var_f0_2 = -temp_f16;
        } else {
            var_f0_2 = temp_f16;
        }
        temp_f2 = CAMERA_PATH_LENGTHS[(D_801FC7D0_5B86E0) - 1] - var_f0_2;
        if (temp_f16 < 0.0f) {
            var_f0_3 = -temp_f16;
        } else {
            var_f0_3 = temp_f16;
        }
        if (temp_f2 < var_f0_3) {
            if (temp_f16 > 0.0f) {
                return -temp_f2;
            }
            var_f12 = temp_f2;
            /* Duplicate return node #14. Try simplifying control flow for better match */
            return var_f12;
        }
        /* Duplicate return node #14. Try simplifying control flow for better match */
        return var_f12;
    }
    return var_f12;
}

void func_801D416C_59007C(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 spA8;
    f32 spAC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spA4;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    u8 sp73;
    u8 sp72;
    f32 sp64;
    CAMERA_PATH_SEGMENT *var_s4;
    f32 *temp_s0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f24;
    f32 var_f14;
    f32 var_f20;
    f32 var_f26;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f2_4;
    f32 var_f2_5;
    s32 var_s2;
    u8 temp_v0;
    u8 var_s1;
    u8 var_s3;
    CAMERA_PATH_POINT *temp_v1;

    var_s4 = CAMERA_PATH_SEGMENTS;
    temp_f24 = (f32) CAMERA_TASK(arg0)->pitch_limit;
    D_8020CF88_5C8E98 = 0;
    temp_v0 = D_801FC7D0_5B86E0;
    var_f26 = D_8020AC40_5C6B50;
    var_s1 = 0;
    if ((s32) temp_v0 > 0) {
        var_s2 = 0;
loop_2:
        if (temp_v0 == (var_s2 + 1)) {
            if (CAMERA_PATH_POINTS[(temp_v0) - 1].flags != 0) {
                var_f14 = temp_f24 * temp_f24;
                var_s3 = 0;
                goto block_6;
            }
        } else {
            var_f14 = temp_f24 * temp_f24;
            var_s3 = (var_s2 + 1) & 0xFF;
block_6:
            temp_v1 = &CAMERA_PATH_POINTS[var_s3];
            spB0 = CAMERA_BG(D_801FC60C_5B851C)->tx - (f32) temp_v1->x;
            spB4 = CAMERA_BG(D_801FC60C_5B851C)->ty - (f32) temp_v1->y;
            sp64 = var_f14;
            spB8 = CAMERA_BG(D_801FC60C_5B851C)->tz - (f32) temp_v1->z;
            func_8001D460_1E060(&spB0, &spA4, ((f32)(s32)(var_s4)));
            temp_f12 = (spA8 * spA8) + (spA4 * spA4);
            temp_f0 = sqrtf(temp_f12);
            if (temp_f0 < var_f26) {
                sp94 = spAC;
                var_f26 = temp_f0;
                sp73 = var_s1;
                sp72 = var_s3;
                sp8C = 0.0f;
                sp90 = 0.0f;
            }
            if (temp_f12 < sp64) {
                temp_s0 = &CAMERA_PATH_LENGTHS[var_s1];
                temp_f0_2 = sqrtf(sp64 - temp_f12);
                if ((spAC + temp_f0_2) >= 0.0f) {
                    if (var_s1 != 0) {
                        var_f2 = CAMERA_PATH_LENGTHS[(var_s2) - 1];
                    } else {
                        var_f2 = 0.0f;
                    }
                    temp_f12_2 = *temp_s0;
                    if ((spAC - temp_f0_2) < (temp_f12_2 - var_f2)) {
                        if (spAC < temp_f0_2) {
                            if ((D_801FC7D0_5B86E0 == (var_s2 + 2)) && (CAMERA_PATH_POINTS[(D_801FC7D0_5B86E0) - 1].flags == 0)) {
                                func_801D458C_59049C(temp_f12_2, sp64, ((f32)(s32)(var_s4)), var_s1 & 0xFF, var_s3 & 0xFF, 0.0f);
                            }
                        } else {
                            func_801D458C_59049C(temp_f12_2, sp64, ((f32)(s32)(var_s4)), var_s1 & 0xFF, var_s3 & 0xFF, spAC - temp_f0_2);
                        }
                        temp_f0_3 = spAC + temp_f0_2;
                        if (var_s1 != 0) {
                            var_f2_2 = CAMERA_PATH_LENGTHS[(var_s2) - 1];
                        } else {
                            var_f2_2 = 0.0f;
                        }
                        if ((*temp_s0 - var_f2_2) < temp_f0_3) {
                            if ((var_s1 == 0) && (CAMERA_PATH_POINTS[(D_801FC7D0_5B86E0) - 1].flags == 0)) {
                                if (var_s1 != 0) {
                                    var_f2_3 = CAMERA_PATH_LENGTHS[(var_s2) - 1];
                                } else {
                                    var_f2_3 = 0.0f;
                                }
                                func_801D458C_59049C(*temp_s0, ((f32)(s32)(var_s4)), ((f32)(s32)((var_s1 & 0xFF))), var_s3 & 0xFF, ((s32)(s32)((*temp_s0 - var_f2_3))));
                            }
                        } else {
                            func_801D458C_59049C(*temp_s0, ((f32)(s32)(var_s4)), ((f32)(s32)((var_s1 & 0xFF))), var_s3 & 0xFF, ((s32)(s32)(temp_f0_3)));
                        }
                    }
                }
            }
            var_s2 = (var_s1 + 1) & 0xFF;
            var_s1 = (u8) var_s2;
            var_s4 += 1;
            if (var_s2 < (s32) D_801FC7D0_5B86E0) {
                goto loop_2;
            }
        }
    }
    if (D_8020CF88_5C8E98 == 0) {
        var_f20 = sp94;
        if (var_f20 < 0.0f) {
            var_f20 = 0.0f;
        }
        if (sp73 != 0) {
            var_f2_4 = CAMERA_PATH_LENGTHS[(sp73) - 1];
        } else {
            var_f2_4 = 0.0f;
        }
        temp_f0_4 = CAMERA_PATH_LENGTHS[sp73];
        if ((temp_f0_4 - var_f2_4) < var_f20) {
            if (sp73 != 0) {
                var_f2_5 = CAMERA_PATH_LENGTHS[(sp73) - 1];
            } else {
                var_f2_5 = 0.0f;
            }
            var_f20 = temp_f0_4 - var_f2_5;
        }
        func_801D458C_59049C(((f32)(s32)&CAMERA_PATH_SEGMENTS[sp73]), ((f32)(s32)(sp73)), ((f32)(s32)(sp72)), ((s32)(s32)(var_f20)));
    }
}

void func_801D458C_59049C(arg0, arg1, arg2, arg3)
s32 arg0;
u8 arg1;
u8 arg2;
f32 arg3;
{
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_f10;
    f32 temp_f6;
    f32 var_f0;
    CAMERA_PATH_POINT *temp_v1;
    CAMERA_PATH_CANDIDATE *temp_v1_2;

    sp30 = 0.0f;
    sp34 = 0.0f;
    sp38 = arg3;
    if ((s32) D_8020CF88_5C8E98 < 0xA) {
        func_8001D5B8_1E1B8(arg3, &sp30, &sp3C, arg0, arg1);
        temp_v1 = &CAMERA_PATH_POINTS[arg2];
        temp_f10 = sp3C + (f32) temp_v1->x;
        sp3C = temp_f10;
        sp40 += (f32) temp_v1->y;
        temp_f6 = sp44 + (f32) temp_v1->z;
        sp44 = temp_f6;
        temp_v1_2 = &CAMERA_PATH_CANDIDATES[D_8020CF88_5C8E98];
        temp_v1_2->heading = func_80003A94_4694(temp_f6 - CAMERA_BG(D_801FC60C_5B851C)->tz, temp_f10 - CAMERA_BG(D_801FC60C_5B851C)->tx, D_801FC60C_5B851C);
        temp_v1_2->x = sp3C;
        temp_v1_2->y = sp40;
        temp_v1_2->z = temp_f6;
        if (arg1 != 0) {
            var_f0 = CAMERA_PATH_LENGTHS[(arg1) - 1];
        } else {
            var_f0 = 0.0f;
        }
        temp_v1_2->segment_index = arg1;
        D_8020CF88_5C8E98 += 1;
        temp_v1_2->segment_distance = (f32) ((CAMERA_PATH_LENGTHS[arg1] - var_f0) - sp38);
    }
}

void func_801D46F8_590608(arg0)
void * arg0;
{
    s32 temp_v0;
    CAMERA_PATH_POINT *var_a2;
    CAMERA_PATH_POINT *var_v1;
    u8 temp_a1;
    CAMERA_ROUTE_DATA *temp_a0;
    CAMERA_PATH_POINT *temp_t1;

    temp_v0 = func_800148F0_154F0(D_8015C5C8_15D1C8->memory_blocks, 0xA0);
    func_80001C00_2800(7, temp_v0);
    temp_a1 = CAMERA_TASK(arg0)->mode_arg;
    temp_a0 = CAMERA_ROUTE(temp_v0);
    var_v1 = CAMERA_ROUTE_POINT(temp_a0, temp_a1);
    var_a2 = CAMERA_ROUTE_POINT(temp_a0, temp_a1 + 1);
    if (((s32) ((s8 *) var_a2 - (s8 *) var_v1) >> 3) >= 0x1E) {
        var_a2 = var_v1 + 0x1E;
    }
    D_801FC7D0_5B86E0 = 0;
    if (var_v1 < var_a2) {
        do {
            temp_t1 = &CAMERA_PATH_POINTS[D_801FC7D0_5B86E0];
            *temp_t1 = *var_v1;
            var_v1 += 1;
            D_801FC7D0_5B86E0 += 1;
        } while (var_v1 < var_a2);
    }
    func_80014B74_15774(D_8015C5C8_15D1C8->memory_blocks, temp_v0, var_a2, 0);
}

void func_801D4828_590738(arg0, arg1)
void * arg0;
s32 arg1;
{
    s32 temp_t5;
    u8 temp_v1;
    u8 var_a1;
    u8 var_v0;
    CAMERA_MODE_DEF *temp_a2;

    var_v0 = arg1 & 0xFF;
    var_a1 = var_v0;
    if (var_v0 == 0x12) {
        var_a1 = 0;
        var_v0 = 0;
    }
    temp_v1 = CAMERA_TASK(arg0)->current_mode;
    if (var_v0 != temp_v1) {
        CAMERA_TASK(arg0)->mode_cooldown = 0xFF;
        temp_a2 = &CAMERA_MODE_TABLE[var_a1];
        CAMERA_TASK(arg0)->route_step = 1;
        CAMERA_TASK(arg0)->mode_flags = temp_a2->flags;
        if (temp_v1 != 0x11) {
            CAMERA_TASK(arg0)->mode_step = temp_a2->default_step;
        } else {
            CAMERA_TASK(arg0)->mode_step = 0U;
        }
        if (var_v0 != 0x11) {
            CAMERA_TASK(arg0)->zoom_target = 0x100;
        }
        CAMERA_TASK(arg0)->path_yaw = temp_a2->yaw;
        temp_t5 = temp_a2->callback;
        CAMERA_TASK(arg0)->flag_aa = 0;
        CAMERA_TASK(arg0)->flag_ab = 0;
        CAMERA_TASK_EXEC_WORD(arg0, 1) = temp_t5;
        if ((s32) &func_801D6444_592354 == temp_t5) {
            CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.pitch;
        }
    }
    CAMERA_TASK(arg0)->mode_id = var_a1;
    CAMERA_TASK(arg0)->current_mode = var_a1;
}

void func_801D48E0_5907F0(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp24;
    s32 temp_t7;
    s32 temp_v1_2;
    u8 temp_a1;
    u8 temp_v0;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v1;
    void *temp_v0_2;

    temp_v0 = CAMERA_BG(D_801FC628_5B8538)->unk_64;
    temp_t7 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    if (temp_v0 != 0) {
        D_801FCBF0_5B8B00 = temp_v0;
    }
    CAMERA_TARGET(D_801FC604_5B8514)->cooldown_ed = 0;
    CAMERA_SOLVE.roll_target = CAMERA_BG(D_801FC628_5B8538)->unk_88;
    CAMERA_BG(D_801FC628_5B8538)->unk_88 = 0.0f;
    if (((f64) CAMERA_SOLVE.roll_target < D_8020AC50_5C6B60) && (((f64) D_800C7DBC < D_8020AC58_5C6B68) || ((temp_v0_2 = CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor, ((CAMERA_ACTOR(temp_v0_2)->flags & 2) != 0)) && ((f64) CAMERA_ACTOR(temp_v0_2)->height < D_8020AC58_5C6B68)))) {
        temp_v0_3 = CAMERA_TASK(arg0)->mode_cooldown;
        if (temp_v0_3 != 0xFF) {
            CAMERA_TASK(arg0)->mode_cooldown = (u8) (temp_v0_3 + 1);
        }
    } else {
        CAMERA_TASK(arg0)->mode_cooldown = 0U;
        CAMERA_TASK(arg0)->zoom_target = 0x100;
    }
    sp24 = temp_t7;
    func_801D55E0_5914F0(temp_t7, &D_801FC604_5B8514, &D_801FC628_5B8538, temp_t7);
    CAMERA_SOLVE.pitch_target = func_801D7818_593728(arg0, sp24);
    CAMERA_SOLVE.yaw_target = func_80003A94_4694(CAMERA_VIEW(sp24)->pos.z - CAMERA_VIEW(sp24)->target.z, CAMERA_VIEW(sp24)->pos.x - CAMERA_VIEW(sp24)->target.x);
    CAMERA_TASK_EXEC_WORD(arg0, 1) = (s32) (CAMERA_TASK_EXEC_WORD(arg0, 1) & 0xFF7FFFFF);
    if ((CAMERA_BG(arg1)->unk_64 != 0) || (CAMERA_TASK(arg0)->active == 0) || ((s32) CAMERA_TARGET(D_801FC604_5B8514)->state_cd >= 4) || ((s32) &func_801D85B0_5944C0 != CAMERA_TASK_EXEC_WORD(arg0, 2))) {
        CAMERA_TASK_EXEC_WORD(arg0, 1) = (s32) (CAMERA_TASK_EXEC_WORD(arg0, 1) | 0x800000);
    }
    if ((CAMERA_BG(arg1)->unk_64 == 0) && (CAMERA_TASK(arg0)->active != 0) && ((s32) CAMERA_TARGET(D_801FC604_5B8514)->state_cd < 4)) {
        func_801D2734_58E644(arg0, sp24);
        temp_v0_4 = CAMERA_TASK(arg0)->current_mode;
        temp_v1 = CAMERA_TASK(arg0)->pending_mode;
        if (((temp_v0_4 != temp_v1) || (temp_v0_4 == CAMERA_TASK(arg0)->mode_id)) && (temp_v1 != 0xFF)) {
            CAMERA_TASK(arg0)->mode_id = temp_v1;
        }
        CAMERA_SOLVE.flag_02 = CAMERA_TASK(arg0)->mode_id;
        if (CAMERA_TARGET(D_801FC604_5B8514)->lock_61 != 0) {
            CAMERA_TASK(arg0)->mode_id = 9U;
        }
        if (CAMERA_TASK(arg0)->scripted_mode != 0) {
            CAMERA_TASK(arg0)->mode_id = 0x11U;
        }
        temp_a1 = CAMERA_TASK(arg0)->mode_id;
        if (temp_a1 != CAMERA_TASK(arg0)->current_mode) {
            func_801D4828_590738(arg0, temp_a1);
            CAMERA_TASK(arg0)->mode_countdown = 0;
            CAMERA_TASK(arg0)->route_step = 1;
        } else {
            func_801D4828_590738(arg0, temp_a1);
        }
        CAMERA_TASK(arg0)->settle_countdown = 0;
        func_801D55E0_5914F0(sp24);
        func_801D4BF0_590B00(arg0, sp24);
        func_801D55E0_5914F0(sp24);
        func_801D51A8_5910B8(arg0, sp24);
        func_801D5214_591124(arg0, sp24);
        func_801D5374_591284(arg0);
        temp_v1_2 = CAMERA_TASK_EXEC_WORD(arg0, 1);
        if ((temp_v1_2 != 0) && !(temp_v1_2 & 0x800000) && (CAMERA_TASK(arg0)->mode_id != 0x11)) {
            func_801D54C0_5913D0(arg0, sp24);
        }
    }
}

s32 func_801D4BF0_590B00(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp28;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 var_f0;
    f32 var_f10;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f4_3;
    f32 var_f8;
    u16 temp_t5;
    u8 temp_t3;
    u8 temp_t6;
    u8 temp_t7;
    u8 temp_v0;
    u8 temp_v1;
    CAMERA_FRAME_OFFSET *temp_s2;

    temp_s2 = CAMERA_BG_FRAME_OFFSET(CAMERA_TASK(arg0)->task.unk_18);
    temp_f0 = func_80003DC0_49C0((u32) (f32) ((f64) (f32) func_80003A94_4694(240.0f, D_8020AC60_5C6B70 / func_80003DC0_49C0(CAMERA_VIEW(arg1)->angle)) * D_8020AC68_5C6B78) & 0xFFFF);
    temp_t5 = CAMERA_TASK(arg0)->zoom_current;
    var_f8 = (f32) temp_t5;
    if ((s32) temp_t5 < 0) {
        var_f8 += 4294967296.0f;
    }
    sp48 = (var_f8 * (CAMERA_SOLVE.distance * temp_f0)) / 256.0f;
    sp74 = func_80003D88_4988(CAMERA_TASK(arg0)->target_yaw, &sp6C);
    sp70 = 0.0f;
    func_8001D394_1DF94(&sp6C);
    func_8001D460_1E060(&sp6C, &sp60, &CAMERA_SOLVE.scratch_vec);
    sp68 = 0.0f;
    if (CAMERA_TASK(arg0)->mode_id != 0x11) {
        sp4C = CAMERA_BG(D_801FC614_5B8524)->tx - CAMERA_VIEW(arg1)->pos.x;
        sp50 = (f32) ((((f64) (CAMERA_BG(D_801FC60C_5B851C)->ty + CAMERA_BG(D_801FC614_5B8524)->ty) * 0.5) - (f64) CAMERA_VIEW(arg1)->pos.y) + 20.0);
        sp54 = CAMERA_BG(D_801FC614_5B8524)->tz - CAMERA_VIEW(arg1)->pos.z;
    } else {
        sp4C = CAMERA_BG(D_801FC634_5B8544)->tx - CAMERA_VIEW(arg1)->pos.x;
        sp50 = (f32) ((((f64) (CAMERA_BG(D_801FC60C_5B851C)->ty + CAMERA_BG(D_801FC614_5B8524)->ty) * 0.5) - (f64) CAMERA_VIEW(arg1)->pos.y) + 20.0);
        sp54 = CAMERA_BG(D_801FC634_5B8544)->tz - CAMERA_VIEW(arg1)->pos.z;
    }
    if ((CAMERA_TASK(arg0)->prev_yaw == CAMERA_TASK(arg0)->target_yaw) || (temp_v0 = CAMERA_TASK(arg0)->yaw_pending, (temp_v0 == 0))) {
        temp_s2->x = sp60;
        temp_s2->z = sp64;
        CAMERA_TASK(arg0)->yaw_pending = 0U;
        CAMERA_TASK(arg0)->prev_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
    } else {
        temp_f0_2 = temp_s2->x;
        temp_f2 = temp_s2->z;
        temp_s2->x = (f32) (((sp60 - temp_f0_2) / ((f32) temp_v0 + 1.0f)) + temp_f0_2);
        temp_t3 = CAMERA_TASK(arg0)->yaw_pending;
        var_f4 = (f32) temp_t3;
        if ((s32) temp_t3 < 0) {
            var_f4 += 4294967296.0f;
        }
        temp_s2->z = (f32) (((sp64 - temp_f2) / (var_f4 + 1.0f)) + temp_f2);
        CAMERA_TASK(arg0)->yaw_pending = (u8) (CAMERA_TASK(arg0)->yaw_pending - 1);
    }
    temp_f14 = sqrtf((f32) ((f64) (CAMERA_SOLVE.distance * CAMERA_SOLVE.distance) - ((f64) (sp48 * sp48) * 0.25)));
    if (CAMERA_SOLVE.distance < 0.0f) {
        var_f0 = -CAMERA_SOLVE.distance;
    } else {
        var_f0 = CAMERA_SOLVE.distance;
    }
    if ((f64) var_f0 < D_8020AC70_5C6B80) {
        return 0;
    }
    temp_f12 = (sp48 * temp_f14) / CAMERA_SOLVE.distance;
    temp_f0_3 = -temp_f12;
    sp60 = temp_s2->x * temp_f0_3;
    sp64 = temp_s2->z * temp_f0_3;
    sp68 = (-sp48 * sp48) / (2.0f * temp_f14);
    func_8001D5B8_1E1B8(temp_f12, temp_f14, &sp60, &sp6C, &CAMERA_SOLVE.scratch_vec);
    temp_f4 = sp4C + sp6C;
    temp_f10 = sp50 + sp70;
    sp4C = temp_f4;
    sp50 = temp_f10;
    temp_f6 = sp54 + sp74;
    sp54 = temp_f6;
    temp_v1 = CAMERA_TASK(arg0)->blend_timer;
    if (temp_v1 != 0) {
        sp28 = temp_f10;
        var_f4_2 = (f32) temp_v1;
        if ((s32) temp_v1 < 0) {
            var_f4_2 += 4294967296.0f;
        }
        sp4C = ((temp_f4 + CAMERA_SOLVE.camera_vec.x) / (var_f4_2 + 1.0f)) - CAMERA_SOLVE.camera_vec.x;
        temp_t6 = CAMERA_TASK(arg0)->blend_timer;
        var_f10 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f10 += 4294967296.0f;
        }
        sp50 = ((sp28 + CAMERA_SOLVE.camera_vec.y) / (var_f10 + 1.0f)) - CAMERA_SOLVE.camera_vec.y;
        temp_t7 = CAMERA_TASK(arg0)->blend_timer;
        var_f4_3 = (f32) temp_t7;
        if ((s32) temp_t7 < 0) {
            var_f4_3 += 4294967296.0f;
        }
        sp54 = ((temp_f6 + CAMERA_SOLVE.camera_vec.z) / (var_f4_3 + 1.0f)) - CAMERA_SOLVE.camera_vec.z;
        CAMERA_TASK(arg0)->blend_timer = (u8) (CAMERA_TASK(arg0)->blend_timer - 1);
    }
    sp6C = CAMERA_VIEW(arg1)->pos.x - CAMERA_VIEW(arg1)->target.x;
    sp70 = CAMERA_VIEW(arg1)->pos.y - CAMERA_VIEW(arg1)->target.y;
    sp74 = CAMERA_VIEW(arg1)->pos.z - CAMERA_VIEW(arg1)->target.z;
    CAMERA_SOLVE.flag_00 = func_80003A94_4694(sp70, sqrtf((sp74 * sp74) + (sp6C * sp6C)));
    CAMERA_VIEW(arg1)->target.x = (f32) (sp4C + CAMERA_VIEW(arg1)->pos.x);
    CAMERA_VIEW(arg1)->target.y = (f32) (sp50 + CAMERA_VIEW(arg1)->pos.y);
    CAMERA_VIEW(arg1)->target.z = (f32) (sp54 + CAMERA_VIEW(arg1)->pos.z);
    return 0;
}

void func_801D51A8_5910B8(arg0, arg1)
void * arg0;
s32 arg1;
{
    u16 temp_t8;
    u16 temp_v0;
    u16 var_a1;

    temp_v0 = CAMERA_TASK(arg0)->zoom_target;
    var_a1 = CAMERA_TASK(arg0)->zoom_current;
    if ((s32) temp_v0 < (s32) var_a1) {
        if ((var_a1 - temp_v0) < 0x10) {
            CAMERA_TASK(arg0)->zoom_current = temp_v0;
            return;
        }
        CAMERA_TASK(arg0)->zoom_current = (u16) (var_a1 - 0x10);
        return;
    }
    temp_t8 = var_a1 + 2;
    if ((s32) var_a1 < (s32) temp_v0) {
        CAMERA_TASK(arg0)->zoom_current = temp_t8;
        var_a1 = temp_t8 & 0xFFFF;
    }
    if ((s32) CAMERA_TASK(arg0)->zoom_target < (s32) var_a1) {
        CAMERA_TASK(arg0)->zoom_current = CAMERA_TASK(arg0)->zoom_target;
    }
}

void func_801D5214_591124(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp30;
    s32 sp34;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    u16 var_v0;
    u8 temp_v1;

    temp_v1 = CAMERA_TASK(arg0)->mode_id;
    var_v0 = CAMERA_MODE_TABLE[temp_v1].step[CAMERA_TASK(arg0)->mode_step].pitch;
    if (CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->flag_59 != 0) {
        var_v0 = 0x600;
    }
    CAMERA_TASK(arg0)->pitch = var_v0;
    if (temp_v1 != 0x11) {
        sp20 = CAMERA_VIEW(arg1)->pos.x - CAMERA_BG(D_801FC614_5B8524)->tx;
        sp24 = 0.0f;
        sp28 = CAMERA_VIEW(arg1)->pos.z - CAMERA_BG(D_801FC614_5B8524)->tz;
        if (func_8001D394_1DF94(&sp20, arg0) != 0) {
            func_8001D460_1E060(&CAMERA_TARGET(D_801FC604_5B8514)->unk_b4, &sp2C, &sp20, arg0);
            sp2C = 0.0f;
            if ((sp34 < 0.0f) && (func_8001D394_1DF94(&sp2C) != 0) && ((u16) CAMERA_TASK(arg0)->mode_id != 0)) {
                func_80003A94_4694(-sp34, sp30);
            }
        }
    }
    func_801D5338_591248(&CAMERA_TASK(arg0)->pitch);
}

void func_801D5338_591248(arg0)
u16 * arg0;
{
    u16 temp_v0;

    temp_v0 = *arg0;
    if (!(temp_v0 & 0x8000)) {
        if ((s32) temp_v0 >= 0x3001) {
            *arg0 = 0x3000;
        }
    } else if ((s32) temp_v0 < 0xDA00) {
        *arg0 = 0xDA00;
    }
}

void func_801D5374_591284(arg0)
void * arg0;
{
    s32 sp40;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp38;
    f32 sp2C;
    f32 temp_f2;
    f32 var_f0;
    u16 temp_v0;

    func_80003D88_4988(CAMERA_TASK(arg0)->pitch, &sp2C);
    temp_f2 = CAMERA_SOLVE.distance * sp2C;
    if (temp_f2 < 0.0f) {
        var_f0 = -temp_f2;
    } else {
        var_f0 = temp_f2;
    }
    if (!((f64) var_f0 < D_8020AC78_5C6B88)) {
        sp44 = func_80003F30_4B30((CAMERA_TARGET(D_801FC604_5B8514)->yaw + 0x200) & 0xFFFF, &sp2C);
        sp4C = sp2C;
        sp48 = 0.0f;
        func_8001D718_1E318(&sp44, &sp38, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84);
        temp_v0 = func_80003A94_4694(sp40, sp38);
        if (((((temp_v0 - CAMERA_TASK(arg0)->target_yaw) + 0x800) & 0xFFFF) >= 0x1000) && ((((temp_v0 - CAMERA_TASK(arg0)->base_yaw) + 0x800) & 0xFFFF) < 0x1000)) {
            CAMERA_TASK(arg0)->stable_frames = (u8) (CAMERA_TASK(arg0)->stable_frames + 1);
        } else {
            CAMERA_TASK(arg0)->stable_frames = 0U;
        }
        if ((s32) CAMERA_TASK(arg0)->stable_frames >= 5) {
            CAMERA_TASK(arg0)->stable_frames = 4U;
            CAMERA_TASK(arg0)->target_yaw = temp_v0;
            CAMERA_TASK(arg0)->yaw_pending = 0x1E;
        }
        CAMERA_TASK(arg0)->base_yaw = temp_v0;
    }
}

void func_801D54C0_5913D0(arg0, arg1)
void * arg0;
s32 arg1;
{
    s32 sp28;
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_v0;

    memcpy(&sp28, arg1, 0x60);
    func_801D55E0_5914F0(arg1);
    CAMERA_SOLVE.height_target = (D_8020CC0C_5C8B1C * 70.0f) / 35.0f;
    func_801D72D4_5931E4(arg0, &sp28);
    temp_v0 = CAMERA_TASK_EXEC_WORD(arg0, 1);
    if (((s32) &func_801D65FC_59250C == temp_v0) || ((s32) &func_801D650C_59241C == temp_v0)) {
        func_801D7720_593630(arg0, &sp28);
    }
    temp_f0 = CAMERA_TARGET(D_801FC604_5B8514)->target_radius;
    temp_f2 = CAMERA_TARGET(D_801FC604_5B8514)->floor_y;
    if (D_8020AC80_5C6B90 < (f64) ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
        CAMERA_TASK(arg0)->flag_aa = 0;
    }
    CAMERA_SOLVE.blend_flag = func_801D7900_593810(arg0, &sp28);
    func_801D80F4_594004(arg0, arg1, &sp28);
}

void func_801D55E0_5914F0(arg0)
void * arg0;
{
    f32 sp1C;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f4;

    temp_f2 = CAMERA_VIEW(arg0)->pos.x - CAMERA_VIEW(arg0)->target.x;
    CAMERA_SOLVE.scratch_vec.x = temp_f2;
    CAMERA_SOLVE.camera_vec.x = temp_f2;
    temp_f2_2 = CAMERA_VIEW(arg0)->pos.y - CAMERA_VIEW(arg0)->target.y;
    CAMERA_SOLVE.camera_vec.y = temp_f2_2;
    CAMERA_SOLVE.scratch_vec.y = temp_f2_2;
    sp1C = CAMERA_SOLVE.camera_vec.x;
    temp_f2_3 = CAMERA_VIEW(arg0)->pos.z - CAMERA_VIEW(arg0)->target.z;
    CAMERA_SOLVE.camera_vec.z = temp_f2_3;
    CAMERA_SOLVE.scratch_vec.z = temp_f2_3;
    temp_f18 = CAMERA_SOLVE.camera_vec.z * CAMERA_SOLVE.camera_vec.z;
    temp_f4 = sp1C * sp1C;
    sp1C = temp_f4;
    CAMERA_SOLVE.distance = sqrtf(temp_f18 + (temp_f4 + (CAMERA_SOLVE.camera_vec.y * CAMERA_SOLVE.camera_vec.y)));
    CAMERA_SOLVE.distance_target = sqrtf(temp_f18 + temp_f4);
    CAMERA_SOLVE.yaw = func_80003A94_4694(CAMERA_SOLVE.camera_vec.y, CAMERA_SOLVE.distance_target, &CAMERA_SOLVE.distance_target);
    CAMERA_SOLVE.pitch = func_80003A94_4694(CAMERA_SOLVE.camera_vec.z, CAMERA_SOLVE.camera_vec.x);
    func_8001D394_1DF94(&CAMERA_SOLVE.scratch_vec);
}

u16 func_801D56D0_5915E0(arg1, arg4)
s32 arg1;
u16 arg4;
{
    u16 sp26;
    u16 temp_v0;

    temp_v0 = func_801D5708_591618((s32) arg4);
    sp26 = temp_v0;
    func_801D55E0_5914F0(arg1);
    return temp_v0;
}

s32 func_801D5708_591618(arg0, arg1, arg2, arg3)
void * arg0;
s32 arg1;
void * arg2;
void * arg3;
{
    f32 sp60;
    f32 sp64;
    f32 sp68;
    s32 sp80;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    s32 sp48;
    f32 sp44;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f2;

    memcpy(&sp90, arg1, 0x60);
    sp30 = ((CAMERA_VEC3F *)&D_801FCC00_5B8B10)->x;
    sp34 = ((CAMERA_VEC3F *)&D_801FCC00_5B8B10)->y;
    sp38 = ((CAMERA_VEC3F *)&D_801FCC00_5B8B10)->z;
    if (arg2 != NULL) {
        sp30 = ((CAMERA_VEC3F *)(arg2))->x;
        sp34 = ((CAMERA_VEC3F *)(arg2))->y;
        sp38 = ((CAMERA_VEC3F *)(arg2))->z;
    }
    if (arg3 != NULL) {
        sp30 += ((CAMERA_VEC3F *)(arg3))->x;
        sp34 += ((CAMERA_VEC3F *)(arg3))->y;
        sp38 += ((CAMERA_VEC3F *)(arg3))->z;
        sp9C += ((CAMERA_VEC3F *)(arg3))->x;
        spA0 += ((CAMERA_VEC3F *)(arg3))->y;
        spA4 += ((CAMERA_VEC3F *)(arg3))->z;
    }
    if ((CAMERA_SOLVE.solve_flag == 0) && (CAMERA_SOLVE.distance < ((CAMERA_TASK(arg0)->distance * 220.0f) / 140.0f))) {
        temp_f0 = sqrtf((sp38 * sp38) + ((sp30 * sp30) + (sp34 * sp34)));
        if (temp_f0 < 0.0f) {
            var_f2 = -temp_f0;
        } else {
            var_f2 = temp_f0;
        }
        if (!((f64) var_f2 < D_8020AC88_5C6B98)) {
            sp44 = temp_f0;
            func_8002C9D4_2D5D4(sp34, temp_f0, &sp48, sp30 + sp90, sp34 + sp94, sp38 + sp98, sp30, sp34, sp38, temp_f0);
            if (sp80 == 0x7FFF) {
                temp_f0_2 = sqrtf((sp60 * sp60) + (sp64 * sp64) + (sp68 * sp68));
                var_f12 = temp_f0_2;
                if (temp_f0_2 < sp44) {
                    var_f12 = temp_f0_2 + 1.0f;
                }
                if (var_f12 < sp44) {
                    temp_f2 = var_f12 / temp_f0_2;
                    sp30 += sp60 * temp_f2;
                    sp34 += sp64 * temp_f2;
                    sp38 += sp68 * temp_f2;
                } else {
                    sp34 = 0.0f;
                    sp38 = 0.0f;
                    sp30 = 0.0f;
                }
            }
        }
        if ((func_801D5A78_591988(arg1, &sp30) != 1) && (func_80029E08_2AA08(sp30 + sp90, sp34 + sp94, sp38 + sp98) == 0x7FFF)) {
            return 0;
        }
        goto block_19;
    }
block_19:
    if (func_801D5A78_591988(arg1, &sp30) == 0) {
        return 0;
    }
    sp90 += sp30;
    sp94 += sp34;
    sp98 += sp38;
    memcpy(arg1, &sp90, 0x60);
    return 1;
}

s8 func_801D5A78_591988(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    s8 sp37;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp18;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f8;
    f32 var_f18;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    s32 temp_cond;
    s8 var_v0;
    s8 var_v1;

    sp54 = (((CAMERA_VEC3F *)(arg1))->x + CAMERA_VIEW(arg0)->pos.x) - CAMERA_VIEW(arg0)->target.x;
    sp58 = (((CAMERA_VEC3F *)(arg1))->y + CAMERA_VIEW(arg0)->pos.y) - CAMERA_VIEW(arg0)->target.y;
    sp37 = 1;
    sp5C = (((CAMERA_VEC3F *)(arg1))->z + CAMERA_VIEW(arg0)->pos.z) - CAMERA_VIEW(arg0)->target.z;
    temp_f12 = func_80003DC0_49C0(0x800, arg0);
    var_v1 = 1;
    temp_f14 = sp58 * temp_f12;
    temp_f6 = (sp5C * sp5C) + (sp54 * sp54);
    temp_cond = temp_f14 < 0.0f;
    sp20 = temp_f6;
    temp_f0 = sqrtf(temp_f6);
    if (temp_cond) {
        var_f2 = -temp_f14;
    } else {
        var_f2 = temp_f14;
    }
    if (temp_f0 < var_f2) {
        temp_f12_2 = temp_f12 * temp_f12;
        temp_f0_2 = ((CAMERA_VEC3F *)(arg1))->x;
        temp_f18 = ((CAMERA_VEC3F *)(arg1))->z;
        temp_f16 = ((CAMERA_VEC3F *)(arg1))->y;
        temp_f14_2 = ((temp_f0_2 * temp_f0_2) + (temp_f18 * temp_f18)) - (temp_f16 * temp_f16 * temp_f12_2);
        if (temp_f14_2 < 0.0f) {
            var_f2_2 = -temp_f14_2;
        } else {
            var_f2_2 = temp_f14_2;
        }
        sp2C = temp_f0_2;
        sp28 = temp_f16;
        sp24 = temp_f18;
        if ((f64) var_f2_2 < D_8020AC90_5C6BA0) {
            return 0;
        }
        var_f18 = -1.0f;
        temp_f16_2 = (((sp54 * sp2C) + (sp5C * sp24)) - (sp28 * sp58 * temp_f12_2)) * 2.0f;
        temp_f8 = 4.0f * temp_f14_2 * (sp20 - (sp58 * sp58 * temp_f12_2));
        temp_f2 = temp_f16_2 * temp_f16_2;
        sp18 = temp_f8;
        if (temp_f8 < temp_f2) {
            temp_f12_3 = temp_f2 - temp_f8;
            if (temp_f12_3 < 0.0f) {
                var_f2_3 = -temp_f12_3;
            } else {
                var_f2_3 = temp_f12_3;
            }
            if (!((f64) var_f2_3 < D_8020AC98_5C6BA8)) {
                temp_f0_3 = sqrtf(temp_f12_3);
                if (temp_f14_2 > 0.0f) {
                    var_f18 = -temp_f16_2 - (temp_f0_3 / (2.0f * temp_f14_2));
                } else {
                    var_f18 = (temp_f0_3 / (2.0f * temp_f14_2)) - temp_f16_2;
                }
            }
        }
        if ((var_f18 > -1.0f) && (var_f18 < 0.0f)) {
            var_v1 = -1;
            temp_f0_4 = 1.0f + var_f18;
            ((CAMERA_VEC3F *)(arg1))->x = (f32) (sp2C * temp_f0_4);
            ((CAMERA_VEC3F *)(arg1))->y = (f32) (sp28 * temp_f0_4);
            ((CAMERA_VEC3F *)(arg1))->z = (f32) (sp24 * temp_f0_4);
            goto block_21;
        }
        return 0;
    }
block_21:
    var_v0 = var_v1;
    temp_f10 = (((CAMERA_VEC3F *)(arg1))->x + CAMERA_VIEW(arg0)->pos.x) - CAMERA_VIEW(arg0)->target.x;
    sp54 = temp_f10;
    temp_f6_2 = (((CAMERA_VEC3F *)(arg1))->z + CAMERA_VIEW(arg0)->pos.z) - CAMERA_VIEW(arg0)->target.z;
    sp5C = temp_f6_2;
    if ((f64) sqrtf((temp_f6_2 * temp_f6_2) + (temp_f10 * temp_f10)) <= D_8020ACA0_5C6BB0) {
        var_v0 = 0;
    }
    return var_v0;
}

u16 func_801D5DC0_591CD0(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp38;
    u16 sp36;
    f32 temp_f2;
    f32 temp_f6;
    f32 var_f18;
    s32 temp_v0;
    u16 temp_t6;
    u16 var_v1;

    var_v1 = 0;
    if (((CAMERA_TASK(arg0)->distance * 180.0f) / 140.0f) < CAMERA_SOLVE.distance) {
        sp48 = 0.0f;
        sp44 = 0.0f;
        temp_t6 = CAMERA_TASK(arg0)->zoom_timer;
        var_f18 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f18 += 4294967296.0f;
        }
        temp_f6 = -var_f18;
        sp4C = temp_f6;
        temp_f2 = ((CAMERA_TASK(arg0)->distance * 180.0f) / 140.0f) - CAMERA_SOLVE.distance;
        if (temp_f6 < temp_f2) {
            sp4C = temp_f2;
        }
        func_8001D5B8_1E1B8(0x43340000, 0x430C0000, &sp44, &sp38, &CAMERA_SOLVE.scratch_vec);
        temp_v0 = func_801D56D0_5915E0(arg0, arg1, &sp38, 0, 0);
        var_v1 = temp_v0 & 0xFFFF;
        if (temp_v0 != 0) {
            sp36 = var_v1;
            func_801D72D4_5931E4(arg0, arg1);
        }
    }
    sp36 = var_v1;
    func_801D55E0_5914F0(arg1);
    return sp36;
}

u16 func_801D5ECC_591DDC(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp38;
    u16 sp36;
    f32 temp_f2;
    f32 var_f10;
    s32 temp_v0;
    u16 temp_t6;
    u16 var_v1;

    var_v1 = 0;
    if (CAMERA_SOLVE.distance < CAMERA_TASK(arg0)->distance) {
        sp48 = 0.0f;
        sp44 = 0.0f;
        temp_t6 = CAMERA_TASK(arg0)->zoom_timer;
        var_f10 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f10 += 4294967296.0f;
        }
        sp4C = var_f10;
        temp_f2 = CAMERA_TASK(arg0)->distance - CAMERA_SOLVE.distance;
        if (temp_f2 < sp4C) {
            sp4C = temp_f2;
        }
        func_8001D5B8_1E1B8(&sp44, &sp38, &CAMERA_SOLVE.scratch_vec);
        temp_v0 = func_801D56D0_5915E0(arg0, arg1, &sp38, 0, 0);
        var_v1 = temp_v0 & 0xFFFF;
        if (temp_v0 != 0) {
            sp36 = var_v1;
            func_801D72D4_5931E4(arg0, arg1);
        }
    }
    return var_v1;
}

u16 func_801D5FA8_591EB8(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s32 sp30;
    u16 sp2E;
    f32 temp_f2;
    f32 var_f0;
    u16 temp_t6;
    u16 var_v1;

    var_v1 = 0;
    if (CAMERA_SOLVE.distance != CAMERA_TASK(arg0)->distance) {
        sp40 = 0.0f;
        sp3C = 0.0f;
        sp44 = CAMERA_TASK(arg0)->distance - CAMERA_SOLVE.distance;
        temp_t6 = CAMERA_TASK(arg0)->zoom_timer;
        var_f0 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f0 += 4294967296.0f;
        }
        if (var_f0 < sp44) {
            sp44 = var_f0;
        } else {
            temp_f2 = -var_f0;
            if (sp44 < temp_f2) {
                sp44 = temp_f2;
            }
        }
        func_8001D5B8_1E1B8(&sp3C, &sp30, &CAMERA_SOLVE.scratch_vec, arg0);
        var_v1 = func_801D56D0_5915E0(arg0, arg1, &sp30, 0, 0) & 0xFFFF;
    }
    sp2E = var_v1;
    func_801D55E0_5914F0(arg1);
    return sp2E;
}

u16 func_801D6098_591FA8(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s32 sp30;
    u16 sp2E;
    f32 temp_f12;
    f32 var_f8;
    s32 temp_v0;
    u16 temp_t7;
    u16 var_v1;

    var_v1 = 0;
    if (CAMERA_SOLVE.distance < CAMERA_SOLVE.height_target) {
        temp_f12 = CAMERA_SOLVE.height_target - CAMERA_SOLVE.distance;
        sp40 = 0.0f;
        sp3C = 0.0f;
        temp_t7 = CAMERA_TASK(arg0)->zoom_timer;
        var_f8 = (f32) temp_t7;
        if ((s32) temp_t7 < 0) {
            var_f8 += 4294967296.0f;
        }
        sp44 = var_f8;
        if (temp_f12 < var_f8) {
            sp44 = temp_f12;
        }
        func_8001D5B8_1E1B8(temp_f12, &sp3C, &sp30, &CAMERA_SOLVE.scratch_vec);
        temp_v0 = func_801D56D0_5915E0(arg0, arg1, &sp30, 0, 0);
        var_v1 = temp_v0 & 0xFFFF;
        if (temp_v0 != 0) {
            sp2E = var_v1;
            func_801D72D4_5931E4(arg0, arg1);
        }
    }
    return var_v1;
}

void func_801D6164_592074(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 temp_t6;

    temp_t6 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    if (CAMERA_TASK(arg0)->flags_bd != 0) {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
        func_801D7B74_593A84(temp_t6, 0x120, 0x120);
    } else if ((s32) CAMERA_TASK(arg0)->mode_cooldown >= 0x15) {
        CAMERA_TASK(arg0)->zoom_target = 0;
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
        func_801D7B74_593A84((s32) arg0, temp_t6, 0x12, 0x200);
    } else {
        CAMERA_TASK(arg0)->yaw_step = 0;
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.pitch;
    }
    func_801D7F20_593E30(arg0, temp_t6);
    func_801D5DC0_591CD0(arg0, temp_t6);
    if ((D_8020ACA8_5C6BB8 < (f64) CAMERA_SOLVE.roll_target) || ((s32) CAMERA_TASK(arg0)->mode_cooldown >= 0x15) || (CAMERA_SOLVE.distance_target < CAMERA_SOLVE.height_target) || (CAMERA_TASK(arg0)->flags_bd != 0)) {
        func_801D5ECC_591DDC(arg0, temp_t6);
    }
}

void func_801D628C_59219C(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp24;
    s32 temp_v1;
    u16 temp_v0;

    sp24 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    if (CAMERA_TASK(arg0)->flags_bd != 0) {
        CAMERA_TASK(arg0)->flag_ab = 0U;
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
        func_801D7B74_593A84(sp24, 0x120, 0x120);
    } else if ((CAMERA_SOLVE.distance_target < CAMERA_SOLVE.height_target) && (temp_v0 = CAMERA_TASK(arg0)->target_yaw, temp_v1 = temp_v0 - CAMERA_SOLVE.pitch, ((((temp_v1 + 0xB800) & 0xFFFF) < 0x7000) != 0))) {
        if (temp_v1 & 0x8000) {
            CAMERA_TASK(arg0)->orbit_yaw = (u16) (temp_v0 - 0x4000);
        } else {
            CAMERA_TASK(arg0)->orbit_yaw = (u16) (temp_v0 + 0x4000);
        }
        CAMERA_TASK(arg0)->flag_ab = 1U;
    } else if ((s32) CAMERA_TASK(arg0)->mode_cooldown >= 0x15) {
        CAMERA_TASK(arg0)->zoom_target = 0;
        CAMERA_TASK(arg0)->flag_ab = 0U;
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
        func_801D7B74_593A84((s32) arg0, sp24, 0x12, 0x200);
    } else {
        CAMERA_TASK(arg0)->flag_ab = 0U;
        CAMERA_TASK(arg0)->yaw_step = 0;
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.pitch;
    }
    func_801D7F20_593E30(arg0, sp24);
    func_801D5DC0_591CD0(arg0, sp24);
    if ((((s32) CAMERA_TASK(arg0)->mode_cooldown >= 0x15) && (CAMERA_TASK(arg0)->mode_flags & 0x10)) || (CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->state_18 & 1)) {
        func_801D5ECC_591DDC(arg0, sp24);
        return;
    }
    if ((CAMERA_SOLVE.distance_target < CAMERA_SOLVE.height_target) || (CAMERA_TASK(arg0)->flag_ab != 0)) {
        func_801D6098_591FA8(arg0, sp24);
    }
}

void func_801D6444_592354(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 temp_t6;

    temp_t6 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    if (CAMERA_TASK(arg0)->flags_bd != 0) {
        CAMERA_TASK(arg0)->flag_ab = 0;
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
        func_801D7B74_593A84(temp_t6, 0x120, 0x120);
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.pitch;
    } else {
        CAMERA_TASK(arg0)->yaw_step = 0;
        func_801D7B74_593A84((s32) arg0, temp_t6, 0x7800, 0x7800);
        if (CAMERA_TASK(arg0)->flag_a3 != 0) {
            CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.pitch;
        }
        CAMERA_TASK(arg0)->yaw_step = 0;
    }
    func_801D7F20_593E30(arg0, temp_t6);
    func_801D5DC0_591CD0(arg0, temp_t6);
    func_801D5ECC_591DDC(arg0, temp_t6);
}

void func_801D650C_59241C(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t6;

    CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.roll;
    temp_t6 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    if ((CAMERA_TASK(arg0)->target_yaw - CAMERA_SOLVE.roll) & 0x8000) {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (CAMERA_SOLVE.roll - CAMERA_TASK(arg0)->path_yaw);
    } else {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (CAMERA_TASK(arg0)->orbit_yaw + CAMERA_TASK(arg0)->path_yaw);
    }
    temp_f0 = CAMERA_TARGET(D_801FC604_5B8514)->target_radius;
    temp_f2 = CAMERA_TARGET(D_801FC604_5B8514)->floor_y;
    if (D_8020ACB0_5C6BC0 < (f64) ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
        func_801D7B74_593A84(arg0, temp_t6, 1, 0x30);
    }
    func_801D7F20_593E30(arg0, temp_t6);
    func_801D5DC0_591CD0(arg0, temp_t6);
    func_801D5ECC_591DDC(arg0, temp_t6);
}

void func_801D65FC_59250C(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t6;
    u16 temp_t8;

    temp_t6 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    temp_t8 = CAMERA_SOLVE.roll + 0x8000;
    CAMERA_TASK(arg0)->orbit_yaw = temp_t8;
    if ((CAMERA_TASK(arg0)->target_yaw - CAMERA_SOLVE.roll) & 0x8000) {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (temp_t8 + CAMERA_TASK(arg0)->path_yaw);
    } else {
        CAMERA_TASK(arg0)->orbit_yaw = (u16) (CAMERA_TASK(arg0)->orbit_yaw - CAMERA_TASK(arg0)->path_yaw);
    }
    temp_f0 = CAMERA_TARGET(D_801FC604_5B8514)->target_radius;
    temp_f2 = CAMERA_TARGET(D_801FC604_5B8514)->floor_y;
    if (D_8020ACB8_5C6BC8 < (f64) ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
        func_801D7B74_593A84(arg0, temp_t6, 1, 0x30);
    }
    func_801D7F20_593E30(arg0, temp_t6);
    func_801D5DC0_591CD0(arg0, temp_t6);
    if (CAMERA_TASK(arg0)->distance < CAMERA_SOLVE.height) {
        func_801D5ECC_591DDC(arg0, temp_t6);
    }
}

void func_801D6710_592620(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp38;
    s32 temp_s1;

    temp_s1 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    if (CAMERA_TASK(arg0)->mode_flags & 2) {

    } else {
        func_80003DC0_49C0(CAMERA_TASK(arg0)->pitch);
    }
    if (CAMERA_SOLVE.height < 70.0f) {
        CAMERA_TASK(arg0)->flag_ab = 1;
    } else {
        CAMERA_TASK(arg0)->flag_ab = 0;
    }
    func_801D7194_5930A4(arg0, temp_s1, &sp38);
    func_801D56D0_5915E0(arg0, temp_s1, &sp38, 0, 0x3F00);
}

void func_801D67C4_5926D4(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 spB4;
    s32 sp54;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    s32 sp30;
    s8 sp2F;
    s32 temp_t1;
    u16 temp_v0;
    u16 temp_v0_2;

    temp_t1 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    memcpy(&sp54, temp_t1, 0x60);
    sp2F = -1;
    if (D_801FC7D0_5B86E0 != 0) {
        spB4 = temp_t1;
        CAMERA_SOLVE.roll = func_801D7818_593728(arg0, temp_t1, temp_t1);
        if (CAMERA_SOLVE.height < 5.0f) {
            CAMERA_TASK(arg0)->flag_ab = 1U;
        }
        if (CAMERA_TASK(arg0)->distance < CAMERA_SOLVE.height) {
            CAMERA_TASK(arg0)->flag_ab = 0U;
        }
        if ((CAMERA_TASK(arg0)->mode_flags & 8) || (CAMERA_TASK(arg0)->flags_bd & 0x80) || (((CAMERA_TASK(arg0)->distance * 180.0f) / 140.0f) < CAMERA_SOLVE.height) || (CAMERA_TASK(arg0)->flag_ab != 0)) {
            sp40 = CAMERA_TASK(arg0)->path_pos.x;
            sp44 = CAMERA_TASK(arg0)->path_pos.y;
            sp48 = CAMERA_TASK(arg0)->path_pos.z;
            sp4C = CAMERA_TASK(arg0)->path_distance;
            if ((D_8020ACC8_5C6BD8 < (f64) CAMERA_SOLVE.roll_target) && !(CAMERA_TASK(arg0)->flags_bd & 0x80)) {
                temp_v0 = CAMERA_TASK(arg0)->pitch_limit;
                if ((s32) CAMERA_TASK(arg0)->yaw_limit >= (s32) temp_v0) {
                    CAMERA_TASK(arg0)->pitch_limit = (u16) (temp_v0 + 6);
                }
            }
            sp2F = func_801D3494_58F3A4(arg0, spB4);
        }
        func_801D7194_5930A4(arg0, spB4, &sp30);
        func_801D56D0_5915E0(arg0, spB4, &sp30, 0, 0x3F00);
        if (sp2F < 0) {
            if (func_801D8290_5941A0(arg0, spB4) != 0) {
                CAMERA_TASK(arg0)->flags_bd = 0x80U;
                return;
            }
            CAMERA_TASK(arg0)->flags_bd = (u8) (CAMERA_TASK(arg0)->flags_bd & 0x7F);
            return;
        }
        if (func_801D8290_5941A0(arg0, spB4) != 0) {
            if (CAMERA_TASK(arg0)->flags_bd & 0x80) {
                temp_v0_2 = CAMERA_TASK(arg0)->pitch_limit;
                if (((s32) temp_v0_2 >= 0x29) && (sp2F == 0)) {
                    CAMERA_TASK(arg0)->pitch_limit = (u16) (temp_v0_2 - 6);
                }
                CAMERA_TASK(arg0)->flags_bd = 0x80U;
                return;
            }
            CAMERA_TASK(arg0)->path_pos.x = sp40;
            CAMERA_TASK(arg0)->path_pos.y = sp44;
            CAMERA_TASK(arg0)->path_pos.z = sp48;
            CAMERA_TASK(arg0)->path_distance = sp4C;
            memcpy(spB4, &sp54, 0x60);
            if (func_801D8290_5941A0(arg0, spB4) != 0) {
                CAMERA_TASK(arg0)->flags_bd = 0x80U;
            }
        } else {
            CAMERA_TASK(arg0)->flags_bd = (u8) (CAMERA_TASK(arg0)->flags_bd & 0x7F);
        }
    }
}

void func_801D6A98_5929A8(arg0, arg1)
void * arg0;
void * arg1;
{
    s16 temp_t1;
    s32 temp_t6;
    u16 temp_v0;

    temp_v0 = CAMERA_TASK(arg0)->yaw_step;
    temp_t6 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    temp_t1 = -0x4000 - CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->yaw_a4;
    CAMERA_TASK(arg0)->orbit_yaw = temp_t1;
    if ((temp_v0 != 0) && ((temp_v0 ^ (temp_t1 - CAMERA_SOLVE.pitch)) & 0x8000)) {
        CAMERA_TASK(arg0)->yaw_step = 0U;
    }
    func_801D7B74_593A84(arg0, temp_t6, 0x12, 0x2D0);
    if (CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->distance_ac < D_8020ACD0_5C6BE0) {
        func_801D8034_593F44(arg0, temp_t6, 3, 0x60);
    }
    func_801D5DC0_591CD0(arg0, temp_t6);
    func_801D5ECC_591DDC(arg0, temp_t6);
}

void func_801D6B80_592A90(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp5C;
    u16 sp58;
    u16 sp54;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp3C;
    f32 temp_f18;
    f32 temp_f8;
    s16 var_a1;
    s16 var_a1_2;
    s16 var_v0;
    s16 var_v1_2;
    s32 temp_t6;
    s32 temp_v0_6;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1;
    u16 var_a0;
    u16 var_v0_2;
    u16 var_v1;
    u8 temp_v0;
    u8 temp_v0_4;
    CAMERA_MODE_DEF *temp_v0_5;

    temp_t6 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    CAMERA_TASK(arg0)->mode_countdown = 0U;
    if ((s32) CAMERA_TASK(arg0)->overlay_state < 2) {
        temp_v0 = CAMERA_TASK(arg0)->yaw_pending;
        if (temp_v0 != 0) {
            if ((s32) temp_v0 < 3) {
                CAMERA_TASK(arg0)->yaw_pending = 0U;
            } else {
                CAMERA_TASK(arg0)->yaw_pending = (u8) (temp_v0 - 3);
            }
        }
        temp_v1 = CAMERA_TASK(arg0)->zoom_current;
        CAMERA_TASK(arg0)->zoom_target = 0U;
        if (temp_v1 != 0) {
            if ((s32) temp_v1 >= 3) {
                CAMERA_TASK(arg0)->zoom_current = (u16) (temp_v1 - 3);
            } else {
                CAMERA_TASK(arg0)->zoom_current = 0U;
            }
        }
    } else {
        var_v1 = CAMERA_TASK(arg0)->zoom_target;
        temp_v0_2 = CAMERA_OVERLAY(D_801FC62C_5B853C)->pitch;
        var_a0 = var_v1;
        if ((s32) var_v1 < (s32) temp_v0_2) {
            var_v1 = temp_v0_2 & 0xFFFF;
            var_a0 = var_v1;
            CAMERA_TASK(arg0)->zoom_target = temp_v0_2;
        }
        temp_v0_3 = CAMERA_TASK(arg0)->zoom_current;
        if ((s32) temp_v0_3 < (s32) var_a0) {
            if ((var_a0 - temp_v0_3) >= 8) {
                CAMERA_TASK(arg0)->zoom_current = (u16) (temp_v0_3 + 8);
            } else {
                CAMERA_TASK(arg0)->zoom_current = var_v1;
            }
        }
    }
    temp_v0_4 = CAMERA_TASK(arg0)->overlay_state;
    switch (temp_v0_4) {                            /* irregular */
    default:
        CAMERA_TASK(arg0)->zoom_target = 0x100U;
        CAMERA_TASK(arg0)->mode_step = 0U;
        CAMERA_TASK(arg0)->scripted_mode = 0;
        return;
    case 0:
        CAMERA_SOLVE.solve_flag = 1;
        CAMERA_TASK(arg0)->flags_bd = 0;
        CAMERA_TASK(arg0)->flag_aa = 0;
        sp5C = temp_t6;
        func_801D5FA8_591EB8(arg0, temp_t6, temp_t6);
        CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_TASK(arg0)->target_yaw;
        CAMERA_SOLVE.solve_flag = 1;
        CAMERA_TASK(arg0)->flags_bd = 0;
        CAMERA_TASK(arg0)->flag_aa = 0;
        if (func_801D7C20_593B30(arg0, sp5C, 8, 0x80, 0xE00) == 0xFF) {
            CAMERA_TASK(arg0)->overlay_state = (u8) (CAMERA_TASK(arg0)->overlay_state + 1);
            return;
        }
        return;
    case 1:
        CAMERA_SOLVE.solve_flag = 1;
        CAMERA_TASK(arg0)->flags_bd = 0;
        CAMERA_TASK(arg0)->flag_aa = 0;
        sp5C = temp_t6;
        func_801D5FA8_591EB8(arg0, temp_t6, temp_t6);
        CAMERA_TASK(arg0)->mode_countdown = (u8) (CAMERA_TASK(arg0)->mode_countdown | 2);
        var_v1_2 = (s32) (CAMERA_INPUT->look_x * D_8020ACD4_5C6BE4) & 0xFFFF;
        var_a1 = var_v1_2;
        if (var_v1_2 >= 0x201) {
            var_v1_2 = 0x200;
            var_a1 = 0x200;
        }
        if (var_a1 < -0x200) {
            var_v1_2 = -0x200;
        }
        sp58 = CAMERA_SOLVE.pitch + var_v1_2;
        var_v0 = (s32) (-CAMERA_INPUT->look_y * D_8020ACD8_5C6BE8) & 0xFFFF;
        var_a1_2 = var_v0;
        if (var_v0 >= 0x101) {
            var_v0 = 0x100;
            var_a1_2 = 0x100;
        }
        if (var_a1_2 < -0x100) {
            var_v0 = -0x100;
        }
        sp54 = CAMERA_SOLVE.yaw + var_v0;
        func_801D5338_591248(&sp54, var_a1_2, &D_800BCCC0_BD8C0);
        temp_f18 = CAMERA_SOLVE.distance * func_80003D88_4988(sp54, &sp3C);
        CAMERA_SOLVE.distance_target = CAMERA_SOLVE.distance * sp3C;
        sp48 = temp_f18 - CAMERA_SOLVE.camera_vec.y;
        temp_f8 = (CAMERA_SOLVE.distance_target * func_80003D88_4988(sp58, &sp3C)) - CAMERA_SOLVE.camera_vec.z;
        sp44 = (CAMERA_SOLVE.distance_target * sp3C) - CAMERA_SOLVE.camera_vec.x;
        sp4C = temp_f8;
        func_801D56D0_5915E0(arg0, sp5C, &sp44, 0, 0x3F00);
        return;
    case 2:
        if ((s32) &func_801D6710_592620 == CAMERA_MODE_TABLE[CAMERA_SOLVE.flag_02].callback) {
            sp5C = temp_t6;
            var_v0_2 = func_80003A94_4694(CAMERA_TASK(arg0)->path_pos.z - CAMERA_VIEW(temp_t6)->target.z, CAMERA_TASK(arg0)->path_pos.x - CAMERA_VIEW(temp_t6)->target.x, &D_801FC91C_5B882C, temp_t6);
        } else {
            sp5C = temp_t6;
            var_v0_2 = func_80003A94_4694(CAMERA_OVERLAY(D_801FC62C_5B853C)->dz, CAMERA_OVERLAY(D_801FC62C_5B853C)->dx, &D_801FC91C_5B882C, temp_t6);
        }
        CAMERA_TASK(arg0)->orbit_yaw = var_v0_2;
        CAMERA_TASK(arg0)->mode_id = (u8) CAMERA_SOLVE.flag_02;
        func_801D5214_591124(arg0, sp5C);
        CAMERA_TASK(arg0)->mode_id = 0x11U;
        if (func_801D7058_592F68(arg0, sp5C) != 0) {
            CAMERA_TASK(arg0)->blend_timer = 0x10;
            func_80221FB0_5DD480();
            return;
        }
        break;
    case 3:
        CAMERA_TASK(arg0)->distance = CAMERA_MODE_TABLE[CAMERA_SOLVE.flag_02].step[CAMERA_TASK(arg0)->mode_step].distance;
        temp_v0_5 = &CAMERA_MODE_TABLE[CAMERA_SOLVE.flag_02];
        if (((s32) &func_801D6710_592620 == temp_v0_5->callback) && !(temp_v0_5->flags & 4)) {
            CAMERA_TASK(arg0)->distance = (f32) CAMERA_SOLVE.height;
        }
        if (CAMERA_SOLVE.distance < CAMERA_SOLVE.height_target) {
            CAMERA_SOLVE.solve_flag = 1;
        }
        temp_v0_6 = func_801D5ECC_591DDC(arg0, temp_t6, temp_t6);
        if ((CAMERA_TASK(arg0)->distance <= CAMERA_SOLVE.distance) || (temp_v0_6 == 0)) {
            CAMERA_TASK(arg0)->overlay_state = (u8) (CAMERA_TASK(arg0)->overlay_state + 1);
        }
        break;
    }
}

s32 func_801D7058_592F68(arg0, arg1)
void * arg0;
s32 arg1;
{
    u16 sp2C;
    u8 sp2B;
    s32 var_v0;
    u16 temp_t2;
    u16 var_t0;

    CAMERA_SOLVE.solve_flag = 1;
    CAMERA_TASK(arg0)->flags_bd = 0;
    CAMERA_TASK(arg0)->flag_aa = 0;
    sp2B = func_801D7C20_593B30(arg1, 8, 0x80, 0xE00);
    temp_t2 = (func_80003A94_4694(CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.z - CAMERA_BG(D_801FC60C_5B851C)->tz, CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.x - CAMERA_BG(D_801FC60C_5B851C)->tx, &D_8020CBF0_5C8B00) - CAMERA_OVERLAY(D_801FC62C_5B853C)->heading) & 0xFFFF;
    var_t0 = temp_t2;
    if (temp_t2 & 0x8000) {
        var_t0 = (0x10000 - temp_t2) & 0xFFFF;
    }
    CAMERA_SOLVE.solve_flag = 1;
    CAMERA_TASK(arg0)->flags_bd = 0;
    CAMERA_TASK(arg0)->flag_aa = 0;
    CAMERA_SOLVE.hit_flag = 0;
    sp2C = var_t0;
    func_801D8034_593F44(arg0, arg1, 0x200, 0x600);
    var_v0 = 0;
    if (((((CAMERA_TASK(arg0)->pitch - CAMERA_SOLVE.yaw) + 8) & 0xFFFF) < 0x10) && ((sp2B == 0xFF) || ((s32) var_t0 < 8))) {
        var_v0 = 1;
        CAMERA_TASK(arg0)->overlay_state = (u8) (CAMERA_TASK(arg0)->overlay_state + 1);
    }
    return var_v0;
}

void func_801D7194_5930A4(arg0, arg1, arg2)
void * arg0;
void * arg1;
void * arg2;
{
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp2C;
    f32 sp24;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f16;
    f32 var_f20;
    u16 var_v0;

    sp2C = CAMERA_TASK(arg0)->path_pos.x;
    sp24 = CAMERA_TASK(arg0)->path_pos.z;
    var_v0 = CAMERA_TASK(arg0)->mode_flags;
    if (var_v0 & 2) {
        var_f20 = CAMERA_TASK(arg0)->path_pos.y;
        var_f16 = CAMERA_VIEW(arg1)->target.y;
    } else {
        var_f16 = CAMERA_VIEW(arg1)->target.y;
        var_v0 = CAMERA_TASK(arg0)->mode_flags;
        var_f20 = (func_80003DC0_49C0(CAMERA_TASK(arg0)->pitch, arg0) * CAMERA_SOLVE.height) + var_f16;
    }
    temp_f18 = var_f20 - var_f16;
    temp_f0 = sqrtf((CAMERA_SOLVE.height * CAMERA_SOLVE.height) + (temp_f18 * temp_f18));
    if (var_v0 & 4) {
        sp20 = CAMERA_TASK(arg0)->distance;
        if (sp20 < temp_f0) {
            temp_f2 = sp20 / temp_f0;
            temp_f12 = CAMERA_VIEW(arg1)->target.x;
            sp40 = temp_f18;
            temp_f4 = sp2C - temp_f12;
            sp44 = temp_f4;
            temp_f14 = CAMERA_VIEW(arg1)->target.z;
            temp_f10 = sp24 - temp_f14;
            sp3C = temp_f10;
            sp2C = temp_f12 + (temp_f4 * temp_f2);
            var_f20 = var_f16 + (sp40 * temp_f2);
            sp24 = temp_f14 + (temp_f10 * temp_f2);
        }
    }
    ((CAMERA_VEC3F *)(arg2))->x = (f32) (sp2C - CAMERA_VIEW(arg1)->pos.x);
    ((CAMERA_VEC3F *)(arg2))->y = (f32) (var_f20 - CAMERA_VIEW(arg1)->pos.y);
    ((CAMERA_VEC3F *)(arg2))->z = (f32) (sp24 - CAMERA_VIEW(arg1)->pos.z);
}

void func_801D72D4_5931E4(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 sp88;
    f32 sp94;
    s32 spA4;
    f32 spD0;
    s32 spEC;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    s32 spB4;
    s32 sp90;
    s32 sp6C;
    u16 sp6A;
    f32 sp5C;
    u8 sp5B;
    f32 sp54;
    u16 sp4A;
    f32 sp44;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_v0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 var_a0;
    u16 var_a2;

    CAMERA_SOLVE.hit_flag = 0;
    sp6A = 0xC000;
    sp5B = 0;
    CAMERA_SOLVE.last_heading = 0xC000;
    if (func_80029E08_2AA08(CAMERA_VIEW(arg1)->pos.x, CAMERA_VIEW(arg1)->pos.y, CAMERA_VIEW(arg1)->pos.z) == 0) {
        CAMERA_SOLVE.solve_flag = 0;
        func_8002A718_2B318(&sp6C, CAMERA_VIEW(arg1)->pos.x, CAMERA_VIEW(arg1)->pos.y, CAMERA_VIEW(arg1)->pos.z);
        if ((spA4 == 0x7FFF) && (func_8001D394_1DF94(&sp90) != 0) && (D_8020ACE0_5C6BF0 < (f64) sp94)) {
            CAMERA_SOLVE.last_heading = func_80003A94_4694(CAMERA_SOLVE.camera_vec.y + 15.0f + sp88, CAMERA_SOLVE.distance_target);
            if (sp88 > -15.0f) {
                sp6A = CAMERA_SOLVE.last_heading;
            }
        }
    } else {
        CAMERA_SOLVE.solve_flag = 1;
        func_8002A458_2B058(&sp6C, CAMERA_VIEW(arg1)->pos.x, CAMERA_VIEW(arg1)->pos.y, CAMERA_VIEW(arg1)->pos.z, 0.0f, -1.0f, 0.0f);
        if ((spA4 == 0x7FFF) && (func_8001D394_1DF94(&sp90) != 0) && (D_8020ACE8_5C6BF8 < (f64) sp94) && (sp88 < 5.0f)) {
            temp_v0 = func_80003A94_4694(CAMERA_SOLVE.camera_vec.y + sp88, CAMERA_SOLVE.distance_target);
            CAMERA_SOLVE.last_heading = temp_v0;
            sp6A = temp_v0;
        }
    }
    if (CAMERA_TARGET(D_801FC604_5B8514)->lock_61 == 0) {
        temp_f14 = CAMERA_SOLVE.distance - CAMERA_VIEW(arg1)->near_clip;
        sp54 = temp_f14;
        temp_v0_2 = func_80003A94_4694(func_80003DC0_49C0(CAMERA_VIEW(arg1)->angle) * CAMERA_VIEW(arg1)->near_clip, temp_f14);
        sp4A = temp_v0_2;
        temp_f2 = func_80003DC0_49C0((CAMERA_SOLVE.yaw - temp_v0_2) & 0xFFFF) * CAMERA_SOLVE.distance_target;
        sp44 = temp_f2;
        func_80032850_33450(&spB4, CAMERA_VIEW(arg1)->pos.x, (CAMERA_VIEW(arg1)->pos.y + temp_f2) - CAMERA_SOLVE.camera_vec.y, CAMERA_VIEW(arg1)->pos.z);
        if ((spEC == 0x7FFF) && (spD0 < (func_80003DC0_49C0(0x3000U) * CAMERA_SOLVE.distance_target))) {
            temp_t7 = func_80003A94_4694(sp44 + spD0, CAMERA_SOLVE.distance_target) + sp4A;
            var_a0 = temp_t7 & 0xFFFF;
            if (((temp_t7 + 0x4000) & 0xFFFF) >= 0x7001) {
                var_a0 = 0x3000;
            }
            if (((sp6A + 0x4000) & 0xFFFF) < ((var_a0 + 0x4000) & 0xFFFF)) {
                CAMERA_SOLVE.last_heading = var_a0;
                sp6A = var_a0;
            }
        }
    }
    var_a2 = sp6A;
    temp_t5 = (var_a2 + 0x4000) & 0xFFFF;
    var_v0 = temp_t5;
    if (temp_t5 >= 0x7801) {
        var_a2 = 0x3800;
        var_v0 = 0x7800;
    }
    if (var_v0 < 0x800) {
        var_a2 = 0xC800;
    }
    temp_t6 = (CAMERA_SOLVE.yaw + 0x4000) & 0xFFFF;
    if (temp_t6 >= 0x7801) {
        var_a2 = 0x3800;
        sp5B = 1;
    }
    if ((sp5B != 0) || (temp_t6 < ((var_a2 + 0x4000) & 0xFFFF))) {
        if (CAMERA_SOLVE.last_heading == var_a2) {
            CAMERA_SOLVE.hit_flag = 1;
        }
        if (CAMERA_TASK(arg0)->pitch_step & 0x8000) {
            CAMERA_TASK(arg0)->pitch_step = 0U;
        }
        temp_f12 = CAMERA_SOLVE.distance * sp5C;
        temp_f6 = (CAMERA_SOLVE.distance * func_80003D88_4988(var_a2 & 0xFFFF, &sp5C, var_a2)) - CAMERA_SOLVE.camera_vec.y;
        spFC = ((temp_f12 * CAMERA_SOLVE.camera_vec.x) / CAMERA_SOLVE.distance_target) - CAMERA_SOLVE.camera_vec.x;
        sp100 = temp_f6;
        sp104 = ((temp_f12 * CAMERA_SOLVE.camera_vec.z) / CAMERA_SOLVE.distance_target) - CAMERA_SOLVE.camera_vec.z;
        if ((func_801D56D0_5915E0(temp_f12, CAMERA_SOLVE.distance_target, arg0, arg1, &spFC, 0, 0x3F00) != 0) && (CAMERA_SOLVE.solve_flag != 0)) {
            CAMERA_SOLVE.solve_flag = func_80029E08_2AA08(CAMERA_VIEW(arg1)->pos.x, CAMERA_VIEW(arg1)->pos.y, CAMERA_VIEW(arg1)->pos.z);
        }
    }
}

u8 func_801D7720_593630(arg0, arg1)
s32 arg0;
s32 arg1;
{
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp2C;
    u8 sp29;
    f32 temp_f4;
    s16 temp_v0;
    s32 temp_t0;
    s32 temp_v0_2;
    u8 temp_v1;

    temp_v0 = func_801D7818_593728();
    CAMERA_SOLVE.roll = temp_v0;
    temp_t0 = ((CAMERA_SOLVE.yaw_target + temp_v0) - CAMERA_SOLVE.pitch_target) & 0xFFFF;
    if ((((temp_t0 - CAMERA_SOLVE.pitch) + 0x20) & 0xFFFF) < 0x41) {
        return 1U;
    }
    temp_f4 = (CAMERA_SOLVE.distance_target * func_80003D88_4988(temp_t0, &sp2C)) - CAMERA_SOLVE.camera_vec.z;
    sp34 = (CAMERA_SOLVE.distance_target * sp2C) - CAMERA_SOLVE.camera_vec.x;
    sp38 = 0.0f;
    sp3C = temp_f4;
    temp_v0_2 = func_801D56D0_5915E0(arg0, arg1, &sp34, 0, 0x3F00);
    temp_v1 = temp_v0_2 & 0xFF;
    if (temp_v0_2 & 0xFF) {
        sp29 = temp_v1;
        func_801D72D4_5931E4(arg0, arg1);
    }
    return temp_v1;
}

s16 func_801D7818_593728(arg0, arg1)
void * arg0;
void * arg1;
{
    f32 temp_f12;
    f32 temp_f14;

    temp_f14 = CAMERA_VIEW(arg1)->target.x - CAMERA_TASK(arg0)->path_pos.x;
    temp_f12 = CAMERA_VIEW(arg1)->target.z - CAMERA_TASK(arg0)->path_pos.z;
    CAMERA_SOLVE.height = sqrtf((temp_f14 * temp_f14) + (temp_f12 * temp_f12));
    return func_80003A94_4694(temp_f12, temp_f14);
}

void func_801D7868_593778(arg0, arg1, arg2, arg3, arg4)
void * arg0;
s32 arg1;
s32 arg2;
s32 arg3;
u16 arg4;
{
    s32 temp_t7;
    u16 temp_t1;
    u16 temp_t7_2;
    u16 var_v0;
    u16 var_v0_2;

    temp_t7 = arg3 & 0xFFFF;
    if (arg2 & 0x8000) {
        var_v0 = CAMERA_TASK(arg0)->yaw_step;
        if (!(var_v0 & 0x8000)) {
            CAMERA_TASK(arg0)->yaw_step = 0U;
            var_v0 = 0 & 0xFFFF;
        }
        temp_t1 = var_v0 - temp_t7;
        CAMERA_TASK(arg0)->yaw_step = temp_t1;
        if ((temp_t1 + arg4) & 0x8000) {
            CAMERA_TASK(arg0)->yaw_step = (u16) -(s32) arg4;
        }
    } else {
        var_v0_2 = CAMERA_TASK(arg0)->yaw_step;
        if (var_v0_2 & 0x8000) {
            CAMERA_TASK(arg0)->yaw_step = 0U;
            var_v0_2 = 0 & 0xFFFF;
        }
        temp_t7_2 = var_v0_2 + temp_t7;
        CAMERA_TASK(arg0)->yaw_step = temp_t7_2;
        if (!((temp_t7_2 - arg4) & 0x8000)) {
            CAMERA_TASK(arg0)->yaw_step = arg4;
        }
    }
}

u16 func_801D7900_593810(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    u16 sp3E;
    f32 temp_f4;
    s32 temp_a1;
    s32 temp_t7;
    s32 temp_t7_3;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_t4;
    u16 temp_t7_2;
    u16 temp_t9;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_4;
    u16 var_a0;
    u8 temp_v0;
    u8 temp_v1_3;

    var_v0 = 0x400;
    temp_t7 = (CAMERA_TASK(arg0)->orbit_yaw - CAMERA_SOLVE.pitch) & 0xFFFF;
    if (CAMERA_TASK(arg0)->flag_ab != 0) {
        CAMERA_TASK(arg0)->yaw_step = 0U;
        if (((temp_t7 + 0x20) & 0xFFFF) < 0x41) {
            CAMERA_SOLVE.pitch = CAMERA_TASK(arg0)->orbit_yaw;
            CAMERA_TASK(arg0)->flag_ab = 0U;
            CAMERA_TASK(arg0)->yaw_step = 0U;
            return 1U;
        }
        if (temp_t7 & 0x8000) {
            CAMERA_TASK(arg0)->yaw_step = 0x100U;
        } else {
            CAMERA_TASK(arg0)->yaw_step = 0xFF00U;
        }
        temp_t9 = CAMERA_TASK(arg0)->yaw_step + CAMERA_SOLVE.pitch;
        CAMERA_SOLVE.pitch = temp_t9;
        if (!((CAMERA_TASK(arg0)->yaw_step ^ temp_t7) & 0x8000)) {
            temp_v1_2 = CAMERA_TASK(arg0)->orbit_yaw;
            if (((temp_v1_2 - temp_t9) ^ temp_t7) & 0x8000) {
                CAMERA_SOLVE.pitch = temp_v1_2;
            }
        }
        var_a0 = CAMERA_SOLVE.pitch;
        goto block_27;
    }
    temp_v1_3 = CAMERA_TASK(arg0)->flag_a3;
    if (temp_v1_3 != 0) {
        if ((temp_v1_3 & 1) && (temp_v1_3 != 0)) {
            temp_a1 = CAMERA_TASK(arg0)->target_heading - CAMERA_SOLVE.pitch;
            if ((temp_a1 & 0xFFFF) < 0x400) {
                var_v0 = temp_a1 & 0xFFFF;
            }
        }
        if (temp_v1_3 & 2) {
            if ((temp_v1_3 != 0) && (temp_v1_4 = CAMERA_TASK(arg0)->target_heading, ((((CAMERA_SOLVE.pitch - temp_v1_4) & 0xFFFF) < var_v0) != 0))) {
                var_v0 = (temp_v1_4 - CAMERA_SOLVE.pitch) & 0xFFFF;
            } else {
                var_v0 = -var_v0 & 0xFFFF;
            }
        }
        temp_t7_2 = CAMERA_SOLVE.pitch + var_v0;
        CAMERA_SOLVE.pitch = temp_t7_2;
        var_a0 = temp_t7_2 & 0xFFFF;
        goto block_27;
    }
    temp_v0 = CAMERA_TASK(arg0)->flags_bd;
    if (temp_v0 & 0x80) {
        if (temp_v0 & 1) {
            var_v0_2 = 1;
        } else {
            var_v0_2 = 0xFFFF;
        }
        func_801D7868_593778(arg0, arg1, var_v0_2 & 0xFFFF, 0x120, 0x120);
        temp_t4 = CAMERA_TASK(arg0)->yaw_step + CAMERA_SOLVE.pitch;
        CAMERA_SOLVE.pitch = temp_t4;
        var_a0 = temp_t4 & 0xFFFF;
block_27:
        temp_f4 = (CAMERA_SOLVE.distance_target * func_80003D88_4988(var_a0, &sp44)) - CAMERA_SOLVE.camera_vec.z;
        sp4C = (CAMERA_SOLVE.distance_target * sp44) - CAMERA_SOLVE.camera_vec.x;
        sp50 = 0.0f;
        sp54 = temp_f4;
        temp_v0_2 = func_801D56D0_5915E0(arg0, arg1, &sp4C, 0, 0x3F00);
        temp_v1 = temp_v0_2 & 0xFFFF;
        temp_t7_3 = temp_v0_2 & 0xFFFF;
        if ((CAMERA_TASK(arg0)->flag_a3 != 0) && (temp_t7_3 == 0)) {
            CAMERA_TASK(arg0)->flag_a3 = 0U;
        }
        if (temp_v0_2 & 0xFFFF) {
            sp3E = temp_v1;
            func_801D72D4_5931E4(arg0, arg1);
        }
        return temp_v1;
    }
    return 0U;
}

void func_801D7B74_593A84(arg0, arg1, arg2, arg3)
s32 arg0;
s32 arg1;
u16 arg2;
u16 arg3;
{
    s32 sp28;
    s32 temp_v0;

    memcpy(&sp28, arg1, 0x60);
    if (CAMERA_SOLVE.blend_flag == 0) {
        temp_v0 = func_801D7C20_593B30(arg0, &sp28, 0x20, arg2, (s32) arg3);
        if (temp_v0 != 0xFF) {
            if (temp_v0 != 0) {
                func_801D72D4_5931E4(arg0, &sp28);
            }
            func_801D80F4_594004(arg0, arg1, &sp28);
        }
    }
}

s32 func_801D7C20_593B30(arg0, arg1, arg2, arg3, arg4)
void * arg0;
s32 arg1;
s32 arg2;
s32 arg3;
u16 arg4;
{
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    u16 sp42;
    s32 sp30;
    f32 temp_f4;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_v1;
    u16 temp_t2;
    u16 temp_t9;
    u16 temp_v1;
    u16 temp_v1_3;

    temp_v1 = CAMERA_TASK(arg0)->orbit_yaw;
    temp_t6 = arg2 & 0xFFFF;
    temp_t9 = temp_v1 - CAMERA_SOLVE.pitch;
    temp_t0 = temp_t9 & 0xFFFF;
    sp42 = temp_t9;
    if ((temp_t6 * 2) >= ((temp_t0 + temp_t6) & 0xFFFF)) {
        CAMERA_SOLVE.pitch = temp_v1;
        CAMERA_TASK(arg0)->yaw_step = 0U;
        CAMERA_TASK(arg0)->flags_bd = 0U;
        return 0xFF;
    }
    temp_v1_2 = temp_t0 & 0x8000;
    if (temp_v1_2 != 0) {
        var_a0 = CAMERA_TASK(arg0)->flags_bd & 1;
    } else {
        var_a0 = CAMERA_TASK(arg0)->flags_bd & 2;
    }
    if (var_a0 == 0) {
        if (temp_v1_2 != 0) {
            var_v1 = CAMERA_TASK(arg0)->flag_aa & 1;
        } else {
            var_v1 = CAMERA_TASK(arg0)->flag_aa & 2;
        }
        if (var_v1 != 0) {
            goto block_10;
        }
        sp30 = temp_t0;
        func_801D7868_593778(arg0, arg1, sp42, arg3 & 0xFFFF, (s32) arg4);
        temp_t2 = CAMERA_TASK(arg0)->yaw_step + CAMERA_SOLVE.pitch;
        CAMERA_SOLVE.pitch = temp_t2;
        if (!((CAMERA_TASK(arg0)->yaw_step ^ temp_t0) & 0x8000)) {
            temp_v1_3 = CAMERA_TASK(arg0)->orbit_yaw;
            if (((temp_v1_3 - temp_t2) ^ temp_t0) & 0x8000) {
                CAMERA_SOLVE.pitch = temp_v1_3;
            }
        }
    } else {
block_10:
        if (!(CAMERA_TASK(arg0)->flags_bd & 0x80)) {
            CAMERA_TASK(arg0)->flags_bd = 0U;
        }
    }
    temp_f4 = (CAMERA_SOLVE.distance_target * func_80003D88_4988(CAMERA_SOLVE.pitch, &sp44)) - CAMERA_SOLVE.camera_vec.z;
    sp4C = (CAMERA_SOLVE.distance_target * sp44) - CAMERA_SOLVE.camera_vec.x;
    sp50 = 0.0f;
    sp54 = temp_f4;
    return func_801D56D0_5915E0(arg0, arg1, &sp4C, 0, 0x3F00) & 0xFF;
}

u16 func_801D7DD0_593CE0(arg0, arg1, arg2, arg3)
void * arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a1_2;
    u16 temp_t3;
    u16 temp_t3_2;
    u16 temp_t5;
    u16 temp_t6;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 var_v1;

    var_v1 = CAMERA_SOLVE.yaw;
    temp_t6_2 = arg2 & 0xFFFF;
    temp_t7 = arg3 & 0xFFFF;
    temp_t9 = (CAMERA_TASK(arg0)->pitch - var_v1) & 0xFFFF;
    if (temp_t9 != 0) {
        if (temp_t9 & 0x8000) {
            if (CAMERA_SOLVE.hit_flag != 0) {
                return var_v1;
            }
            temp_v0 = -temp_t7;
            temp_t3 = CAMERA_TASK(arg0)->pitch_step - temp_t6_2;
            var_a1 = temp_t3 & 0xFFFF;
            CAMERA_TASK(arg0)->pitch_step = temp_t3;
            if ((var_a1 & 0x8000) && (var_a1 < (temp_v0 & 0xFFFF))) {
                CAMERA_TASK(arg0)->pitch_step = (u16) temp_v0;
                var_a1 = temp_v0 & 0xFFFF;
            }
            temp_t6 = (var_v1 + var_a1) & 0xFFFF;
            var_v1 = temp_t6;
            if ((CAMERA_SOLVE.last_heading != 0x8000) && (((temp_t6 + 0x4000) & 0xFFFF) < ((CAMERA_SOLVE.last_heading + 0x4000) & 0xFFFF))) {
                return temp_t6;
            }
            temp_v0_2 = CAMERA_TASK(arg0)->pitch;
            temp_a2 = temp_v0_2 - var_v1;
            if ((temp_a2 == 0) || !(temp_a2 & 0x8000)) {
                var_v1 = temp_v0_2 & 0xFFFF;
                goto block_19;
            }
            /* Duplicate return node #20. Try simplifying control flow for better match */
            return var_v1;
        }
        temp_t3_2 = CAMERA_TASK(arg0)->pitch_step + temp_t6_2;
        var_a1_2 = temp_t3_2 & 0xFFFF;
        CAMERA_TASK(arg0)->pitch_step = temp_t3_2;
        if (!(var_a1_2 & 0x8000) && (temp_t7 < var_a1_2)) {
            CAMERA_TASK(arg0)->pitch_step = (u16) temp_t7;
            var_a1_2 = temp_t7 & 0xFFFF;
        }
        temp_v0_3 = CAMERA_TASK(arg0)->pitch;
        temp_t5 = (var_v1 + var_a1_2) & 0xFFFF;
        temp_a2_2 = temp_v0_3 - temp_t5;
        var_v1 = temp_t5;
        if ((temp_a2_2 == 0) || (temp_a2_2 & 0x8000)) {
            var_v1 = temp_v0_3 & 0xFFFF;
block_19:
            CAMERA_TASK(arg0)->pitch_step = 0U;
        }
        /* Duplicate return node #20. Try simplifying control flow for better match */
        return var_v1;
    }
    return var_v1;
}

void func_801D7F20_593E30(arg0, arg1)
s32 arg0;
s32 arg1;
{
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 temp_f12;
    f32 temp_f8;

    if (((CAMERA_SOLVE.yaw + 0x4000) & 0xFFFF) < ((CAMERA_SOLVE.flag_00 + 0x4000) & 0xFFFF)) {
        temp_f12 = CAMERA_SOLVE.distance * sp40;
        temp_f8 = (CAMERA_SOLVE.distance * func_80003D88_4988(CAMERA_SOLVE.flag_00 & 0xFFFF, &sp40, CAMERA_SOLVE.flag_00)) - CAMERA_SOLVE.camera_vec.y;
        sp34 = ((temp_f12 * CAMERA_SOLVE.camera_vec.x) / CAMERA_SOLVE.distance_target) - CAMERA_SOLVE.camera_vec.x;
        sp38 = temp_f8;
        sp3C = ((temp_f12 * CAMERA_SOLVE.camera_vec.z) / CAMERA_SOLVE.distance_target) - CAMERA_SOLVE.camera_vec.z;
        func_801D56D0_5915E0(temp_f12, CAMERA_SOLVE.camera_vec.x, arg0, arg1, &sp34, 0, 0x3F00);
    }
    if (CAMERA_SOLVE.height_target < CAMERA_SOLVE.distance_target) {
        func_801D8034_593F44(arg0, arg1, 3, 0x60);
        return;
    }
    func_801D8034_593F44(arg0, arg1, 0x120, 0x400);
}

s32 func_801D8034_593F44(arg0, arg1, arg2, arg3)
s32 arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp38;
    f32 temp_f12;
    f32 temp_f8;

    temp_f12 = CAMERA_SOLVE.distance * sp38;
    temp_f8 = (CAMERA_SOLVE.distance * func_80003D88_4988(func_801D7DD0_593CE0(arg2 & 0xFFFF, arg3 & 0xFFFF) & 0xFFFF, &sp38)) - CAMERA_SOLVE.camera_vec.y;
    sp44 = ((temp_f12 * CAMERA_SOLVE.camera_vec.x) / CAMERA_SOLVE.distance_target) - CAMERA_SOLVE.camera_vec.x;
    sp48 = temp_f8;
    sp4C = ((temp_f12 * CAMERA_SOLVE.camera_vec.z) / CAMERA_SOLVE.distance_target) - CAMERA_SOLVE.camera_vec.z;
    return func_801D56D0_5915E0(temp_f12, CAMERA_SOLVE.camera_vec.x, arg0, arg1, &sp44, 0, 0x3F00) & 0xFF;
}

void func_801D80F4_594004(arg0, arg1, arg2)
void * arg0;
void * arg1;
void * arg2;
{
    u16 sp24;
    s32 temp_a1;
    s32 temp_v0;
    s32 var_a0;
    CAMERA_ACTOR_WORK *temp_a0;

    if (CAMERA_TASK(arg0)->mode_flags & 1) {
        CAMERA_TASK(arg0)->flags_bd = 0U;
        return;
    }
    if (func_801D8290_5941A0(arg0, arg2) == 0) {
        CAMERA_TASK(arg0)->flags_bd = (u8) (CAMERA_TASK(arg0)->flags_bd & 0x7F);
        memcpy(arg1, arg2, 0x60);
        return;
    }
    if (!(CAMERA_TASK(arg0)->flags_bd & 0x80)) {
        temp_v0 = func_801D8290_5941A0(arg0, arg1);
        temp_a1 = temp_v0 & 0xFFFF;
        var_a0 = temp_v0 & 0xFFFF;
        if (temp_a1 != 0) {
            if (temp_a1 & 0x80) {
                sp24 = func_80003A94_4694(CAMERA_BG(D_801FC614_5B8524)->tz - CAMERA_VIEW(arg1)->pos.z, CAMERA_BG(D_801FC614_5B8524)->tx - CAMERA_VIEW(arg1)->pos.x, var_a0, temp_a1);
                temp_a0 = CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor;
                var_a0 = 2;
                if ((sp24 - func_80003A94_4694((CAMERA_BG(D_801FC614_5B8524)->tz + temp_a0->offset_z_14) - CAMERA_VIEW(arg1)->pos.z, (CAMERA_BG(D_801FC614_5B8524)->tx + temp_a0->offset_x_0c) - CAMERA_VIEW(arg1)->pos.x, (s32) temp_a0)) & 0x8000) {
                    var_a0 = 1;
                }
            }
            CAMERA_TASK(arg0)->flags_bd = (u8) (var_a0 | 0x80);
            CAMERA_TASK(arg0)->flag_aa = (u8) (CAMERA_TASK(arg0)->flag_aa | var_a0);
            return;
        }
    }
    memcpy(arg1, arg2, 0x60);
}

s8 func_801D8290_5941A0(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp6C;
    f32 sp70;
    s32 unksp7D;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp88;
    f32 sp80;
    u16 sp7C;
    s32 sp34;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    s32 temp_v0;

    sp7C = 0;
    sp94 = CAMERA_VIEW(arg1)->pos.x - CAMERA_BG(D_801FC614_5B8524)->tx;
    sp98 = CAMERA_VIEW(arg1)->pos.y - (CAMERA_BG(D_801FC614_5B8524)->ty + 20.0f);
    sp9C = CAMERA_VIEW(arg1)->pos.z - CAMERA_BG(D_801FC614_5B8524)->tz;
    temp_v0 = func_80029E08_2AA08(CAMERA_VIEW(arg1)->pos.x, CAMERA_VIEW(arg1)->pos.y, CAMERA_VIEW(arg1)->pos.z);
    if (CAMERA_TASK(arg0)->flag_a3 != 0) {
        temp_f20 = sqrtf((sp9C * sp9C) + ((sp94 * sp94) + (sp98 * sp98)));
        if (temp_v0 == 0) {
            func_8001D394_1DF94(sp98, sp9C, &sp94);
            func_8002C9D4_2D5D4(&sp34, CAMERA_BG(D_801FC614_5B8524)->tx, CAMERA_BG(D_801FC614_5B8524)->ty + 20.0f, CAMERA_BG(D_801FC614_5B8524)->tz, sp94, sp98, sp9C, temp_f20);
            if ((sp6C == 0x7FFF) && (sqrtf(sp70) < temp_f20)) {
                sp7C = 0x80;
            }
        }
        if (sp7C != 0) {
            CAMERA_TASK(arg0)->flag_a3 = 0U;
        }
    } else if (temp_v0 == 0) {
        func_8001D460_1E060(sp98, &sp94, &sp88, &CAMERA_SOLVE.scratch_vec, arg1);
        temp_f2 = CAMERA_VIEW(arg1)->near_clip;
        temp_f10 = func_80003DC0_49C0(CAMERA_VIEW(arg1)->angle) * temp_f2;
        sp90 -= temp_f2;
        temp_f12 = temp_f10 * 0.75f;
        sp80 = temp_f12;
        sp88 -= temp_f12;
        func_8001D5B8_1E1B8(temp_f12, &sp88, &sp94, &CAMERA_SOLVE.scratch_vec, arg1);
        temp_f20_2 = sqrtf((sp9C * sp9C) + ((sp94 * sp94) + (sp98 * sp98)));
        func_8001D394_1DF94(sp98, sp9C, &sp94);
        func_8002C9D4_2D5D4(&sp34, CAMERA_BG(D_801FC614_5B8524)->tx, CAMERA_BG(D_801FC614_5B8524)->ty + 20.0f, CAMERA_BG(D_801FC614_5B8524)->tz, sp94, sp98, sp9C, temp_f20_2);
        if ((sp6C == 0x7FFF) && (sqrtf(sp70) < temp_f20_2)) {
            sp7C = 2;
        } else {
            sp88 += sp80 * 2.0f;
            func_8001D5B8_1E1B8(((f32)(s32)(&sp88)), &sp94, &CAMERA_SOLVE.scratch_vec);
            func_8001D394_1DF94(((f32)(s32)(&sp94)));
            func_8002C9D4_2D5D4(&sp34, CAMERA_BG(D_801FC614_5B8524)->tx, CAMERA_BG(D_801FC614_5B8524)->ty + 20.0f, CAMERA_BG(D_801FC614_5B8524)->tz, sp94, sp98, sp9C, temp_f20_2);
            if ((sp6C == 0x7FFF) && (sqrtf(sp70) < temp_f20_2)) {
                sp7C = 1;
            }
        }
    }
    return unksp7D;
}

void func_801D85B0_5944C0(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp1C;
    s32 temp_t7;

    temp_t7 = CAMERA_BG(arg1)->AModel & 0x8FFFFFFE;
    sp1C = temp_t7;
    func_801D8F94_594EA4(temp_t7);
    if (CAMERA_BG(arg1)->unk_64 == 0) {
        func_801D896C_59487C(arg0, sp1C);
        if (CAMERA_TASK(arg0)->active != 0) {
            CAMERA_TASK(arg0)->mode_id = (u8) CAMERA_SOLVE.flag_02;
            CAMERA_TASK(arg0)->pending_mode = (u8) CAMERA_SOLVE.flag_02;
            func_801D90D8_594FE8(arg0);
        }
    }
}

void func_801D8634_594544(arg0, arg1, arg2, arg3)
void * arg0;
u16 arg1;
f32 arg2;
f32 arg3;
{
    s32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f16;
    f32 var_f20;
    s32 var_v0;
    u16 var_a1;

    var_f20 = arg2;
    sp70 = CAMERA_BG(CAMERA_TASK(arg0)->task.unk_18)->AModel & 0x8FFFFFFE;
    sp64 = 0.0f;
    sp60 = 0.0f;
    sp68 = CAMERA_SOLVE.distance;
    var_f16 = func_80003CC8_48C8(2.87e-42f) * CAMERA_SOLVE.distance;
    var_a1 = arg1;
    if ((f64) var_f16 < D_8020ACF0_5C6C00) {
        var_f16 = D_8020ACF8_5C6C08;
    }
    if (CAMERA_SOLVE.camera_vec.y < 0.0f) {
        var_f14 = -CAMERA_SOLVE.camera_vec.y;
    } else {
        var_f14 = CAMERA_SOLVE.camera_vec.y;
    }
    temp_f2 = CAMERA_SOLVE.distance - var_f14;
    sp68 += arg3;
    temp_f0 = sqrtf((CAMERA_SOLVE.distance_target * CAMERA_SOLVE.distance_target) + (temp_f2 * temp_f2));
    if (var_f20 != 0.0f) {
        if ((temp_f0 - var_f20) < var_f16) {
            var_v0 = 0;
            if (CAMERA_SOLVE.scratch_vec.y >= 0.0f) {
                var_v0 = 0x8000;
            }
            if (var_v0 == ((var_a1 - 0x4000) & 0x8000)) {
                if (temp_f0 < var_f16) {
                    var_a1 = 0;
                    if (CAMERA_SOLVE.scratch_vec.y >= 0.0f) {
                        var_a1 = 0x8000;
                    }
                }
                var_f20 = var_f16 - temp_f0;
            }
        }
        temp_f2_2 = var_f20 * var_f20;
        arg1 = var_a1;
        temp_f10 = (var_f20 * sqrtf((CAMERA_SOLVE.distance * CAMERA_SOLVE.distance) - (temp_f2_2 / 4.0f))) / CAMERA_SOLVE.distance;
        sp48 = temp_f10;
        sp68 = CAMERA_SOLVE.distance - (temp_f2_2 / (2.0f * CAMERA_SOLVE.distance));
        sp60 = func_80003CC8_48C8(CAMERA_SOLVE.distance_target, var_f14, var_a1 & 0xFFFF, var_a1) * -sp48;
        sp64 = func_80003D28_4928(arg1) * temp_f10;
    }
    if (sp68 <= 1.0f) {
        sp68 = 1.0f;
    }
    if (D_8020ACFC_5C6C0C <= sp68) {
        sp68 = D_8020ACFC_5C6C0C;
    }
    func_8001D5B8_1E1B8(&sp60, &sp54, &CAMERA_SOLVE.scratch_vec);
    sp54 -= CAMERA_SOLVE.camera_vec.x;
    sp58 -= CAMERA_SOLVE.camera_vec.y;
    CAMERA_SOLVE.solve_flag = 1;
    sp5C -= CAMERA_SOLVE.camera_vec.z;
    func_801D56D0_5915E0(arg0, sp70, &sp54, 0, 0x3F00);
    if ((s32) &func_801D6710_592620 != (CAMERA_TASK_EXEC_WORD(arg0, 1) & 0xFF7FFFFF)) {
        if (var_f20 < 0.0f) {
            var_f14_2 = -var_f20;
        } else {
            var_f14_2 = var_f20;
        }
        if (!((f64) var_f14_2 < D_8020AD00_5C6C10)) {
            CAMERA_TASK(arg0)->orbit_yaw = (u16) CAMERA_SOLVE.pitch;
            CAMERA_TASK(arg0)->pitch = (u16) CAMERA_SOLVE.yaw;
        }
        CAMERA_TASK(arg0)->flag_a2 = 1;
    }
    CAMERA_TASK(arg0)->mode_id = (u8) CAMERA_SOLVE.flag_02;
    CAMERA_TASK(arg0)->pending_mode = (u8) CAMERA_SOLVE.flag_02;
}

void func_801D896C_59487C(arg0, arg1)
void * arg0;
s32 arg1;
{
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    s32 sp60;
    f32 sp5C;
    u16 sp5A;
    u16 sp58;
    u16 sp56;
    f32 sp4C;
    s32 sp30;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_v1;
    u16 temp_v0_4;
    u16 var_t0;
    u8 temp_v0;
    u8 temp_v0_2;

    sp5C = CAMERA_TASK(arg0)->distance;
    sp4C = 0.0f;
    sp5A = CAMERA_INPUT->buttons_held;
    sp56 = 0;
    sp58 = CAMERA_INPUT->buttons_pressed;
    var_t0 = sp56;
    if ((func_801D8E08_594D18(D_801FC604_5B8514) == 0) && (CAMERA_TASK(arg0)->scripted_mode != 0)) {
        func_801D8F74_594E84(arg0);
    }
    if ((CAMERA_TASK(arg0)->route_step == 0) && (sp5A & 0x10)) {
        temp_v0 = CAMERA_TASK(arg0)->mode_step;
        if (temp_v0 == 0) {
            if ((sp58 & 8) && (D_800C7AB2 != 0x1AF)) {
                CAMERA_TARGET(D_801FC604_5B8514)->cooldown_ed = 1;
                sp56 = var_t0;
                sp30 = (s32) sp58;
                if ((func_801D8E08_594D18(D_801FC604_5B8514) != 0) && (CAMERA_TASK(arg0)->mode_id != 0x11)) {
                    sp30 = (s32) sp58;
                    sp56 = var_t0;
                    func_801D8E94_594DA4(arg0);
                }
            }
        } else if (sp58 & 8) {
            CAMERA_TASK(arg0)->mode_step = (u8) (temp_v0 - 1);
            CAMERA_TASK(arg0)->route_step = 1U;
        }
        if (sp58 & 4) {
            if (CAMERA_TASK(arg0)->scripted_mode != 0) {
                sp56 = var_t0;
                func_801D8F74_594E84(arg0);
            } else {
                temp_v0_2 = CAMERA_TASK(arg0)->mode_step;
                if ((temp_v0_2 + 1) < (s32) CAMERA_MODE_TABLE[CAMERA_TASK(arg0)->mode_id].step_count) {
                    CAMERA_TASK(arg0)->mode_step = (u8) (temp_v0_2 + 1);
                    CAMERA_TASK(arg0)->route_step = 1U;
                }
            }
        }
    }
    sp30 = sp5A & 0x10;
    if (CAMERA_TASK(arg0)->route_step != 0) {
        temp_f0 = CAMERA_TASK(arg0)->distance;
        temp_f2 = CAMERA_MODE_TABLE[CAMERA_TASK(arg0)->mode_id].step[CAMERA_TASK(arg0)->mode_step].distance;
        if (temp_f0 != temp_f2) {
            if (temp_f2 < temp_f0) {
                CAMERA_TASK(arg0)->distance_velocity = (f32) (CAMERA_TASK(arg0)->distance_velocity - 2.0f);
                if (CAMERA_TASK(arg0)->distance_velocity < -10.0f) {
                    CAMERA_TASK(arg0)->distance_velocity = -10.0f;
                }
                CAMERA_TASK(arg0)->distance = (f32) (CAMERA_TASK(arg0)->distance + CAMERA_TASK(arg0)->distance_velocity);
                temp_f2_2 = CAMERA_MODE_TABLE[CAMERA_TASK(arg0)->mode_id].step[CAMERA_TASK(arg0)->mode_step].distance;
                if (CAMERA_TASK(arg0)->distance <= temp_f2_2) {
                    CAMERA_TASK(arg0)->distance = temp_f2_2;
                    goto block_29;
                }
            } else {
                CAMERA_TASK(arg0)->distance_velocity = (f32) (CAMERA_TASK(arg0)->distance_velocity + 2.0f);
                if (CAMERA_TASK(arg0)->distance_velocity > 10.0f) {
                    CAMERA_TASK(arg0)->distance_velocity = 10.0f;
                }
                CAMERA_TASK(arg0)->distance = (f32) (CAMERA_TASK(arg0)->distance + CAMERA_TASK(arg0)->distance_velocity);
                temp_f2_3 = CAMERA_MODE_TABLE[CAMERA_TASK(arg0)->mode_id].step[CAMERA_TASK(arg0)->mode_step].distance;
                if (temp_f2_3 <= CAMERA_TASK(arg0)->distance) {
                    CAMERA_TASK(arg0)->distance = temp_f2_3;
block_29:
                    CAMERA_TASK(arg0)->distance_velocity = 0.0f;
                }
            }
        }
        sp4C = CAMERA_TASK(arg0)->distance - sp5C;
    }
    if (sp4C != 0.0f) {
        sp74 = sp4C;
        sp56 = var_t0;
        sp6C = 0.0f;
        sp70 = 0.0f;
        func_8001D5B8_1E1B8(&sp6C, &sp60, &CAMERA_SOLVE.scratch_vec);
        func_801D56D0_5915E0(arg0, arg1, &sp60, 0, 0);
        var_t0 = sp56;
        if ((s32) &func_801D6710_592620 != (CAMERA_TASK_EXEC_WORD(arg0, 1) & 0xFF7FFFFF)) {
            CAMERA_TASK(arg0)->flag_a2 = 1;
            CAMERA_TASK(arg0)->pitch = (u16) CAMERA_SOLVE.yaw;
        }
    } else {
        CAMERA_TASK(arg0)->route_step = 0U;
    }
    if ((CAMERA_TASK(arg0)->flag_a3 != 0) && ((((CAMERA_TASK(arg0)->target_heading - CAMERA_SOLVE.pitch) + 0x20) & 0xFFFF) < 0x40)) {
        CAMERA_TASK(arg0)->flag_a3 = 0U;
    }
    if (sp30 != 0) {
        if (sp58 & 2) {
            var_t0 = 1;
        }
        if (sp58 & 1) {
            var_t0 = (var_t0 | 2) & 0xFFFF;
        }
        temp_v0_3 = var_t0 & 3;
        if ((temp_v0_3 == 0) && (temp_v0_3 == 3)) {
            var_t0 = 0;
        }
        if (var_t0 != 0) {
            CAMERA_TASK(arg0)->flag_a3 = (u8) var_t0;
            if (var_t0 & 1) {
                var_a0 = 0x2000;
            } else {
                var_a0 = 0;
            }
            if (var_t0 & 2) {
                var_v1 = 0x2000;
            } else {
                var_v1 = 0;
            }
            temp_v0_4 = CAMERA_TASK(arg0)->target_yaw;
            CAMERA_TASK(arg0)->target_heading = (u16) ((temp_v0_4 + (((CAMERA_SOLVE.pitch - temp_v0_4) + 0x1000) & 0xE000) + var_a0) - var_v1);
        }
    }
}

s32 func_801D8E08_594D18(arg0)
void * arg0;
{
    s32 var_v0;

    if ((func_801E7DA0_5A3CB0() == 0) || (func_8003F1D8_3FDD8() != 0) || (CAMERA_TARGET(arg0)->flag_62 != 0) || (D_8020AD08_5C6C18 < (f64) CAMERA_TARGET(arg0)->tracked_actor->distance_b0) || (var_v0 = 1, (CAMERA_TASK(D_801FC624_5B8534)->mode_cooldown == 0))) {
        var_v0 = 0;
    }
    return var_v0;
}

void func_801D8E94_594DA4(arg0)
void * arg0;
{
    CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_y = 0U;
    CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_x = (u16) CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_y;
    CAMERA_OVERLAY(D_801FC62C_5B853C)->dx = (f32) (CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.x - CAMERA_VIEW(&D_8020CBF0_5C8B00)->target.x);
    CAMERA_OVERLAY(D_801FC62C_5B853C)->dy = (f32) (CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.y - CAMERA_VIEW(&D_8020CBF0_5C8B00)->target.y);
    CAMERA_OVERLAY(D_801FC62C_5B853C)->dz = (f32) (CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.z - CAMERA_VIEW(&D_8020CBF0_5C8B00)->target.z);
    CAMERA_OVERLAY(D_801FC62C_5B853C)->heading = func_80003A94_4694(CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.z - CAMERA_BG(D_801FC60C_5B851C)->tz, CAMERA_VIEW(&D_8020CBF0_5C8B00)->pos.x - CAMERA_BG(D_801FC60C_5B851C)->tx, D_801FC60C_5B851C, &D_801FC62C_5B853C);
    CAMERA_OVERLAY(D_801FC62C_5B853C)->pitch = (u16) CAMERA_TASK(D_801FC624_5B8534)->zoom_current;
    CAMERA_TASK(arg0)->overlay_state = 0;
    CAMERA_TASK(arg0)->scripted_mode = 1;
    CAMERA_TASK(arg0)->blend_timer = 4;
    func_80221F70_5DD440(arg0);
}

void func_801D8F74_594E84(arg0)
void * arg0;
{
    if ((s32) CAMERA_TASK(arg0)->overlay_state < 2) {
        CAMERA_TASK(arg0)->overlay_state = 2U;
    }
}

void func_801D8F94_594EA4(arg0, arg1)
void * arg0;
void * arg1;
{
    s32 sp3C;
    s32 sp38;
    u16 temp_t3;
    u16 var_v1;
    u8 temp_v0;
    void *temp_s0;

    temp_s0 = D_801FC604_5B8514;
    temp_v0 = CAMERA_TARGET(temp_s0)->state_cc;
    if (((s32) temp_v0 < 2) || ((s32) temp_v0 >= 0xC) || (D_800C7AE0 & 3)) {
        CAMERA_TASK(arg0)->overlay_yaw = (u16) CAMERA_TARGET(temp_s0)->yaw;
        return;
    }
    var_v1 = CAMERA_TASK(arg0)->overlay_yaw;
    if (!(var_v1 & 0x400)) {
        temp_t3 = func_801CF564_58B474(temp_s0, CAMERA_VIEW(arg1)->pos.x, CAMERA_VIEW(arg1)->pos.y, CAMERA_VIEW(arg1)->pos.z, &sp3C, &sp38) | 0x400;
        CAMERA_TASK(arg0)->overlay_yaw = temp_t3;
        var_v1 = temp_t3 & 0xFFFF;
    }
    func_8001DB04_1E704(&CAMERA_BG(D_801FC614_5B8524)->rx, CAMERA_TARGET(temp_s0)->tracked_actor->unk_3c, 0, var_v1 & 0x3FF, 0);
    func_8001DB04_1E704(&CAMERA_BG(D_801FC60C_5B851C)->rx, CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->unk_3c, 0, CAMERA_TASK(arg0)->overlay_yaw & 0x3FF, 0);
    func_8001DB04_1E704(&CAMERA_BG(D_801FC61C_5B852C)->rx, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84, 0, CAMERA_TASK(arg0)->overlay_yaw & 0x3FF, 0);
    CAMERA_TASK(arg0)->overlay_yaw = (u16) (CAMERA_TASK(arg0)->overlay_yaw | 0x8000);
}

void func_801D90D8_594FE8() {
    s32 sp3C[8];
    s32 *sp70;
    s32 *sp68;
    s32 *sp60;
    s32 *sp58;
    s32 *sp50;
    s32 *sp48;
    s32 *sp40;
    u16 sp3A;
    u16 sp38;
    s32 sp28;
    s32 *temp_a3;
    s32 temp_t5;
    s32 temp_t9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0_2;
    s32 var_v1;
    u8 var_v0;

    sp40 = &D_8006DFF8_6EBF8;
    sp48 = &D_8006E000;
    sp50 = &D_8006E008;
    sp58 = &D_8006E010;
    sp60 = &D_8006E018;
    sp68 = &D_8006E020_6EC20;
    sp70 = &D_8006E028;
    if (CAMERA_TASK(D_801FC624_5B8534)->scripted_mode != 0) {
        var_v0 = CAMERA_TARGET(D_801FC604_5B8514)->mode_60;
        if ((var_v0 == 0) && (CAMERA_TARGET(D_801FC604_5B8514)->tracked_actor->flag_86 != 0)) {
            var_v0 = 4;
        }
        D_8020D200_5C9110 = CAMERA_BG(D_801FC60C_5B851C)->header.pri;
        memcpy(D_801FC634_5B8544, D_801FC60C_5B851C, 0x90);
        CAMERA_BG(D_801FC634_5B8544)->unk_90 = (s32) CAMERA_BG(D_801FC60C_5B851C)->unk_90;
        var_a0 = var_v0 * 4;
        CAMERA_BG(D_801FC634_5B8544)->prev = CAMERA_BG(D_801FC60C_5B851C)->prev;
        CAMERA_BG(D_801FC634_5B8544)->header.next = 0;
        if (var_v0 != 4) {
            var_a0 = var_v0 * 4;
            CAMERA_BG(D_801FC634_5B8544)->AModel = (s32) (CAMERA_OVERLAY_MODELS[var_a0] + 0x10000000);
        } else {
            CAMERA_BG(D_801FC634_5B8544)->AModel = (s32) (CAMERA_OVERLAY_MODELS[var_a0] + 0x40000000);
        }
        temp_a3 = CAMERA_OVERLAY_GLISTS[var_a0];
        var_v0_2 = 0;
        var_v1 = 0;
        temp_t9 = *temp_a3;
        var_a0_2 = temp_t9;
        if (temp_t9 != 0) {
            do {
                temp_t5 = (var_v1 + 1) & 0xFF;
                (&sp3C[0])[var_v0_2] = var_a0_2;
                var_a0_2 = *(temp_a3 + (temp_t5 * 4));
                var_v0_2 = (var_v0_2 + 2) & 0xFF;
                var_v1 = temp_t5;
            } while (var_a0_2 != 0);
        }
        (&sp3C[0])[var_v0_2] = 0;
        sp28 = (s32) var_v0;
        func_8001B918_1C518(D_801FC634_5B8544, D_801FC60C_5B851C, *temp_a3, temp_a3);
        func_8001C3E0_1CFE0(D_801FC60C_5B851C, CAMERA_BG(D_801FC60C_5B851C)->AModel, &sp3C[0]);
        CAMERA_TASK(D_801FC624_5B8534)->overlay_frame = (s8) (sp28 + 1);
        sp3A = 0;
        sp38 = 0;
        if (CAMERA_TASK(D_801FC624_5B8534)->overlay_state == 1) {
            func_801D9480_595390(&sp3A, &sp38);
        }
        func_801D96E4_5955F4(sp3A, sp38);
        func_801D978C_59569C(CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_x, CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_y);
        CAMERA_OVERLAY(D_801FC62C_5B853C)->visible = (u8) CAMERA_BG(D_801FC628_5B8538)->unk_64;
        CAMERA_OVERLAY(D_801FC62C_5B853C)->header.pri = 8;
        CAMERA_OVERLAY(D_801FC62C_5B853C)->init_glist = (s32) ((s32) &D_8006E0F0 | 0x20000000 | 0x10000000);
        CAMERA_FB_INIT->mode = (s32) (((D_8015C5C8_15D1C8->frame_buffer_bits_per_pixel & 3) << 0x13) | 0xFF000000 | 0x13F);
        CAMERA_FB_INIT->frame_buffer = (void *) ((D_8015C5C8_15D1C8->current_frame_buffer * 0x25800) + 0x80000000 + (s32) &D_80261000);
        osWritebackDCache(&D_8006E0F8, 8);
        memcpy(&D_8020CC50_5C8B60, &D_8020CBF0_5C8B00, 0x60);
        if (CAMERA_VIEW(&D_8020CC50_5C8B60)->near_clip > 15.0f) {
            CAMERA_VIEW(&D_8020CC50_5C8B60)->near_clip = 15.0f;
            CAMERA_VIEW(&D_8020CC50_5C8B60)->far_clip = 2000.0f;
            CAMERA_BG(D_801FC60C_5B851C)->header.pri = 9U;
            CAMERA_BG(D_801FC634_5B8544)->header.pri = (u8) CAMERA_BG(D_801FC60C_5B851C)->header.pri;
            return;
        }
        CAMERA_OVERLAY(D_801FC62C_5B853C)->visible = 1U;
    }
}

void func_801D9480_595390(arg0, arg1)
u16 * arg0;
u16 * arg1;
{
    s32 sp50;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp48;
    f32 sp40;
    u16 sp3E;
    u8 sp39;
    s16 var_a1;
    s16 var_a1_2;
    s32 temp_t1;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_a0_3;
    u16 temp_a0_4;
    u16 temp_a1;
    u16 temp_a2;
    u16 temp_a2_2;
    CAMERA_LIMIT_ENTRY *temp_v0;
    CAMERA_LIMIT_ENTRY *temp_v0_2;

    sp39 = CAMERA_TARGET(D_801FC604_5B8514)->mode_60;
    sp54 = func_80003F30_4B30(CAMERA_TARGET(D_801FC604_5B8514)->yaw, &sp40, arg1);
    sp5C = sp40;
    sp58 = 0.0f;
    func_8001D718_1E318(&sp54, &sp48, &CAMERA_TARGET(D_801FC604_5B8514)->unk_84);
    sp3E = func_80003A94_4694(sp48, sp50);
    *arg0 = func_80003A94_4694(-CAMERA_SOLVE.camera_vec.x, -CAMERA_SOLVE.camera_vec.z) - sp3E;
    *arg1 = func_80003A94_4694(CAMERA_SOLVE.camera_vec.y, CAMERA_SOLVE.distance_target) - (CAMERA_TARGET(D_801FC604_5B8514)->pitch << 6);
    temp_a0 = *arg0;
    if ((temp_a0 + 0x4000) & 0x8000) {
        *arg0 = temp_a0 + 0x8000;
        temp_t1 = -(s32) *arg1;
        *arg1 = (u16) temp_t1;
        temp_v0 = &CAMERA_LIMIT_TABLE[sp39];
        *arg1 = temp_t1 + temp_v0->unk_06;
        temp_a1 = temp_v0->divisor;
        if ((s16) *arg1 < (s16) temp_a1) {
            *arg1 = temp_a1;
        }
        temp_a0_2 = temp_v0->unk_0a;
        if ((s16) temp_a0_2 < (s16) *arg1) {
            *arg1 = temp_a0_2;
        }
        temp_a2 = temp_v0->unk_0c;
        var_a1 = (s16) temp_a2;
        if ((s16) temp_a2 < (s16) *arg0) {
            *arg0 = temp_a2;
            var_a1 = (s16) temp_v0->unk_0c;
        }
        if ((s16) *arg0 < -var_a1) {
            *arg0 = (u16) -(s32) temp_v0->unk_0c;
        }
    } else {
        temp_v0_2 = &CAMERA_LIMIT_TABLE[sp39];
        temp_a0_3 = temp_v0_2->mode;
        if ((s16) *arg1 < (s16) temp_a0_3) {
            *arg1 = temp_a0_3;
        }
        temp_a0_4 = temp_v0_2->min_yaw;
        if ((s16) temp_a0_4 < (s16) *arg1) {
            *arg1 = temp_a0_4;
        }
        temp_a2_2 = temp_v0_2->max_yaw;
        var_a1_2 = (s16) temp_a2_2;
        if ((s16) temp_a2_2 < (s16) *arg0) {
            *arg0 = temp_a2_2;
            var_a1_2 = (s16) temp_v0_2->max_yaw;
        }
        if ((s16) *arg0 < -var_a1_2) {
            *arg0 = (u16) -(s32) temp_v0_2->max_yaw;
        }
    }
}

void func_801D96E4_5955F4(arg0, arg1)
s32 arg0;
s32 arg1;
{
    s16 var_a0;
    s16 var_a3;
    s16 var_t0;
    s16 var_t0_2;
    u16 temp_a2;

    temp_a2 = CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_x;
    var_a3 = (arg0 - temp_a2) & 0xFFFF;
    var_t0 = var_a3;
    if (var_a3 >= 0x201) {
        var_a3 = 0x200;
        var_t0 = 0x200;
    }
    if (var_t0 < -0x200) {
        var_a3 = -0x200;
    }
    var_a0 = ((arg1 & 0xFFFF) - CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_y) & 0xFFFF;
    var_t0_2 = var_a0;
    if (var_a0 >= 0x101) {
        var_a0 = 0x100;
        var_t0_2 = 0x100;
    }
    if (var_t0_2 < -0x100) {
        var_a0 = -0x100;
    }
    CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_x = (u16) (temp_a2 + var_a3);
    CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_y = (u16) (CAMERA_OVERLAY(D_801FC62C_5B853C)->rot_y + var_a0);
}

void func_801D978C_59569C(arg0, arg1)
u16 arg0;
u16 arg1;
{
    s32 unksp36;
    s32 sp80;
    s32 sp40;
    u8 sp3F;
    s32 sp34;
    s32 sp30;
    u8 temp_t6;

    func_8001E2BC_1EEBC(&sp40, D_801FC60C_5B851C);
    sp34 = (s32) arg1;
    func_8001E4A4_1F0A4(&sp80, ((s32) arg1 >> 6) & 0x3FF, ((s32) arg0 >> 6) & 0x3FF, 0);
    func_8001F2D8_1FED8(&sp40, &sp80);
    func_8001EEF4_1FAF4(0, 0, 0, &CAMERA_BG(D_801FC634_5B8544)->rx, &CAMERA_BG(D_801FC634_5B8544)->ry, &CAMERA_BG(D_801FC634_5B8544)->rz, 0, 0, 0, &sp80);
    CAMERA_BG(D_801FC634_5B8544)->unk_64 = 0;
    temp_t6 = (CAMERA_TASK(D_801FC624_5B8534)->overlay_frame - 1) & 0xFF;
    if (temp_t6 == 3) {
        if (unksp36 > 0) {
            CAMERA_BG(D_801FC634_5B8544)->time = 0.0f;
            return;
        }
        sp3F = temp_t6;
        sp30 = (s32) unksp36;
        CAMERA_BG(D_801FC634_5B8544)->time = (f32) (((f32) unksp36 / (f32) CAMERA_LIMIT_TABLE[temp_t6].divisor) * (func_8001B5AC_1C1AC(D_801FC634_5B8544, &D_801FC634_5B8544) - 1.0f));
    }
}
