#pragma once

#include "Resource/Script.h"
#include "World/ZoneFeatures.h"

struct Struct_020fdc20 {
    ZoneFeatures::Opcode6aEntry *currentEntry;
    SafeAllocator *allocator;
    ZoneFeatures *warp;
    // Float accumulators at +0x0c..+0x1c, initialized by __sinit_020e5a74.
    float accumulatedValues[5];
};

extern Struct_020fdc20 data_020fdc20;

void ExecuteZoneWarpScript(const void* data, unsigned int length, ZoneFeatures* features, SafeAllocator* allocator);

bool ProcessExtraOpcode69Params(Script::Parameter *param, int numParams, ZoneFeatures::Opcode68Entry &entry);
int WarpScript_Opcode_69(Script::Parameter *params, int numParams);
int WarpScript_Opcode_72(Script::Parameter *params, int numParams);
int WarpScript_Opcode_67(Script::Parameter *params, int numParams);
