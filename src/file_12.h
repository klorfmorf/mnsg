#ifndef FILE_12_H
#define FILE_12_H
// Enemy overlay: enemy spawning around the player.

#include "common.h"
#include "structs.h"

extern RoomDef *D_80231300_5EC7D0[];                // by Sys.intended_room_id
extern void (*D_802287C0_5E3C90[])(Task *, Obj *); // enemy exec by EnemyDef.type - 1
extern unsigned short D_802297D6_5E4CA6[];          // enemy task priority by EnemyDef.type
extern unsigned char  D_80229FE4_5E54B4[];          // enemy category by EnemyDef.type - 1

#endif // FILE_12_H
