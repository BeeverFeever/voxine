#ifndef vox_INE_MATH_H
#define vox_INE_MATH_H

#include <stdint.h>

typedef union {
    float v[4];
    float x, y;
} vox_fvec2;

typedef union {
    int32_t v[4];
    int32_t x, y;
} vox_ivec2;

typedef union {
    uint32_t v[2];
    uint32_t x, y; 
} vox_uvec2;

typedef union {
    float v[3];
    float x, y, z;
} vox_fvec3;

typedef union {
    int32_t v[3];
    int32_t x, y, z;
} vox_ivec3;

typedef union {
    uint32_t v[3];
    uint32_t x, y, z; 
} vox_uvec3;

typedef union {
    float v[4];
    float x, y, z, w;
} vox_fvec4;

typedef union {
    int32_t v[4];
    int32_t x, y, z, w;
} vox_ivec4;

typedef union {
    uint32_t v[4];
    uint32_t x, y, z, w; 
} vox_uvec4;

typedef union {
    float m[2][2];
} vox_mat2;

typedef union {
    float m[3][3];
} vox_mat3;

typedef union {
    float m[4][4];
} vox_mat4;

#endif // vox_INE_MATH_H
