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
    /* 0x1A */ unsigned char  unk_1a;
    /* 0x1B */ unsigned char  unk_1b;
    /* 0x1C */ union {
        int   unk_1c_word;
        short unk_1c;
    };
    /* 0x20 */ union {
        int   unk_20_word;
        short unk_20;
    };
    /* 0x24 */ unsigned char  unk_24;
    /* 0x25 */ unsigned char  unk_25;
    /* 0x26 */ unsigned char  unk_26;
    /* 0x27 */ unsigned char  unk_27;
    /* 0x28 */ unsigned char  unk_28;
    /* 0x29 */ unsigned char  unk_29;
    /* 0x2A */ unsigned char  unk_2a;
    /* 0x2B */ unsigned char  unk_2b;
    /* 0x2C */ float          unk_2c;
    /* 0x30 */ float          unk_30;
    /* 0x34 */ ObjSpritePart *unk_34;
    /* 0x38 */ unsigned int   unk_38;
    /* 0x3C */ unsigned int   unk_3c;
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
    /* 0x80 */ unsigned char    work[20];
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
    /* 0x014 */ int            unk_14;
    /* 0x018 */ int            unk_18;
    /* 0x01C */ short          unk_1c;
    /* 0x01E */ short          unk_1e;
    /* 0x020 */ short          unk_20;
    /* 0x022 */ short          unk_22;
    /* 0x024 */ unsigned char  unk_24;
    /* 0x025 */ unsigned char  unk_25;
    /* 0x026 */ unsigned char  unk_26;
    /* 0x027 */ unsigned char  unk_27;
    /* 0x028 */ int            unk_28;
    /* 0x02C */ unsigned char  unk_2c;
    /* 0x02D */ unsigned char  unk_2d;
    /* 0x02E */ unsigned char  unk_2e;
    /* 0x02F */ unsigned char  unk_2f;
    /* 0x030 */ unsigned char  unk_30;
    /* 0x031 */ unsigned char  unk_31;
    /* 0x032 */ short          unk_32;
    /* 0x034 */ unsigned short unk_34;
    /* 0x036 */ unsigned short unk_36;
    /* 0x038 */ unsigned short unk_38;
    /* 0x03A */ unsigned short unk_3a;
    /* 0x03C */ short          unk_3c;
    /* 0x03E */ short          unk_3e;
    /* 0x040 */ short          unk_40;
    /* 0x042 */ short          unk_42;
    /* 0x044 */ short          unk_44;
    /* 0x046 */ short          unk_46;
    /* 0x048 */ short          unk_48;
    /* 0x04A */ short          unk_4a;
    /* 0x04C */ unsigned char  unk_4c;
    /* 0x04D */ unsigned char  unk_4d;
    /* 0x04E */ unsigned char  unk_4e;
    /* 0x04F */ unsigned char  unk_4f;
    /* 0x050 */ unsigned char  unk_50;
    /* 0x051 */ unsigned char  unk_51;
    /* 0x052 */ unsigned char  unk_52;
    /* 0x053 */ unsigned char  unk_53;
    /* 0x054 */ unsigned char  unk_54;
    /* 0x055 */ unsigned char  unk_55;
    /* 0x056 */ unsigned char  unk_56;
    /* 0x057 */ unsigned char  unk_57;
    /* 0x058 */ unsigned char  unk_58;
    /* 0x059 */ unsigned char  unk_59;
    /* 0x05A */ unsigned char  unk_5a;
    /* 0x05B */ unsigned char  unk_5b;
    /* 0x05C */ unsigned char  unk_5c;
    /* 0x05D */ unsigned char  unk_5d;
    /* 0x05E */ unsigned char  unk_5e;
    /* 0x05F */ unsigned char  unk_5f;
    /* 0x060 */ unsigned char  unk_60;
    /* 0x061 */ unsigned char  unk_61;
    /* 0x062 */ unsigned char  unk_62;
    /* 0x063 */ unsigned char  unk_63;
    /* 0x064 */ unsigned char  unk_64;
    /* 0x065 */ unsigned char  unk_65;
    /* 0x066 */ unsigned char  unk_66;
    /* 0x067 */ unsigned char  unk_67;
    /* 0x068 */ unsigned char  unk_68;
    /* 0x069 */ unsigned char  unk_69;
    /* 0x06A */ unsigned char  unk_6a;
    /* 0x06B */ unsigned char  unk_6b;
    /* 0x06C */ unsigned char  unk_6c;
    /* 0x06D */ unsigned char  unk_6d;
    /* 0x06E */ unsigned char  unk_6e;
    /* 0x06F */ unsigned char  unk_6f;
    /* 0x070 */ unsigned char  unk_70;
    /* 0x071 */ unsigned char  unk_71;
    /* 0x072 */ unsigned char  unk_72;
    /* 0x073 */ unsigned char  unk_73;
    /* 0x074 */ unsigned char  unk_74;
    /* 0x075 */ unsigned char  unk_75;
    /* 0x076 */ unsigned char  unk_76;
    /* 0x077 */ unsigned char  unk_77;
    /* 0x078 */ unsigned char  unk_78;
    /* 0x079 */ unsigned char  unk_79;
    /* 0x07A */ unsigned char  unk_7a;
    /* 0x07B */ unsigned char  unk_7b;
    /* 0x07C */ unsigned char  unk_7c;
    /* 0x07D */ unsigned char  unk_7d;
    /* 0x07E */ unsigned char  unk_7e;
    /* 0x07F */ unsigned char  unk_7f;
    /* 0x080 */ unsigned char  unk_80;
    /* 0x081 */ unsigned char  unk_81;
    /* 0x082 */ unsigned char  unk_82;
    /* 0x083 */ unsigned char  unk_83;
    /* 0x084 */ unsigned char  unk_84;
    /* 0x085 */ unsigned char  unk_85;
    /* 0x086 */ unsigned char  unk_86;
    /* 0x087 */ unsigned char  unk_87;
    /* 0x088 */ unsigned char  unk_88;
    /* 0x089 */ unsigned char  unk_89;
    /* 0x08A */ unsigned char  unk_8a;
    /* 0x08B */ unsigned char  unk_8b;
    /* 0x08C */ unsigned char  unk_8c;
    /* 0x08D */ unsigned char  unk_8d;
    /* 0x08E */ unsigned char  unk_8e;
    /* 0x08F */ unsigned char  unk_8f;
    /* 0x090 */ unsigned char  unk_90;
    /* 0x091 */ unsigned char  unk_91;
    /* 0x092 */ unsigned char  unk_92;
    /* 0x093 */ unsigned char  unk_93;
    /* 0x094 */ unsigned char  unk_94;
    /* 0x095 */ unsigned char  unk_95;
    /* 0x096 */ unsigned char  unk_96;
    /* 0x097 */ unsigned char  unk_97;
    /* 0x098 */ unsigned char  unk_98;
    /* 0x099 */ unsigned char  unk_99;
    /* 0x09A */ unsigned char  unk_9a;
    /* 0x09B */ unsigned char  unk_9b;
    /* 0x09C */ unsigned char  unk_9c;
    /* 0x09D */ unsigned char  unk_9d;
    /* 0x09E */ unsigned char  unk_9e;
    /* 0x09F */ unsigned char  unk_9f;
    /* 0x0A0 */ unsigned char  unk_a0;
    /* 0x0A1 */ unsigned char  unk_a1;
    /* 0x0A2 */ unsigned char  unk_a2;
    /* 0x0A3 */ unsigned char  unk_a3;
    /* 0x0A4 */ unsigned char  unk_a4;
    /* 0x0A5 */ unsigned char  unk_a5;
    /* 0x0A6 */ unsigned char  unk_a6;
    /* 0x0A7 */ unsigned char  unk_a7;
    /* 0x0A8 */ unsigned char  unk_a8;
    /* 0x0A9 */ unsigned char  unk_a9;
    /* 0x0AA */ unsigned char  unk_aa;
    /* 0x0AB */ unsigned char  unk_ab;
    /* 0x0AC */ unsigned char  unk_ac;
    /* 0x0AD */ unsigned char  unk_ad;
    /* 0x0AE */ unsigned char  unk_ae;
    /* 0x0AF */ unsigned char  unk_af;
    /* 0x0B0 */ unsigned char  unk_b0;
    /* 0x0B1 */ unsigned char  unk_b1;
    /* 0x0B2 */ unsigned char  unk_b2;
    /* 0x0B3 */ unsigned char  unk_b3;
    /* 0x0B4 */ unsigned char  unk_b4;
    /* 0x0B5 */ unsigned char  unk_b5;
    /* 0x0B6 */ unsigned char  unk_b6;
    /* 0x0B7 */ unsigned char  unk_b7;
    /* 0x0B8 */ unsigned char  unk_b8;
    /* 0x0B9 */ unsigned char  unk_b9;
    /* 0x0BA */ unsigned char  unk_ba;
    /* 0x0BB */ unsigned char  unk_bb;
    /* 0x0BC */ unsigned char  unk_bc;
    /* 0x0BD */ unsigned char  unk_bd;
    /* 0x0BE */ unsigned char  unk_be;
    /* 0x0BF */ unsigned char  unk_bf;
    /* 0x0C0 */ unsigned char  unk_c0;
    /* 0x0C1 */ unsigned char  unk_c1;
    /* 0x0C2 */ unsigned char  unk_c2;
    /* 0x0C3 */ unsigned char  unk_c3;
    /* 0x0C4 */ unsigned char  unk_c4;
    /* 0x0C5 */ unsigned char  unk_c5;
    /* 0x0C6 */ unsigned char  unk_c6;
    /* 0x0C7 */ unsigned char  unk_c7;
    /* 0x0C8 */ unsigned char  unk_c8;
    /* 0x0C9 */ unsigned char  unk_c9;
    /* 0x0CA */ unsigned char  unk_ca;
    /* 0x0CB */ unsigned char  unk_cb;
    /* 0x0CC */ unsigned char  unk_cc;
    /* 0x0CD */ unsigned char  unk_cd;
    /* 0x0CE */ unsigned char  unk_ce;
    /* 0x0CF */ unsigned char  unk_cf;
    /* 0x0D0 */ unsigned char  unk_d0;
    /* 0x0D1 */ unsigned char  unk_d1;
    /* 0x0D2 */ unsigned char  unk_d2;
    /* 0x0D3 */ unsigned char  unk_d3;
    /* 0x0D4 */ unsigned char  unk_d4;
    /* 0x0D5 */ unsigned char  unk_d5;
    /* 0x0D6 */ unsigned char  unk_d6;
    /* 0x0D7 */ unsigned char  unk_d7;
    /* 0x0D8 */ unsigned char  unk_d8;
    /* 0x0D9 */ unsigned char  unk_d9;
    /* 0x0DA */ unsigned char  unk_da;
    /* 0x0DB */ unsigned char  unk_db;
    /* 0x0DC */ unsigned char  unk_dc;
    /* 0x0DD */ unsigned char  unk_dd;
    /* 0x0DE */ unsigned char  unk_de;
    /* 0x0DF */ unsigned char  unk_df;
    /* 0x0E0 */ unsigned char  unk_e0;
    /* 0x0E1 */ unsigned char  unk_e1;
    /* 0x0E2 */ unsigned char  unk_e2;
    /* 0x0E3 */ unsigned char  unk_e3;
    /* 0x0E4 */ unsigned char  unk_e4;
    /* 0x0E5 */ unsigned char  unk_e5;
    /* 0x0E6 */ unsigned char  unk_e6;
    /* 0x0E7 */ unsigned char  unk_e7;
    /* 0x0E8 */ unsigned char  unk_e8;
    /* 0x0E9 */ unsigned char  unk_e9;
    /* 0x0EA */ unsigned char  unk_ea;
    /* 0x0EB */ unsigned char  unk_eb;
    /* 0x0EC */ unsigned char  unk_ec;
    /* 0x0ED */ unsigned char  unk_ed;
    /* 0x0EE */ unsigned char  unk_ee;
    /* 0x0EF */ unsigned char  unk_ef;
    /* 0x0F0 */ unsigned char  unk_f0;
    /* 0x0F1 */ unsigned char  unk_f1;
    /* 0x0F2 */ unsigned char  unk_f2;
    /* 0x0F3 */ unsigned char  unk_f3;
    /* 0x0F4 */ unsigned char  unk_f4;
    /* 0x0F5 */ unsigned char  unk_f5;
    /* 0x0F6 */ unsigned char  unk_f6;
    /* 0x0F7 */ unsigned char  unk_f7;
    /* 0x0F8 */ unsigned char  unk_f8;
    /* 0x0F9 */ unsigned char  unk_f9;
    /* 0x0FA */ unsigned char  unk_fa;
    /* 0x0FB */ unsigned char  unk_fb;
    /* 0x0FC */ unsigned char  unk_fc;
    /* 0x0FD */ unsigned char  unk_fd;
    /* 0x0FE */ unsigned char  unk_fe;
    /* 0x0FF */ unsigned char  unk_ff;
    /* 0x100 */ unsigned char  unk_100;
    /* 0x101 */ unsigned char  unk_101;
    /* 0x102 */ unsigned char  unk_102;
    /* 0x103 */ unsigned char  unk_103;
    /* 0x104 */ unsigned char  unk_104;
    /* 0x105 */ unsigned char  unk_105;
    /* 0x106 */ unsigned char  unk_106;
    /* 0x107 */ unsigned char  unk_107;
    /* 0x108 */ unsigned char  unk_108;
    /* 0x109 */ unsigned char  unk_109;
    /* 0x10A */ unsigned char  unk_10a;
    /* 0x10B */ unsigned char  unk_10b;
    /* 0x10C */ unsigned char  unk_10c;
    /* 0x10D */ unsigned char  unk_10d;
    /* 0x10E */ unsigned char  unk_10e;
    /* 0x10F */ unsigned char  unk_10f;
    /* 0x110 */ unsigned char  unk_110;
    /* 0x111 */ unsigned char  unk_111;
    /* 0x112 */ unsigned char  unk_112;
    /* 0x113 */ unsigned char  unk_113;
    /* 0x114 */ unsigned char  unk_114;
    /* 0x115 */ unsigned char  unk_115;
    /* 0x116 */ unsigned char  unk_116;
    /* 0x117 */ unsigned char  unk_117;
    /* 0x118 */ unsigned char  unk_118;
    /* 0x119 */ unsigned char  unk_119;
    /* 0x11A */ unsigned char  unk_11a;
    /* 0x11B */ unsigned char  unk_11b;
    /* 0x11C */ unsigned char  unk_11c;
    /* 0x11D */ unsigned char  unk_11d;
    /* 0x11E */ unsigned char  unk_11e;
    /* 0x11F */ unsigned char  unk_11f;
    /* 0x120 */ unsigned char  unk_120;
    /* 0x121 */ unsigned char  unk_121;
    /* 0x122 */ unsigned char  unk_122;
    /* 0x123 */ unsigned char  unk_123;
    /* 0x124 */ unsigned char  unk_124;
    /* 0x125 */ unsigned char  unk_125;
    /* 0x126 */ unsigned char  unk_126;
    /* 0x127 */ unsigned char  unk_127;
    /* 0x128 */ unsigned char  unk_128;
    /* 0x129 */ unsigned char  unk_129;
    /* 0x12A */ unsigned char  unk_12a;
    /* 0x12B */ unsigned char  unk_12b;
    /* 0x12C */ unsigned char  unk_12c;
    /* 0x12D */ unsigned char  unk_12d;
    /* 0x12E */ unsigned char  unk_12e;
    /* 0x12F */ unsigned char  unk_12f;
    /* 0x130 */ unsigned char  unk_130;
    /* 0x131 */ unsigned char  unk_131;
    /* 0x132 */ unsigned char  unk_132;
    /* 0x133 */ unsigned char  unk_133;
    /* 0x134 */ unsigned char  unk_134;
    /* 0x135 */ unsigned char  unk_135;
    /* 0x136 */ unsigned char  unk_136;
    /* 0x137 */ unsigned char  unk_137;
    /* 0x138 */ unsigned char  unk_138;
    /* 0x139 */ unsigned char  unk_139;
    /* 0x13A */ unsigned char  unk_13a;
    /* 0x13B */ unsigned char  unk_13b;
    /* 0x13C */ unsigned char  unk_13c;
    /* 0x13D */ unsigned char  unk_13d;
    /* 0x13E */ unsigned char  unk_13e;
    /* 0x13F */ unsigned char  unk_13f;
    /* 0x140 */ unsigned char  unk_140;
    /* 0x141 */ unsigned char  unk_141;
    /* 0x142 */ unsigned char  unk_142;
    /* 0x143 */ unsigned char  unk_143;
    /* 0x144 */ unsigned char  unk_144;
    /* 0x145 */ unsigned char  unk_145;
    /* 0x146 */ unsigned char  unk_146;
    /* 0x147 */ unsigned char  unk_147;
    /* 0x148 */ unsigned char  unk_148;
    /* 0x149 */ unsigned char  unk_149;
    /* 0x14A */ unsigned char  unk_14a;
    /* 0x14B */ unsigned char  unk_14b;
    /* 0x14C */ unsigned char  unk_14c;
    /* 0x14D */ unsigned char  unk_14d;
    /* 0x14E */ unsigned char  unk_14e;
    /* 0x14F */ unsigned char  unk_14f;
    /* 0x150 */ unsigned char  unk_150;
    /* 0x151 */ unsigned char  unk_151;
    /* 0x152 */ unsigned char  unk_152;
    /* 0x153 */ unsigned char  unk_153;
    /* 0x154 */ unsigned char  unk_154;
    /* 0x155 */ unsigned char  unk_155;
    /* 0x156 */ unsigned char  unk_156;
    /* 0x157 */ unsigned char  unk_157;
    /* 0x158 */ unsigned char  unk_158;
    /* 0x159 */ unsigned char  unk_159;
    /* 0x15A */ unsigned char  unk_15a;
    /* 0x15B */ unsigned char  unk_15b;
    /* 0x15C */ unsigned char  unk_15c;
    /* 0x15D */ unsigned char  unk_15d;
    /* 0x15E */ unsigned char  unk_15e;
    /* 0x15F */ unsigned char  unk_15f;
    /* 0x160 */ unsigned char  unk_160;
    /* 0x161 */ unsigned char  unk_161;
    /* 0x162 */ unsigned char  unk_162;
    /* 0x163 */ unsigned char  unk_163;
    /* 0x164 */ unsigned char  unk_164;
    /* 0x165 */ unsigned char  unk_165;
    /* 0x166 */ unsigned char  unk_166;
    /* 0x167 */ unsigned char  unk_167;
    /* 0x168 */ unsigned char  unk_168;
    /* 0x169 */ unsigned char  unk_169;
    /* 0x16A */ unsigned char  unk_16a;
    /* 0x16B */ unsigned char  unk_16b;
    /* 0x16C */ unsigned char  unk_16c;
    /* 0x16D */ unsigned char  unk_16d;
    /* 0x16E */ unsigned char  unk_16e;
    /* 0x16F */ unsigned char  unk_16f;
    /* 0x170 */ unsigned char  unk_170;
    /* 0x171 */ unsigned char  unk_171;
    /* 0x172 */ unsigned char  unk_172;
    /* 0x173 */ unsigned char  unk_173;
    /* 0x174 */ unsigned char  unk_174;
    /* 0x175 */ unsigned char  unk_175;
    /* 0x176 */ unsigned char  unk_176;
    /* 0x177 */ unsigned char  unk_177;
    /* 0x178 */ unsigned char  unk_178;
    /* 0x179 */ unsigned char  unk_179;
    /* 0x17A */ unsigned char  unk_17a;
    /* 0x17B */ unsigned char  unk_17b;
    /* 0x17C */ unsigned char  unk_17c;
    /* 0x17D */ unsigned char  unk_17d;
    /* 0x17E */ unsigned char  unk_17e;
    /* 0x17F */ unsigned char  unk_17f;
    /* 0x180 */ unsigned char  unk_180;
    /* 0x181 */ unsigned char  unk_181;
    /* 0x182 */ unsigned char  unk_182;
    /* 0x183 */ unsigned char  unk_183;
    /* 0x184 */ unsigned char  unk_184;
    /* 0x185 */ unsigned char  unk_185;
    /* 0x186 */ unsigned char  unk_186;
    /* 0x187 */ unsigned char  unk_187;
    /* 0x188 */ unsigned char  unk_188;
    /* 0x189 */ unsigned char  unk_189;
    /* 0x18A */ unsigned char  unk_18a;
    /* 0x18B */ unsigned char  unk_18b;
    /* 0x18C */ unsigned char  unk_18c;
    /* 0x18D */ unsigned char  unk_18d;
    /* 0x18E */ unsigned char  unk_18e;
    /* 0x18F */ unsigned char  unk_18f;
    /* 0x190 */ unsigned char  unk_190;
    /* 0x191 */ unsigned char  unk_191;
    /* 0x192 */ unsigned char  unk_192;
    /* 0x193 */ unsigned char  unk_193;
    /* 0x194 */ unsigned char  unk_194;
    /* 0x195 */ unsigned char  unk_195;
    /* 0x196 */ unsigned char  unk_196;
    /* 0x197 */ unsigned char  unk_197;
    /* 0x198 */ unsigned char  unk_198;
    /* 0x199 */ unsigned char  unk_199;
    /* 0x19A */ unsigned char  unk_19a;
    /* 0x19B */ unsigned char  unk_19b;
    /* 0x19C */ unsigned char  unk_19c;
    /* 0x19D */ unsigned char  unk_19d;
    /* 0x19E */ unsigned char  unk_19e;
    /* 0x19F */ unsigned char  unk_19f;
    /* 0x1A0 */ unsigned char  unk_1a0;
    /* 0x1A1 */ unsigned char  unk_1a1;
    /* 0x1A2 */ unsigned char  unk_1a2;
    /* 0x1A3 */ unsigned char  unk_1a3;
    /* 0x1A4 */ unsigned char  unk_1a4;
    /* 0x1A5 */ unsigned char  unk_1a5;
    /* 0x1A6 */ unsigned char  unk_1a6;
    /* 0x1A7 */ unsigned char  unk_1a7;
    /* 0x1A8 */ unsigned char  unk_1a8;
    /* 0x1A9 */ unsigned char  unk_1a9;
    /* 0x1AA */ unsigned char  unk_1aa;
    /* 0x1AB */ unsigned char  unk_1ab;
    /* 0x1AC */ unsigned char  unk_1ac;
    /* 0x1AD */ unsigned char  unk_1ad;
    /* 0x1AE */ unsigned char  unk_1ae;
    /* 0x1AF */ unsigned char  unk_1af;
    /* 0x1B0 */ unsigned char  unk_1b0;
    /* 0x1B1 */ unsigned char  unk_1b1;
    /* 0x1B2 */ unsigned char  unk_1b2;
    /* 0x1B3 */ unsigned char  unk_1b3;
    /* 0x1B4 */ unsigned char  unk_1b4;
    /* 0x1B5 */ unsigned char  unk_1b5;
    /* 0x1B6 */ unsigned char  unk_1b6;
    /* 0x1B7 */ unsigned char  unk_1b7;
    /* 0x1B8 */ unsigned char  unk_1b8;
    /* 0x1B9 */ unsigned char  unk_1b9;
    /* 0x1BA */ unsigned char  unk_1ba;
    /* 0x1BB */ unsigned char  unk_1bb;
    /* 0x1BC */ unsigned char  unk_1bc;
    /* 0x1BD */ unsigned char  unk_1bd;
    /* 0x1BE */ unsigned char  unk_1be;
    /* 0x1BF */ unsigned char  unk_1bf;
    /* 0x1C0 */ unsigned char  unk_1c0;
    /* 0x1C1 */ unsigned char  unk_1c1;
    /* 0x1C2 */ unsigned char  unk_1c2;
    /* 0x1C3 */ unsigned char  unk_1c3;
    /* 0x1C4 */ unsigned char  unk_1c4;
    /* 0x1C5 */ unsigned char  unk_1c5;
    /* 0x1C6 */ unsigned char  unk_1c6;
    /* 0x1C7 */ unsigned char  unk_1c7;
    /* 0x1C8 */ unsigned char  unk_1c8;
    /* 0x1C9 */ unsigned char  unk_1c9;
    /* 0x1CA */ unsigned char  unk_1ca;
    /* 0x1CB */ unsigned char  unk_1cb;
    /* 0x1CC */ unsigned char  unk_1cc;
    /* 0x1CD */ unsigned char  unk_1cd;
    /* 0x1CE */ unsigned char  unk_1ce;
    /* 0x1CF */ unsigned char  unk_1cf;
    /* 0x1D0 */ unsigned char  unk_1d0;
    /* 0x1D1 */ unsigned char  unk_1d1;
    /* 0x1D2 */ unsigned char  unk_1d2;
    /* 0x1D3 */ unsigned char  unk_1d3;
    /* 0x1D4 */ unsigned char  unk_1d4;
    /* 0x1D5 */ unsigned char  unk_1d5;
    /* 0x1D6 */ unsigned char  unk_1d6;
    /* 0x1D7 */ unsigned char  unk_1d7;
    /* 0x1D8 */ unsigned char  unk_1d8;
    /* 0x1D9 */ unsigned char  unk_1d9;
    /* 0x1DA */ unsigned char  unk_1da;
    /* 0x1DB */ unsigned char  unk_1db;
    /* 0x1DC */ unsigned char  unk_1dc;
    /* 0x1DD */ unsigned char  unk_1dd;
    /* 0x1DE */ unsigned char  unk_1de;
    /* 0x1DF */ unsigned char  unk_1df;
    /* 0x1E0 */ unsigned char  unk_1e0;
    /* 0x1E1 */ unsigned char  unk_1e1;
    /* 0x1E2 */ unsigned char  unk_1e2;
    /* 0x1E3 */ unsigned char  unk_1e3;
    /* 0x1E4 */ unsigned char  unk_1e4;
    /* 0x1E5 */ unsigned char  unk_1e5;
    /* 0x1E6 */ unsigned char  unk_1e6;
    /* 0x1E7 */ unsigned char  unk_1e7;
    /* 0x1E8 */ unsigned char  unk_1e8;
    /* 0x1E9 */ unsigned char  unk_1e9;
    /* 0x1EA */ unsigned char  unk_1ea;
    /* 0x1EB */ unsigned char  unk_1eb;
    /* 0x1EC */ unsigned char  unk_1ec;
    /* 0x1ED */ unsigned char  unk_1ed;
    /* 0x1EE */ unsigned char  unk_1ee;
    /* 0x1EF */ unsigned char  unk_1ef;
    /* 0x1F0 */ unsigned char  unk_1f0;
    /* 0x1F1 */ unsigned char  unk_1f1;
    /* 0x1F2 */ unsigned char  unk_1f2;
    /* 0x1F3 */ unsigned char  unk_1f3;
    /* 0x1F4 */ unsigned char  unk_1f4;
    /* 0x1F5 */ unsigned char  unk_1f5;
    /* 0x1F6 */ unsigned char  unk_1f6;
    /* 0x1F7 */ unsigned char  unk_1f7;
    /* 0x1F8 */ unsigned char  unk_1f8;
    /* 0x1F9 */ unsigned char  unk_1f9;
    /* 0x1FA */ unsigned char  unk_1fa;
    /* 0x1FB */ unsigned char  unk_1fb;
    /* 0x1FC */ unsigned char  unk_1fc;
    /* 0x1FD */ unsigned char  unk_1fd;
    /* 0x1FE */ unsigned char  unk_1fe;
    /* 0x1FF */ unsigned char  unk_1ff;
    /* 0x200 */ unsigned char  unk_200;
    /* 0x201 */ unsigned char  unk_201;
    /* 0x202 */ unsigned char  unk_202;
    /* 0x203 */ unsigned char  unk_203;
    /* 0x204 */ unsigned char  unk_204;
    /* 0x205 */ unsigned char  unk_205;
    /* 0x206 */ unsigned char  unk_206;
    /* 0x207 */ unsigned char  unk_207;
    /* 0x208 */ unsigned char  unk_208;
    /* 0x209 */ unsigned char  unk_209;
    /* 0x20A */ unsigned char  unk_20a;
    /* 0x20B */ unsigned char  unk_20b;
    /* 0x20C */ unsigned char  unk_20c;
    /* 0x20D */ unsigned char  unk_20d;
    /* 0x20E */ unsigned char  unk_20e;
    /* 0x20F */ unsigned char  unk_20f;
    /* 0x210 */ unsigned char  unk_210;
    /* 0x211 */ unsigned char  unk_211;
    /* 0x212 */ unsigned char  unk_212;
    /* 0x213 */ unsigned char  unk_213;
    /* 0x214 */ unsigned char  unk_214;
    /* 0x215 */ unsigned char  unk_215;
    /* 0x216 */ unsigned char  unk_216;
    /* 0x217 */ unsigned char  unk_217;
    /* 0x218 */ unsigned char  unk_218;
    /* 0x219 */ unsigned char  unk_219;
    /* 0x21A */ unsigned char  unk_21a;
    /* 0x21B */ unsigned char  unk_21b;
    /* 0x21C */ unsigned char  unk_21c;
    /* 0x21D */ unsigned char  unk_21d;
    /* 0x21E */ unsigned char  unk_21e;
    /* 0x21F */ unsigned char  unk_21f;
    /* 0x220 */ unsigned char  unk_220;
    /* 0x221 */ unsigned char  unk_221;
    /* 0x222 */ unsigned char  unk_222;
    /* 0x223 */ unsigned char  unk_223;
    /* 0x224 */ unsigned char  unk_224;
    /* 0x225 */ unsigned char  unk_225;
    /* 0x226 */ unsigned char  unk_226;
    /* 0x227 */ unsigned char  unk_227;
    /* 0x228 */ unsigned char  unk_228;
    /* 0x229 */ unsigned char  unk_229;
    /* 0x22A */ unsigned char  unk_22a;
    /* 0x22B */ unsigned char  unk_22b;
    /* 0x22C */ unsigned char  unk_22c;
    /* 0x22D */ unsigned char  unk_22d;
    /* 0x22E */ unsigned char  unk_22e;
    /* 0x22F */ unsigned char  unk_22f;
    /* 0x230 */ unsigned char  unk_230;
    /* 0x231 */ unsigned char  unk_231;
    /* 0x232 */ unsigned char  unk_232;
    /* 0x233 */ unsigned char  unk_233;
    /* 0x234 */ unsigned char  unk_234;
    /* 0x235 */ unsigned char  unk_235;
    /* 0x236 */ unsigned char  unk_236;
    /* 0x237 */ unsigned char  unk_237;
    /* 0x238 */ unsigned char  unk_238;
    /* 0x239 */ unsigned char  unk_239;
    /* 0x23A */ unsigned char  unk_23a;
    /* 0x23B */ unsigned char  unk_23b;
    /* 0x23C */ unsigned char  unk_23c;
    /* 0x23D */ unsigned char  unk_23d;
    /* 0x23E */ unsigned char  unk_23e;
    /* 0x23F */ unsigned char  unk_23f;
    /* 0x240 */ unsigned char  unk_240;
    /* 0x241 */ unsigned char  unk_241;
    /* 0x242 */ unsigned char  unk_242;
    /* 0x243 */ unsigned char  unk_243;
    /* 0x244 */ unsigned char  unk_244;
    /* 0x245 */ unsigned char  unk_245;
    /* 0x246 */ unsigned char  unk_246;
    /* 0x247 */ unsigned char  unk_247;
    /* 0x248 */ unsigned char  unk_248;
    /* 0x249 */ unsigned char  unk_249;
    /* 0x24A */ unsigned char  unk_24a;
    /* 0x24B */ unsigned char  unk_24b;
    /* 0x24C */ unsigned char  unk_24c;
    /* 0x24D */ unsigned char  unk_24d;
    /* 0x24E */ unsigned char  unk_24e;
    /* 0x24F */ unsigned char  unk_24f;
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
    /* 0x04 */ struct Task *unk_4;
    /* 0x08 */ void (*exec[3])(struct Task *, struct Obj *);
    /* 0x14 */ void (*prev_exec)(struct Task *, struct Obj *);
    /* 0x18 */ Obj           *obj_head;
    /* 0x1C */ Obj           *obj_tail;
    /* 0x20 */ unsigned short priority;
    /* 0x22 */ unsigned short status;
    /* 0x24 */ unsigned short timer;
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
    /* 0x52 */ unsigned short unk_52;
    /* 0x54 */ unsigned int   unk_54;
    /* 0x58 */ unsigned int   unk_58;
    /* 0x5C */ unsigned char  work[0x94]; // Task-specific data; see the `*_WORK` macros.
} Task;                                   // size = 0xF0

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
    /* 0x1C */ unsigned char  unk_1C[0x42];
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

// ===== yamamoto =====
typedef struct SpriteList {
    /* 0x00 */ short          unk_00;
    /* 0x02 */ short          count;
    /* 0x04 */ short          max;
    /* 0x06 */ short          unk_06;
    /* 0x08 */ ObjSpritePart *parts;
} SpriteList; // size = 0xC

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

// ===== save_file =====
typedef struct EntryPoint {
    /* 0x00 */ unsigned short room_id;
    /* 0x02 */ short          x;
    /* 0x04 */ short          y;
    /* 0x06 */ short          z;
    /* 0x08 */ unsigned short player_yaw; // 0x400 = full turn
    /* 0x0A */ unsigned short camera_yaw;
} EntryPoint; // size = 0xC

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

#endif // STRUCTS_H
