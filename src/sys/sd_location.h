#ifndef SD_LOCATION_H
#define SD_LOCATION_H

#include "common.h"
#include "structs.h"

void  func_8000F240(unsigned short id, AnimeCamera *camera, ObjSolid *obj);
void  func_8000F280(unsigned short id, AnimeCamera *camera, float x, float y, float z);
void  func_8000F3D8(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range);
void  func_8000F420(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range);
void  func_8000F468(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range);
void  func_8000F52C(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range);
void  func_8000F5F8(unsigned short id, AnimeCamera *camera, float x, float y, float z, float range);
void  func_8000F6E8(unsigned short id, AnimeCamera *camera, float x, float y, float z, float range);
int   func_8000FBA8(Task *task);
Task *func_8000FBE0(Task *parent, unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range);
void  func_8000FDD4(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range);
void  func_8000FE1C(unsigned short id, AnimeCamera *camera, float x, float y, float z, float range);

#endif // SD_LOCATION_H
