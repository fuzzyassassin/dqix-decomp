#include "World/ZoneWarpScript.h"
#include <globaldefs.h>

// USA: func_0201d044
ARM int WarpScript_Opcode_6b(Script::Parameter* params, int numParams)
{
    ZoneFeatures::Opcode6aEntry entry;
    entry.Reset();
    int entryType = (params++)->ToInt();
    entry.maybeType = entryType;
    bool hasAngle = false;
    if (entry.maybeType >= 10)
    {
        entry.maybeType -= 10;
        hasAngle = true;
    }

    Vector3fix tempVector;
    params = params->ToVec3fix(&tempVector);
    entry.unk_8.vec = tempVector;
    params = params->ToVec3fix(&tempVector);
    entry.unk_14.vec = tempVector;

    if (hasAngle)
    {
        fix32_t angle = 4096.0f * (params++)->ToFloat();
        entry.unk_22 = fix32ReduceAngle0To2Pi(angle);
    }
    entry.unk_20 = 4096.0f * (params++)->ToFloat();

    fix32_t halfx = entry.unk_14.vec.x / 2;
    fix32_t halfz = entry.unk_14.vec.z / 2;
    fix32_t xsqu = FIX32_MULTIPLY(halfx, halfx);
    fix32_t zsqu = FIX32_MULTIPLY(halfz, halfz);
    entry.unk_24 = zsqu;
    entry.unk_24 = xsqu + zsqu;

    if (entry.maybeType == 2)
    {
        entry.unk_2c.type2.unk_0 = (params++)->ToInt();
        entry.unk_2c.type2.unk_1 = (params++)->ToInt();
        entry.unk_2c.type2.unk_2_high = (params++)->ToInt();
    }
    else if (entry.maybeType == 3)
    {
        entry.unk_2c.type3.unk_0 = (params++)->ToInt();
    }
    else if (entry.maybeType == 4)
    {
        int arg = (params++)->ToInt();
        entry.unk_2c.type4.unk_1 = -1;
        entry.unk_2c.type4.unk_0 = arg;
        entry.unk_2c.type4.unk_0_high = 0;
        switch (entry.unk_2c.type4.unk_0)
        {
        case 0:
            entry.unk_2c.type4.vector_4.vec3.vec.y = 4096.0f * (params++)->ToFloat();
            entry.unk_2c.type4.vector_4.vec3.vec.z = 4096.0f * (params++)->ToFloat();
            break;
        case 1:
            params = params->ToVec3fix(&tempVector);
            entry.unk_2c.type4.vector_4.vec3.vec = tempVector;
            break;
        case 2:
        case 3:
            params = params->ToVec3fix(&tempVector);
            entry.unk_2c.type4.vector_4.vec3.vec = tempVector;
            break;
        case 4:
        case 5:
        {
            Vector3fix vecB;
            Vector3fix vecA;
            params = params->ToVec3fix(&vecB);
            params = params->ToVec3fix(&vecA);
            MaybeVector4fix difference;
            Vector3fix_Subtract(&vecA, &vecB, &difference.vec3.vec);
            fix32_t distance = Vector3fix_Length(&difference.vec3.vec);
            Vector3fix_Normalize(&difference.vec3.vec, &difference.vec3.vec);
            difference.w = Vector3fix_InnerProduct(&difference.vec3.vec, &vecB);
            Vector3fix vecC  = { 0, 0, 0 };
            if (entry.unk_2c.type4.unk_0 == 4)
            {
                vecC.x = 4096.0f * (params++)->ToFloat();
            }
            vecC.y = 4096.0f * (params++)->ToFloat();
            vecC.z = 4096.0f * (params++)->ToFloat();
            Vector3fix vecD;
            params = params->ToVec3fix(&vecD);
            entry.unk_2c.type4.vector_4.CopyFrom(difference);
            entry.unk_2c.type4.distance_14 = distance;
            entry.unk_2c.type4.vector_18 = vecC;
            entry.unk_2c.type4.vector_24 = vecD;
            break;
        }
        }
        entry.unk_2c.type4.vector_30.x = 0;
        entry.unk_2c.type4.vector_30.y = 0;
        entry.unk_2c.type4.vector_30.z = 0;
        if (numParams > 12)
        {
            params = params->ToVec3fix(&tempVector);
            entry.unk_2c.type4.vector_30 = tempVector;
        }
    }
    else if (entry.maybeType == 5)
    {
        entry.unk_2c.type5.unk_0 = (params++)->ToInt();
        entry.unk_2c.type5.unk_2 = (params++)->ToInt();
        entry.unk_2c.type5.unk_4 = 0;
    }

    ZoneFeatures* instance = data_020fdc20.warp;
    entry.pNext = NULL;
    instance->CreateOpcode6aEntry(entry);
    return 1;
}
