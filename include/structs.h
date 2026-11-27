#ifndef STRUCTS_H
#define STRUCTS_H

#include "common.h"
#include "macros.h"
#include "enums.h"

// ===== wave_uty =====
typedef struct Wave {
    /* 0x00 */ unsigned short wave_no;
    /* 0x04 */ int            data;
} Wave; // size = 0x8

typedef struct WaveResource {
    /* 0x00 */ unsigned int file_id;
    /* 0x04 */ unsigned int dest_addr;
} WaveResource; // size = 0x8

// ===== amem =====
typedef struct AmemBlock {
    /* 0x00 */ char             *pt;
    /* 0x04 */ unsigned int      size;
    /* 0x08 */ struct AmemBlock *next;
    /* 0x0C */ struct AmemBlock *up;
} AmemBlock; // size = 0x10

// ===== obj =====
typedef struct Obj {
    /* 0x00 */ struct Obj    *next;
    /* 0x04 */ unsigned char  kind;
    /* 0x05 */ unsigned char  pri;
    /* 0x06 */ unsigned short s_pri;
} Obj; // size = 0x8

typedef struct ObjSpriteFlags {
    unsigned int mode : 3;
    unsigned int dither_alpha : 1;
    unsigned int modulate_color : 1;
    unsigned int scaled : 1;
    unsigned int override_mode : 1;
    unsigned int wrap_s : 3;
    unsigned int wrap_t : 3;
    unsigned int tex_width_shift : 4;
    unsigned int tex_height_shift : 4;
    unsigned int flip_x : 1;
    unsigned int flip_y : 1;
    unsigned int unk_b0 : 9;
} ObjSpriteFlags; // size = 0x4

typedef struct ObjSpritePart {
    /* 0x00 */ unsigned short flags;
    /* 0x02 */ unsigned char  width;
    /* 0x03 */ unsigned char  height;
    /* 0x04 */ short          x;
    /* 0x06 */ short          y;
    /* 0x08 */ unsigned short s;
    /* 0x0A */ unsigned short t;
} ObjSpritePart; // size = 0xC

typedef struct ObjSpriteTex {
    /* 0x00 */ unsigned short width;
    /* 0x02 */ unsigned short height;
    /* 0x04 */ unsigned char  fmt;
    /* 0x05 */ unsigned char  pal;
    /* 0x06 */ unsigned short unk_6;
    /* 0x08 */ void          *data;
    /* 0x0C */ unsigned short wave;
    /* 0x0E */ unsigned short unk_e;
} ObjSpriteTex; // size = 0x10

typedef struct ObjSprite {
    /* 0x00 */ Obj header;
    /* 0x08 */ union {
        ObjSpriteFlags flags;
        unsigned int   flags_word;
    };
    /* 0x0C */ unsigned char  palette_slot;
    /* 0x0D */ unsigned char  r;
    /* 0x0E */ unsigned char  g;
    /* 0x0F */ unsigned char  b;
    /* 0x10 */ unsigned char  a;
    /* 0x11 */ unsigned char  unk_11;
    /* 0x12 */ unsigned char  unk_12;
    /* 0x13 */ unsigned char  unk_13;
    /* 0x14 */ ObjSpriteTex  *textures;
    /* 0x18 */ unsigned short attr;
    /* 0x1A */ unsigned char  unk_1a; // Respawn delay.
    /* 0x1B */ unsigned char  unk_1b;
    /* 0x1C */ union {
        int   x_word;
        short x;
    };
    /* 0x20 */ union {
        int   y_word;
        short y;
    };
    /* 0x24 */ unsigned char   unk_24;
    /* 0x25 */ unsigned char   unk_25;
    /* 0x26 */ unsigned char   unk_26;
    /* 0x27 */ unsigned char   unk_27;
    /* 0x28 */ unsigned char   unk_28;
    /* 0x29 */ unsigned char   unk_29;
    /* 0x2A */ unsigned char   unk_2a;
    /* 0x2B */ unsigned char   unk_2b;
    /* 0x2C */ float           scale_x;
    /* 0x30 */ float           scale_y;
    /* 0x34 */ ObjSpritePart  *parts;
    /* 0x38 */ unsigned short *palette;
    /* 0x3C */ unsigned int    unk_3c;
} ObjSprite; // size = 0x40

typedef struct ObjSolid {
    /* 0x00 */ Obj              header;
    /* 0x08 */ float            tx, ty, tz;
    /* 0x14 */ unsigned short   rx, ry, rz;
    /* 0x1C */ float            sx, sy, sz;
    /* 0x28 */ float            time;
    /* 0x2C */ unsigned int     AModel;
    /* 0x30 */ unsigned int     init_glist;
    /* 0x34 */ Wave             SegWave[6];
    /* 0x64 */ unsigned char    hidden;
    /* 0x65 */ signed char      disabled;
    /* 0x68 */ float            scratch_f[2];
    /* 0x70 */ float            blend;
    /* 0x74 */ struct ObjSolid *sibling;
    /* 0x78 */ struct ObjSolid *child;
    /* 0x7C */ unsigned char    param;
    /* 0x7E */ unsigned short   param_fx8;
    /* 0x80 */ union {
        unsigned char work[20];
        float         work_f[5];
        unsigned int  work_w[5];
        int           work_i[5];
        struct {
            int x;
            int y;
        } work_pos;
    };
    /* 0x94 */ union {
        struct ObjSolid *parent;
        float            frame_count;
    };
} ObjSolid; // size = 0x98

typedef struct ObjMoji {
    /* 0x000 */ Obj header;
    /* 0x008 */ int unk_8;
    /* 0x00C */ union {
        int   scroll_x_word;
        short scroll_x;
    };
    /* 0x010 */ union {
        int   scroll_y_word;
        short scroll_y;
    };
    /* 0x014 */ int             unk_14;
    /* 0x018 */ int             unk_18;
    /* 0x01C */ short           width;
    /* 0x01E */ short           height;
    /* 0x020 */ short           unk_20;
    /* 0x022 */ short           unk_22;
    /* 0x024 */ unsigned char   unk_24;
    /* 0x025 */ unsigned char   unk_25;
    /* 0x026 */ unsigned char   unk_26;
    /* 0x027 */ unsigned char   unk_27;
    /* 0x028 */ unsigned short *palette_src;
    /* 0x02C */ unsigned char   unk_2c;
    /* 0x02D */ unsigned char   unk_2d;
    /* 0x02E */ unsigned char   unk_2e;
    /* 0x02F */ unsigned char   unk_2f;
    /* 0x030 */ unsigned char   unk_30;
    /* 0x031 */ unsigned char   unk_31;
    /* 0x032 */ short           unk_32;
    /* 0x034 */ unsigned short  clip_x0;
    /* 0x036 */ unsigned short  clip_y0;
    /* 0x038 */ unsigned short  clip_x1;
    /* 0x03A */ unsigned short  clip_y1;
    /* 0x03C */ short           r;
    /* 0x03E */ short           g;
    /* 0x040 */ short           b;
    /* 0x042 */ short           a;
    /* 0x044 */ short           unk_44;
    /* 0x046 */ short           unk_46;
    /* 0x048 */ short           unk_48;
    /* 0x04A */ short           unk_4a;
    /* 0x04C */ unsigned char   unk_4c;
    /* 0x04D */ unsigned char   unk_4d;
    /* 0x04E */ unsigned char   unk_4e;
    /* 0x04F */ unsigned char   unk_4f;
    /* 0x050 */ unsigned short  palette[256];
} ObjMoji; // size = 0x250

typedef struct ObjGbg {
    /* 0x00 */ Obj            header;
    /* 0x08 */ int            unk_8;
    /* 0x0C */ unsigned short wave_no;
    /* 0x0E */ unsigned short flags;
    /* 0x10 */ short          texture_width, texture_height;
    /* 0x14 */ float          u, v;
    /* 0x1C */ float          x, y;
    /* 0x24 */ float          w, h;
    /* 0x2C */ unsigned char  alpha;
    /* 0x2E */ short          min_x, min_y;
    /* 0x32 */ short          max_x, max_y;
    /* 0x38 */ unsigned char *texture_data;
    /* 0x3C */ unsigned char *palette_data;
    /* 0x40 */ unsigned short bits_per_pixel;
} ObjGbg; // size = 0x44

typedef struct ObjLayer {
    /* 0x000 */ Obj          *objects[220];
    /* 0x370 */ unsigned char size;
    /* 0x371 */ unsigned char sort_flags;
} ObjLayer; // size = 0x374

// ===== anime =====
typedef struct AnimeCamera {
    /* 0x00 */ float          eye[3];
    /* 0x0C */ float          at[3];
    /* 0x18 */ unsigned short roll;
    /* 0x1A */ unsigned short fovy;
    /* 0x1C */ float          near;
    /* 0x20 */ float          far;
    /* 0x24 */ float          light[6];
    /* 0x3C */ unsigned char  tex_w;
    /* 0x3D */ unsigned char  tex_h;
    /* 0x3E */ unsigned char  flags;
    /* 0x3F */ unsigned char  unk_3f;
    /* 0x40 */ Vp            *vp;
    /* 0x44 */ int            clip;
    /* 0x48 */ short          scissor0;
    /* 0x4A */ short          scissor1;
    /* 0x4C */ short          scissor2;
    /* 0x4E */ short          scissor3;
    /* 0x50 */ float          left;
    /* 0x54 */ float          top;
    /* 0x58 */ float          right;
    /* 0x5C */ float          bottom;
} AnimeCamera; // size = 0x60

typedef struct AnimeCameraKeys {
    /* 0x00 */ unsigned short eye[3];
    /* 0x06 */ unsigned short at[3];
    /* 0x0C */ unsigned short roll;
    /* 0x0E */ unsigned short fovy;
    /* 0x10 */ unsigned short near;
    /* 0x12 */ unsigned short far;
} AnimeCameraKeys; // size = 0x14

typedef struct AnimeAmbient {
    /* 0x00 */ unsigned char col[3];
    /* 0x03 */ unsigned char keep;
} AnimeAmbient; // size = 0x4

typedef struct AnimeLight {
    /* 0x00 */ signed char   dir[3];
    /* 0x03 */ unsigned char col[3];
} AnimeLight; // size = 0x6

typedef struct AnimeLightKeys {
    /* 0x00 */ unsigned short dir[3];
    /* 0x06 */ unsigned short col[3];
} AnimeLightKeys; // size = 0xC

typedef struct AnimeJoint {
    /* 0x00 */ unsigned int   model;
    /* 0x04 */ signed char    child;
    /* 0x05 */ signed char    sibling;
    /* 0x06 */ unsigned short sx, sy, sz;
    /* 0x0C */ unsigned short rx, ry, rz;
    /* 0x12 */ unsigned short tx, ty, tz;
} AnimeJoint; // size = 0x18

typedef struct AnimeMtx {
    /* 0x00 */ float m[4][4];
} AnimeMtx; // size = 0x40

// ===== controller_pak =====
// Header data read from a Controller Pak block.
typedef struct ContPakHeader {
    unsigned int word[3];
} ContPakHeader; // size = 0xC

// Padded 256-byte Controller Pak header block.
typedef struct PakHeaderBlock {
    /* 0x00 */ unsigned int  checksum;
    /* 0x04 */ ContPakHeader header;
    /* 0x10 */ unsigned char pad10[0xF0];
} PakHeaderBlock; // size = 0x100

// Active Controller Pak file system and save buffer state.
typedef struct MemPak {
    /* 0x000 */ OSPfs          pfs;
    /* 0x068 */ unsigned char  unk_68[0x148];
    /* 0x1B0 */ OSPfsState     files[16];
    /* 0x3B0 */ unsigned char  file_errors[0x40];
    /* 0x3F0 */ s32            file_no;
    /* 0x3F4 */ unsigned char *buffer;
    /* 0x3F8 */ unsigned char  no_pak;
    /* 0x3F9 */ unsigned char  pad_3F9[0x3];
    /* 0x3FC */ int            error;
    /* 0x400 */ s32            max_files;
    /* 0x404 */ s32            used_files;
    /* 0x408 */ int            free_blocks;
} MemPak; // size = 0x40C

// ===== is_debug =====
typedef struct IsDebug {
    /* 0x0000 */ unsigned int  magic;
    /* 0x0004 */ unsigned int  get;
    /* 0x0008 */ unsigned char unk_08[12];
    /* 0x0014 */ unsigned int  put;
    /* 0x0018 */ unsigned char unk_18[8];
    /* 0x0020 */ unsigned char data[0xFFE0];
} IsDebug; // size = 0x10000

// ===== sched =====
typedef struct {
    /* 0x00 */ short type;
    /* 0x02 */ char  misc[30];
} OSScMsg; // size = 0x20

typedef struct OSScTask_s {
    /* 0x00 */ struct OSScTask_s *next; // Must be the first field.
    /* 0x04 */ unsigned int       state;
    /* 0x08 */ unsigned int       flags;
    /* 0x0C */ void              *frame_buffer; // Target frame buffer for graphics tasks.
    /* 0x10 */ OSTask             list;
    /* 0x50 */ OSMesgQueue       *msgQ;
    /* 0x54 */ OSMesg             msg;
    /* 0x58 */ OSTime             startTime;
    /* 0x60 */ OSTime             totalTime;
} OSScTask; // size = 0x68

// Client list node used to receive scheduler messages.
typedef struct SCClient_s {
    /* 0x00 */ struct SCClient_s *next; // Next client in the list.
    /* 0x04 */ OSMesgQueue       *msgQ; // Message queue for scheduler notifications.
} OSScClient;                           // size = 0x8

typedef struct {
    /* 0x000 */ OSScMsg      retraceMsg;
    /* 0x020 */ OSScMsg      prenmiMsg;
    /* 0x040 */ OSMesgQueue  interruptQ;
    /* 0x058 */ OSMesg       intBuf[OS_SC_MAX_MESGS];
    /* 0x078 */ OSMesgQueue  cmdQ;
    /* 0x090 */ OSMesg       cmdMsgBuf[OS_SC_MAX_MESGS];
    /* 0x0B0 */ OSMesgQueue  unknownQ;
    /* 0x0C8 */ OSMesg       unknownBuf[OS_SC_MAX_MESGS];
    /* 0x0E8 */ OSThread     thread;
    /* 0x298 */ OSScClient  *clientList;
    /* 0x29C */ OSScTask    *audioListHead;
    /* 0x2A0 */ OSScTask    *gfxListHead;
    /* 0x2A4 */ OSScTask    *audioListTail;
    /* 0x2A8 */ OSScTask    *gfxListTail;
    /* 0x2AC */ OSScTask    *curRSPTask;
    /* 0x2B0 */ OSScTask    *curRDPTask;
    /* 0x2B4 */ unsigned int frameCount;
    /* 0x2B8 */ int          doAudio;
} OSSched; // size = 0x2C0

// ===== pic =====
typedef struct Pic {
    /* 0x00 */ int             width;
    /* 0x04 */ int             height;
    /* 0x08 */ int             bits;
    /* 0x0C */ int             size;
    /* 0x10 */ int             type;
    /* 0x14 */ int             transparent;
    /* 0x18 */ unsigned char  *data;
    /* 0x1C */ void           *image;
    /* 0x20 */ unsigned short *palette;
} Pic; // size = 0x24

typedef struct ColorCacheEntry {
    /* 0x00 */ short color;
    /* 0x02 */ short next;
    /* 0x04 */ short prev;
} ColorCacheEntry; // size = 0x6

// ===== rom_queue =====
typedef struct WaveReq {
    /* 0x00 */ int            wave_no;
    /* 0x04 */ unsigned char *data;
} WaveReq; // size = 0x8

// ===== rom_trans =====
typedef struct LoadRomTable {
    /* 0x0000 */ char         name[16];
    /* 0x0010 */ unsigned int offsets[LOAD_FILE_MAX];
} LoadRomTable; // size = 0x1490

// ===== step =====
typedef struct GameStepTable {
    /* 0x00 */ void (*funcs[18])(void);
} GameStepTable; // size = 0x48

// ===== task =====
typedef struct Task {
    /* 0x00 */ struct Task *next;
    /* 0x04 */ struct Task *prev;
    /* 0x08 */ void (*exec[3])(struct Task *, struct Obj *);
    /* 0x14 */ void (*prev_exec)(struct Task *, struct Obj *);
    /* 0x18 */ Obj           *obj_head;
    /* 0x1C */ Obj           *obj_tail;
    /* 0x20 */ unsigned short priority;
    /* 0x22 */ unsigned short status;
    /* 0x24 */ short          timer;
    /* 0x28 */ Wave           wave;
    /* 0x30 */ unsigned char  hit_flags;
    /* 0x31 */ unsigned char  pad_31;
    /* 0x32 */ unsigned char  pad_32;
    /* 0x33 */ unsigned char  pad_33;
    /* 0x34 */ struct Task   *hit;
    /* 0x38 */ struct Task   *hit_by;
    /* 0x3C */ unsigned short width;
    /* 0x3E */ unsigned short height;
    /* 0x40 */ short          offset_y;
    /* 0x42 */ short          offset_z;
    /* 0x44 */ unsigned char  hit_index;
    /* 0x45 */ unsigned char  pad_45;
    /* 0x46 */ unsigned char  pad_46;
    /* 0x47 */ unsigned char  pad_47;
    /* 0x48 */ unsigned int   hit_ref;
    /* 0x4C */ unsigned char  hit_kind;
    /* 0x4D */ unsigned char  pad_4d;
    /* 0x4E */ unsigned short attack_radius;
    /* 0x50 */ short          attack_offset_y;
    /* 0x52 */ short          attack_offset_z;
    /* 0x54 */ float         *contact;
    /* 0x58 */ unsigned int   anim_events;
    /* 0x5C */ unsigned int   work[0x25]; // Task-specific work area; see the *_WORK macros.
} Task;                                   // size = 0xF0

typedef struct TaskList {
    /* 0x00 */ Task          *head;
    /* 0x04 */ Task          *tail;
    /* 0x08 */ Task          *free;
    /* 0x0C */ unsigned short count;
    /* 0x10 */ void          *unk_10;
} TaskList; // size = 0x14

// ===== vram =====
typedef struct ColPlane {
    /* 0x00 */ float         normal_x;
    /* 0x04 */ float         normal_y;
    /* 0x08 */ float         normal_z;
    /* 0x0C */ float         distance;
    /* 0x10 */ unsigned char type;
} ColPlane; // size = 0x14

typedef struct ColTree {
    /* 0x00 */ unsigned short next_tree;
    /* 0x02 */ short          type;
    /* 0x04 */ short          scale;
    /* 0x06 */ short          box_max_x;
    /* 0x08 */ short          box_max_y;
    /* 0x0A */ short          box_max_z;
    /* 0x0C */ short          box_min_x;
    /* 0x0E */ short          box_min_y;
    /* 0x10 */ short          box_min_z;
} ColTree; // size = 0x12

// Collision BSP node or bounding-box record (links, max corner, and min corner).
typedef struct ColNode {
    /* 0x00 */ union {
        unsigned short index; // Next box index, or plane index for a tree node.
        short          x;
    };
    /* 0x02 */ union {
        short y;
        short group;
        short back; // Child node behind the plane.
    };
    /* 0x04 */ union {
        short z;
        short front; // Child node in front of the plane.
    };
} ColNode; // size = 0x6

typedef struct ColHead {
    /* 0x00 */ short unk_0;
    /* 0x02 */ short unk_2;
    /* 0x04 */ short range;
} ColHead; // size = 0x6

typedef struct ColEntry {
    /* 0x00 */ ColHead *nodes;
    /* 0x04 */ void    *planes;
} ColEntry; // size = 0x8

typedef struct ColFile {
    /* 0x00 */ unsigned short *wave_no;
    /* 0x04 */ int             unk_4;
    /* 0x08 */ int             unk_8;
    /* 0x0C */ ColEntry       *entries;
} ColFile; // size = 0x10

typedef struct ColHit {
    /* 0x00 */ float       x;
    /* 0x04 */ float       y;
    /* 0x08 */ float       z;
    /* 0x0C */ float       move_x;
    /* 0x10 */ float       move_y;
    /* 0x14 */ float       move_z;
    /* 0x18 */ float       hit_x;
    /* 0x1C */ float       hit_y;
    /* 0x20 */ float       hit_z;
    /* 0x24 */ float       normal_x;
    /* 0x28 */ float       normal_y;
    /* 0x2C */ float       normal_z;
    /* 0x30 */ float       plane_distance;
    /* 0x34 */ signed char plane_type;
    /* 0x36 */ short       group;
    /* 0x38 */ short       result;
    /* 0x3C */ float       dist_sq;
    /* 0x40 */ ObjSolid   *solid;
    /* 0x44 */ Task       *obj;
} ColHit; // size = 0x48

// ===== solid_atari =====
// Animation track indices defining a collision shape's size and offset.
typedef struct ColShape {
    /* 0x00 */ unsigned short size;
    /* 0x02 */ unsigned short x, y, z;
} ColShape; // size = 0x8

// ===== yamamoto =====
typedef struct SpriteList {
    /* 0x00 */ short          in_use;
    /* 0x02 */ short          count;
    /* 0x04 */ short          max;
    /* 0x06 */ short          unk_06;
    /* 0x08 */ ObjSpritePart *parts;
} SpriteList; // size = 0xC

typedef struct SpriteOwner {
    /* 0x00 */ unsigned char pad_00[0x1C];
    /* 0x1C */ ObjSprite    *sprite;
} SpriteOwner; // size = 0x20

struct YamamotoObj;

typedef struct YamamotoSub {
    /* 0x00 */ int parent;
    /* 0x04 */ void (*destroy)(struct YamamotoObj *);
    /* 0x08 */ float          offset_x;
    /* 0x0C */ float          offset_y;
    /* 0x10 */ float          offset_z;
    /* 0x14 */ unsigned short offset_rx;
    /* 0x16 */ unsigned short offset_ry;
    /* 0x18 */ union {
        unsigned short offset_rz;
        void (*exec)(Task *, Obj *);
    };
} YamamotoSub; // size = 0x1C

typedef struct YamamotoObj {
    /* 0x00 */ struct YamamotoObj *next;
    /* 0x04 */ char                pad_04[0x1C];
    /* 0x20 */ unsigned short      priority;
    /* 0x22 */ char                pad_22[0x3A];
    /* 0x5C */ YamamotoSub         sub;
} YamamotoObj; // size = 0x78

typedef struct Link2DWork {
    /* 0x00 */ struct Link2DWork *parent;
    /* 0x04 */ void (*destroy)(Task *);
    /* 0x08 */ int offset_x;
    /* 0x0C */ int offset_y;
    /* 0x10 */ int x;
    /* 0x14 */ int y;
    /* 0x18 */ void (*exec)(Task *, Obj *);
} Link2DWork; // size = 0x1C

typedef struct Link3DWork {
    /* 0x00 */ struct Link3DWork *parent;
    /* 0x04 */ void (*destroy)(Task *);
    /* 0x08 */ float          offset_x;
    /* 0x0C */ float          offset_y;
    /* 0x10 */ float          offset_z;
    /* 0x14 */ unsigned short offset_rx;
    /* 0x16 */ unsigned short offset_ry;
    /* 0x18 */ unsigned short offset_rz;
    /* 0x1A */ unsigned char  pad_1a[2];
    /* 0x1C */ float          x;
    /* 0x20 */ float          y;
    /* 0x24 */ float          z;
    /* 0x28 */ unsigned short rx;
    /* 0x2A */ unsigned short ry;
    /* 0x2C */ unsigned short rz;
} Link3DWork; // size = 0x30

typedef struct YamamotoEntry {
    /* 0x00 */ short         width;
    /* 0x02 */ short         height;
    /* 0x04 */ unsigned char fmt;
    /* 0x05 */ unsigned char pal;
    /* 0x08 */ int           data;
    /* 0x0C */ short         wave;
} YamamotoEntry; // size = 0x10

typedef struct YamamotoFlagEntry {
    /* 0x00 */ unsigned short  flags;
    /* 0x02 */ short           unk_02;
    /* 0x04 */ short           unk_04;
    /* 0x06 */ short           unk_06;
    /* 0x08 */ unsigned short *unk_08;
} YamamotoFlagEntry; // size = 0xC

typedef struct YamamotoPos {
    /* 0x00 */ void *parent;
    /* 0x04 */ int   destroy;
    /* 0x08 */ int   x;
    /* 0x0C */ int   y;
    /* 0x10 */ int   world_x;
    /* 0x14 */ int   world_y;
    /* 0x18 */ int   exec;
} YamamotoPos; // size = 0x1C

typedef struct YamamotoWork {
    /* 0x00 */ char        pad_00[0x5C];
    /* 0x5C */ YamamotoPos pos;
} YamamotoWork; // size = 0x78

// ===== joypad =====
typedef struct Controller {
    /* 0x00 */ unsigned short status;
    /* 0x02 */ unsigned short button_held_down;
    /* 0x04 */ unsigned short button_pressed;
    /* 0x06 */ short          stick_raw_x;
    /* 0x08 */ short          stick_raw_y;
    /* 0x0C */ float          stick_magnitude;
    /* 0x10 */ float          stick_x;
    /* 0x14 */ float          stick_y;
} Controller; // size = 0x18

typedef struct DemoKey {
    /* 0x0 */ unsigned short button;
    /* 0x2 */ signed char    stick_x;
    /* 0x3 */ signed char    stick_y;
    /* 0x4 */ int            time;
} DemoKey; // size = 0x8

typedef struct DemoKeyState {
    /* 0x0 */ int index;
    /* 0x4 */ int time;
} DemoKeyState; // size = 0x8

// ===== save_file =====
typedef struct EntryPoint {
    /* 0x00 */ unsigned short stage_id;
    /* 0x02 */ unsigned short x;
    /* 0x04 */ unsigned short y;
    /* 0x06 */ unsigned short z;
    /* 0x08 */ unsigned short player_yaw; // Angle in units where 0x400 equals a full turn.
    /* 0x0A */ unsigned short camera_yaw;
} EntryPoint; // size = 0xC

typedef struct SaveStats {
    /* 0x00 */ int           unk_00;
    /* 0x04 */ int           character;
    /* 0x08 */ int           max_health;
    /* 0x0C */ int           health;
    /* 0x10 */ int           money;
    /* 0x14 */ int           lives;
    /* 0x18 */ int           healing_item; // 0: none, 1: heal 8, 2: heal 20, 3: full heal.
    /* 0x1C */ unsigned char unk_1c[0x10];
    /* 0x2C */ int           weapon; // Selected weapon index (1 to 3).
} SaveStats;                         // size = 0x30

typedef struct SaveFile {
    /* 0x000 */ unsigned char  flags[100];
    /* 0x064 */ SaveStats      stats;
    /* 0x094 */ int            character_joined[4];
    /* 0x0A4 */ int            weapon_level[4];
    /* 0x0B4 */ int            has_weapon_2[4];
    /* 0x0C4 */ int            has_weapon_3[4];
    /* 0x0D4 */ int            has_charge[4]; // Whether weapon 3 can be charged for each character.
    /* 0x0E4 */ int            has_ability[4];
    /* 0x0F4 */ unsigned char  unk_f4[8];
    /* 0x0FC */ int            lucky_cats; // Lucky cat count; every fourth increases maximum health.
    /* 0x100 */ unsigned char  unk_100[0x38];
    /* 0x138 */ unsigned char  area_map_flags[5][40];
    /* 0x200 */ int            entry_id;
    /* 0x204 */ unsigned short stage_id;
    /* 0x206 */ unsigned char  stage_group;
    /* 0x207 */ unsigned char  pad_207;
    /* 0x208 */ short          camera_yaw;
    /* 0x20A */ short          x;
    /* 0x20C */ short          y;
    /* 0x20E */ short          z;
    /* 0x210 */ unsigned short player_yaw;
    /* 0x212 */ unsigned char  unk_212[22];
    /* 0x228 */ int            bomber_reached[4];
    /* 0x238 */ int            stage_reached[5];
    /* 0x24C */ int            unk_24c;
    /* 0x250 */ int            has_menu_item[4];
    /* 0x260 */ int            unk_260;
    /* 0x264 */ int            play_seconds;
    /* 0x268 */ int            has_large_map; // Map of Japan unlocked for stage groups 1 and 2.
    /* 0x26C */ int            has_area_map[5];
    /* 0x280 */ int            has_area_marker[5];
    /* 0x294 */ int            unk_294[2];
    /* 0x29C */ int            unk_29c;
    /* 0x2A0 */ int            unk_2a0;
    /* 0x2A4 */ int            map_point_reached[19];
    /* 0x2F0 */ unsigned char  unk_2f0[0x14];
    /* 0x304 */ int            unk_304;
} SaveFile; // size = 0x308

// ===== sd_main =====
typedef struct SoundSet {
    /* 0x00 */ unsigned char   tracks;
    /* 0x01 */ unsigned char   voice;
    /* 0x02 */ unsigned char   pri;
    /* 0x03 */ unsigned char   bank;
    /* 0x04 */ unsigned char   delay;
    /* 0x05 */ unsigned char   pad_05[3];
    /* 0x08 */ unsigned char **addr;
} SoundSet; // size = 0xC

typedef struct SoundEntry {
    /* 0x00 */ unsigned char tracks;
    /* 0x01 */ unsigned char bank;
    /* 0x02 */ unsigned char group;
    /* 0x03 */ unsigned char slot;
} SoundEntry; // size = 0x4

typedef struct SoundScripts {
    /* 0x00 */ unsigned char   tracks;
    /* 0x01 */ unsigned char   bank;
    /* 0x02 */ unsigned char   pad_02[2];
    /* 0x04 */ unsigned char **addr;
} SoundScripts; // size = 0x8

typedef struct SoundData {
    /* 0x00 */ unsigned char pri;
    /* 0x01 */ unsigned char voice_bank;
    /* 0x02 */ unsigned char pad_02[2];
    /* 0x04 */ union {
        unsigned char  *addr;
        unsigned char **addr_tbl;
    };
} SoundData; // size = 0x8

typedef struct SoundWork {
    // Sound code: ID (0x7FFF), pan (0x7F0000), and volume scale (0xFF000000).
    /* 0x00 */ union {
        unsigned int  code;
        unsigned char code_b[4];
    };
    /* 0x04 */ unsigned char  pri;
    /* 0x05 */ unsigned char  delay;
    /* 0x06 */ unsigned char  flags;
    /* 0x07 */ unsigned char  pad_07;
    /* 0x08 */ unsigned char *mpointer;
    /* 0x0C */ unsigned char  bank;
    /* 0x0D */ unsigned char  snos;
    /* 0x0E */ unsigned char  voice_on;
    /* 0x0F */ unsigned char  stop_cnt;
    /* 0x10 */ unsigned char  fx_mix;
    /* 0x11 */ unsigned char  pad_11[3];
    /* 0x14 */ ALWaveTable   *wavetable;
    // Tempo, tempo counter, and tempo interpolation.
    /* 0x18 */ unsigned short tmp;
    /* 0x1A */ unsigned short tmpd;
    /* 0x1C */ unsigned char  tmpm;
    /* 0x1D */ unsigned char  tmpc;
    /* 0x1E */ short          tmpad;
    // Step time, step counter, gate time, and gate-off counter.
    /* 0x20 */ unsigned char  ngs;
    /* 0x21 */ unsigned char  ngc;
    /* 0x22 */ unsigned char  ngg;
    /* 0x23 */ unsigned char  last_ngg;
    /* 0x24 */ unsigned char  ngo;
    /* 0x25 */ unsigned char  note;
    /* 0x26 */ unsigned char  pad_26[2];
    // Pitch (in 1/256 semitones) and pitch offsets.
    /* 0x28 */ int            swpd;
    /* 0x2C */ short          tone_tune;
    /* 0x2E */ short          ptps;
    /* 0x30 */ short          tund;
    /* 0x32 */ short          lp1_freq;
    /* 0x34 */ short          lp2_freq;
    /* 0x36 */ short          vib_data;
    /* 0x38 */ unsigned short rdm_data;
    // Volume and volume interpolation.
    /* 0x3A */ unsigned short pvod;
    /* 0x3C */ unsigned char  unk_3c[4];
    /* 0x40 */ short          lp1_vol;
    /* 0x42 */ short          lp2_vol;
    /* 0x44 */ short          pvoad;
    /* 0x46 */ unsigned char  pvom;
    /* 0x47 */ unsigned char  pvoc;
    // Velocity and ADSR envelope.
    /* 0x48 */ unsigned char  vol;
    /* 0x49 */ unsigned char  env_step;
    /* 0x4A */ unsigned short env_vol;
    /* 0x4C */ unsigned short env_time;
    /* 0x4E */ unsigned short ar;
    /* 0x50 */ unsigned short dr;
    /* 0x52 */ unsigned short sr;
    /* 0x54 */ unsigned short sl;
    /* 0x56 */ unsigned short rr;
    // Pan and pan interpolation (bit 15 of pand indicates caller-forced pan).
    /* 0x58 */ unsigned short pand;
    /* 0x5A */ unsigned char  panm;
    /* 0x5B */ unsigned char  panc;
    /* 0x5C */ short          panad;
    // Loops and conditional brackets.
    /* 0x5E */ unsigned char  lp1_cnt;
    /* 0x5F */ unsigned char  pad_5f;
    /* 0x60 */ unsigned char *lp1_addr;
    /* 0x64 */ unsigned char  lp2_cnt;
    /* 0x65 */ unsigned char  pad_65[3];
    /* 0x68 */ unsigned char *lp2_addr;
    /* 0x6C */ unsigned char *lp3_addr;
    /* 0x70 */ unsigned char  kakfg;
    /* 0x71 */ unsigned char  pad_71[3];
    /* 0x74 */ unsigned char *kak1ptr;
    /* 0x78 */ unsigned char *kak2ptr;
    // Sweep (swsk == 0) or portamento (swsk == 1); swpad also stores the previous pitch.
    /* 0x7C */ unsigned char  swphc;
    /* 0x7D */ unsigned char  swpc;
    /* 0x7E */ unsigned char  pad_7e[2];
    /* 0x80 */ int            swpm;
    /* 0x84 */ int            swpad;
    /* 0x88 */ unsigned char  swshc;
    /* 0x89 */ unsigned char  swsc;
    /* 0x8A */ short          swss;
    /* 0x8C */ unsigned char  swsk;
    // Random LFO.
    /* 0x8D */ unsigned char  rdmo;
    /* 0x8E */ unsigned short rdmd;
    /* 0x90 */ unsigned short rdmc;
    /* 0x92 */ unsigned char  rdms;
    // Vibrato.
    /* 0x93 */ unsigned char  vibhs;
    /* 0x94 */ unsigned char  vibhc;
    /* 0x95 */ unsigned char  vibcad;
    /* 0x96 */ unsigned short vib_tmp_cnt;
    /* 0x98 */ unsigned char  vib_tbl_cnt;
    /* 0x99 */ unsigned char  vib_tc_ofst;
    /* 0x9A */ unsigned short vibdm;
    /* 0x9C */ unsigned short vibd;
    /* 0x9E */ unsigned char  vibcs;
    /* 0x9F */ unsigned char  vibcc;
    /* 0xA0 */ unsigned short vibad;
    /* 0xA2 */ short          pad_a2;
    /* 0xA4 */ float          pitch;
    /* 0xA8 */ unsigned short last_vol[2];
    /* 0xAC */ unsigned char  mute;
    /* 0xAD */ unsigned char  pad_ad;
    /* 0xAE */ unsigned short vol_scale;
} SoundWork; // size = 0xB0

// ===== sd_sub2 =====
typedef struct InstParam {
    /* 0x00 */ signed char   transpose;
    /* 0x01 */ unsigned char detune;
    /* 0x02 */ unsigned char attack;
    /* 0x03 */ unsigned char decay;
    /* 0x04 */ unsigned char sustain;
    /* 0x05 */ unsigned char release;
    /* 0x06 */ unsigned char pan;
} InstParam; // size = 0x7

typedef struct DrumInstParam {
    /* 0x00 */ unsigned char id;
    /* 0x01 */ InstParam     param;
} DrumInstParam; // size = 0x8

// ===== stage =====
typedef struct CameraRegion {
    /* 0x00 */ short         type;
    /* 0x02 */ unsigned char pad_2;
    /* 0x03 */ unsigned char pad_3;
    /* 0x04 */ int           max_x;
    /* 0x08 */ int           min_x;
    /* 0x0C */ int           max_y;
    /* 0x10 */ int           min_y;
    /* 0x14 */ int           max_z;
    /* 0x18 */ int           min_z;
    /* 0x1C */ int           rail_x;
    /* 0x20 */ int           rail_y;
    /* 0x24 */ int           rail_z;
} CameraRegion; // size = 0x28

typedef struct StageEntry {
    /* 0x00 */ unsigned short camera_yaw_step;
    /* 0x02 */ short          x;
    /* 0x04 */ short          y;
    /* 0x06 */ short          z;
    /* 0x08 */ unsigned short facing;
} StageEntry; // size = 0xA

// ===== stage_select =====
typedef struct StageSelectEntry {
    /* 0x00 */ short          x;
    /* 0x02 */ short          y;
    /* 0x04 */ short          z;
    /* 0x06 */ unsigned short player_yaw; // Angle in units where 0x400 equals a full turn.
    /* 0x08 */ unsigned short camera_yaw;
} StageSelectEntry; // size = 0xA

// ===== sys =====
typedef struct GraphBuf {
    /* 0x00000 */ Gfx     display_lists[10640];
    /* 0x14C80 */ Mtx     matrices[540];
    /* 0x1D380 */ Vp      viewports[4];
    /* 0x1D3C0 */ Lights7 lights[5];
    /* 0x1D618 */ LookAt  look_ats[4];
    /* 0x1D698 */ Hilite  hilites[4];
} GraphBuf; // size = 0x1D6D8

typedef struct TextLabel {
    /* 0x00 */ unsigned char type;
    /* 0x01 */ unsigned char pad_1;
    /* 0x02 */ short         x;
    /* 0x04 */ short         y;
    /* 0x06 */ unsigned char pad_6;
    /* 0x07 */ unsigned char pad_7;
    /* 0x08 */ char         *string;
    /* 0x0C */ unsigned int  number;
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
    /* 0x3ADE2 */ unsigned char  title_menu_choice;
    /* 0x3ADE3 */ unsigned char  unk_3ade3;
    /* 0x3ADE4 */ unsigned char  intended_stage_group;
    /* 0x3ADE5 */ unsigned char  unk_3ade5;
    /* 0x3ADE6 */ unsigned short map_area_index;
    /* 0x3ADE8 */ unsigned int   map_area;
    /* 0x3ADEC */ unsigned short map_floor;
    /* 0x3ADEE */ unsigned short map_cell;
    /* 0x3ADF0 */ unsigned short map_floor_split;
    /* 0x3ADF2 */ unsigned short intended_stage_id;
    /* 0x3ADF4 */ unsigned short intended_stage_group_index;
    /* 0x3ADF6 */ unsigned char  current_stage_group;
    /* 0x3ADF7 */ unsigned char  unk_3adf7;
    /* 0x3ADF8 */ unsigned short current_stage_group_index;
    /* 0x3ADFA */ unsigned char  prev_stage_group;
    /* 0x3ADFB */ unsigned char  unk_3adfb;
    /* 0x3ADFC */ unsigned short prev_stage_id;
    /* 0x3ADFE */ unsigned short prev_stage_group_index;
    /* 0x3AE00 */ unsigned short unk_3ae00;
    /* 0x3AE02 */ unsigned char  stage_exit_sound_count;
    /* 0x3AE03 */ unsigned char  unk_3ae03;
    /* 0x3AE04 */ unsigned int   bgm;
    /* 0x3AE08 */ unsigned int   prev_bgm;
    /* 0x3AE0C */ unsigned char  enter_voice_pending;
    /* 0x3AE0D */ unsigned char  pause_menu_choice;
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
    /* 0x3AE20 */ unsigned char  player_event_mode;
    /* 0x3AE21 */ unsigned char  unk_3ae21;
    /* 0x3AE22 */ unsigned char  event_input_locked;
    /* 0x3AE23 */ unsigned char  player_input_locked;
    /* 0x3AE24 */ unsigned short task_disabled_status;
    /* 0x3AE26 */ unsigned short paused;
    /* 0x3AE28 */ unsigned char  culling_disabled;
    /* 0x3AE29 */ unsigned char  stage_change_flags;
    /* 0x3AE2A */ unsigned char  unk_3ae2a;
    /* 0x3AE2B */ unsigned char  unk_3ae2b;
    /* 0x3AE2C */ unsigned int   stage_change_cam_distance;
    /* 0x3AE30 */ unsigned short stage_change_cam_yaw_step;
    /* 0x3AE32 */ unsigned char  unk_3ae32;
    /* 0x3AE33 */ unsigned char  unk_3ae33;
    /* 0x3AE34 */ unsigned char  unk_3ae34;
    /* 0x3AE35 */ unsigned char  unk_3ae35;
    /* 0x3AE36 */ unsigned char  unk_3ae36;
    /* 0x3AE37 */ unsigned char  unk_3ae37;
    /* 0x3AE38 */ unsigned char  no_enter_walk;
    /* 0x3AE39 */ unsigned char  unk_3ae39;
    /* 0x3AE3A */ unsigned short demo_wave;
    /* 0x3AE3C */ int            demo_offset;
    /* 0x3AE40 */ unsigned short camera_type;
    /* 0x3AE42 */ unsigned char  unk_3ae42;
    /* 0x3AE43 */ unsigned char  unk_3ae43;
    /* 0x3AE44 */ unsigned int   camera_rail_x;
    /* 0x3AE48 */ unsigned int   camera_rail_y;
    /* 0x3AE4C */ unsigned int   camera_rail_z;
    /* 0x3AE50 */ CameraRegion   camera_regions[10];
    /* 0x3AFE0 */ unsigned short next_stage_id;
    /* 0x3AFE2 */ StageEntry     next_entry;
    /* 0x3AFEC */ StageEntry     entry;
    /* 0x3AFF6 */ StageEntry     prev_entry;
    /* 0x3B000 */ unsigned int   minimap_x;
    /* 0x3B004 */ unsigned int   minimap_y;
    /* 0x3B008 */ unsigned int   minimap_scale;
    /* 0x3B00C */ unsigned char  unk_3b00c[4];
    /* 0x3B010 */ unsigned char  stage_player_idle_type;
    /* 0x3B011 */ unsigned char  unk_3b011;
    /* 0x3B012 */ unsigned char  unk_3b012;
    /* 0x3B013 */ unsigned char  unk_3b013;
    /* 0x3B014 */ ObjSprite     *fade;
    /* 0x3B018 */ ObjSprite     *color_fade;
    /* 0x3B01C */ unsigned char  unk_3b01c;
    /* 0x3B01D */ unsigned char  wait_frames;
    /* 0x3B01E */ unsigned short stage_wave_base;
    /* 0x3B020 */ short          stage_wave_end;
    /* 0x3B022 */ unsigned short stage_wave_list[6];
    /* 0x3B02E */ unsigned char  temp_wave_slot;
    /* 0x3B02F */ unsigned char  unk_3b02f;
    /* 0x3B030 */ unsigned int   temp_wave_slot_addr;
    /* 0x3B034 */ unsigned int   pause_wave_clobber_end;
    /* 0x3B038 */ unsigned char  pause_wave_reload_index;
    /* 0x3B039 */ unsigned char  unk_3b039;
    /* 0x3B03A */ unsigned char  unk_3b03a;
    /* 0x3B03B */ unsigned char  unk_3b03b;
    /* 0x3B03C */ void          *load_files_function;
    /* 0x3B040 */ unsigned int   pak_save_slot;
    /* 0x3B044 */ unsigned char  unk_3b044[4];
    /* 0x3B048 */ int            stage_select_digit;
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
    /* 0x3B668 */ ObjMoji        mojis[2];
    /* 0x3BB08 */ unsigned char  unknown_data[524288];
    /* 0xBBB08 */ ObjGbg         gbgs[2];
    /* 0xBBB90 */ ObjSolid       solids[192];
    /* 0xC2D90 */ unsigned short common_wave_no;
    /* 0xC2D92 */ unsigned char  unk_c2d92;
    /* 0xC2D93 */ unsigned char  unk_c2d93;
    /* 0xC2D94 */ ObjSprite      sprites[24];
    /* 0xC3394 */ ObjLayer       layers[12];
    /* 0xC5D04 */ unsigned char  stop_processing_draw_lists;
    /* 0xC5D05 */ unsigned char  unk_c5d05;
    /* 0xC5D06 */ short          sprite_color_r;
    /* 0xC5D08 */ short          sprite_color_g;
    /* 0xC5D0A */ short          sprite_color_b;
    /* 0xC5D0C */ short          sprite_color_a;
    /* 0xC5D0E */ unsigned char  unk_c5d0e;
    /* 0xC5D0F */ unsigned char  unk_c5d0f;
    /* 0xC5D10 */ union {
        ObjSpriteFlags sprite_override_flags;
        unsigned int   sprite_override_flags_word;
    };
    /* 0xC5D14 */ unsigned char   unk_c5d14[4];
    /* 0xC5D18 */ unsigned short  tlut_buffer[256];
    /* 0xC5F18 */ unsigned short  palette_slot_refs[16];
    /* 0xC5F38 */ unsigned short *palette_slot_srcs[16];
    /* 0xC5F78 */ void           *sprite_tex_table;
    /* 0xC5F7C */ unsigned int    unk_c5f7c;
    /* 0xC5F80 */ WaveReq        *file_requests_table[8];
    /* 0xC5FA0 */ unsigned char   decompression_buffer[8192];
    /* 0xC7FA0 */ unsigned char   wave_load_state;
    /* 0xC7FA1 */ unsigned char   unk_c7fa1;
    /* 0xC7FA2 */ unsigned char   unk_c7fa2;
    /* 0xC7FA3 */ unsigned char   unk_c7fa3;
    /* 0xC7FA4 */ AmemBlock       memory_blocks[1920];
    /* 0xCF7A4 */ unsigned char   unk_cf7a4[12];
    /* 0xCF7B0 */ int            *default_palette;
    /* 0xCF7B4 */ unsigned char   unk_cf7b4[88];
    /* 0xCF80C */ unsigned int    tlb_physical_addresses[32];
    /* 0xCF88C */ unsigned char   player_exists;
    /* 0xCF88D */ unsigned char   player_dead;
    /* 0xCF88E */ unsigned short  minimap_yaw;
    /* 0xCF890 */ short           kill_plane_y;
    /* 0xCF892 */ unsigned char   unk_cf892;
    /* 0xCF893 */ unsigned char   unk_cf893;
    /* 0xCF894 */ unsigned int    unk_cf894;
    /* 0xCF898 */ unsigned char   trigger_id;
    /* 0xCF899 */ unsigned char   unk_cf899;
    /* 0xCF89A */ unsigned char   unk_cf89a;
    /* 0xCF89B */ unsigned char   unk_cf89b;
    /* 0xCF89C */ Task           *player_attach_task;
    /* 0xCF8A0 */ unsigned char   used_stage_select;
    /* 0xCF8A1 */ unsigned char   pause_show_map;
    /* 0xCF8A2 */ unsigned char   pause_disabled;
    /* 0xCF8A3 */ unsigned char   unk_cf8a3;
    /* 0xCF8A4 */ unsigned char   unk_cf8a4[12];
    /* 0xCF8B0 */ unsigned int    unk_cf8b0;
    /* 0xCF8B4 */ unsigned char   minimap_open;
    /* 0xCF8B5 */ unsigned char   unk_cf8b5;
    /* 0xCF8B6 */ unsigned char   unk_cf8b6;
    /* 0xCF8B7 */ unsigned char   unk_cf8b7;
    // [0]: menu parent task, [1]: menu task, [2..7]: tasks suspended while paused.
    /* 0xCF8B8 */ Task           *menu_tasks[8];
    /* 0xCF8D8 */ void           *player_manager_task;
    /* 0xCF8DC */ void           *dummy_task;
    /* 0xCF8E0 */ void           *actor_manager_task;
    /* 0xCF8E4 */ void           *skybox_manager_task;
    /* 0xCF8E8 */ Task           *stage_lighting_task;
    /* 0xCF8EC */ Task           *script_task;
    /* 0xCF8F0 */ Task           *hud_graphics_task;
    /* 0xCF8F4 */ void           *stage_graphics_task;
    /* 0xCF8F8 */ void           *unk_cf8f8;
    /* 0xCF8FC */ unsigned int    unk_cf8fc;
    /* 0xCF900 */ unsigned int    unk_cf900;
    /* 0xCF904 */ unsigned int    unk_cf904;
} Sys; // size = 0xCF908

// ===== demo =====
// Initial state and input stream reference for an attract-mode demo (D_8005B1E0).
typedef struct DemoStart {
    /* 0x00 */ unsigned short stage;
    /* 0x02 */ unsigned short posi_extra;
    /* 0x04 */ short          x;
    /* 0x06 */ short          y;
    /* 0x08 */ short          z;
    /* 0x0A */ unsigned short angle;
    /* 0x0C */ unsigned short end_frame;
    /* 0x0E */ unsigned short keys_file;
    /* 0x10 */ int            keys_addr;
} DemoStart; // size = 0x14

// ===== vibration_pak =====
typedef struct VibrationPak {
    /* 0x00 */ int active;
    /* 0x04 */ int duration;
    /* 0x08 */ int state;
    /* 0x0C */ int retry;
    /* 0x10 */ int status;
    /* 0x14 */ int timer;
    /* 0x18 */ int pattern;
    /* 0x1C */ int bit;
} VibrationPak; // size = 0x20

// ===== window =====
typedef struct WindowStyle {
    /* 0x00 */ unsigned char *texture;
    /* 0x04 */ unsigned int  *palette;
    /* 0x08 */ int            width;
    /* 0x0C */ int            strip_height;
    /* 0x10 */ int            strip_count;
    /* 0x14 */ int            r;
    /* 0x18 */ int            g;
    /* 0x1C */ int            b;
    /* 0x20 */ int            a;
} WindowStyle; // size = 0x24

typedef struct WindowEntry {
    /* 0x00 */ unsigned char *glyph;
    /* 0x04 */ short          kind;
    /* 0x06 */ short          palette;
    /* 0x08 */ short          x;
    /* 0x0A */ short          y;
    /* 0x0C */ short          unk_0c;
    /* 0x0E */ short          unk_0e;
    /* 0x10 */ short          unk_10;
    /* 0x12 */ short          unk_12;
    /* 0x14 */ float          scale_x;
    /* 0x18 */ float          scale_y;
    /* 0x1C */ float          unk_1c;
    /* 0x20 */ short          unk_20;
    /* 0x22 */ short          unk_22;
    /* 0x24 */ int            unk_24;
    /* 0x28 */ long long      flags;
} WindowEntry; // size = 0x30

typedef struct Window {
    /* 0x000 */ int                active;
    /* 0x004 */ unsigned char     *texture;
    /* 0x008 */ unsigned int      *palette;
    /* 0x00C */ unsigned char      pad_00c[4];
    /* 0x010 */ unsigned long long flags;
    /* 0x018 */ unsigned long long char_flags;
    /* 0x020 */ int                id;
    /* 0x024 */ int                text_palette;
    /* 0x028 */ int                style;
    /* 0x02C */ int                effect;
    /* 0x030 */ short              state;
    /* 0x032 */ short              x;
    /* 0x034 */ short              y;
    /* 0x036 */ short              target_x;
    /* 0x038 */ short              target_y;
    /* 0x03A */ short              from_x;
    /* 0x03C */ short              from_y;
    /* 0x03E */ short              width;
    /* 0x040 */ short              strip_height;
    /* 0x042 */ short              strip_count;
    /* 0x044 */ float              scale;
    /* 0x048 */ float              rest_scale;
    /* 0x04C */ float              scale_speed;
    /* 0x050 */ int                text_left;
    /* 0x054 */ int                text_top;
    /* 0x058 */ int                unk_058;
    /* 0x05C */ int                unk_05c;
    /* 0x060 */ int                unk_060;
    /* 0x064 */ short              clip_x0;
    /* 0x066 */ short              clip_y0;
    /* 0x068 */ short              clip_x1;
    /* 0x06A */ short              clip_y1;
    /* 0x06C */ short              column;
    /* 0x06E */ short              cursor_x;
    /* 0x070 */ short              char_advance;
    /* 0x072 */ short              line;
    /* 0x074 */ short              cursor_y;
    /* 0x076 */ short              line_height;
    /* 0x078 */ int                frames;
    /* 0x07C */ int                unk_07c;
    /* 0x080 */ unsigned char      unk_080[8];
    /* 0x088 */ float              char_scale;
    /* 0x08C */ int                unk_08c;
    /* 0x090 */ int                unk_090;
    /* 0x094 */ unsigned char      pad_094[0x4];
    /* 0x098 */ Mtx                projection[2];
    /* 0x118 */ unsigned char      unk_118[0x80];
    /* 0x198 */ WindowEntry        entries[120];
} Window;

// ===== fade =====
typedef struct FadeWork {
    /* 0x00 */ int          step;
    /* 0x04 */ int          rise_frames;
    /* 0x08 */ int          hold_frames;
    /* 0x0C */ int          fall_frames;
    /* 0x10 */ unsigned int hold_timer;
    /* 0x14 */ int          active;
    /* 0x18 */ float        alpha;
    /* 0x1C */ float        alpha_step;
} FadeWork; // size = 0x20

// ===== sprite =====
typedef struct ObjSpriteFrame {
    /* 0x00 */ int            unk_00;
    /* 0x04 */ ObjSpritePart *parts;
} ObjSpriteFrame; // size = 0x8

// ===== okutani =====
typedef struct FlashWork {
    /* 0x00 */ unsigned char pad_00[0x34];
    /* 0x34 */ float         anim_speed;
    /* 0x38 */ unsigned char pad_38[0x1C];
    /* 0x54 */ unsigned int  second_glist[6];
    /* 0x6C */ unsigned char pad_6c[8];
    /* 0x74 */ unsigned int  first_glist[6];
} FlashWork; // size = 0x8C

typedef struct VelocityWork {
    /* 0x00 */ unsigned char pad_00[0x14];
    /* 0x14 */ float         vel_x;
    /* 0x18 */ float         vel_y;
    /* 0x1C */ float         vel_z;
} VelocityWork; // size = 0x20

typedef struct TintWork {
    /* 0x00 */ unsigned char pad_00[0x6C];
    /* 0x6C */ unsigned int  glist[8];
} TintWork; // size = 0x8C

// ===== ripple =====
typedef struct Vec3f {
    /* 0x00 */ float x;
    /* 0x04 */ float y;
    /* 0x08 */ float z;
} Vec3f; // size = 0xC

// Height grid and rendering state for a ripple surface.
typedef struct RippleSurface {
    /* 0x00 */ unsigned int flags;
    /* 0x04 */ int          cols;
    /* 0x08 */ int          rows;
    /* 0x0C */ int          width;
    /* 0x10 */ int          depth;
    /* 0x14 */ float        damping;
    /* 0x18 */ float        time_step;
    /* 0x1C */ void (*exec)(Task *, Obj *);
    /* 0x20 */ void (*update)(Task *);
    /* 0x24 */ unsigned char   r;
    /* 0x25 */ unsigned char   g;
    /* 0x26 */ unsigned char   b;
    /* 0x27 */ unsigned char   a;
    /* 0x28 */ unsigned short *env_texture;
    /* 0x2C */ unsigned short *env_texture2;
    /* 0x30 */ unsigned short *texture;
    /* 0x34 */ unsigned short *palette;
    /* 0x38 */ float           tex_scale_s;
    /* 0x3C */ float           tex_scale_t;
    /* 0x40 */ Vtx            *vertices[2];
    /* 0x48 */ unsigned char  *glists[2];
    /* 0x50 */ float          *accelerations;
    /* 0x54 */ float          *velocities;
    /* 0x58 */ float          *heights;
    /* 0x5C */ float          *divisors;
    /* 0x60 */ Vec3f          *normals;
    /* 0x64 */ unsigned int    mesh_glists[2];
    /* 0x6C */ unsigned char   pad_6c[4];
    /* 0x70 */ float           scroll;
    /* 0x74 */ Gfx            *texture_glists[2];
    /* 0x7C */ unsigned char   pad_7c[4];
} RippleSurface; // size = 0x80

// Work data for the ripple task.
typedef struct RippleWork {
    /* 0x00 */ unsigned char  pad_00[0x4];
    /* 0x04 */ int            flags_04;
    /* 0x08 */ unsigned int   flags_08;
    /* 0x0C */ unsigned char  pad_0c[0x22];
    /* 0x2E */ unsigned short unk_2e;
    /* 0x30 */ unsigned char  pad_30[0x44];
    /* 0x74 */ RippleSurface *surface;
    /* 0x78 */ unsigned char  pad_78[0x4];
    /* 0x7C */ int            vertex_size;
    /* 0x80 */ int            kill_timer;
    /* 0x84 */ unsigned char  pad_84[0x10];
} RippleWork; // size = 0x94

// ===== spline =====
// Path evaluated by spline_point (type 0: piecewise linear, type 1: spline).
typedef struct SplinePath {
    /* 0x00 */ unsigned char type;
    /* 0x02 */ short         count;
    /* 0x04 */ float         tension;
    /* 0x08 */ Vec3f        *points;
} SplinePath; // size = 0xC

// ===== scenario =====
// Work data for the script hold task.
typedef struct ScriptHeldWork {
    /* 0x00 */ unsigned char pad_00[0x60];
    /* 0x60 */ void (*resume_exec)(Task *, Obj *);
} ScriptHeldWork; // size = 0x64

// Work data for the script page task.
typedef struct ScriptWork {
    /* 0x00 */ unsigned char cursor_blink;
    /* 0x01 */ unsigned char page_mark_blink;
} ScriptWork; // size = 0x2

// Wait state of the script interpreter (D_801C77E8).
typedef struct ScriptWaitState {
    /* 0x00 */ short         *text;
    /* 0x04 */ unsigned short held_dir;
    /* 0x06 */ unsigned short held_frames;
    /* 0x08 */ short          last_char;
    /* 0x0A */ unsigned short hurry;
    /* 0x0C */ int            choice_state;
    /* 0x10 */ int            wait_frames;
    /* 0x14 */ unsigned int   file_addr;
} ScriptWaitState; // size = 0x18

// Script page prompt indicator (D_801C78D8).
typedef struct ScriptPageMark {
    /* 0x00 */ int             x;
    /* 0x04 */ int             y;
    /* 0x08 */ unsigned short *texture;
    /* 0x0C */ unsigned int    blink_pattern;
} ScriptPageMark; // size = 0x10

// Node in the script choice list.
typedef struct ChoiceEntry {
    /* 0x00 */ int                 x;
    /* 0x04 */ int                 y;
    /* 0x08 */ struct ChoiceEntry *prev;
    /* 0x0C */ struct ChoiceEntry *next;
    /* 0x10 */ int                *script;
} ChoiceEntry; // size = 0x14

// ===== dracam =====
// Work data for a draw camera task. Each interpolated property stores a target value and a step speed.
typedef struct DracamWork {
    /* 0x00 */ unsigned char shake_timer;
    /* 0x01 */ unsigned char shake_period;
    /* 0x02 */ unsigned char pad_02[2];
    /* 0x04 */ float         shake_x;
    /* 0x08 */ float         shake_y;
    /* 0x0C */ float         shake_z;
    /* 0x10 */ AnimeCamera  *camera;
    /* 0x14 */ float         steps;
    /* 0x18 */ float         fovy;
    /* 0x1C */ float         fovy_target;
    /* 0x20 */ float         fovy_speed;
    /* 0x24 */ float         eye_x;
    /* 0x28 */ float         eye_y;
    /* 0x2C */ float         eye_z;
    /* 0x30 */ float         at_x;
    /* 0x34 */ float         at_y;
    /* 0x38 */ float         at_z;
    /* 0x3C */ float         eye_x_target;
    /* 0x40 */ float         eye_x_speed;
    /* 0x44 */ float         eye_z_target;
    /* 0x48 */ float         eye_z_speed;
    /* 0x4C */ float         eye_y_target;
    /* 0x50 */ float         eye_y_speed;
    /* 0x54 */ float         at_x_target;
    /* 0x58 */ float         at_x_speed;
    /* 0x5C */ float         at_z_target;
    /* 0x60 */ float         at_z_speed;
    /* 0x64 */ float         at_y_target;
    /* 0x68 */ float         at_y_speed;
    /* 0x6C */ short         path_frame;
    /* 0x6E */ short         path_frames;
    /* 0x70 */ SplinePath   *path;
} DracamWork; // size = 0x74

// Work data for a draw light task. Each interpolated property stores a target value and a step speed.
typedef struct DraligWork {
    /* 0x00 */ float         steps;
    /* 0x04 */ float         dir_x;
    /* 0x08 */ float         dir_x_target;
    /* 0x0C */ float         dir_x_speed;
    /* 0x10 */ float         dir_y;
    /* 0x14 */ float         dir_z_target;
    /* 0x18 */ float         dir_z_speed;
    /* 0x1C */ float         dir_z;
    /* 0x20 */ float         dir_y_target;
    /* 0x24 */ float         dir_y_speed;
    /* 0x28 */ float         r;
    /* 0x2C */ float         r_target;
    /* 0x30 */ float         r_speed;
    /* 0x34 */ float         g;
    /* 0x38 */ float         g_target;
    /* 0x3C */ float         g_speed;
    /* 0x40 */ float         b;
    /* 0x44 */ float         b_target;
    /* 0x48 */ float         b_speed;
    /* 0x4C */ float         ambient_r;
    /* 0x50 */ float         ambient_r_target;
    /* 0x54 */ float         ambient_r_speed;
    /* 0x58 */ float         ambient_g;
    /* 0x5C */ float         ambient_g_target;
    /* 0x60 */ float         ambient_g_speed;
    /* 0x64 */ float         ambient_b;
    /* 0x68 */ float         ambient_b_target;
    /* 0x6C */ float         ambient_b_speed;
    /* 0x70 */ signed char   light_dir[3];
    /* 0x73 */ unsigned char light_col[3];
    /* 0x76 */ unsigned char ambient_col[3];
    /* 0x79 */ unsigned char pad_79[27];
} DraligWork; // size = 0x94

// ===== sd_location =====
typedef struct SoundTaskWork {
    /* 0x00 */ unsigned short sound_id;
    /* 0x04 */ AnimeCamera   *camera;
    /* 0x08 */ ObjSolid      *solid;
    /* 0x0C */ float          range;
} SoundTaskWork; // size = 0x10

// ===== impact_battle =====
typedef struct Boss3dView {
    /* 0x00 */ unsigned char unk_00[0x48];
    /* 0x48 */ short         viewport_x0;
    /* 0x4A */ short         viewport_y0;
    /* 0x4C */ short         viewport_x1;
    /* 0x4E */ short         viewport_y1;
} Boss3dView; // size = 0x50

typedef struct Boss3dParam {
    /* 0x00 */ unsigned char unk_00;
    /* 0x01 */ unsigned char unk_01;
    /* 0x02 */ short         unk_02;
    /* 0x04 */ short         unk_04;
    /* 0x06 */ short         unk_06;
    /* 0x08 */ short         unk_08;
    /* 0x0A */ unsigned char unk_0a;
    /* 0x0B */ unsigned char unk_0b;
} Boss3dParam; // size = 0xC

typedef struct Boss3dState {
    /* 0x00 */ float         unk_00;
    /* 0x04 */ float         unk_04;
    /* 0x08 */ float         unk_08;
    /* 0x0C */ float         unk_0c;
    /* 0x10 */ float         unk_10;
    /* 0x14 */ float         unk_14;
    /* 0x18 */ unsigned char unk_18;
    /* 0x1C */ unsigned int  unk_1c;
    /* 0x20 */ Task         *unk_20;
    /* 0x24 */ Task         *unk_24;
    /* 0x28 */ unsigned char unk_28[0x4];
    /* 0x2C */ unsigned int  unk_2c;
} Boss3dState; // size = 0x30

typedef struct Boss3d {
    /* 0x000 */ unsigned char  unk_000[0x2E];
    /* 0x02E */ unsigned short unk_02e;
    /* 0x030 */ unsigned char  unk_030[0x3C];
    /* 0x06C */ int            unk_06c;
    /* 0x070 */ unsigned char  unk_070[0x8];
    /* 0x078 */ float          unk_078;
    /* 0x07C */ unsigned char  unk_07c[0xC];
    /* 0x088 */ float          unk_088;
    /* 0x08C */ float          unk_08c;
    /* 0x090 */ unsigned char  unk_090[0x10];
    /* 0x0A0 */ Boss3dView     view;
    /* 0x0F0 */ unsigned char  unk_0f0[0x88];
    /* 0x178 */ Boss3dState    state;
    /* 0x1A8 */ unsigned char  unk_1a8[0x8];
    /* 0x1B0 */ Boss3dParam    unk_1b0;
    /* 0x1BC */ unsigned char  unk_1bc[0x30];
    /* 0x1EC */ unsigned int   letterbox_x0;
    /* 0x1F0 */ unsigned int   letterbox_y0;
    /* 0x1F4 */ unsigned int   letterbox_x1;
    /* 0x1F8 */ unsigned int   letterbox_y1;
    /* 0x1FC */ unsigned int   letterbox_y1_limit;
    /* 0x200 */ Gfx            viewport_glist[4];
    /* 0x220 */ unsigned char  unk_220[0x20];
    /* 0x240 */ Gfx            unk_240[3];
    /* 0x258 */ unsigned char  unk_258[0x28];
    /* 0x280 */ Gfx            scissor_glist[4];
    /* 0x2A0 */ unsigned char  unk_2a0[0x20];
    /* 0x2C0 */ unsigned char  cutscene_lock;
} Boss3d; // size = 0x2C8

typedef struct ColStage {
    /* 0x00 */ ColPlane *planes;
    /* 0x04 */ ColNode  *nodes;
} ColStage; // size = 0x8

// ===== konami =====
typedef struct KonamiLogoKey {
    /* 0x00 */ float a[3];
    /* 0x0C */ float b[3];
    /* 0x18 */ float c;
} KonamiLogoKey; // size = 0x1C

typedef struct KonamiLogoMtx {
    /* 0x000 */ Mtx proj;
    /* 0x040 */ Mtx view;
    /* 0x080 */ Mtx ident;
    /* 0x0C0 */ Mtx obj[3];
} KonamiLogoMtx; // size = 0x180

typedef struct KonamiLogoMap {
    /* 0x00 */ unsigned short  enabled;
    /* 0x02 */ unsigned short  unk_2;
    /* 0x04 */ unsigned char  *cells;
    /* 0x08 */ unsigned short *tiles;
    /* 0x0C */ unsigned short *offsets;
    /* 0x10 */ unsigned char  *image;
    /* 0x14 */ unsigned char  *palette;
    /* 0x18 */ unsigned short  unk_18;
    /* 0x1A */ unsigned char   format;
    /* 0x1B */ unsigned char   unk_1b;
    /* 0x1C */ short           cols;
    /* 0x1E */ short           rows;
    /* 0x20 */ short           cell_w;
    /* 0x22 */ short           cell_h;
} KonamiLogoMap; // size = 0x24

typedef union KonamiLogoFade {
    int           amount;
    unsigned char byte[4];
} KonamiLogoFade;

typedef struct KonamiLogoSteps {
    void (*fn[2])(void);
} KonamiLogoSteps; // size = 0x8

// ===== audiomgr =====
typedef struct AMDMABuffer {
    /* 0x00 */ struct AMDMABuffer *next;
    /* 0x04 */ struct AMDMABuffer *prev;
    /* 0x08 */ unsigned int        startAddr;
    /* 0x0C */ unsigned int        lastFrame;
    /* 0x10 */ unsigned char      *ptr;
} AMDMABuffer; // size = 0x14

typedef struct AMDMAState {
    /* 0x00 */ unsigned char initialized;
    /* 0x04 */ AMDMABuffer  *firstUsed;
    /* 0x08 */ AMDMABuffer  *firstFree;
} AMDMAState; // size = 0xC

typedef struct {
    /* 0x0 */ int          outputRate;
    /* 0x4 */ unsigned int framesPerField;
    /* 0x8 */ int          maxACMDSize;
} amConfig; // size = 0xC

typedef union {
    struct {
        /* 0x0 */ short type;
    } gen;

    struct {
        /* 0x0 */ short               type;
        /* 0x4 */ struct AudioInfo_s *info;
    } done;

    /* 0x0 */ OSScMsg app;
} AudioMsg; // size = 0x20

typedef struct AudioInfo_s {
    /* 0x00 */ short   *data;
    /* 0x04 */ short    frameSamples;
    /* 0x08 */ OSScTask task;
    /* 0x70 */ AudioMsg msg;
} AudioInfo; // size = 0x90

typedef struct {
    /* 0x0000 */ Acmd         *ACMDList[2];
    /* 0x0008 */ AudioInfo    *audioInfo[3];
    /* 0x0014 */ unsigned char pad_14[4];
    /* 0x0018 */ OSThread      thread;
    /* 0x01C8 */ OSMesgQueue   audioFrameMsgQ;
    /* 0x01E0 */ OSMesg        audioFrameMsgBuf[64];
    /* 0x02E0 */ OSMesgQueue   audioReplyMsgQ;
    /* 0x02F8 */ OSMesg        audioReplyMsgBuf[64];
    /* 0x03F8 */ ALGlobals     g;
} AMAudioMgr; // size = 0x448

// ===== file_12 =====
// Stage table entry in D_80231300_5EC7D0, indexed by Sys.intended_stage_id.
typedef struct StageDef {
    /* 0x00 */ struct EnemySpawn *spawns; // Stage spawn list (see EnemyMgr.spawns).
    /* 0x04 */ int                unk_04;
    /* 0x08 */ int                wave_spawns; // Wave-relative offset to stage spawns (as are cells and grid).
    /* 0x0C */ int                cells;
    /* 0x10 */ int                grid;
    /* 0x14 */ unsigned short     wave_no;
    /* 0x18 */ void              *load_files_function;
} StageDef;

// Enemy spawn point entry.
typedef struct EnemySpawn {
    /* 0x00 */ short          x, y, z;
    /* 0x06 */ unsigned short rx, ry, rz;
    /* 0x0C */ int            def; // Wave-relative offset to EnemyDef (resolved by func_80014840).
    /* 0x10 */ unsigned char  spawned;
} EnemySpawn; // size = 0x14

typedef struct EnemyDef {
    /* 0x00 */ unsigned short type;    // 1-based index into the enemy tables (D_802287C0_5E3C90, ...).
    /* 0x04 */ unsigned int   ebuf[3]; // Initial values for EnemyWork.ebuf[0..2].
} EnemyDef;                            // size = 0x10

// Generic per-enemy work slot (named EbufNN in debug strings).
typedef union EnemyBuf {
    unsigned int   u;
    int            s;
    float          f;
    unsigned short h[2];
    unsigned char  b[4];
} EnemyBuf; // size = 0x4

// Enemy manager state in sys.c BSS (D_8015CC30; see ENEMY_MGR).
typedef struct EnemyMgr {
    /* 0x00 */ unsigned short  frame;  // Update counter incremented by func_8020DD78_5C9248.
    /* 0x04 */ float           cell_x; // Grid cell size.
    /* 0x08 */ float           cell_y;
    /* 0x0C */ float           cell_z;
    /* 0x10 */ float           center_x; // World-space center of the spawn grid.
    /* 0x14 */ float           center_y;
    /* 0x18 */ float           center_z;
    /* 0x1C */ int             size_x; // Grid dimensions in cells.
    /* 0x20 */ int             size_y;
    /* 0x24 */ int             size_z;
    /* 0x28 */ int             unk_28;
    /* 0x2C */ EnemySpawn     *spawns; // Stage-table spawn list placed on stage entry.
    /* 0x30 */ int             unk_30;
    /* 0x34 */ EnemySpawn     *wave_spawns; // Wave-file spawn list placed on stage entry.
    /* 0x38 */ int            *cells;       // Array of wave-relative EnemySpawn lists per grid cell.
    /* 0x3C */ void           *grid_header; // Stage grid metadata (cell size, center, and grid dimensions).
    /* 0x40 */ unsigned short  wave_no;
    /* 0x44 */ int             radius;       // Spawn radius in cells.
    /* 0x48 */ int             random_state; // PRNG state used by func_802192B4_5D4784.
    /* 0x4C */ unsigned char   unk_4c[0x40];
    /* 0x8C */ Task           *parents[9];  // Parent tasks for each enemy category (func_80219CA0_5D5170).
    /* 0xB0 */ int             limits[5];   // Maximum active enemies for capped categories.
    /* 0xC4 */ unsigned int    spawn_count; // Enemies spawned during the current frame.
    /* 0xC8 */ unsigned int    last_spawn_count;
    /* 0xCC */ unsigned int    spawn_limit; // Frame spawn limit; spawning pauses while below spawn_count or last_spawn_count.
    /* 0xD0 */ unsigned char   category;    // Category from the most recent func_80219CA0_5D5170 call.
    /* 0xD1 */ unsigned char   unk_d1[3];
    /* 0xD4 */ unsigned int    flags;
    /* 0xD8 */ unsigned char   next_id;
    /* 0xD9 */ unsigned char   unk_d9[0x2B];
    /* 0x104 */ float          unk_104;   // Initialized to 1.0f.
    /* 0x108 */ unsigned char  search_id; // Candidate enemy ID used by func_8020DC78_5C9148.
    /* 0x109 */ unsigned char  unk_109;
    /* 0x10A */ unsigned short unk_10a;
    /* 0x10C */ unsigned char  unk_10c[0x20];
    /* 0x12C */ Task          *player_task; // Cached player task pointer (D_801FC604_5B8514).
    /* 0x130 */ ObjSolid      *player;      // Cached player ObjSolid pointer (D_801FC60C_5B851C).
    /* 0x134 */ unsigned short col_hits;    // Hit flags for the enemy currently under collision testing.
    /* 0x136 */ unsigned short col_mask;
    /* 0x138 */ unsigned char  unk_138[0x20];
    /* 0x158 */ int            unk_158;
    /* 0x15C */ int            unk_15c;
} EnemyMgr;

// Work data for an enemy task.
typedef struct EnemyWork {
    /* 0x00 */ unsigned short type; // Enemy type index (EnemyDef.type).
    /* 0x02 */ unsigned short type2;
    /* 0x04 */ unsigned int   flags_04;
    /* 0x08 */ unsigned int   flags_08;
    /* 0x0C */ unsigned int   flags_0c;  // Bit 0: hit; bit 1: dead (func_80218F30_5D4400 queues a respawn).
    /* 0x10 */ unsigned char  col_entry; // Collision entry index in the enemy type's ColFile.
    /* 0x11 */ unsigned char  unk_11[3];
    /* 0x14 */ EnemySpawn    *spawn;
    /* 0x18 */ unsigned char  id; // Unique enemy ID assigned from EnemyMgr.next_id.
    /* 0x19 */ unsigned char  unk_19;
    /* 0x1A */ unsigned char  respawn_delay;
    /* 0x1B */ unsigned char  category; // Enemy category index (D_80229FE4_5E54B4); selects parent task.
    /* 0x1C */ float          velocity[3];
    /* 0x28 */ ObjSolid      *player; // Cached pointer to EnemyMgr.player.
    /* 0x2C */ unsigned char  unk_2c[4];
    /* 0x30 */ unsigned char  hit_timer;
    /* 0x31 */ unsigned char  health;
    /* 0x32 */ unsigned char  unk_32[2];
    /* 0x34 */ void (*hit_exec)(Task *, Obj *); // Update callback to switch to upon taking a hit.
    /* 0x38 */ unsigned short col_hits;         // Bitmask of collision probes that registered a hit.
    /* 0x3A */ unsigned short col_mask;         // Bitmask of collision probes to evaluate.
    /* 0x3C */ unsigned char  col_height;
    /* 0x3D */ unsigned char  col_width;
    /* 0x3E */ unsigned char  col_depth;
    /* 0x3F */ signed char    col_offset_y;
    /* 0x40 */ unsigned char  unk_40[8];
    /* 0x48 */ unsigned short unk_48;
    /* 0x4A */ unsigned char  unk_4a[0x2A];
    /* 0x74 */ EnemyBuf       ebuf[8]; // Enemy-specific work slots (Ebuf00..Ebuf07).
} EnemyWork;                           // size = 0x94 (all of Task.work)

// ===== file_11 =====
typedef struct PlayerWaveList {
    /* 0x00 */ unsigned short wave[2];
} PlayerWaveList; // size = 0x4

typedef struct PlayerByteTable {
    /* 0x00 */ unsigned char byte[4];
} PlayerByteTable; // size = 0x4

typedef struct PlayerModeTable {
    /* 0x00 */ void (*funcs[3])(void);
} PlayerModeTable; // size = 0xC

typedef struct PlayerPhysics {
    /* 0x00 */ unsigned short forced_move;
    /* 0x02 */ unsigned short forced_angle;
    /* 0x04 */ float          forced_speed;
    /* 0x08 */ unsigned short input_angle;
    /* 0x0A */ unsigned short contact_flags;
    /* 0x0C */ float          raw_vel_x;
    /* 0x10 */ float          raw_vel_y;
    /* 0x14 */ float          raw_vel_z;
    /* 0x18 */ unsigned char  slide_flags;
    /* 0x19 */ unsigned char  unk_19;
    /* 0x1A */ unsigned short angle;
    /* 0x1C */ float          extra_anime_speed;
    /* 0x20 */ float          speed;
    /* 0x24 */ float          speed_prev;
    /* 0x28 */ float          speed_prev2;
    /* 0x2C */ unsigned char  state_step;
    /* 0x2D */ unsigned char  input_frames;
    /* 0x2E */ unsigned char  jump_cut;
    /* 0x2F */ unsigned char  up_mode;
    /* 0x30 */ unsigned short state_timer;
    /* 0x32 */ short          jump_start_y;
    /* 0x34 */ unsigned short aim_angle;
    /* 0x36 */ unsigned short charge_frames;
    /* 0x38 */ ObjSolid      *interact_solid;
    /* 0x3C */ float          up_x;
    /* 0x40 */ float          up_y;
    /* 0x44 */ float          up_z;
    /* 0x48 */ float          gravity;
    /* 0x4C */ Task          *water_task;
    /* 0x50 */ float          buoyancy;
    /* 0x54 */ float          water_height;
    /* 0x58 */ unsigned char  body_height;
    /* 0x59 */ unsigned char  water_state;
    /* 0x5A */ unsigned char  pad_5a[2];
    /* 0x5C */ float          contact_x;
    /* 0x60 */ float          contact_y;
    /* 0x64 */ float          contact_z;
    /* 0x68 */ unsigned char  charge_level;
    /* 0x69 */ unsigned char  changing_character;
    /* 0x6A */ unsigned short held_stick_angle;
    /* 0x6C */ float          held_dir_x;
    /* 0x70 */ float          held_dir_y;
    /* 0x74 */ float          held_dir_z;
    /* 0x78 */ unsigned char  held_dir_frames;
    /* 0x79 */ unsigned char  pad_79[3];
    /* 0x7C */ Task          *wall_task;
    /* 0x80 */ Task          *floor_task;
    /* 0x84 */ unsigned char  model_swap;
    /* 0x85 */ unsigned char  walk_frames;
    /* 0x86 */ unsigned short ability_timer;
    /* 0x88 */ Task          *target_task;
    /* 0x8C */ Task          *held_task;
    /* 0x90 */ Task          *push_task;
    /* 0x94 */ Task          *ladder_task;
    /* 0x98 */ Task          *effect_tasks[3];
    /* 0xA4 */ unsigned short swim_yaw;
    /* 0xA6 */ unsigned short swim_pitch;
    /* 0xA8 */ unsigned short swim_turn;
    /* 0xAA */ unsigned char  water_result;
    /* 0xAB */ unsigned char  pad_ab;
    /* 0xAC */ float          swim_speed;
    /* 0xB0 */ float          velocity_length;
    /* 0xB4 */ Task          *afterline;
    /* 0xB8 */ float          water_normal[3];
} PlayerPhysics; // size = 0xC4

// Work data for the player task.
typedef struct PlayerWork {
    /* 0x00 */ PlayerPhysics *physics;
    /* 0x04 */ unsigned char  character;
    /* 0x05 */ unsigned char  movement_locked;
    /* 0x06 */ unsigned char  pushed;
    /* 0x07 */ unsigned char  kill_request;
    /* 0x08 */ Task          *camera;
    /* 0x0C */ float          vel_x;
    /* 0x10 */ float          vel_y;
    /* 0x14 */ float          vel_z;
    /* 0x18 */ float          accel_x;
    /* 0x1C */ float          accel_y;
    /* 0x20 */ float          accel_z;
    /* 0x24 */ unsigned short action_timer;
    /* 0x26 */ unsigned short unk_26;
    /* 0x28 */ float          ground_normal_x;
    /* 0x2C */ float          ground_normal_y;
    /* 0x30 */ float          ground_normal_z;
    /* 0x34 */ unsigned char  controller;
    /* 0x35 */ unsigned char  probe_height;
    /* 0x36 */ unsigned char  box_probe_height;
    /* 0x37 */ unsigned char  pad_37;
    /* 0x38 */ unsigned short angle;
    /* 0x3A */ unsigned short wall_group;
    /* 0x3C */ unsigned short floor_group;
    /* 0x3E */ unsigned short ceiling_hit;
    /* 0x40 */ ObjSolid      *wall_solid;
    /* 0x44 */ ObjSolid      *floor_solid;
    /* 0x48 */ float          vertical_speed;
    /* 0x4C */ float          wall_normal_x;
    /* 0x50 */ float          wall_normal_y;
    /* 0x54 */ float          wall_normal_z;
    /* 0x58 */ float          floor_normal_x;
    /* 0x5C */ float          floor_normal_y;
    /* 0x60 */ float          floor_normal_z;
    /* 0x64 */ float          push_x;
    /* 0x68 */ float          push_y;
    /* 0x6C */ float          push_z;
    /* 0x70 */ unsigned char  state;
    /* 0x71 */ unsigned char  interact_step;
    /* 0x72 */ unsigned short facing_override;
    /* 0x74 */ float          anime_speed;
    /* 0x78 */ unsigned char  invincible_frames;
    /* 0x79 */ unsigned char  pad_79[6];
    /* 0x7F */ unsigned char  anime_mode;
    /* 0x80 */ Task          *fx_mgr;
    /* 0x84 */ Task          *interact_task;
    /* 0x88 */ float          max_speed;
    /* 0x8C */ float          move_accel;
    /* 0x90 */ unsigned char  unk_90;
    /* 0x91 */ unsigned char  unk_91;
    /* 0x92 */ unsigned short idle_frames;
} PlayerWork; // size = 0x94

// Work data for the player effects manager task.
typedef struct PlayerFxWork {
    /* 0x00 */ Task *player;
} PlayerFxWork;

// ===== 5907F0 =====
// Current and previous world positions of the player model.
typedef struct PlayerMotion {
    /* 0x00 */ float          x, y, z;
    /* 0x0C */ float          prev_x, prev_y, prev_z;
    /* 0x18 */ unsigned char  pad_18[2];
    /* 0x1A */ unsigned short angle;
} PlayerMotion;

// Work data for the player-following camera task.
typedef struct CameraWork {
    /* 0x00 */ unsigned short active;
    /* 0x02 */ unsigned char  flags;
    /* 0x03 */ unsigned char  unk_03;
    /* 0x04 */ unsigned char  pad_04[2];
    /* 0x06 */ unsigned char  look_blend_frames;
    /* 0x07 */ unsigned char  turn_frames;
    /* 0x08 */ unsigned short last_look_angle;
    /* 0x0A */ unsigned short look_angle;
    /* 0x0C */ unsigned short settled_look_angle;
    /* 0x0E */ unsigned char  pad_0e[4];
    /* 0x12 */ unsigned short pitch;
    /* 0x14 */ unsigned char  zoom_level;
    /* 0x15 */ unsigned char  zoom_changed;
    /* 0x16 */ unsigned char  pad_16;
    /* 0x17 */ unsigned char  requested_mode;
    /* 0x18 */ unsigned char  pad_18[0x24];
    /* 0x3C */ union {
        unsigned char  mode;
        unsigned short mode_h;
    };
    /* 0x3E */ unsigned char  pad_3e[0x16];
    /* 0x54 */ unsigned short look_scale;
    /* 0x56 */ unsigned short look_scale_target;
    /* 0x58 */ unsigned char  pad_58[0x1C];
    /* 0x74 */ unsigned char  target_blend_frames;
    /* 0x75 */ unsigned char  current_mode;
    /* 0x76 */ unsigned char  focus_override;
    /* 0x77 */ unsigned char  pad_77[0x15];
    /* 0x8C */ unsigned char  still_frames;
    /* 0x8D */ unsigned char  pad_8d[7];
} CameraWork; // size = 0x94

// ===== 5AE300 =====
// Color and update callback for a player effect type.
typedef struct PlayerEffectTemplate {
    /* 0x00 */ void (*exec)(struct Task *, struct Obj *);
    /* 0x04 */ unsigned char prim_r;
    /* 0x05 */ unsigned char prim_g;
    /* 0x06 */ unsigned char prim_b;
    /* 0x07 */ unsigned char env_r;
    /* 0x08 */ unsigned char env_g;
    /* 0x09 */ unsigned char env_b;
    /* 0x0A */ unsigned char env_a;
} PlayerEffectTemplate;

typedef struct PlayerEffectAnim {
    /* 0x0 */ signed char state;
    /* 0x2 */ short       counter;
    /* 0x4 */ float       speed;
} PlayerEffectAnim; // size = 0x8

// Frame sequence state for a player effect.
typedef struct PlayerEffectSeq {
    /* 0x0 */ unsigned int *tbl;
    /* 0x4 */ unsigned char idx;
    /* 0x5 */ unsigned char pad_5;
    /* 0x6 */ short         timer;
} PlayerEffectSeq; // size = 0x8

// Work data for a player effect task.
typedef struct PlayerEffectWork {
    /* 0x00 */ union {
        PlayerPhysics *physics;
        Task          *player_task;
    };
    /* 0x04 */ unsigned char  state;
    /* 0x05 */ unsigned char  param;
    /* 0x06 */ unsigned short timer;
    /* 0x08 */ unsigned char  kind;
    /* 0x09 */ unsigned char  done;
    /* 0x0A */ unsigned char  unk_0a;
    /* 0x0B */ unsigned char  phase;
    /* 0x0C */ unsigned short spawn_timer;
    /* 0x0E */ unsigned char  pad_0e[2];
    /* 0x10 */ float          vel[3];
    /* 0x1C */ unsigned char  pad_1c[0xC];
    /* 0x28 */ Task          *player;
    /* 0x2C */ union {
        int   dir;
        float step;
    };
    /* 0x30 */ union {
        int   frames;
        float life;
    };
    /* 0x34 */ float            growth;
    /* 0x38 */ PlayerEffectSeq  seq;
    /* 0x40 */ unsigned char    pad_40[4];
    /* 0x44 */ unsigned short   angle;
    /* 0x46 */ unsigned char    pad_46[4];
    /* 0x4A */ unsigned char    count;
    /* 0x4B */ unsigned char    pad_4b;
    /* 0x4C */ unsigned int     model;
    /* 0x50 */ unsigned char    pad_50[0xC];
    /* 0x5C */ unsigned int     dl[6];
    /* 0x74 */ unsigned char    pad_74[0xC];
    /* 0x80 */ PlayerEffectAnim anim;
} PlayerEffectWork;

// ===== 5AFA40 =====
typedef struct AfterlineJoints {
    /* 0x00 */ unsigned int target[6];
} AfterlineJoints; // size = 0x18

// ===== 5B6060 =====
typedef struct StageIdleType {
    /* 0x0 */ unsigned short stage_id;
    /* 0x2 */ unsigned char  type;
    /* 0x3 */ unsigned char  pad_3;
} StageIdleType; // size = 0x4

#endif // STRUCTS_H
