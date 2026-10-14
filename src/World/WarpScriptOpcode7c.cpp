#include <globaldefs.h>
#include "World/ZoneWarpScript.h"
#include "Graphics/Vector.h"

#if defined(usa)

// USA: func_0201e018
ARM int WarpScript_Opcode_7c(Script::Parameter* params, int numParams)
{
    ZoneFeatures::Opcode7bEntry entry;
    params = params->ToVec3fix(&entry.vector_0.vec);
    params = params->ToVec3fix(&entry.vector_c.vec);
    entry.unk_18 = 4096.0f * (params++)->ToFloat();

    fix32_t mhalfx = -entry.vector_c.vec.x / 2;
    fix32_t mhalfz = -entry.vector_c.vec.z / 2;
    fix32_t phalfx = entry.vector_c.vec.x / 2;
    fix32_t phalfz = entry.vector_c.vec.z / 2;

    Vector3fix vertices[4] = { 0 };

    vertices[0].x = mhalfx;
    vertices[0].z = mhalfz;
    vertices[1].x = mhalfx;
    vertices[1].z = phalfz;
    vertices[2].x = phalfx;
    vertices[2].z = mhalfz;
    vertices[3].x = phalfx;
    vertices[3].z = phalfz;

    Matrix4x3 matrix;
    matrix = RotationMatrixY(entry.unk_18);

    for (int i = 0; i < 4; i++)
        Mat4x3_ApplyToVector(&vertices[i], &matrix, &vertices[i]);

    entry.minX = vertices[0].x;
    entry.minZ = vertices[0].z;
    entry.maxX = vertices[0].x;
    entry.maxZ = vertices[0].z;

    for (int i = 1; i < 4; i++)
    {
        if (entry.minX > vertices[i].x)
            entry.minX = vertices[i].x;
        if (entry.minZ > vertices[i].z)
            entry.minZ = vertices[i].z;
        if (entry.maxX < vertices[i].x)
            entry.maxX = vertices[i].x;
        if (entry.maxZ < vertices[i].z)
            entry.maxZ = vertices[i].z;
    }

    entry.minX += entry.vector_0.vec.x;
    entry.minZ += entry.vector_0.vec.z;
    entry.maxX += entry.vector_0.vec.x;
    entry.maxZ += entry.vector_0.vec.z;
    data_020fdc20.warp->CreateOpcode7bEntry(entry);
    return 1;
}
#endif
