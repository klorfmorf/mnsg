#ifndef SYS_H
#define SYS_H


#include "common.h"
#include "system/object.h"
#include "controller.h"
#include "stage.h"
#include "system/file_request.h"
#include "system/wave_uty.h"

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

typedef struct GraphBuf {
    /* 0x00000 */ Gfx     display_lists[10640];
    /* 0x14C80 */ Mtx     matrices[540];
    /* 0x1D380 */ Vp      viewports[4];
    /* 0x1D3C0 */ Lights7 lights[5];
    /* 0x1D618 */ LookAt  look_ats[4];
    /* 0x1D698 */ Hilite  hilites[4];
} GraphBuf; // size = 0x1D6D8

typedef struct TextLabel {
    /* 0x00 */ unsigned char  type;
    /* 0x01 */ unsigned char  unk_1;
    /* 0x02 */ short          x;
    /* 0x04 */ short          y;
    /* 0x06 */ unsigned char  unk_6;
    /* 0x07 */ unsigned char  unk_7;
    /* 0x08 */ unsigned char *string;
    /* 0x0C */ unsigned int   number;
} TextLabel; // size = 0x10

typedef struct Sys {
    /* 0x00000 */ GraphBuf       graphics_buffer[2];
    /* 0x3ADB0 */ short          current_frame_buffer;
    /* 0x3ADB2 */ short          current_graphics_pool;
    /* 0x3ADB4 */ short          file_loader_working_graphics_pool;
    /* 0x3ADB6 */ short          disable_graphics_tasks;
    /* 0x3ADB8 */ unsigned short frames_elapsed;
    /* 0x3ADBA */ unsigned short fill_color_red;
    /* 0x3ADBC */ unsigned short fill_color_green;
    /* 0x3ADBE */ unsigned short fill_color_blue;
    /* 0x3ADC0 */ unsigned short fill_color_alpha;
    /* 0x3ADC2 */ unsigned short frame_buffer_bits_per_pixel;
    /* 0x3ADC4 */ short          clear_depth_buffer;
    /* 0x3ADC6 */ unsigned char  unk_3adc6[2];
    /* 0x3ADC8 */ short          dont_process_draw_lists;
    /* 0x3ADCA */ unsigned char  retraces_per_game_step;
    /* 0x3ADCB */ unsigned char  unk_3adcb;
    /* 0x3ADCC */ unsigned short retrace_count;
    /* 0x3ADCE */ unsigned short game_loops_count;
    /* 0x3ADD0 */ unsigned short attrack_demo_frames_elapsed;
    /* 0x3ADD2 */ unsigned short mode_frame_count;
    /* 0x3ADD4 */ unsigned char  stepw;
    /* 0x3ADD5 */ unsigned char  stepw_end;
    /* 0x3ADD6 */ unsigned char  step_sub;
    /* 0x3ADD7 */ unsigned char  step_sub_end;
    /* 0x3ADD8 */ unsigned char  step_sub2;
    /* 0x3ADD9 */ unsigned char  step_sub2_end;
    /* 0x3ADDA */ unsigned char  demo_state;
    /* 0x3ADDB */ unsigned char  unk_3addb;
    /* 0x3ADDC */ unsigned char  unk_3addc;
    /* 0x3ADDD */ unsigned char  unk_3addd;
    /* 0x3ADDE */ unsigned char  mode;
    /* 0x3ADDF */ unsigned char  mode_end;
    /* 0x3ADE0 */ unsigned char  pause_state;
    /* 0x3ADE1 */ unsigned char  pause_close_state;
    /* 0x3ADE2 */ unsigned char  unk_3ade2;
    /* 0x3ADE3 */ unsigned char  unk_3ade3;
    /* 0x3ADE4 */ unsigned char  intended_room_group;
    /* 0x3ADE5 */ unsigned char  unk_3ade5;
    /* 0x3ADE6 */ unsigned short map_area_index;
    /* 0x3ADE8 */ unsigned int   map_area;
    /* 0x3ADEC */ unsigned short map_floor;
    /* 0x3ADEE */ unsigned short map_cell;
    /* 0x3ADF0 */ unsigned short map_floor_split;
    /* 0x3ADF2 */ unsigned short intended_room_id;
    /* 0x3ADF4 */ unsigned short intended_room_group_index;
    /* 0x3ADF6 */ unsigned char  current_room_group;
    /* 0x3ADF7 */ unsigned char  unk_3adf7;
    /* 0x3ADF8 */ unsigned short current_room_group_index;
    /* 0x3ADFA */ unsigned char  prev_room_group;
    /* 0x3ADFB */ unsigned char  unk_3adfb;
    /* 0x3ADFC */ unsigned short prev_room_id;
    /* 0x3ADFE */ unsigned short prev_room_group_index;
    /* 0x3AE00 */ unsigned short unk_3ae00;
    /* 0x3AE02 */ unsigned char  room_exit_sound_count;
    /* 0x3AE03 */ unsigned char  unk_3ae03;
    /* 0x3AE04 */ unsigned int   bgm;
    /* 0x3AE08 */ unsigned int   prev_bgm;
    /* 0x3AE0C */ unsigned char  enter_voice_pending;
    /* 0x3AE0D */ unsigned char  unk_3ae0d;
    /* 0x3AE0E */ unsigned char  unk_3ae0e;
    /* 0x3AE0F */ unsigned char  unk_3ae0f;
    /* 0x3AE10 */ unsigned char  unk_3ae10;
    /* 0x3AE11 */ unsigned char  unk_3ae11;
    /* 0x3AE12 */ unsigned char  unk_3ae12;
    /* 0x3AE13 */ unsigned char  unk_3ae13;
    /* 0x3AE14 */ unsigned short is_controller_pak_connected;
    /* 0x3AE16 */ unsigned short demo_mode;
    /* 0x3AE18 */ unsigned short demo_no;
    /* 0x3AE1A */ unsigned char  unk_3ae1a;
    /* 0x3AE1B */ unsigned char  unk_3ae1b;
    /* 0x3AE1C */ float         *skybox_fallback_view;
    /* 0x3AE20 */ unsigned char  unk_3ae20;
    /* 0x3AE21 */ unsigned char  unk_3ae21;
    /* 0x3AE22 */ unsigned char  unk_3ae22;
    /* 0x3AE23 */ unsigned char  player_input_locked;
    /* 0x3AE24 */ unsigned short task_disabled_status;
    /* 0x3AE26 */ unsigned short paused;
    /* 0x3AE28 */ unsigned char  unk_3ae28;
    /* 0x3AE29 */ unsigned char  room_change_flags;
    /* 0x3AE2A */ unsigned char  unk_3ae2a;
    /* 0x3AE2B */ unsigned char  unk_3ae2b;
    /* 0x3AE2C */ unsigned int   room_change_cam_distance;
    /* 0x3AE30 */ unsigned short room_change_cam_yaw_step;
    /* 0x3AE32 */ unsigned char  unk_3ae32;
    /* 0x3AE33 */ unsigned char  unk_3ae33;
    /* 0x3AE34 */ unsigned char  unk_3ae34;
    /* 0x3AE35 */ unsigned char  unk_3ae35;
    /* 0x3AE36 */ unsigned char  unk_3ae36;
    /* 0x3AE37 */ unsigned char  unk_3ae37;
    /* 0x3AE38 */ unsigned char  no_enter_walk;
    /* 0x3AE39 */ unsigned char  unk_3ae39;
    /* 0x3AE3A */ unsigned short demo_wave;
    /* 0x3AE3C */ unsigned int   demo_offset;
    /* 0x3AE40 */ unsigned short camera_type;
    /* 0x3AE42 */ unsigned char  unk_3ae42;
    /* 0x3AE43 */ unsigned char  unk_3ae43;
    /* 0x3AE44 */ unsigned int   camera_rail_x;
    /* 0x3AE48 */ unsigned int   camera_rail_y;
    /* 0x3AE4C */ unsigned int   camera_rail_z;
    /* 0x3AE50 */ CameraRegion   camera_regions[10];
    /* 0x3AFE0 */ unsigned short next_room_id;
    /* 0x3AFE2 */ RoomEntry      next_entry;
    /* 0x3AFEC */ RoomEntry      entry;
    /* 0x3AFF6 */ RoomEntry      prev_entry;
    /* 0x3B000 */ unsigned int   unk_3b000;
    /* 0x3B004 */ unsigned int   unk_3b004;
    /* 0x3B008 */ unsigned int   unk_3b008;
    /* 0x3B00C */ unsigned char  unk_3b00c[4];
    /* 0x3B010 */ unsigned char  room_player_idle_type;
    /* 0x3B011 */ unsigned char  unk_3b011;
    /* 0x3B012 */ unsigned char  unk_3b012;
    /* 0x3B013 */ unsigned char  unk_3b013;
    /* 0x3B014 */ ObjSprite     *fade;
    /* 0x3B018 */ unsigned int   unk_3b018;
    /* 0x3B01C */ unsigned char  unk_3b01c;
    /* 0x3B01D */ unsigned char  wait_frames;
    /* 0x3B01E */ unsigned short room_wave_base;
    /* 0x3B020 */ short          room_wave_end;
    /* 0x3B022 */ unsigned short room_wave_list[6];
    /* 0x3B02E */ unsigned char  temp_wave_slot;
    /* 0x3B02F */ unsigned char  unk_3b02f;
    /* 0x3B030 */ unsigned int   temp_wave_slot_addr;
    /* 0x3B034 */ unsigned int   pause_wave_clobber_end;
    /* 0x3B038 */ unsigned char  pause_wave_reload_index;
    /* 0x3B039 */ unsigned char  unk_3b039;
    /* 0x3B03A */ unsigned char  unk_3b03a;
    /* 0x3B03B */ unsigned char  unk_3b03b;
    /* 0x3B03C */ void          *load_files_function;
    /* 0x3B040 */ unsigned int   unk_3b040;
    /* 0x3B044 */ unsigned char  unk_3b044[4];
    /* 0x3B048 */ unsigned int   unk_3b048;
    /* 0x3B04C */ unsigned char  unk_3b04c[4];
    /* 0x3B050 */ unsigned char  unk_3b050[4];
    /* 0x3B054 */ unsigned int   unk_3b054;
    /* 0x3B058 */ unsigned char  unk_3b058[28];
    /* 0x3B074 */ unsigned char  file_requests_count;
    /* 0x3B075 */ unsigned char  unk_3b075;
    /* 0x3B076 */ unsigned char  unk_3b076;
    /* 0x3B077 */ unsigned char  unk_3b077;
    /* 0x3B078 */ Controller     controller[5];
    /* 0x3B0F0 */ Controller     player_controller[5];
    /* 0x3B168 */ TextLabel      text_label[80];
    /* 0x3B668 */ ObjMoji        unknown_heap[2];
    /* 0x3BB08 */ unsigned char  unknown_data[524288];
    /* 0xBBB08 */ ObjGbg         skybox_heap[2];
    /* 0xBBB90 */ ObjSolid       solids[192];
    /* 0xC2D90 */ unsigned short unk_c2d90;
    /* 0xC2D92 */ unsigned char  unk_c2d92;
    /* 0xC2D93 */ unsigned char  unk_c2d93;
    /* 0xC2D94 */ ObjSprite      sprite_heap[24];
    /* 0xC3394 */ ObjLayer       draw_lists[12];
    /* 0xC5D04 */ unsigned char  stop_processing_draw_lists;
    /* 0xC5D05 */ unsigned char  unk_c5d05;
    /* 0xC5D06 */ short          unk_c5d06;
    /* 0xC5D08 */ short          unk_c5d08;
    /* 0xC5D0A */ short          unk_c5d0a;
    /* 0xC5D0C */ short          unk_c5d0c;
    /* 0xC5D0E */ unsigned char  unk_c5d0e;
    /* 0xC5D0F */ unsigned char  unk_c5d0f;
    /* 0xC5D10 */ union { ObjSpriteFlags unk_c5d10; unsigned int unk_c5d10_word; };
    /* 0xC5D14 */ unsigned char  unk_c5d14[4];
    /* 0xC5D18 */ short          unknown_rgba16_buffer[256];
    /* 0xC5F18 */ unsigned short unk_c5f18[16];
    /* 0xC5F38 */ unsigned int   unk_c5f38[16];
    /* 0xC5F78 */ void          *sprite_tex_table;
    /* 0xC5F7C */ unsigned int   unk_c5f7c;
    /* 0xC5F80 */ WaveReq       *file_requests_table[8];
    /* 0xC5FA0 */ unsigned char  decompression_buffer[8192];
    /* 0xC7FA0 */ unsigned char  wave_load_state;
    /* 0xC7FA1 */ unsigned char  unk_c7fa1;
    /* 0xC7FA2 */ unsigned char  unk_c7fa2;
    /* 0xC7FA3 */ unsigned char  unk_c7fa3;
    /* 0xC7FA4 */ AmemBlock      memory_blocks[1920];
    /* 0xCF7A4 */ unsigned char  unk_cf7a4[12];
    /* 0xCF7B0 */ int           *unk_cf7b0;
    /* 0xCF7B4 */ unsigned char  unk_cf7b4[88];
    /* 0xCF80C */ unsigned int   tlb_physical_addresses[32];
    /* 0xCF88C */ unsigned char  player_exists;
    /* 0xCF88D */ unsigned char  player_dead;
    /* 0xCF88E */ unsigned short unk_cf88e;
    /* 0xCF890 */ short          kill_plane_y;
    /* 0xCF892 */ unsigned char  unk_cf892;
    /* 0xCF893 */ unsigned char  unk_cf893;
    /* 0xCF894 */ unsigned int   unk_cf894;
    /* 0xCF898 */ unsigned char  unk_cf898;
    /* 0xCF899 */ unsigned char  unk_cf899;
    /* 0xCF89A */ unsigned char  unk_cf89a;
    /* 0xCF89B */ unsigned char  unk_cf89b;
    /* 0xCF89C */ unsigned int   unk_cf89c;
    /* 0xCF8A0 */ unsigned char  unk_cf8a0;
    /* 0xCF8A1 */ unsigned char  pause_show_map;
    /* 0xCF8A2 */ unsigned char  pause_disabled;
    /* 0xCF8A3 */ unsigned char  unk_cf8a3;
    /* 0xCF8A4 */ unsigned char  unk_cf8a4[12];
    /* 0xCF8B0 */ unsigned int   unk_cf8b0;
    /* 0xCF8B4 */ unsigned char  unk_cf8b4;
    /* 0xCF8B5 */ unsigned char  unk_cf8b5;
    /* 0xCF8B6 */ unsigned char  unk_cf8b6;
    /* 0xCF8B7 */ unsigned char  unk_cf8b7;
    /* 0xCF8B8 */ void          *menu_root_task;
    /* 0xCF8BC */ void          *menu_map_task;
    /* 0xCF8C0 */ void          *menu_solid_pool_task;
    /* 0xCF8C4 */ void          *unk_cf8c4;
    /* 0xCF8C8 */ void          *unk_cf8c8;
    /* 0xCF8CC */ void          *unk_cf8cc;
    /* 0xCF8D0 */ void          *unk_cf8d0;
    /* 0xCF8D4 */ void          *unk_cf8d4;
    /* 0xCF8D8 */ void          *player_manager_task;
    /* 0xCF8DC */ void          *dummy_task;
    /* 0xCF8E0 */ void          *actor_manager_task;
    /* 0xCF8E4 */ void          *skybox_manager_task;
    /* 0xCF8E8 */ void          *room_lighting_task;
    /* 0xCF8EC */ void          *unk_cf8ec;
    /* 0xCF8F0 */ void          *hud_graphics_task;
    /* 0xCF8F4 */ void          *room_graphics_task;
    /* 0xCF8F8 */ void          *unk_cf8f8;
    /* 0xCF8FC */ unsigned int   unk_cf8fc;
    /* 0xCF900 */ unsigned int   unk_cf900;
    /* 0xCF904 */ unsigned int   unk_cf904;
} Sys; // size = 0xCF908

void func_80004170(void);
void func_80004208(void *src, void *dst, int size);

extern Sys            g_sys_real;
extern Sys           *g_sys;
extern unsigned short g_frame_buffers[3][320 * 240];
extern char           D_2D1800[];
extern char           D_301000[];

#endif // SYS_H
