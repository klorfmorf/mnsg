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
    unsigned int unk_b28 : 1;
    unsigned int unk_b27 : 1;
    unsigned int scaled : 1;
    unsigned int unk_b25 : 1;
    unsigned int unk_b22 : 3;
    unsigned int unk_b19 : 3;
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
        ObjSpriteFlags unk_8;
        unsigned int   unk_8_word;
    };
    /* 0x0C */ unsigned char  unk_c;
    /* 0x0D */ unsigned char  unk_d;
    /* 0x0E */ unsigned char  unk_e;
    /* 0x0F */ unsigned char  unk_f;
    /* 0x10 */ unsigned char  unk_10;
    /* 0x11 */ unsigned char  unk_11;
    /* 0x12 */ unsigned char  unk_12;
    /* 0x13 */ unsigned char  unk_13;
    /* 0x14 */ ObjSpriteTex  *unk_14;
    /* 0x18 */ unsigned short unk_18;
    /* 0x1A */ unsigned char  unk_1a; // respawn delay
    /* 0x1B */ unsigned char  unk_1b;
    /* 0x1C */ union {
        int   unk_1c_word;
        short unk_1c;
    };
    /* 0x20 */ union {
        int   unk_20_word;
        short unk_20;
    };
    /* 0x24 */ unsigned char   unk_24;
    /* 0x25 */ unsigned char   unk_25;
    /* 0x26 */ unsigned char   unk_26;
    /* 0x27 */ unsigned char   unk_27;
    /* 0x28 */ unsigned char   unk_28;
    /* 0x29 */ unsigned char   unk_29;
    /* 0x2A */ unsigned char   unk_2a;
    /* 0x2B */ unsigned char   unk_2b;
    /* 0x2C */ float           unk_2c;
    /* 0x30 */ float           unk_30;
    /* 0x34 */ ObjSpritePart  *unk_34;
    /* 0x38 */ unsigned short *unk_38;
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
    };
    /* 0x94 */ struct ObjSolid *parent;
} ObjSolid; // size = 0x98

typedef struct ObjMoji {
    /* 0x000 */ Obj header;
    /* 0x008 */ int unk_8;
    /* 0x00C */ union {
        int   unk_c_word;
        short unk_c;
    };
    /* 0x010 */ union {
        int   unk_10_word;
        short unk_10;
    };
    /* 0x014 */ int             unk_14;
    /* 0x018 */ int             unk_18;
    /* 0x01C */ short           unk_1c;
    /* 0x01E */ short           unk_1e;
    /* 0x020 */ short           unk_20;
    /* 0x022 */ short           unk_22;
    /* 0x024 */ unsigned char   unk_24;
    /* 0x025 */ unsigned char   unk_25;
    /* 0x026 */ unsigned char   unk_26;
    /* 0x027 */ unsigned char   unk_27;
    /* 0x028 */ unsigned short *unk_28;
    /* 0x02C */ unsigned char   unk_2c;
    /* 0x02D */ unsigned char   unk_2d;
    /* 0x02E */ unsigned char   unk_2e;
    /* 0x02F */ unsigned char   unk_2f;
    /* 0x030 */ unsigned char   unk_30;
    /* 0x031 */ unsigned char   unk_31;
    /* 0x032 */ short           unk_32;
    /* 0x034 */ unsigned short  unk_34;
    /* 0x036 */ unsigned short  unk_36;
    /* 0x038 */ unsigned short  unk_38;
    /* 0x03A */ unsigned short  unk_3a;
    /* 0x03C */ short           unk_3c;
    /* 0x03E */ short           unk_3e;
    /* 0x040 */ short           unk_40;
    /* 0x042 */ short           unk_42;
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
    /* 0x371 */ unsigned char unk_371;
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
// A 12-byte header copied out of a pak block.
typedef struct MemPakHeader {
    unsigned int word[3];
} MemPakHeader; // size = 0xC

// The state of the memory pak in use: the libultra file system and the game file.
typedef struct MemPak {
    /* 0x000 */ OSPfs         pfs;
    /* 0x068 */ unsigned char unk_68[0x148];
    /* 0x1B0 */ OSPfsState    files[16];
    /* 0x3B0 */ unsigned char unk_3B0[0x40];
    /* 0x3F0 */ int           fileNo;
    /* 0x3F4 */ unsigned char unk_3F4[0x8];
    /* 0x3FC */ int           error;
} MemPak; // size = 0x400

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
    /* 0x00 */ struct OSScTask_s *next; // note: this must be first
    /* 0x04 */ unsigned int       state;
    /* 0x08 */ unsigned int       flags;
    /* 0x0C */ void              *frame_buffer; // used by graphics tasks
    /* 0x10 */ OSTask             list;
    /* 0x50 */ OSMesgQueue       *msgQ;
    /* 0x54 */ OSMesg             msg;
    /* 0x58 */ OSTime             startTime;
    /* 0x60 */ OSTime             totalTime;
} OSScTask; // size = 0x68

// Data structure used by threads that wish to communicate to the scheduling thread.
typedef struct SCClient_s {
    /* 0x00 */ struct SCClient_s *next; // next client in the list
    /* 0x04 */ OSMesgQueue       *msgQ; // where to send the frame msg
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
} OSSched; // size = 0x2BC

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

// ===== string =====
typedef struct TextureOffsets {
    /* 0x0 */ short s;
    /* 0x2 */ short t;
} TextureOffsets; // size = 0x4

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
    /* 0x30 */ unsigned char  unk_30;
    /* 0x31 */ unsigned char  unk_31;
    /* 0x32 */ unsigned char  unk_32;
    /* 0x33 */ unsigned char  unk_33;
    /* 0x34 */ unsigned int   unk_34;
    /* 0x38 */ unsigned int   unk_38;
    /* 0x3C */ unsigned short unk_3c;
    /* 0x3E */ unsigned short unk_3e;
    /* 0x40 */ unsigned short unk_40;
    /* 0x42 */ unsigned short unk_42;
    /* 0x44 */ unsigned char  unk_44;
    /* 0x45 */ unsigned char  unk_45;
    /* 0x46 */ unsigned char  unk_46;
    /* 0x47 */ unsigned char  unk_47;
    /* 0x48 */ unsigned int   unk_48;
    /* 0x4C */ unsigned char  unk_4c;
    /* 0x4D */ unsigned char  unk_4d;
    /* 0x4E */ unsigned short unk_4e;
    /* 0x50 */ unsigned short unk_50;
    /* 0x52 */ short          unk_52;
    /* 0x54 */ void         *unk_54;
    /* 0x58 */ unsigned int   unk_58;
    /* 0x5C */ unsigned int   work[0x25]; // Task-specific data; see the `*_WORK` macros.
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
    /* 0x00 */ float       normal_x;
    /* 0x04 */ float       normal_y;
    /* 0x08 */ float       normal_z;
    /* 0x0C */ float       distance;
    /* 0x10 */ signed char type;
} ColPlane; // size = 0x14

typedef struct ColTree {
    /* 0x00 */ unsigned short next_tree;
    /* 0x02 */ unsigned short type;
    /* 0x04 */ unsigned short scale;
    /* 0x06 */ short          box_max_x;
    /* 0x08 */ short          box_max_y;
    /* 0x0A */ short          box_max_z;
    /* 0x0C */ short          box_min_x;
    /* 0x0E */ short          box_min_y;
    /* 0x10 */ short          box_min_z;
} ColTree; // size = 0x12

typedef struct ColNode {
    /* 0x00 */ unsigned short a;
    /* 0x02 */ short          b;
    /* 0x04 */ short          c;
} ColNode; // size = 0x6

typedef struct ColHead {
    /* 0x00 */ short unk_0;
    /* 0x02 */ short unk_2;
    /* 0x04 */ short range;
} ColHead; // size = 0x6

typedef struct ColEntry {
    /* 0x00 */ ColHead *unk_0;
    /* 0x04 */ void    *unk_4;
} ColEntry; // size = 0x8

typedef struct ColFile {
    /* 0x00 */ unsigned short *wave_no;
    /* 0x04 */ int             unk_4;
    /* 0x08 */ int             unk_8;
    /* 0x0C */ ColEntry       *entries;
} ColFile; // size = 0x10

typedef struct ColObj {
    /* 0x00 */ struct ColObj *next;
    /* 0x04 */ unsigned char  unk_4[0x14];
    /* 0x18 */ ObjSolid      *solid;
    /* 0x1C */ unsigned char  unk_1C[4];
    /* 0x20 */ unsigned short unk_20;
    /* 0x22 */ unsigned char  unk_22[0xE];
    /* 0x30 */ unsigned char  flags;
    /* 0x34 */ struct ColObj *hit;
    /* 0x38 */ struct ColObj *hit_by;
    /* 0x3C */ unsigned short width;
    /* 0x3E */ unsigned short height;
    /* 0x40 */ short          offset_y;
    /* 0x42 */ short          offset_z;
    /* 0x44 */ unsigned char  hit_index;
    /* 0x48 */ unsigned int   ref;
    /* 0x4C */ unsigned char  kind;
    /* 0x4E */ unsigned short unk_4E;
    /* 0x50 */ short          unk_50;
    /* 0x52 */ short          unk_52;
    /* 0x54 */ float         *contact;
    /* 0x58 */ unsigned int   script;
    /* 0x5C */ unsigned char  unk_5C[2];
    /* 0x5E */ unsigned short file;
    /* 0x60 */ unsigned int   unk_60;
    /* 0x64 */ unsigned char  unk_64[8];
    /* 0x6C */ unsigned char  entry;
} ColObj; // size = 0x70

typedef struct ColHit {
    /* 0x00 */ float       x;
    /* 0x04 */ float       y;
    /* 0x08 */ float       z;
    /* 0x0C */ float       move_x;
    /* 0x10 */ float       move_y;
    /* 0x14 */ float       move_z;
    /* 0x18 */ float       unk_18;
    /* 0x1C */ float       unk_1C;
    /* 0x20 */ float       unk_20;
    /* 0x24 */ float       unk_24;
    /* 0x28 */ float       unk_28;
    /* 0x2C */ float       unk_2C;
    /* 0x30 */ float       unk_30;
    /* 0x34 */ signed char unk_34;
    /* 0x36 */ short       unk_36;
    /* 0x38 */ short       unk_38;
    /* 0x3C */ float       unk_3C;
    /* 0x40 */ ObjSolid   *solid;
    /* 0x44 */ ColObj     *obj;
} ColHit; // size = 0x48

// ===== solid_atari =====
// Four animation "tracks" of one collision shape that determine the size and the offset from the solid.
typedef struct ColShape {
    /* 0x00 */ unsigned short size;
    /* 0x02 */ unsigned short x, y, z;
} ColShape; // size = 0x8

// ===== yamamoto =====
typedef struct SpriteList {
    /* 0x00 */ short          unk_00;
    /* 0x02 */ short          count;
    /* 0x04 */ short          max;
    /* 0x06 */ short          unk_06;
    /* 0x08 */ ObjSpritePart *parts;
} SpriteList; // size = 0xC

typedef struct SpriteOwner {
    /* 0x00 */ unsigned char unk_00[0x1C];
    /* 0x1C */ ObjSprite    *sprite;
} SpriteOwner; // size = 0x20

typedef struct YamamotoSub {
    /* 0x00 */ int unk_00;
    /* 0x04 */ void (*unk_04)(struct YamamotoObj *);
    /* 0x08 */ float          unk_08;
    /* 0x0C */ float          unk_0C;
    /* 0x10 */ float          unk_10;
    /* 0x14 */ unsigned short unk_14;
    /* 0x16 */ unsigned short unk_16;
    /* 0x18 */ union {
        unsigned short unk_18;
        void (*exec)(Task *, Obj *);
    };
} YamamotoSub; // size = 0x1C

typedef struct YamamotoObj {
    /* 0x00 */ struct YamamotoObj *unk_00;
    /* 0x04 */ char                unk_04[0x1C];
    /* 0x20 */ unsigned short      unk_20;
    /* 0x22 */ char                unk_22[0x3A];
    /* 0x5C */ YamamotoSub         sub;
} YamamotoObj; // size = 0x70

typedef struct YamamotoEntry {
    /* 0x00 */ short         unk_00;
    /* 0x02 */ short         unk_02;
    /* 0x04 */ unsigned char unk_04;
    /* 0x05 */ unsigned char unk_05;
    /* 0x08 */ int           unk_08;
    /* 0x0C */ short         unk_0C;
} YamamotoEntry; // size = 0x10

typedef struct YamamotoFlagEntry {
    /* 0x00 */ unsigned short  flags;
    /* 0x02 */ short           unk_02;
    /* 0x04 */ short           unk_04;
    /* 0x06 */ short           unk_06;
    /* 0x08 */ unsigned short *unk_08;
} YamamotoFlagEntry; // size = 0xC

typedef struct YamamotoPos {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ int   unk_04;
    /* 0x08 */ int   x;
    /* 0x0C */ int   y;
    /* 0x10 */ int   unk_10;
    /* 0x14 */ int   unk_14;
    /* 0x18 */ int   unk_18;
} YamamotoPos; // size = 0x1C

typedef struct YamamotoWork {
    /* 0x00 */ char        unk_00[0x5C];
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
    /* 0x00 */ unsigned short room_id;
    /* 0x02 */ unsigned short x;
    /* 0x04 */ unsigned short y;
    /* 0x06 */ unsigned short z;
    /* 0x08 */ unsigned short player_yaw; // 0x400 = full turn
    /* 0x0A */ unsigned short camera_yaw;
} EntryPoint; // size = 0xC

typedef struct SaveStats {
    /* 0x00 */ int           unk_00;
    /* 0x04 */ int           unk_04;
    /* 0x08 */ int           unk_08;
    /* 0x0C */ int           unk_0c;
    /* 0x10 */ int           unk_10;
    /* 0x14 */ int           unk_14;
    /* 0x18 */ unsigned char unk_18[0x14];
    /* 0x2C */ int           unk_2c;
} SaveStats; // size = 0x30

typedef struct SaveFile {
    /* 0x000 */ unsigned char  flags[100];
    /* 0x064 */ SaveStats      stats;
    /* 0x094 */ int            unk_94;
    /* 0x098 */ int            unk_98;
    /* 0x09C */ unsigned char  unk_9c[8];
    /* 0x0A4 */ int            unk_a4[4];
    /* 0x0B4 */ unsigned char  unk_b4[0x10];
    /* 0x0C4 */ int            unk_c4;
    /* 0x0C8 */ unsigned char  unk_c8[0x34];
    /* 0x0FC */ int            unk_fc;
    /* 0x100 */ unsigned char  unk_100[0x100];
    /* 0x200 */ int            entry_id;
    /* 0x204 */ unsigned short room_id;
    /* 0x206 */ unsigned char  unk_206;
    /* 0x207 */ unsigned char  unk_207;
    /* 0x208 */ short          camera_yaw;
    /* 0x20A */ short          x;
    /* 0x20C */ short          y;
    /* 0x20E */ short          z;
    /* 0x210 */ unsigned short player_yaw;
    /* 0x212 */ unsigned char  unk_212[0x52];
    /* 0x264 */ int            unk_264;
    /* 0x268 */ unsigned char  unk_268[0x34];
    /* 0x29C */ int            unk_29c;
    /* 0x2A0 */ int            unk_2a0;
    /* 0x2A4 */ unsigned char  unk_2a4[0x60];
    /* 0x304 */ int            unk_304;
} SaveFile; // size = 0x308

// ===== sd_main =====
typedef struct SoundSet {
    /* 0x00 */ unsigned char unk_00;
    /* 0x01 */ unsigned char unk_01;
    /* 0x02 */ unsigned char unk_02;
    /* 0x03 */ unsigned char unk_03;
    /* 0x04 */ unsigned char unk_04;
    /* 0x05 */ unsigned char unk_05[3];
    /* 0x08 */ unsigned int *unk_08;
} SoundSet; // size = 0xC

typedef struct SoundWork {
    /* 0x00 */ union {
        unsigned int  unk_00;
        unsigned char unk_00_b[4];
    };
    /* 0x04 */ unsigned char  unk_04;
    /* 0x05 */ unsigned char  unk_05;
    /* 0x06 */ unsigned char  unk_06;
    /* 0x07 */ unsigned char  unk_07;
    /* 0x08 */ unsigned char *unk_08;
    /* 0x0C */ unsigned char  unk_0c;
    /* 0x0D */ unsigned char  unk_0d;
    /* 0x0E */ unsigned char  unk_0e;
    /* 0x0F */ unsigned char  unk_0f;
    /* 0x10 */ unsigned char  unk_10;
    /* 0x11 */ unsigned char  unk_11[3];
    /* 0x14 */ unsigned int   unk_14;
    /* 0x18 */ unsigned short unk_18;
    /* 0x1A */ unsigned short unk_1a;
    /* 0x1C */ unsigned char  unk_1c;
    /* 0x1D */ unsigned char  unk_1d;
    /* 0x1E */ short          unk_1e;
    /* 0x20 */ unsigned char  unk_20;
    /* 0x21 */ unsigned char  unk_21;
    /* 0x22 */ unsigned char  unk_22;
    /* 0x23 */ unsigned char  unk_23;
    /* 0x24 */ unsigned char  unk_24;
    /* 0x25 */ unsigned char  unk_25;
    /* 0x26 */ unsigned char  unk_26[2];
    /* 0x28 */ int            unk_28;
    /* 0x2C */ short          unk_2c;
    /* 0x2E */ short          unk_2e;
    /* 0x30 */ short          unk_30;
    /* 0x32 */ short          unk_32;
    /* 0x34 */ short          unk_34;
    /* 0x36 */ short          unk_36;
    /* 0x38 */ unsigned short unk_38;
    /* 0x3A */ unsigned short unk_3a;
    /* 0x3C */ unsigned char  unk_3c[4];
    /* 0x40 */ short          unk_40;
    /* 0x42 */ short          unk_42;
    /* 0x44 */ short          unk_44;
    /* 0x46 */ unsigned char  unk_46;
    /* 0x47 */ unsigned char  unk_47;
    /* 0x48 */ unsigned char  unk_48;
    /* 0x49 */ unsigned char  unk_49;
    /* 0x4A */ unsigned short unk_4a;
    /* 0x4C */ unsigned short unk_4c;
    /* 0x4E */ unsigned short unk_4e;
    /* 0x50 */ unsigned short unk_50;
    /* 0x52 */ unsigned short unk_52;
    /* 0x54 */ unsigned short unk_54;
    /* 0x56 */ unsigned short unk_56;
    /* 0x58 */ unsigned short unk_58;
    /* 0x5A */ unsigned char  unk_5a;
    /* 0x5B */ unsigned char  unk_5b;
    /* 0x5C */ short          unk_5c;
    /* 0x5E */ unsigned char  unk_5e;
    /* 0x5F */ unsigned char  unk_5f;
    /* 0x60 */ unsigned char *unk_60;
    /* 0x64 */ unsigned char  unk_64;
    /* 0x65 */ unsigned char  unk_65[3];
    /* 0x68 */ unsigned char *unk_68;
    /* 0x6C */ unsigned char *lp3_addr;
    /* 0x70 */ unsigned char  unk_70;
    /* 0x71 */ unsigned char  unk_71[3];
    /* 0x74 */ unsigned char *unk_74;
    /* 0x78 */ unsigned char *unk_78;
    /* 0x7C */ unsigned char  unk_7c;
    /* 0x7D */ unsigned char  unk_7d;
    /* 0x7E */ unsigned char  unk_7e[2];
    /* 0x80 */ int            unk_80;
    /* 0x84 */ int            unk_84;
    /* 0x88 */ unsigned char  unk_88;
    /* 0x89 */ unsigned char  unk_89;
    /* 0x8A */ short          unk_8a;
    /* 0x8C */ unsigned char  unk_8c;
    /* 0x8D */ unsigned char  unk_8d;
    /* 0x8E */ unsigned short unk_8e;
    /* 0x90 */ unsigned short unk_90;
    /* 0x92 */ unsigned char  unk_92;
    /* 0x93 */ unsigned char  unk_93;
    /* 0x94 */ unsigned char  unk_94;
    /* 0x95 */ unsigned char  unk_95;
    /* 0x96 */ unsigned short unk_96;
    /* 0x98 */ unsigned char  unk_98;
    /* 0x99 */ unsigned char  unk_99;
    /* 0x9A */ unsigned short unk_9a;
    /* 0x9C */ unsigned short unk_9c;
    /* 0x9E */ unsigned char  unk_9e;
    /* 0x9F */ unsigned char  unk_9f;
    /* 0xA0 */ unsigned short unk_a0;
    /* 0xA2 */ short          unk_a2;
    /* 0xA4 */ float          unk_a4;
    /* 0xA8 */ unsigned short unk_a8[2];
    /* 0xAC */ unsigned char  unk_ac;
    /* 0xAD */ unsigned char  unk_ad;
    /* 0xAE */ unsigned short unk_ae;
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
    /* 0x02 */ unsigned char unk_2;
    /* 0x03 */ unsigned char unk_3;
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

typedef struct RoomEntry {
    /* 0x00 */ unsigned short camera_yaw_step;
    /* 0x02 */ short          x;
    /* 0x04 */ short          y;
    /* 0x06 */ short          z;
    /* 0x08 */ unsigned short facing;
} RoomEntry; // size = 0xA

// ===== stage_select =====
typedef struct StageEntry {
    /* 0x00 */ short          x;
    /* 0x02 */ short          y;
    /* 0x04 */ short          z;
    /* 0x06 */ unsigned short player_yaw; // 0x400 = full turn
    /* 0x08 */ unsigned short camera_yaw;
} StageEntry; // size = 0xA

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
    /* 0x3B668 */ ObjMoji        mojis[2];
    /* 0x3BB08 */ unsigned char  unknown_data[524288]; // WTF?
    /* 0xBBB08 */ ObjGbg         gbgs[2];
    /* 0xBBB90 */ ObjSolid       solids[192];
    /* 0xC2D90 */ unsigned short unk_c2d90;
    /* 0xC2D92 */ unsigned char  unk_c2d92;
    /* 0xC2D93 */ unsigned char  unk_c2d93;
    /* 0xC2D94 */ ObjSprite      sprites[24];
    /* 0xC3394 */ ObjLayer       layers[12];
    /* 0xC5D04 */ unsigned char  stop_processing_draw_lists;
    /* 0xC5D05 */ unsigned char  unk_c5d05;
    /* 0xC5D06 */ short          unk_c5d06;
    /* 0xC5D08 */ short          unk_c5d08;
    /* 0xC5D0A */ short          unk_c5d0a;
    /* 0xC5D0C */ short          unk_c5d0c;
    /* 0xC5D0E */ unsigned char  unk_c5d0e;
    /* 0xC5D0F */ unsigned char  unk_c5d0f;
    /* 0xC5D10 */ union {
        ObjSpriteFlags unk_c5d10;
        unsigned int   unk_c5d10_word;
    };
    /* 0xC5D14 */ unsigned char   unk_c5d14[4];
    /* 0xC5D18 */ unsigned short  unknown_rgba16_buffer[256];
    /* 0xC5F18 */ unsigned short  unk_c5f18[16];
    /* 0xC5F38 */ unsigned short *unk_c5f38[16];
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
    /* 0xCF7B0 */ int            *unk_cf7b0;
    /* 0xCF7B4 */ unsigned char   unk_cf7b4[88];
    /* 0xCF80C */ unsigned int    tlb_physical_addresses[32];
    /* 0xCF88C */ unsigned char   player_exists;
    /* 0xCF88D */ unsigned char   player_dead;
    /* 0xCF88E */ unsigned short  unk_cf88e;
    /* 0xCF890 */ short           kill_plane_y;
    /* 0xCF892 */ unsigned char   unk_cf892;
    /* 0xCF893 */ unsigned char   unk_cf893;
    /* 0xCF894 */ unsigned int    unk_cf894;
    /* 0xCF898 */ unsigned char   unk_cf898;
    /* 0xCF899 */ unsigned char   unk_cf899;
    /* 0xCF89A */ unsigned char   unk_cf89a;
    /* 0xCF89B */ unsigned char   unk_cf89b;
    /* 0xCF89C */ unsigned int    unk_cf89c;
    /* 0xCF8A0 */ unsigned char   unk_cf8a0;
    /* 0xCF8A1 */ unsigned char   pause_show_map;
    /* 0xCF8A2 */ unsigned char   pause_disabled;
    /* 0xCF8A3 */ unsigned char   unk_cf8a3;
    /* 0xCF8A4 */ unsigned char   unk_cf8a4[12];
    /* 0xCF8B0 */ unsigned int    unk_cf8b0;
    /* 0xCF8B4 */ unsigned char   unk_cf8b4;
    /* 0xCF8B5 */ unsigned char   unk_cf8b5;
    /* 0xCF8B6 */ unsigned char   unk_cf8b6;
    /* 0xCF8B7 */ unsigned char   unk_cf8b7;
    /* 0xCF8B8 */ void           *menu_root_task;
    /* 0xCF8BC */ void           *menu_map_task;
    /* 0xCF8C0 */ void           *menu_solid_pool_task;
    /* 0xCF8C4 */ void           *unk_cf8c4;
    /* 0xCF8C8 */ void           *unk_cf8c8;
    /* 0xCF8CC */ void           *unk_cf8cc;
    /* 0xCF8D0 */ void           *unk_cf8d0;
    /* 0xCF8D4 */ void           *unk_cf8d4;
    /* 0xCF8D8 */ void           *player_manager_task;
    /* 0xCF8DC */ void           *dummy_task;
    /* 0xCF8E0 */ void           *actor_manager_task;
    /* 0xCF8E4 */ void           *skybox_manager_task;
    /* 0xCF8E8 */ void           *room_lighting_task;
    /* 0xCF8EC */ void           *unk_cf8ec;
    /* 0xCF8F0 */ Task           *hud_graphics_task;
    /* 0xCF8F4 */ void           *room_graphics_task;
    /* 0xCF8F8 */ void           *unk_cf8f8;
    /* 0xCF8FC */ unsigned int    unk_cf8fc;
    /* 0xCF900 */ unsigned int    unk_cf900;
    /* 0xCF904 */ unsigned int    unk_cf904;
} Sys; // size = 0xCF908

// ===== vibration_pak =====
typedef struct VibrationPak {
    /* 0x00 */ int active;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int state;
    /* 0x0C */ int retry;
    /* 0x10 */ int status;
    /* 0x14 */ int timer;
    /* 0x18 */ int pattern;
    /* 0x1C */ int bit;
} VibrationPak; // size = 0x20

// ===== window =====
typedef struct WindowStyle {
    /* 0x00 */ void *texture;
    /* 0x04 */ void *palette;
    /* 0x08 */ int   unk_8;
    /* 0x0C */ int   unk_c;
    /* 0x10 */ int   unk_10;
    /* 0x14 */ int   r;
    /* 0x18 */ int   g;
    /* 0x1C */ int   b;
    /* 0x20 */ int   a;
} WindowStyle; // size = 0x24

typedef struct WindowEntry {
    /* 0x00 */ void     *unk_00;
    /* 0x04 */ short     unk_04;
    /* 0x06 */ short     unk_06;
    /* 0x08 */ short     unk_08;
    /* 0x0A */ short     unk_0a;
    /* 0x0C */ short     unk_0c;
    /* 0x0E */ short     unk_0e;
    /* 0x10 */ short     unk_10;
    /* 0x12 */ short     unk_12;
    /* 0x14 */ float     unk_14;
    /* 0x18 */ float     unk_18;
    /* 0x1C */ float     unk_1c;
    /* 0x20 */ short     unk_20;
    /* 0x22 */ short     unk_22;
    /* 0x24 */ int       unk_24;
    /* 0x28 */ long long unk_28;
} WindowEntry; // size = 0x30

typedef struct Window {
    /* 0x000 */ int                unk_000;
    /* 0x004 */ int                unk_004;
    /* 0x008 */ int                unk_008;
    /* 0x00C */ unsigned char      unk_00c[4];
    /* 0x010 */ unsigned long long unk_010;
    /* 0x018 */ unsigned long long unk_018;
    /* 0x020 */ int                unk_020;
    /* 0x024 */ int                unk_024;
    /* 0x028 */ int                unk_028;
    /* 0x02C */ int                unk_02c;
    /* 0x030 */ short              state;
    /* 0x032 */ short              unk_032;
    /* 0x034 */ short              unk_034;
    /* 0x036 */ short              unk_036;
    /* 0x038 */ short              unk_038;
    /* 0x03A */ short              unk_03a;
    /* 0x03C */ short              unk_03c;
    /* 0x03E */ short              unk_03e;
    /* 0x040 */ short              unk_040;
    /* 0x042 */ short              unk_042;
    /* 0x044 */ float              unk_044;
    /* 0x048 */ float              unk_048;
    /* 0x04C */ float              unk_04c;
    /* 0x050 */ int                unk_050;
    /* 0x054 */ int                unk_054;
    /* 0x058 */ int                unk_058;
    /* 0x05C */ int                unk_05c;
    /* 0x060 */ int                unk_060;
    /* 0x064 */ short              unk_064;
    /* 0x066 */ short              unk_066;
    /* 0x068 */ short              unk_068;
    /* 0x06A */ short              unk_06a;
    /* 0x06C */ short              unk_06c;
    /* 0x06E */ short              unk_06e;
    /* 0x070 */ short              unk_070;
    /* 0x072 */ short              unk_072;
    /* 0x074 */ short              unk_074;
    /* 0x076 */ short              unk_076;
    /* 0x078 */ int                unk_078;
    /* 0x07C */ int                unk_07c;
    /* 0x080 */ unsigned char      unk_080[8];
    /* 0x088 */ float              unk_088;
    /* 0x08C */ int                unk_08c;
    /* 0x090 */ int                unk_090;
    /* 0x094 */ unsigned char      unk_094[0x104];
    /* 0x198 */ WindowEntry        entries[1];
} Window;

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
    /* 0x08 */ int       unk_8;
    /* 0x0C */ int       unk_C;
    /* 0x10 */ int       unk_10;
    /* 0x14 */ int       unk_14;
} ColStage; // size = 0x18

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
    /* 0x0014 */ unsigned char unk_14[4];
    /* 0x0018 */ OSThread      thread;
    /* 0x01C8 */ OSMesgQueue   audioFrameMsgQ;
    /* 0x01E0 */ OSMesg        audioFrameMsgBuf[64];
    /* 0x02E0 */ OSMesgQueue   audioReplyMsgQ;
    /* 0x02F8 */ OSMesg        audioReplyMsgBuf[64];
    /* 0x03F8 */ ALGlobals     g;
} AMAudioMgr; // size = 0x448

// ===== file_12 =====
// Entry of the room table D_80231300_5EC7D0, indexed by Sys.intended_room_id.
typedef struct RoomDef {
    /* 0x00 */ unsigned char pad_00[0x18];
    /* 0x18 */ void         *load_files_function;
} RoomDef;

// One spawn point; EnemyMgr.cells holds a list of these per grid cell.
typedef struct EnemySpawn {
    /* 0x00 */ short          x, y, z;
    /* 0x06 */ unsigned short rx, ry, rz;
    /* 0x0C */ int            def; // EnemyDef, still wave relative (func_80014840)
    /* 0x10 */ unsigned char  spawned;
} EnemySpawn; // size = 0x14

typedef struct EnemyDef {
    /* 0x00 */ unsigned short type; // 1-based index into the enemy tables (D_802287C0_5E3C90, ...)
    /* 0x04 */ unsigned int   ebuf[3]; // initial EnemyWork.ebuf[0..2]
} EnemyDef; // size = 0x10

// One generic enemy work slot; the debug strings name them EbufNN with a type suffix ("Ebuf02U", "Ebuf07U").
typedef union EnemyBuf {
    unsigned int   u;
    int            s;
    float          f;
    unsigned short h[2];
    unsigned char  b[4];
} EnemyBuf; // size = 0x4

// Enemy manager at D_8015CC30 in the sys bss (a view over the D_8015CC30, D_8015CCC0 and D_8015CCD8 arrays of
// sys.c; see ENEMY_MGR). The size is not known yet.
typedef struct EnemyMgr {
    /* 0x00 */ unsigned short frame; // counts calls of func_8020DD78_5C9248
    /* 0x04 */ float          cell_x; // cell size
    /* 0x08 */ float          cell_y;
    /* 0x0C */ float          cell_z;
    /* 0x10 */ float          center_x; // world position of the grid center
    /* 0x14 */ float          center_y;
    /* 0x18 */ float          center_z;
    /* 0x1C */ int            size_x; // grid size in cells
    /* 0x20 */ int            size_y;
    /* 0x24 */ int            size_z;
    /* 0x28 */ unsigned char  unk_28[0x10];
    /* 0x38 */ int           *cells; // size_x * size_y * size_z wave-relative EnemySpawn lists
    /* 0x3C */ unsigned int   unk_3c;
    /* 0x40 */ unsigned short wave_no;
    /* 0x44 */ int            radius; // spawn radius in cells
    /* 0x48 */ unsigned char  unk_48[0x44];
    /* 0x8C */ Task          *parents[9]; // parent tasks of the enemy categories (func_80219CA0_5D5170)
    /* 0xB0 */ int            limits[5];  // most enemies of a capped category under one parent
    /* 0xC4 */ unsigned int   unk_c4;
    /* 0xC8 */ unsigned int   unk_c8;
    /* 0xCC */ unsigned int   unk_cc; // no enemy spawns while this is below unk_c4 or unk_c8
    /* 0xD0 */ unsigned char  category; // of the last func_80219CA0_5D5170 call
    /* 0xD1 */ unsigned char  unk_d1[7];
    /* 0xD8 */ unsigned char  next_id;
    /* 0xD9 */ unsigned char  unk_d9[0x2B];
    /* 0x104 */ float         unk_104; // set to 1.0f by the init
    /* 0x108 */ unsigned char unk_108; // enemy id candidate of func_8020DC78_5C9148
    /* 0x109 */ unsigned char unk_109;
    /* 0x10A */ unsigned short unk_10a;
    /* 0x10C */ unsigned char unk_10c[0x20];
    /* 0x12C */ void         *unk_12c; // D_801FC604_5B8514 of the player overlay
    /* 0x130 */ ObjSolid     *player; // D_801FC60C_5B851C of the player overlay
    /* 0x134 */ unsigned char unk_134[0x24];
    /* 0x158 */ int           unk_158;
    /* 0x15C */ int           unk_15c;
} EnemyMgr;

// The work area of every enemy task (Task.work). Enemy specific state lives in the ebuf slots.
typedef struct EnemyWork {
    /* 0x00 */ unsigned short type; // EnemyDef.type
    /* 0x02 */ unsigned short type2;
    /* 0x04 */ unsigned int   flags_04;
    /* 0x08 */ unsigned int   flags_08;
    /* 0x0C */ unsigned int   flags_0c; // bit 0: hit, bit 1: dead (func_80218F30_5D4400 then queues a respawn)
    /* 0x10 */ unsigned char  unk_10;
    /* 0x11 */ unsigned char  unk_11[3];
    /* 0x14 */ EnemySpawn    *spawn;
    /* 0x18 */ unsigned char  id; // from EnemyMgr.next_id
    /* 0x19 */ unsigned char  unk_19;
    /* 0x1A */ unsigned char  unk_1a; // respawn delay
    /* 0x1B */ unsigned char  category; // D_80229FE4_5E54B4; selects the parent task (func_80219CA0_5D5170)
    /* 0x1C */ float          unk_1c[3];
    /* 0x28 */ ObjSolid      *player; // EnemyMgr.player
    /* 0x2C */ unsigned char  unk_2c[5];
    /* 0x31 */ unsigned char  unk_31;
    /* 0x32 */ unsigned char  unk_32[8];
    /* 0x3A */ unsigned short unk_3a;
    /* 0x3C */ unsigned char  unk_3c;
    /* 0x3D */ unsigned char  unk_3d;
    /* 0x3E */ unsigned char  unk_3e;
    /* 0x3F */ unsigned char  unk_3f;
    /* 0x40 */ unsigned char  unk_40[8];
    /* 0x48 */ unsigned short unk_48;
    /* 0x4A */ unsigned char  unk_4a[0x2A];
    /* 0x74 */ EnemyBuf       ebuf[8]; // Ebuf00..Ebuf07; each enemy decides what they hold
} EnemyWork; // size = 0x94 (all of Task.work)

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
    /* 0x00 */ unsigned short unk_00;
    /* 0x02 */ unsigned short unk_02;
    /* 0x04 */ float          unk_04;
    /* 0x08 */ unsigned short unk_08;
    /* 0x0A */ unsigned char  pad_0a[2];
    /* 0x0C */ float          unk_0c;
    /* 0x10 */ float          unk_10;
    /* 0x14 */ float          unk_14;
    /* 0x18 */ unsigned char  unk_18;
    /* 0x19 */ unsigned char  unk_19;
    /* 0x1A */ unsigned short angle;
    /* 0x1C */ float          unk_1c;
    /* 0x20 */ float          speed;
    /* 0x24 */ float          speed_prev;
    /* 0x28 */ float          speed_prev2;
    /* 0x2C */ unsigned char  unk_2c;
    /* 0x2D */ unsigned char  unk_2d;
    /* 0x2E */ unsigned char  unk_2e;
    /* 0x2F */ unsigned char  unk_2f;
    /* 0x30 */ unsigned short unk_30;
    /* 0x32 */ unsigned short unk_32;
    /* 0x34 */ unsigned short unk_34;
    /* 0x36 */ unsigned short unk_36;
    /* 0x38 */ int            unk_38;
    /* 0x3C */ float          unk_3c;
    /* 0x40 */ float          unk_40;
    /* 0x44 */ float          unk_44;
    /* 0x48 */ float          unk_48;
    /* 0x4C */ int            unk_4c;
    /* 0x50 */ float          unk_50;
    /* 0x54 */ float          unk_54;
    /* 0x58 */ unsigned char  unk_58;
    /* 0x59 */ unsigned char  unk_59;
    /* 0x5A */ unsigned char  pad_5a[2];
    /* 0x5C */ float          unk_5c;
    /* 0x60 */ float          unk_60;
    /* 0x64 */ float          unk_64;
    /* 0x68 */ unsigned char  unk_68;
    /* 0x69 */ unsigned char  unk_69;
    /* 0x6A */ unsigned short unk_6a;
    /* 0x6C */ float          unk_6c;
    /* 0x70 */ float          unk_70;
    /* 0x74 */ float          unk_74;
    /* 0x78 */ unsigned char  unk_78;
    /* 0x79 */ unsigned char  pad_79[3];
    /* 0x7C */ void          *unk_7c;
    /* 0x80 */ int            unk_80;
    /* 0x84 */ unsigned char  unk_84;
    /* 0x85 */ unsigned char  unk_85;
    /* 0x86 */ unsigned short unk_86;
    /* 0x88 */ Task         *unk_88;
    /* 0x8C */ int            unk_8c;
    /* 0x90 */ int            unk_90;
    /* 0x94 */ int            unk_94;
    /* 0x98 */ int            unk_98;
    /* 0x9C */ int            unk_9c;
    /* 0xA0 */ int            unk_a0;
    /* 0xA4 */ unsigned short unk_a4;
    /* 0xA6 */ unsigned short unk_a6;
    /* 0xA8 */ unsigned short unk_a8;
    /* 0xAA */ unsigned char  unk_aa;
    /* 0xAB */ unsigned char  pad_ab;
    /* 0xAC */ float          unk_ac;
    /* 0xB0 */ float          unk_b0;
    /* 0xB4 */ Task          *afterline;
    /* 0xB8 */ float          unk_b8[3];
} PlayerPhysics; // size = 0xC4

// Task.work of the player task.
typedef struct PlayerWork {
    /* 0x00 */ PlayerPhysics *physics;
    /* 0x04 */ unsigned char  character;
    /* 0x05 */ unsigned char  unk_05;
    /* 0x06 */ unsigned char  unk_06;
    /* 0x07 */ unsigned char  unk_07;
    /* 0x08 */ Task          *camera;
    /* 0x0C */ float          unk_0c;
    /* 0x10 */ float          unk_10;
    /* 0x14 */ float          unk_14;
    /* 0x18 */ float          unk_18;
    /* 0x1C */ float          unk_1c;
    /* 0x20 */ float          unk_20;
    /* 0x24 */ unsigned short unk_24;
    /* 0x26 */ unsigned short unk_26;
    /* 0x28 */ float          unk_28;
    /* 0x2C */ float          unk_2c;
    /* 0x30 */ float          unk_30;
    /* 0x34 */ unsigned char  controller;
    /* 0x35 */ unsigned char  unk_35;
    /* 0x36 */ unsigned char  unk_36;
    /* 0x37 */ unsigned char  pad_37;
    /* 0x38 */ unsigned short angle;
    /* 0x3A */ unsigned short unk_3a;
    /* 0x3C */ unsigned short unk_3c;
    /* 0x3E */ unsigned short unk_3e;
    /* 0x40 */ int            unk_40;
    /* 0x44 */ int            unk_44;
    /* 0x48 */ float          unk_48;
    /* 0x4C */ float          unk_4c;
    /* 0x50 */ float          unk_50;
    /* 0x54 */ float          unk_54;
    /* 0x58 */ float          unk_58;
    /* 0x5C */ float          unk_5c;
    /* 0x60 */ float          unk_60;
    /* 0x64 */ float          unk_64;
    /* 0x68 */ float          unk_68;
    /* 0x6C */ float          unk_6c;
    /* 0x70 */ unsigned char  state;
    /* 0x71 */ unsigned char  unk_71;
    /* 0x72 */ unsigned short unk_72;
    /* 0x74 */ float          unk_74;
    /* 0x78 */ unsigned char  unk_78;
    /* 0x79 */ unsigned char  pad_79[6];
    /* 0x7F */ unsigned char  unk_7f;
    /* 0x80 */ Task          *fx_mgr;
    /* 0x84 */ int            unk_84;
    /* 0x88 */ float          unk_88;
    /* 0x8C */ float          unk_8c;
    /* 0x90 */ unsigned char  unk_90;
    /* 0x91 */ unsigned char  unk_91;
    /* 0x92 */ unsigned short unk_92;
} PlayerWork; // size = 0x94

// Task.work of the player effects manager.
typedef struct PlayerFxWork {
    /* 0x00 */ Task *player;
} PlayerFxWork;

// ===== 5907F0 =====
// Position of the player model (ObjSolid.AModel without the flag bits), followed by the previous position.
typedef struct PlayerMotion {
    /* 0x00 */ float          x, y, z;
    /* 0x0C */ float          prev_x, prev_y, prev_z;
    /* 0x18 */ unsigned char  pad_18[2];
    /* 0x1A */ unsigned short angle;
} PlayerMotion;

// Task.work of the camera task that follows the player.
typedef struct CameraWork {
    /* 0x00 */ unsigned short unk_00;
    /* 0x02 */ unsigned char  unk_02;
    /* 0x03 */ unsigned char  unk_03;
    /* 0x04 */ unsigned char  pad_04[2];
    /* 0x06 */ unsigned char  unk_06;
    /* 0x07 */ unsigned char  unk_07;
    /* 0x08 */ unsigned short unk_08;
    /* 0x0A */ unsigned short unk_0a;
    /* 0x0C */ unsigned short unk_0c;
    /* 0x0E */ unsigned char  pad_0e[4];
    /* 0x12 */ unsigned short unk_12;
    /* 0x14 */ unsigned char  unk_14;
    /* 0x15 */ unsigned char  unk_15;
    /* 0x16 */ unsigned char  pad_16;
    /* 0x17 */ unsigned char  unk_17;
    /* 0x18 */ unsigned char  pad_18[0x24];
    /* 0x3C */ union {
        unsigned char  unk_3c;
        unsigned short unk_3c_h;
    };
    /* 0x3E */ unsigned char  pad_3e[0x16];
    /* 0x54 */ unsigned short unk_54;
    /* 0x56 */ unsigned short unk_56;
    /* 0x58 */ unsigned char  pad_58[0x1C];
    /* 0x74 */ unsigned char  unk_74;
    /* 0x75 */ unsigned char  unk_75;
    /* 0x76 */ unsigned char  unk_76;
    /* 0x77 */ unsigned char  pad_77[0x15];
    /* 0x8C */ unsigned char  unk_8c;
    /* 0x8D */ unsigned char  pad_8d[7];
} CameraWork; // size = 0x94

// ===== 5AE300 =====
// Colour and exec of one kind of player effect.
typedef struct PlayerEffectTemplate {
    /* 0x00 */ void (*exec)(struct Task *, struct Obj *);
    /* 0x04 */ unsigned char unk_4;
    /* 0x05 */ unsigned char unk_5;
    /* 0x06 */ unsigned char unk_6;
    /* 0x07 */ unsigned char unk_7;
    /* 0x08 */ unsigned char unk_8;
    /* 0x09 */ unsigned char unk_9;
    /* 0x0A */ unsigned char unk_a;
} PlayerEffectTemplate;

typedef struct PlayerEffectAnim {
    /* 0x0 */ signed char state;
    /* 0x2 */ short       counter;
    /* 0x4 */ float       speed;
} PlayerEffectAnim; // size = 0x8

// Frame table of a player effect: entry, index into it and frames left on the entry.
typedef struct PlayerEffectSeq {
    /* 0x0 */ unsigned int  *tbl;
    /* 0x4 */ unsigned char  idx;
    /* 0x5 */ unsigned char  pad_5;
    /* 0x6 */ short          timer;
} PlayerEffectSeq; // size = 0x8

// Task.work of a player effect.
typedef struct PlayerEffectWork {
    /* 0x00 */ union {
        PlayerPhysics *physics;
        Task          *player_task;
    };
    /* 0x04 */ unsigned char  state;
    /* 0x05 */ unsigned char  unk_05;
    /* 0x06 */ unsigned short unk_06;
    /* 0x08 */ unsigned char  kind;
    /* 0x09 */ unsigned char  done;
    /* 0x0A */ unsigned char  unk_0a;
    /* 0x0B */ unsigned char  unk_0b;
    /* 0x0C */ unsigned short unk_0c;
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
    /* 0x34 */ float          growth;
    /* 0x38 */ PlayerEffectSeq seq;
    /* 0x40 */ unsigned char  pad_40[4];
    /* 0x44 */ unsigned short angle;
    /* 0x46 */ unsigned char  pad_46[4];
    /* 0x4A */ unsigned char  count;
    /* 0x4B */ unsigned char  pad_4b;
    /* 0x4C */ unsigned int   model;
    /* 0x50 */ unsigned char  pad_50[0xC];
    /* 0x5C */ unsigned int  dl[6];
    /* 0x74 */ unsigned char  pad_74[0xC];
    /* 0x80 */ PlayerEffectAnim anim;
} PlayerEffectWork;

// ===== 5AFA40 =====
typedef struct AfterlineJoints {
    /* 0x00 */ unsigned int target[6];
} AfterlineJoints; // size = 0x18

// ===== 5B71E0 =====
typedef struct RoomIdleType {
    /* 0x0 */ unsigned short room_id;
    /* 0x2 */ unsigned char  type;
    /* 0x3 */ unsigned char  pad_3;
} RoomIdleType; // size = 0x4

#endif // STRUCTS_H
